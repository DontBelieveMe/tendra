/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "types.h"
#include "enc_types.h"
#include "bitstream.h"
#include "encode.h"
#include "high.h"
#include "names.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
 *    ENCODE AN EXTENDED VALUE
 *
 *    The extended value n is encoded in b bits on the bitstream p.
 */

void
enc_bits_extn(bitstream *p, int b, long n)
{
    long m = ((1 << b) - 1);
    if (n == 0) fatal_error ("Can't encode 0 as an extended value");
    while (n > m) {
		enc_bits (p, b, (long) 0);
		n -= m;
    }
    enc_bits (p, b, n);
    return;
}


/*
 *    AUXILIARY TDF INTEGER ENCODING ROUTINE
 *
 *    The value n is encoded as a series of octal digits into the
 *    bitstream p.
 */

static void
enc_tdf_int_aux(bitstream *p, long n)
{
    unsigned long m = (unsigned long) n;
    if (m >= 8) enc_tdf_int_aux (p, (long) (m >> 3));
    enc_bits (p, 4, (long) (m & 7));
    return;
}


/*
 *    ENCODE A TDF INTEGER
 *
 *    The value n is encoded as a TDF integer into the bitstream p.
 */

void
enc_tdf_int(bitstream *p, long n)
{
    unsigned long m = (unsigned long) n;
    if (m >= 8) enc_tdf_int_aux (p, (long) (m >> 3));
    enc_bits (p, 4, (long) ((m & 7) | 8));
    return;
}


/*
 *    ENCODE AN ALIGNED STRING
 *
 *    The string s is encoded as an aligned string into the bitstream p.
 *    n is either the length of s, or -1, indicating that strlen should
 *    be used to find the length.
 */

void
enc_aligned_string(bitstream *p, char *s,
				   long n)
{
    long i;
    if (n == -1) n = (long) strlen (s);
    enc_tdf_int (p, (long) 8);
    enc_tdf_int (p, n);
    align_bitstream (p);
    for (i = 0 ; i < n ; i++) {
		long c = (long) s [i];
		enc_bits (p, 8, c);
    }
    return;
}


/*
 *    ENCODE AN EXTERNAL NAME
 *
 *    The external name of the construct p is encoded into the bitstream b.
 */

void
enc_external(bitstream *b, construct *p)
{
    node *e = p->ename;
    enc_tdf_int (b, p->encoding);
    if (e->cons->encoding) {
		node *q = e->son;
		if (q->cons->sortnum == SORT_tdfstring) {
			node *r = q->bro;
			if (r == null) {
				enc_external_bits (b, ENC_string_extern);
				align_bitstream (b);
				enc_aligned_string (b, q->cons->name, q->cons->encoding);
			} else {
				enc_external_bits (b, ENC_chain_extern);
				align_bitstream (b);
				enc_aligned_string (b, q->cons->name, q->cons->encoding);
				enc_node (b, r);
			}
		} else {
			enc_external_bits (b, ENC_unique_extern);
			align_bitstream (b);
			enc_tdf_int (b, q->cons->encoding);
			for (q = e->son->son ; q ; q = q->bro) {
				enc_aligned_string (b, q->cons->name, q->cons->encoding);
			}
		}
    } else {
		enc_external_bits (b, ENC_string_extern);
		align_bitstream (b);
		enc_aligned_string (b, p->name, (long) -1);
    }
    return;
}


/*
 *    FIND THE VALUE OF A STRING OF OCTAL DIGITS
 *
 *    The value of the node p, which represents a number, is returned.
 */

static long
octval(node *p)
{
    long n = (long) octal_to_ulong (p->bro->cons->name);
    if (p->cons->encoding) n = -n;
    return (n);
}


/*
 *    ENCODE A NODE
 *
 *    The node p is encoded into the bitstream b.
 */

void
enc_node(bitstream *b, node *p)
{
    while (p) {
		construct *q = p->cons;
		switch (q->sortnum) {
			
	    case SORT_tdfbool : {
			/* Encode a bit */
			enc_bits (b, 1, q->encoding);
			break;
	    }
			
	    case SORT_bytestream : {
			/* Encode a bytestream */
			bitstream *c = new_bitstream ();
			enc_node (c, p->son);
			enc_tdf_int (b, bitstream_length (c));
			join_bitstreams (b, c);
			break;
	    }
			
	    case SORT_completion : {
			/* Encode a completion */
			if (p->son) enc_node (b, p->son);
			break;
	    }
			
	    case SORT_small_tdfint : {
			/* Encode a small integer */
			enc_tdf_int (b, q->encoding);
			break;
	    }
			
	    case SORT_tdfint : {
			/* Encode a number */
			char *num = q->name;
			while (*num) {
				long d = (long) (*num - '0');
				num++;
				if (*num == 0) d |= 8;
				enc_bits (b, 4, d);
			}
			break;
	    }
			
	    case SORT_option : {
			/* Encode an optional argument */
			if (p->son) {
				enc_bits (b, 1, (long) 1);
				enc_node (b, p->son);
			} else {
				enc_bits (b, 1, (long) 0);
			}
			break;
	    }
			
	    case SORT_repeat : {
			/* Encode a repeated argument */
			enc_list_start (b);
			enc_tdf_int (b, q->encoding);
			if (p->son) enc_node (b, p->son);
			break;
	    }
			
	    case SORT_tdfstring : {
			/* Encode a string */
			long i, n = q->encoding;
			if (n == -1) {
				node *r = p->son;
				long m = octval (r);
				if (m < 0) m = -m;
				r = r->bro->bro;
				n = r->cons->encoding;
				r = r->son;
				enc_tdf_int (b, m);
				enc_tdf_int (b, n);
				for (i = 0 ; i < n ; i++) {
					enc_bits (b, (int) m, octval (r));
					r = r->bro->bro;
				}
			} else {
				enc_tdf_int (b, (long) 8);
				enc_tdf_int (b, n);
				for (i = 0 ; i < n ; i++) {
					long c = (long) q->name [i];
					enc_bits (b, 8, c);
				}
			}
			break;
	    }
			
	    case SORT_unknown : {
			/* Encode an unknown bitstream */
			fatal_error ("Can't encode unknown bitstream");
			break;
	    }
			
	    case SORT_al_tag : {
			/* Encode an alignment tag */
			long e = q->encoding;
			enc_al_tag_bits (b, (int) e);
			if (e == ENC_make_al_tag) {
				enc_tdf_int (b, p->son->cons->encoding);
			} else {
				if (p->son) enc_node (b, p->son);
			}
			break;
	    }
			
	    case SORT_label : {
			/* Encode a label */
			long e = q->encoding;
			enc_label_bits (b, (int) e);
			if (e == ENC_make_label) {
				enc_tdf_int (b, p->son->cons->encoding);
			} else {
				if (p->son) enc_node (b, p->son);
			}
			break;
	    }
			
	    case SORT_tag : {
			/* Encode a tag */
			long e = q->encoding;
			enc_tag_bits (b, (int) e);
			if (e == ENC_make_tag) {
				enc_tdf_int (b, p->son->cons->encoding);
			} else {
				if (p->son) enc_node (b, p->son);
			}
			break;
	    }
			
	    case SORT_token : {
			/* Encode a token */
			tok_info *info = get_tok_info (q);
			if (is_high (info->res)) {
				enc_token_bits (b, ENC_token_apply_token);
				enc_token_bits (b, ENC_make_tok);
				enc_tdf_int (b, q->encoding);
				enc_tdf_int (b, (long) 0);
			} else {
				enc_token_bits (b, ENC_make_tok);
				enc_tdf_int (b, q->encoding);
			}
			if (p->son) {
				if (p->son->cons != &token_cons) {
					bitstream *c = new_bitstream ();
					enc_node (c, p->son);
					enc_tdf_int (b, bitstream_length (c));
					join_bitstreams (b, c);
				}
			} else {
				enc_tdf_int (b, (long) 0);
			}
			break;
	    }
			
	    default : {
			/* Encode a simple sort */
			int bits = sort_encoding [ q->sortnum ];
			int extn = sort_extension [ q->sortnum ];
			if (extn) {
				enc_bits_extn (b, bits, q->encoding);
			} else {
				enc_bits (b, bits, q->encoding);
			}
			if (p->son) enc_node (b, p->son);
			break;
	    }
		}
		p = p->bro;
    }
    return;
}


/*
 *    ENCODE A SORT
 */

static void
enc_sort(bitstream *b, sortname s)
{
    if (is_high (s)) {
		int i;
		high_sort *h = high_sorts + high_no (s);
		enc_sort (b, SORT_token);
		enc_sort (b, h->res);
		enc_list_start (b);
		enc_tdf_int (b, (long) h->no_args);
		for (i = 0 ; i < h->no_args ; i++) {
			enc_sort (b, h->args [i]);
		}
    } else {
		enc_sortname_bits (b, s);
    }
    return;
}


/*
 *    ALIGNMENT TAG DEFINITION AUXILIARY ENCODING ROUTINE
 *
 *    The definition of the alignment tag p is encoded into the bitstream p.
 */

void
enc_aldef(bitstream *b, construct *p)
{
    al_tag_info *info = get_al_tag_info (p);
    enc_al_tagdef_bits (b, ENC_make_al_tagdef);
    enc_tdf_int (b, p->encoding);
    enc_node (b, info->def);
    return;
}


/*
 *    TAG DECLARATION AUXILIARY ENCODING ROUTINE
 *
 *    The declaration of the tag p is encoded into the bitstream p.
 */

void
enc_tagdec(bitstream *b, construct *p)
{
    int m = 0;
    tag_info *info = get_tag_info (p);
    switch (info->var) {
	case 0 : m = ENC_make_id_tagdec ; break;
	case 1 : m = ENC_make_var_tagdec ; break;
	case 2 : m = ENC_common_tagdec ; break;
    }
    enc_tagdec_bits (b, m);
    enc_tdf_int (b, p->encoding);
    enc_node (b, info->dec);
    return;
}


/*
 *    TAG DEFINITION AUXILIARY ENCODING ROUTINE
 *
 *    The definition of the tag p is encoded into the bitstream p.  Because
 *    of common_tagdef, there may actually be more than one definition.
 *    The number of definitions is returned.
 */

int
enc_tagdef(bitstream *b, construct *p)
{
    int n = 0;
    int m = 0;
    tag_info *info = get_tag_info (p);
    node *d = info->def;
    switch (info->var) {
	case 0 : m = ENC_make_id_tagdef ; break;
	case 1 : m = ENC_make_var_tagdef ; break;
	case 2 : m = ENC_common_tagdef ; break;
    }
    while (d) {
		/* Can have multiple definitions */
		enc_tagdef_bits (b, m);
		enc_tdf_int (b, p->encoding);
		enc_node (b, d->son);
		d = d->bro;
		n++;
    }
    return (n);
}


/*
 *    WORK OUT THE NUMBER OF FORMAL ARGUMENTS GIVEN A STRING
 */

static long
no_formals(char *args)
{
    long n = 0;
    while (*args) {
		args = find_sortname (args, (sortname *) null);
		args++;
		n = n + 1;
    }
    return (n);
}


/*
 *    TOKEN DECLARATION AUXILIARY ENCODING ROUTINE
 *
 *    The declaration of the token p is encoded into the bitstream p.
 */

void
enc_tokdec(bitstream *b, construct *p)
{
    tok_info *info = get_tok_info (p);
    enc_tokdec_bits (b, ENC_make_tokdec);
    enc_tdf_int (b, p->encoding);
	
    /* Deal with signature */
    if (info->sig == null) {
		enc_bits (b, 1, (long) 0);
    } else {
		enc_node (b, info->sig);
    }
	
    /* Encode token sort */
    enc_sort (b, SORT_token);
	
    /* Encode the token result sort */
    enc_sort (b, info->res);
	
    /* Encode the token argument sorts */
    enc_list_start (b);
    if (info->args) {
		char *q = info->args;
		enc_tdf_int (b, no_formals (q));
		while (*q) {
			sortname s;
			q = find_sortname (q, &s);
			q++;
			enc_sort (b, s);
		}
    } else {
		enc_tdf_int (b, (long) 0);
    }
    return;
}


/*
 *    TOKEN DEFINITION AUXILIARY ENCODING ROUTINE
 *
 *    The definition of the token p is encoded into the bitstream p.
 */

void
enc_tokdef(bitstream *b, construct *p)
{
    bitstream *c = new_bitstream ();
    tok_info *info = get_tok_info (p);
    enc_tokdef_bits (b, ENC_make_tokdef);
    enc_tdf_int (b, p->encoding);
	
    /* Deal with signature */
    if (info->sig == null) {
		enc_bits (b, 1, (long) 0);
    } else {
		enc_node (b, info->sig);
    }
	
    /* Encode token definition type */
    enc_token_defn_bits (c, ENC_token_definition);
	
    /* Encode the token result sort */
    enc_sort (c, info->res);
	
    /* Encode the token arguments */
    enc_list_start (c);
    if (info->args) {
		construct **q = info->pars;
		enc_tdf_int (c, no_formals (info->args));
		while (*q) {
			tok_info *qinfo = get_tok_info (*q);
			enc_sort (c, qinfo->res);
			enc_tdf_int (c, (*q)->encoding);
			q++;
		}
    } else {
		enc_tdf_int (c, (long) 0);
    }
	
    /* Encode the token definition */
    enc_node (c, info->def);
    enc_tdf_int (b, bitstream_length (c));
    join_bitstreams (b, c);
    return;
}
