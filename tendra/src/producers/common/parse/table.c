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
#include <limits.h>
#include "system.h"
#include "c_types.h"
#include "hashid_ops.h"
#include "error.h"
#include "catalog.h"
#include "char.h"
#include "file.h"
#include "inttype.h"
#include "lex.h"
#include "literal.h"
#include "macro.h"
#include "preproc.h"
#include "syntax.h"
#include "table.h"
#include "ustring.h"


/*
 *    PORTABILITY TABLE ENTRIES
 *
 *    This table describes the portability table entries.  The entries need
 *    to be keep in one-to-one correspondence with the PORT_* macros defined
 *    in table.h.
 */

PORT_ENTRY port_entry [] = {
    { "char_bits", 0, 0, btype_none },			/* 0 */
    { "short_bits", 0, 0, btype_none },			/* 1 */
    { "int_bits", 0, 0, btype_none },			/* 2 */
    { "long_bits", 0, 0, btype_none },			/* 3 */
    { "longlong_bits", 0, 0, btype_none },		/* 4 */
    { "max_bits", 1, UINT_MAX, btype_none },		/* 5 */
    { "signed_range", 0, 0, btype_none },		/* 6 */
    { "char_type", 0, 0, btype_none },			/* 7 */
    { "exact_range", 1, 0, btype_none },		/* 8 */
    { "ptr_int", 1, 0, btype_none },			/* 9 */
    { "ptr_fn", 1, 0, btype_none },			/* 10 */
    { "non_prototype_checks", 1, 0, btype_none },	/* 11 */
    { "multibyte", 1, 0, btype_none }			/* 12 */
};


/*
 *    PARSE A PORTABILITY TABLE
 *
 *    This routine parses and processes the portability table.  It returns
 *    the last token read.
 */

static int
parse_table(void)
{
    int t;
    PORT_ENTRY *p = port_entry;
    while (t = read_token (), t == lex_identifier) {
		int i;
		unsigned n = 0;
		HASHID nm = token_hashid;
		BASE_TYPE bt = btype_none;
		string us = DEREF_string (hashid_name_etc_text (nm));
		update_column ();
		
		/* Check through table entries */
		for (i = 0; i < PORT_size; i++) {
			string ut = ustrlit (p [i].name);
			if (ustreq (us, ut)) {
				/* Entry found */
				if (p [i].set == 2) {
					report (crt_loc, ERR_port_entry_redef (ut));
				}
				p [i].set = 2;
				break;
			}
		}
		
		/* Perform appropriate action */
		switch (i) {
			
	    case PORT_char_bits :
	    case PORT_short_bits :
	    case PORT_int_bits :
	    case PORT_long_bits :
	    case PORT_llong_bits :
	    case PORT_max_bits :
	    case PORT_multibyte : {
			/* Deal with integral values */
			unsigned err = 0;
			t = read_token ();
			update_column ();
			if (t != lex_integer_Hlit) return (t);
			us = token_buff.start;
			n = (unsigned) eval_line_digits (us, &err);
			if (err) report (crt_loc, ERR_lex_literal_bad (us));
			break;
	    }
			
	    case PORT_signed_range : {
			/* Deal with range values */
			t = read_token ();
			update_column ();
			if (t != lex_identifier) return (t);
			nm = token_hashid;
			us = DEREF_string (hashid_name_etc_text (nm));
			if (ustrseq (us, "maximum")) {
				bt = (btype_signed | btype_long);
			} else if (ustrseq (us, "symmetric")) {
				bt = btype_signed;
			} else {
				return (t);
			}
			break;
	    }
			
	    case PORT_char_type : {
			/* Deal with sign values */
			t = read_token ();
			update_column ();
			if (t != lex_identifier) return (t);
			nm = token_hashid;
			us = DEREF_string (hashid_name_etc_text (nm));
			if (ustrseq (us, "signed")) {
				bt = btype_signed;
			} else if (ustrseq (us, "unsigned")) {
				bt = btype_unsigned;
			} else if (ustrseq (us, "either")) {
				bt = btype_none;
			} else {
				return (t);
			}
			break;
	    }
			
	    case PORT_ptr_int : {
			/* Deal with type values */
			t = read_token ();
			update_column ();
			if (t != lex_identifier) return (t);
			nm = token_hashid;
			us = DEREF_string (hashid_name_etc_text (nm));
			if (ustrseq (us, "char")) {
				bt = btype_char;
			} else if (ustrseq (us, "short")) {
				bt = btype_short;
			} else if (ustrseq (us, "int")) {
				bt = btype_int;
			} else if (ustrseq (us, "long")) {
				bt = btype_long;
			} else if (ustrseq (us, "none")) {
				bt = btype_none;
			} else {
				return (t);
			}
			break;
	    }
			
	    case PORT_exact_range :
	    case PORT_ptr_fn :
	    case PORT_non_proto : {
			/* Deal with boolean values */
			t = read_token ();
			update_column ();
			if (t != lex_identifier) return (t);
			nm = token_hashid;
			us = DEREF_string (hashid_name_etc_text (nm));
			if (ustrseq (us, "no")) {
				n = 0;
			} else if (ustrseq (us, "yes")) {
				n = 1;
			} else {
				return (t);
			}
			break;
	    }
			
	    default : {
			/* Unknown entry identifier */
			return (t);
	    }
		}
		p [i].value = n;
		p [i].type = bt;
    }
    return (t);
}


/*
 *    READ THE PORTABILITY TABLE
 *
 *    This routine reads and processes the portability table given by nm.
 */

void
read_table(string nm)
{
    int set = 0;
    PORT_ENTRY *p = port_entry;
	
    /* Read table */
    if (nm) {
		int i, t;
		input_name = nm;
		if (!open_input (text_mode)) {
			/* Can't open portability table */
			fail (ERR_fail_port (nm));
		} else {
			/* Read portability table */
			set = 1;
			pragma_number = 1;
			no_preproc_dir = 1;
			crt_buff_no = 0;
			IGNORE init_buffer (crt_buff_no);
			unread_char (char_newline);
			crt_loc.line--;
			t = parse_table ();
			update_column ();
			if (t != lex_eof) {
				/* Parse error in portability table */
				PPTOKEN *r = new_pptok ();
				r->tok = t;
				token_parts (t, r);
				report (crt_loc, ERR_lex_parse (r));
				set = 0;
			} else {
				/* Check for undefined values */
				for (i = 0; i < PORT_size; i++) {
					if (p [i].set == 0) {
						string nt = ustrlit (p [i].name);
						report (crt_loc, ERR_port_entry_undef (nt));
						set = 0;
					}
				}
			}
			no_preproc_dir = 0;
			pragma_number = 0;
			close_input ();
		}
    }
	
    /* Set values from table */
    if (set) {
		unsigned m = p [ PORT_llong_bits ].value;
		unsigned long n;
		BASE_INFO *q = basetype_info;
		set_char_sign (p [ PORT_char_type ].type);
		if (p [ PORT_exact_range ].value == 0) {
			/* Find maximum number of bits in an integer */
			m = p [ PORT_max_bits ].value;
		}
		for (n = 0; n < ORDER_ntype; n++) {
			unsigned exact = p [ PORT_exact_range ].value;
			switch (n) {
			case ntype_char :
			case ntype_schar :
			case ntype_uchar : {
				q [n].min_bits = p [ PORT_char_bits ].value;
				q [n].max_bits = m;
				break;
			}
			case ntype_sshort :
			case ntype_ushort : {
				q [n].min_bits = p [ PORT_short_bits ].value;
				q [n].max_bits = m;
				break;
			}
			case ntype_sint :
			case ntype_uint :
			case ntype_none : {
				q [n].min_bits = p [ PORT_int_bits ].value;
				q [n].max_bits = m;
				break;
			}
			case ntype_slong :
			case ntype_ulong : {
				q [n].min_bits = p [ PORT_long_bits ].value;
				q [n].max_bits = m;
				break;
			}
			case ntype_sllong :
			case ntype_ullong : {
				q [n].min_bits = p [ PORT_llong_bits ].value;
				q [n].max_bits = m;
				break;
			}
			case ntype_ptrdiff_t :
			case ntype_size_t : {
				q [n].min_bits = p [ PORT_int_bits ].value;
				q [n].max_bits = m;
				exact = 0;
				break;
			}
			case ntype_wchar_t :
			case ntype_ellipsis : {
				q [n].min_bits = p [ PORT_char_bits ].value;
				q [n].max_bits = m;
				exact = 0;
				break;
			}
			}
			if (exact) {
				/* Exact integer range known */
				q [n].max_bits = q [n].min_bits;
			}
			if (q [n].sign & btype_signed) {
				/* Set signed type range */
				q [n].sign = p [ PORT_signed_range ].type;
			}
		}
		if (p [ PORT_exact_range ].value) {
			/* Set exact type ranges */
			set_exact_types ();
		}
    }
    return;
}
