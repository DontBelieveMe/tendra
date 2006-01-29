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
#include "producer.h"

#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

#include "version.h"
#include "system.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "basetype.h"
#include "bits.h"
#include "buffer.h"
#include "char.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "convert.h"
#include "decode.h"
#include "derive.h"
#include "dump.h"
#include "encode.h"
#include "exception.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "inttype.h"
#include "lex.h"
#include "literal.h"
#include "load.h"
#include "merge.h"
#include "namespace.h"
#include "redeclare.h"
#include "save.h"
#include "symbols.h"
#include "syntax.h"
#include "token.h"
#include "ustring.h"


/*
 *    FORWARD DECLARATIONS
 *
 *    The following forward declarations are required in the spec input
 *    routines.
 */

static EXP load_exp(BITSTREAM *, TYPE);
static TYPE load_type(BITSTREAM *, IDENTIFIER);
static TYPE load_ctype(BITSTREAM *, IDENTIFIER, CLASS_TYPE *);
static IDENTIFIER load_id(BITSTREAM *, NAMESPACE);
static LIST (TYPE) load_type_list(BITSTREAM *);
static TOKEN load_tok(BITSTREAM *, int);
static void load_nspace(BITSTREAM *, NAMESPACE, int);


/*
 *    SPEC INPUT ERROR FLAG
 *
 *    This flag is set to true to indicate a spec input error.
 */

static int spec_error = 0;


/*
 *    SPEC ERROR ROUTINE
 *
 *    This routine is called when a spec input error occurs.  code gives
 *    the reason for the error.
 */

static void
spec_fail(int code)
{
	if (!spec_error) spec_error = code;
	return;
}


/*
 *    SPEC ERROR CODES
 *
 *    The spec error codes are given by the corresponding source line.
 *    This macro gives a convenient shorthand for calling spec_fail.
 */

#ifdef __LINE__
#define SPEC_ERROR()		spec_fail (__LINE__)
#else
#define SPEC_ERROR()		spec_fail (100)
#endif


/*
 *    SIMPLE READING ROUTINES
 *
 *    These macros give the simple reading routines for the enumeration
 *    types etc.  Note that DE_BITS_2 is used for types which occupy more
 *    than 16 bits.
 */

#define load_btype(A)		(BASE_TYPE) DE_BITS_2 ((A), BITS_btype)
#define load_cinfo(A)		(CLASS_INFO) DE_BITS_2 ((A), BITS_cinfo)
#define load_cusage(A)	(CLASS_USAGE) DE_BITS ((A), BITS_cusage)
#define load_cv(A)		(CV_SPEC) DE_BITS ((A), BITS_cv_qual)
#define load_dspec(A)		(DECL_SPEC) DE_BITS_2 ((A), BITS_dspec)
#define load_mqual(A)		(CV_SPEC) DE_BITS ((A), BITS_cv)
#define load_qual(A)		(QUALIFIER) DE_BITS ((A), BITS_qual)


/*
 *    READ A LEXICAL TOKEN NUMBER
 *
 *    This routine reads a lexical token number from the bitstream bs.
 */

static int
load_lex(BITSTREAM *bs)
{
	int t = (int) DE_BITS (bs, BITS_lex);
	if (t > LAST_TOKEN) {
		t = lex_unknown;
		SPEC_ERROR ();
	}
	return (t);
}


/*
 *    READ A LIST OF PREPROCESSING TOKENS
 *
 *    This routine reads a list of preprocessing tokens from the
 *    bitstream bs.
 */

static PPTOKEN *
load_pptoks(BITSTREAM *bs)
{
	/* NOT YET IMPLEMENTED */
	UNUSED (bs);
	return (NULL);
}


/*
 *    READ A LOCATION
 *
 *    This routine reads the current location from the bitstream bs.
 */

static void
load_loc(BITSTREAM *bs)
{
	if (DE_BOOL (bs)) {
		/* Line number has changed */
		crt_loc.line = DE_INT (bs);
		crt_loc.column = 0;
		if (DE_BOOL (bs)) {
			/* File position has changed */
			string file;
			string input;
			ulong date, date2;
			STAT_TYPE *fs = NULL;
			PTR (POSITION) posn;
			PTR (LOCATION) from = NULL_ptr (LOCATION);
			unsigned long off = DE_INT (bs);
			if (DE_BOOL (bs)) {
				STAT_TYPE fstr;
				BUFFER *bf = clear_buffer (&token_buff, NULL);
				de_tdfstring (bs, bf);
				file = ustring_copy (bf->start);
				if (DE_BOOL (bs)) {
					bf = clear_buffer (&token_buff, NULL);
					de_tdfstring (bs, bf);
					input = ustring_copy (bf->start);
				} else {
					input = file;
				}
				date = DE_INT (bs);
				fs = stat_func (strlit (input), &fstr);
				date2 = stat_date (fs);
			} else {
				posn = crt_loc.posn;
				file = DEREF_string (posn_file (posn));
				input = DEREF_string (posn_input (posn));
				date = DEREF_ulong (posn_datestamp (posn));
				date2 = date;
			}
			posn = MAKE_ptr (SIZE_posn);
			MAKE_posn (file, 1, input, input, NULL, off, from, date, posn);
			crt_loc.posn = posn;
			if (date && date2 && date != date2) {
				/* File has changed on disk */
				if (!already_included (input, fs, 4)) {
					report (crt_loc, ERR_cpp_include_date ());
				}
			}
		}
	}
	return;
}


/*
 *    READ AN IDENTIFIER NAME
 *
 *    This routine reads an identifier name from the bitstream bs.  ns gives
 *    the current namespace.
 */

static HASHID
load_hashid(BITSTREAM *bs, NAMESPACE ns)
{
	HASHID nm = NULL_hashid;
	unsigned n = DE_BITS (bs, BITS_hashid);
	if (n) {
		if (n <= ORDER_hashid) {
			unsigned tag = n - 1;
			CT_ASSERT (ORDER_hashid == 7);
			switch (tag) {
			case hashid_name_tag :
			case hashid_ename_tag : {
				string s;
				int ext = 0;
				unsigned long h;
				BUFFER *bf = clear_buffer (&token_buff, NULL);
				de_tdfstring (bs, bf);
				s = bf->start;
				h = hash (s);
				if (tag == hashid_ename_tag) ext = 1;
				nm = lookup_name (s, h, ext, lex_unknown);
				break;
			}
			case hashid_constr_tag : {
				if (IS_nspace_ctype (ns)) {
					IDENTIFIER cid = DEREF_id (nspace_name (ns));
					if (IS_id_class_name (cid)) {
						TYPE t;
						t = DEREF_type (id_class_name_defn (cid));
						nm = lookup_constr (t, cid);
						break;
					}
				}
				SPEC_ERROR ();
				break;
			}
			case hashid_destr_tag : {
				if (IS_nspace_ctype (ns)) {
					IDENTIFIER cid = DEREF_id (nspace_name (ns));
					if (IS_id_class_name (cid)) {
						TYPE t;
						t = DEREF_type (id_class_name_defn (cid));
						nm = lookup_destr (t, cid);
						break;
					}
				}
				SPEC_ERROR ();
				break;
			}
			case hashid_conv_tag : {
				TYPE t = load_type (bs, NULL_id);
				if (!IS_NULL_type (t)) {
					nm = lookup_conv (t);
					break;
				}
				SPEC_ERROR ();
				break;
			}
			case hashid_op_tag : {
				int op = load_lex (bs);
				nm = lookup_op (op);
				break;
			}
			case hashid_anon_tag : {
				nm = lookup_anon ();
				break;
			}
			}
		} else {
			SPEC_ERROR ();
		}
	}
	return (nm);
}


/*
 *    READ A LIST OF IDENTIFIER NAMES
 *
 *    This routine reads a list of identifier names from the bitstream bs.
 */

static LIST (HASHID)
load_hashid_list(BITSTREAM *bs, NAMESPACE ns)
{
	LIST (HASHID) p = NULL_list (HASHID);
	while (DE_BOOL (bs)) {
		HASHID nm = load_hashid (bs, ns);
		if (IS_NULL_hashid (nm)) {
			SPEC_ERROR ();
			break;
		}
		CONS_hashid (nm, p, p);
	}
	p = REVERSE_list (p);
	return (p);
}


/*
 *    IDENTIFIER LOOK-UP TABLE
 *
 *    These variables give the table which gives the mapping between identifier
 *    numbers and identifiers.
 */

static IDENTIFIER *id_table = NULL;
static ulong id_table_size = 0;
static ulong ids_pending = 0;


/*
 *    LOOK UP IDENTIFIER IN TABLE
 *
 *    This routine returns a pointer to the dth element of the table above,
 *    extending it if necessary.
 */

static IDENTIFIER *
id_lookup(ulong d)
{
	ulong m = id_table_size;
	IDENTIFIER *p = id_table;
	if (d >= m) {
		ulong n = d + 100;
		p = xrealloc (p, sizeof(*p) * n);
		while (m < n) {
			p [m] = NULL_id;
			m++;
		}
		id_table_size = n;
		id_table = p;
	}
	return (p + d);
}


/*
 *    READ AN IDENTIFIER NUMBER
 *
 *    This routine reads an identifier number from the bitstream bs.  It is
 *    possible for an identifier to be used before it is declared using
 *    load_id.
 */

static IDENTIFIER
load_use(BITSTREAM *bs, unsigned tag)
{
	IDENTIFIER id;
	IDENTIFIER *pid;
	ulong d = DE_INT (bs);
	if (d == 0) {
		/* Null identifier */
		return (NULL_id);
	}
	pid = id_lookup (d);
	id = *pid;
	if (IS_NULL_id (id)) {
		/* Create dummy identifier */
		HASHID nm = KEYWORD (lex_zzzz);
		MAKE_id_pending (nm, dspec_none, NULL_nspace, crt_loc,
						 tag, NULL_type, id);
		COPY_ulong (id_dump (id), d);
		ids_pending++;
		*pid = id;
	}
	return (id);
}


/*
 *    READ A LIST OF IDENTIFIER NUMBERS
 *
 *    This routine reads a list of identifier numbers from the bitstream bs.
 */

static LIST (IDENTIFIER)
load_use_list(BITSTREAM *bs)
{
	LIST (IDENTIFIER) p = NULL_list (IDENTIFIER);
	while (DE_BOOL (bs)) {
		IDENTIFIER id = load_use (bs, null_tag);
		if (spec_error) break;
		CONS_id (id, p, p);
	}
	p = REVERSE_list (p);
	return (p);
}


/*
 *    READ A LIST OF TOKENS
 *
 *    This routine reads a list of tokens from the bitstream bs.  def is
 *    as in load_tok.
 */

static LIST (TOKEN)
load_tok_list(BITSTREAM *bs, int def)
{
	LIST (TOKEN) p = NULL_list (TOKEN);
	while (DE_BOOL (bs)) {
		TOKEN tok = load_tok (bs, def);
		if (spec_error) break;
		CONS_tok (tok, p, p);
	}
	p = REVERSE_list (p);
	return (p);
}


/*
 *    READ AN INTEGER CONSTANT
 *
 *    This routine reads an integer constant from the bitstream bs.
 */

static NAT
load_nat(BITSTREAM *bs)
{
	NAT m = NULL_nat;
	unsigned n = DE_BITS (bs, BITS_nat);
	if (n == 0) {
		/* Null constants */
		return (m);
	}
	if (n > ORDER_nat) {
		SPEC_ERROR ();
		return (m);
	}
	CT_ASSERT (ORDER_nat == 5);
	switch (n - 1) {
	case nat_small_tag : {
		unsigned long v = DE_INT (bs);
		m = make_nat_value (v);
		break;
	}
	case nat_large_tag : {
		int count = 0;
		LIST (unsigned) p = NULL_list (unsigned);
		while (DE_BOOL (bs)) {
			unsigned v = (unsigned) DE_INT (bs);
			CONS_unsigned (v, p, p);
			if (++count == 10) {
				/* Check for end of file */
				if (tdf_stream_eof (bs)) {
					SPEC_ERROR ();
					break;
				}
				count = 0;
			}
		}
		p = REVERSE_list (p);
		m = make_large_nat (p);
		break;
	}
	case nat_calc_tag : {
		EXP e = load_exp (bs, type_sint);
		if (!IS_NULL_exp (e)) {
			MAKE_nat_calc (e, m);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case nat_neg_tag : {
		m = load_nat (bs);
		if (!IS_NULL_nat (m)) {
			m = negate_nat (m);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case nat_token_tag : {
		IDENTIFIER tok = load_use (bs, null_tag);
		if (!IS_NULL_id (tok)) {
			LIST (TOKEN) args = load_tok_list (bs, 1);
			MAKE_nat_token (tok, args, m);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	}
	return (m);
}


/*
 *    READ AN OFFSET
 *
 *    This routine reads an offset from the bitstream bs.
 */

static OFFSET
load_off(BITSTREAM *bs)
{
	/* NOT YET IMPLEMENTED */
	UNUSED (bs);
	return (NULL_off);
}


/*
 *    READ AN EXPRESSION
 *
 *    This routine reads an expression from the bitstream bs.
 */

static EXP
load_exp(BITSTREAM *bs, TYPE t)
{
	unsigned tag;
	EXP e = NULL_exp;
	unsigned n = DE_BITS (bs, BITS_exp);
	if (n == 0) {
		/* Null expressions */
		return (e);
	}
	if (n > ORDER_exp) {
		SPEC_ERROR ();
		return (e);
	}
	tag = n - 1;
	switch (tag) {
	case exp_int_lit_tag : {
		NAT m = load_nat (bs);
		if (!IS_NULL_nat (m)) {
			unsigned etag = DE_BITS (bs, BITS_exp);
			if (etag < ORDER_exp) {
				MAKE_exp_int_lit (t, m, etag, e);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}
	case exp_token_tag : {
		IDENTIFIER tok = load_use (bs, null_tag);
		if (!IS_NULL_id (tok)) {
			LIST (TOKEN) args = load_tok_list (bs, 1);
			MAKE_exp_token (t, tok, args, e);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	default : {
		/* NOT YET IMPLEMENTED */
		MAKE_exp_value (t, e);
		break;
	}
	}
	return (e);
}


/*
 *    READ A BUILT-IN TYPE
 *
 *    This routine reads a built-in type number from the bitstream bs.
 */

static BUILTIN_TYPE
load_ntype(BITSTREAM *bs)
{
	BUILTIN_TYPE nt = (BUILTIN_TYPE) DE_BITS (bs, BITS_ntype);
	if (nt >= ORDER_ntype) {
		nt = ntype_none;
		SPEC_ERROR ();
	}
	return (nt);
}


/*
 *    READ AN INTEGRAL TYPE
 *
 *    This routine reads a integral type from the bitstream bs.  Note that
 *    the result is returned as a type rather than an integral type.
 */

static TYPE
load_itype(BITSTREAM *bs, CV_SPEC cv, unsigned tag)
{
	TYPE t = NULL_type;
	unsigned n = DE_BITS (bs, BITS_itype);
	if (n == 0) {
		/* Null types */
		return (t);
	}
	if (n > ORDER_itype) {
		SPEC_ERROR ();
		return (t);
	}
	switch (n - 1) {
	case itype_basic_tag : {
		BUILTIN_TYPE nt = load_ntype (bs);
		t = type_builtin [nt];
		break;
	}
	case itype_bitfield_tag : {
		TYPE s = load_type (bs, NULL_id);
		if (!IS_NULL_type (s)) {
			BASE_TYPE bt = load_btype (bs);
			NAT m = load_nat (bs);
			if (!IS_NULL_nat (m)) {
				t = check_bitfield_type (cv, s, bt, m, 1);
				cv = cv_none;
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}
	case itype_promote_tag : {
		TYPE s = load_itype (bs, cv_none, type_integer_tag);
		if (!IS_NULL_type (s)) {
			t = promote_type (s);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case itype_arith_tag : {
		TYPE s = load_itype (bs, cv_none, type_integer_tag);
		if (!IS_NULL_type (s)) {
			TYPE r = load_itype (bs, cv_none, type_integer_tag);
			if (!IS_NULL_type (r)) {
				t = arith_itype (s, r, NULL_exp, NULL_exp);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}
	case itype_literal_tag : {
		NAT m = load_nat (bs);
		if (!IS_NULL_nat (m)) {
			int form = (int) DE_BITS (bs, 2);
			if (form >= 0 && form < BASE_NO) {
				int suff = (int) DE_BITS (bs, 3);
				if (suff >= 0 && suff < SUFFIX_NO) {
					int fit = 0;
					string str = NULL_string;
					t = find_literal_type (m, form, suff, str, &fit);
					break;
				}
			}
		}
		SPEC_ERROR ();
		break;
	}
	case itype_token_tag : {
		IDENTIFIER tok = load_use (bs, null_tag);
		if (!IS_NULL_id (tok)) {
			LIST (TOKEN) args = load_tok_list (bs, 1);
			t = apply_itype_token (tok, args);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	}
	if (!IS_NULL_type (t)) {
		if (TAG_type (t) == tag) {
			if (cv) t = qualify_type (t, cv, 0);
		} else {
			SPEC_ERROR ();
		}
	}
	return (t);
}


/*
 *    READ A FLOATING POINT TYPE
 *
 *    This routine reads a floating point type from the bitstream bs.  Note
 *    that the result is returned as a type rather than a floating point type.
 */

static TYPE
load_ftype(BITSTREAM *bs, CV_SPEC cv)
{
	TYPE t = NULL_type;
	unsigned n = DE_BITS (bs, BITS_ftype);
	if (n == 0) {
		/* Null types */
		return (t);
	}
	if (n > ORDER_ftype) {
		SPEC_ERROR ();
		return (t);
	}
	CT_ASSERT (ORDER_ftype == 4);
	switch (n - 1) {
	case ftype_basic_tag : {
		BUILTIN_TYPE nt = load_ntype (bs);
		t = type_builtin [nt];
		break;
	}
	case ftype_arg_promote_tag : {
		TYPE s = load_ftype (bs, cv_none);
		if (!IS_NULL_type (s)) {
			t = arg_promote_type (s, KILL_err);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case ftype_arith_tag : {
		TYPE s = load_ftype (bs, cv_none);
		if (!IS_NULL_type (s)) {
			TYPE r = load_ftype (bs, cv_none);
			if (!IS_NULL_type (r)) {
				t = arith_ftype (s, r);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}
	case ftype_token_tag : {
		IDENTIFIER tok = load_use (bs, null_tag);
		if (!IS_NULL_id (tok)) {
			LIST (TOKEN) args = load_tok_list (bs, 1);
			t = apply_ftype_token (tok, args);
			break;
		}
		break;
	}
	}
	if (!IS_NULL_type (t)) {
		if (IS_type_floating (t)) {
			if (cv) t = qualify_type (t, cv, 0);
		} else {
			SPEC_ERROR ();
			t = NULL_type;
		}
	}
	return (t);
}


/*
 *    READ A BASE CLASS GRAPH
 *
 *    This routine reads a base class from the bitstream bs.  gu gives the
 *    parent graph and gt gives the top of the graph.
 */

static GRAPH
load_graph(BITSTREAM *bs, GRAPH gu, GRAPH gt)
{
	GRAPH gr;
	LIST (GRAPH) br = NULL_list (GRAPH);
	if (IS_NULL_graph (gu)) {
		/* Top graph node */
		gr = gt;
	} else {
		/* Read graph node */
		CLASS_TYPE ct = NULL_ctype;
		IGNORE load_ctype (bs, NULL_id, &ct);
		if (!IS_NULL_ctype (ct)) {
			DECL_SPEC acc = load_dspec (bs);
			MAKE_graph_basic (ct, acc, gr);
		} else {
			SPEC_ERROR ();
			return (NULL_graph);
		}
	}
	while (DE_BOOL (bs)) {
		/* Read base classes */
		GRAPH gs = load_graph (bs, gr, gt);
		if (IS_NULL_graph (gs)) break;
		CONS_graph (gs, br, br);
	}
	br = REVERSE_list (br);
	COPY_list (graph_tails (gr), br);
	COPY_graph (graph_top (gr), gt);
	COPY_graph (graph_up (gr), gu);
	return (gr);
}


/*
 *    READ A CLASS TYPE
 *
 *    This routine reads a class type from the bitstream bs.  If def is not
 *    null then the full class definition is read, otherwise just a use is
 *    read.
 */

static TYPE
load_ctype(BITSTREAM *bs, IDENTIFIER def, CLASS_TYPE *pct)
{
	TYPE t = NULL_type;
	if (!IS_NULL_id (def)) {
		if (IS_id_class_name (def)) {
			/* Read class definition */
			GRAPH gr;
			CLASS_TYPE ct;
			DECL_SPEC acc;
			NAMESPACE mns;

			/* Read the class information */
			CLASS_INFO ci = load_cinfo (bs);
			CLASS_USAGE cu = load_cusage (bs);

			/* Create the class type */
			acc = (dspec_public | dspec_defn);
			MAKE_graph_basic (NULL_ctype, acc, gr);
			mns = make_namespace (def, nspace_ctype_tag, 20);
			MAKE_ctype_basic (def, ci, cu, mns, gr, 1, NULL_type, ct);
			COPY_ctype (graph_head (gr), ct);
			MAKE_type_compound (cv_none, ct, t);
			COPY_type (id_class_name_defn (def), t);
			COPY_id (type_name (t), def);
			IGNORE lookup_constr (t, def);
			IGNORE lookup_destr (t, def);
			crt_class = ct;
			*pct = ct;

			/* Read the base class graph */
			IGNORE load_graph (bs, NULL_graph, gr);
			end_base_class (ct, 1);

			/* Read template form */
			if (DE_BOOL (bs)) {
				TYPE form = load_type (bs, NULL_id);
				COPY_type (ctype_form (ct), form);
			}

		} else {
			SPEC_ERROR ();
		}

	} else {
		/* Read class name */
		IDENTIFIER cid = load_use (bs, id_class_name_tag);
		if (!IS_NULL_id (cid)) {
			if (IS_id_class_name (cid)) {
				t = DEREF_type (id_class_name_defn (cid));
			}
		}
		if (!IS_NULL_type (t)) {
			while (IS_type_templ (t)) {
				t = DEREF_type (type_templ_defn (t));
			}
			if (IS_type_compound (t)) {
				CLASS_TYPE ct = DEREF_ctype (type_compound_defn (t));
				*pct = ct;
			} else {
				t = NULL_type;
				SPEC_ERROR ();
			}
		} else {
			SPEC_ERROR ();
		}
	}
	return (t);
}


/*
 *    READ AN ENUMERATION TYPE
 *
 *    This routine reads an enumeration type from the bitstream bs.  If def
 *    is not null then the full enumeration definition is read, otherwise
 *    just a use is read.
 */

static TYPE
load_etype(BITSTREAM *bs, IDENTIFIER def, ENUM_TYPE *pet)
{
	TYPE t = NULL_type;
	if (!IS_NULL_id (def)) {
		if (IS_id_enum_name (def)) {
			/* Read enumeration definition */
			ENUM_TYPE et;
			CLASS_INFO ei = load_cinfo (bs);
			TYPE s = load_type (bs, NULL_id);
			if (!IS_NULL_type (s)) {
				MAKE_etype_basic (def, ei, s, et);
				if (DE_BOOL (bs)) {
					TYPE form = load_type (bs, NULL_id);
					COPY_type (etype_form (et), form);
				}
				MAKE_type_enumerate (cv_none, et, t);
				COPY_type (id_enum_name_defn (def), t);
				COPY_id (type_name (t), def);
				*pet = et;
			} else {
				SPEC_ERROR ();
			}
		} else {
			SPEC_ERROR ();
		}
	} else {
		/* Read enumeration name */
		IDENTIFIER eid = load_use (bs, id_enum_name_tag);
		if (!IS_NULL_id (eid)) {
			if (IS_id_enum_name (eid)) {
				t = DEREF_type (id_enum_name_defn (eid));
			}
		}
		if (!IS_NULL_type (t) && IS_type_enumerate (t)) {
			ENUM_TYPE et;
			et = DEREF_etype (type_enumerate_defn (t));
			*pet = et;
		} else {
			t = NULL_type;
			SPEC_ERROR ();
		}
	}
	return (t);
}


/*
 *    READ A FUNCTION PARAMETER LIST
 *
 *    This routine reads a list of function or template parameters (as
 *    indicated by tag) from the bitstream bs into the namespace ns.
 */

static LIST (IDENTIFIER)
load_param_list(BITSTREAM *bs, NAMESPACE ns, unsigned tag)
{
	LIST (IDENTIFIER) pids = NULL_list (IDENTIFIER);
	while (DE_BOOL (bs)) {
		HASHID nm;
		MEMBER mem;
		IDENTIFIER pid = load_id (bs, ns);
		if (IS_NULL_id (pid) || TAG_id (pid) != tag) {
			SPEC_ERROR ();
			break;
		}
		nm = DEREF_hashid (id_name (pid));
		mem = search_member (ns, nm, 1);
		COPY_id (member_id (mem), pid);
		CONS_id (pid, pids, pids);
	}
	pids = REVERSE_list (pids);
	return (pids);
}


/*
 *    READ A TYPE
 *
 *    This routine reads a type from the bitstream bs.  def is passed to
 *    load_ctype and load_etype.
 */

static TYPE
load_type(BITSTREAM *bs, IDENTIFIER def)
{
	unsigned n;
	CV_SPEC cv;
	unsigned tag;
	TYPE t = NULL_type;
	if (DE_BOOL (bs)) {
		/* Built-in types */
		BUILTIN_TYPE nt;
		cv = load_cv (bs);
		nt = load_ntype (bs);
		t = type_builtin [nt];
		if (cv) t = qualify_type (t, cv, 0);
		return (t);
	}

	/* Read type independent fields */
	n = DE_BITS (bs, BITS_type);
	if (n == 0) {
		/* Null types */
		return (t);
	}
	if (n > ORDER_type) {
		SPEC_ERROR ();
		return (NULL_type);
	}
	tag = n - 1;
	cv = load_cv (bs);

	/* Read type dependent fields */
	CT_ASSERT (ORDER_type == 18);
	switch (tag) {

	case type_pre_tag : {
		IDENTIFIER tid = load_use (bs, null_tag);
		QUALIFIER qual = load_qual (bs);
		BASE_TYPE bt = load_btype (bs);
		MAKE_type_pre (cv, bt, qual, t);
		COPY_id (type_name (t), tid);
		break;
	}

	case type_integer_tag : {
		t = load_itype (bs, cv, tag);
		if (!IS_NULL_type (t)) {
			if (DE_BOOL (bs)) {
				TYPE s = load_itype (bs, cv_none, tag);
				if (!IS_NULL_type (s)) {
					INT_TYPE it, is;
					it = DEREF_itype (type_integer_rep (t));
					is = DEREF_itype (type_integer_rep (s));
					t = make_itype (it, is);
				}
			}
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_floating_tag : {
		t = load_ftype (bs, cv);
		break;
	}

	case type_top_tag :
	case type_bottom_tag : {
		/* Should not happen */
		MAKE_type_top_etc (tag, cv, t);
		break;
	}

	case type_ptr_tag :
	case type_ref_tag : {
		/* Pointer and reference types */
		TYPE s = load_type (bs, NULL_id);
		if (!IS_NULL_type (s)) {
			MAKE_type_ptr_etc (tag, cv, s, t);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_ptr_mem_tag : {
		/* Pointer to member types */
		CLASS_TYPE cs = NULL_ctype;
		IGNORE load_ctype (bs, NULL_id, &cs);
		if (!IS_NULL_ctype (cs)) {
			TYPE r = load_type (bs, NULL_id);
			if (!IS_NULL_type (r)) {
				MAKE_type_ptr_mem (cv, cs, r, t);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}

	case type_func_tag : {
		/* Function types */
		TYPE r = load_type (bs, NULL_id);
		if (!IS_NULL_type (r)) {
			int ell;
			NAMESPACE pns;
			CV_SPEC mqual;
			LIST (IDENTIFIER) pids;
			CLASS_TYPE cs = NULL_ctype;
			LIST (TYPE) ex = univ_type_set;
			begin_param (NULL_id);
			pns = crt_namespace;
			pids = load_param_list (bs, pns, id_parameter_tag);
			DESTROY_list (pids, SIZE_id);
			ell = (int) DE_BITS (bs, BITS_ellipsis);
			mqual = load_mqual (bs);
			if (DE_BOOL (bs)) {
				/* Read member function type */
				IGNORE load_ctype (bs, NULL_id, &cs);
			}
			if (DE_BOOL (bs)) {
				/* Read exception specifier */
				ex = load_type_list (bs);
			}
			t = make_func_type (r, ell, mqual, ex);
			end_param ();
			if (!IS_NULL_ctype (cs)) {
				member_func_type (cs, id_mem_func_tag, t);
			}
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_array_tag : {
		/* Array types */
		TYPE s = load_type (bs, NULL_id);
		if (!IS_NULL_type (s)) {
			NAT m = load_nat (bs);
			MAKE_type_array (cv, s, m, t);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_bitfield_tag : {
		/* Bitfield types */
		t = load_itype (bs, cv, tag);
		break;
	}

	case type_compound_tag : {
		/* Class types */
		CLASS_TYPE ct = NULL_ctype;
		t = load_ctype (bs, def, &ct);
		if (!IS_NULL_type (t)) {
			if (cv) t = qualify_type (t, cv, 0);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_enumerate_tag : {
		/* Enumeration types */
		ENUM_TYPE et = NULL_etype;
		t = load_etype (bs, def, &et);
		if (!IS_NULL_type (t)) {
			if (cv) t = qualify_type (t, cv, 0);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_token_tag : {
		IDENTIFIER tok = load_use (bs, null_tag);
		if (!IS_NULL_id (tok)) {
			LIST (TOKEN) args = load_tok_list (bs, 1);
			MAKE_type_token (cv, tok, args, t);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case type_templ_tag : {
		TOKEN tok = load_tok (bs, 0);
		if (!IS_NULL_tok (tok) && IS_tok_templ (tok)) {
			TYPE s = load_type (bs, def);
			if (!IS_NULL_type (s)) {
				int fix = DE_BOOL (bs);
				MAKE_type_templ (cv, tok, s, fix, t);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}

	case type_instance_tag : {
		IDENTIFIER tid = load_use (bs, null_tag);
		if (!IS_NULL_id (tid)) {
			IDENTIFIER id = load_use (bs, null_tag);
			if (!IS_NULL_id (id)) {
				DECL_SPEC acc = load_dspec (bs);
				MAKE_type_instance (cv, id, acc, t);
				COPY_id (type_name (t), tid);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}

	case type_dummy_tag : {
		int tok = (int) DE_INT (bs);
		MAKE_type_dummy (cv, tok, t);
		break;
	}

	case type_error_tag : {
		t = type_error;
		if (cv) t = qualify_type (t, cv, 0);
		break;
	}
	}
	return (t);
}


/*
 *    READ A LIST OF TYPES
 *
 *    This routine reads a list of types from the bitstream bs.
 */

static LIST (TYPE)
load_type_list(BITSTREAM *bs)
{
	LIST (TYPE) p = NULL_list (TYPE);
	while (DE_BOOL (bs)) {
		TYPE t = load_type (bs, NULL_id);
		if (spec_error) break;
		CONS_type (t, p, p);
	}
	p = REVERSE_list (p);
	return (p);
}


/*
 *    READ A TOKEN
 *
 *    This routine reads a token from the bitstream bs.  If def is true
 *    then the token value is also read.
 */

static TOKEN
load_tok(BITSTREAM *bs, int def)
{
	unsigned tag;
	TOKEN tok = NULL_tok;
	unsigned n = DE_BITS (bs, BITS_tok);
	if (n == 0) {
		return (tok);
	}
	if (n > ORDER_tok) {
		SPEC_ERROR ();
		return (tok);
	}
	CT_ASSERT (ORDER_tok == 10);
	tag = n - 1;
	switch (tag) {
	case tok_exp_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			EXP e = NULL_exp;
			int c = DE_BOOL (bs);
			if (def) e = load_exp (bs, t);
			MAKE_tok_exp (t, c, e, tok);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case tok_stmt_tag : {
		EXP e = NULL_exp;
		if (def) e = load_exp (bs, type_void);
		MAKE_tok_stmt (e, tok);
		break;
	}
	case tok_nat_tag :
	case tok_snat_tag : {
		NAT m = NULL_nat;
		if (def) m = load_nat (bs);
		MAKE_tok_nat_etc (tag, m, tok);
		break;
	}
	case tok_type_tag : {
		BASE_TYPE kind = load_btype (bs);
		TYPE s = load_type (bs, NULL_id);
		TYPE t = NULL_type;
		if (def) t = load_type (bs, NULL_id);
		MAKE_tok_type (kind, t, tok);
		COPY_type (tok_type_alt (tok), s);
		break;
	}
	case tok_func_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t) && IS_type_func (t)) {
			TOKEN proc = load_tok (bs, 0);
			IDENTIFIER id = NULL_id;
			if (def) id = load_use (bs, null_tag);
			MAKE_tok_func (t, tok);
			COPY_tok (tok_func_proc (tok), proc);
			COPY_id (tok_func_defn (tok), id);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case tok_member_tag : {
		TYPE s = load_type (bs, NULL_id);
		if (!IS_NULL_type (s)) {
			TYPE t = load_type (bs, NULL_id);
			if (!IS_NULL_type (t)) {
				OFFSET off = NULL_off;
				if (def) off = load_off (bs);
				MAKE_tok_member (s, t, off, tok);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}
	case tok_class_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			TYPE s = load_type (bs, NULL_id);
			IDENTIFIER id = NULL_id;
			if (def) id = load_use (bs, null_tag);
			MAKE_tok_class (t, id, tok);
			COPY_type (tok_class_alt (tok), s);
			break;
		}
		SPEC_ERROR ();
		break;
	}
	case tok_proc_tag : {
		TOKEN res;
		NAMESPACE pns;
		int key = lex_identifier;
		LIST (IDENTIFIER) bids;
		LIST (IDENTIFIER) pids;
		begin_param (NULL_id);
		pns = crt_namespace;
		bids = load_param_list (bs, pns, id_token_tag);
		if (DE_BOOL (bs)) {
			pids = bids;
		} else {
			pids = load_use_list (bs);
		}
		end_param ();
		res = load_tok (bs, def);
		if (DE_BOOL (bs)) key = load_lex (bs);
		if (!IS_NULL_tok (res)) {
			MAKE_tok_proc (res, pns, key, tok);
			tok = cont_proc_token (tok, bids, pids);
		} else {
			SPEC_ERROR ();
		}
		break;
	}
	case tok_templ_tag : {
		DECL_SPEC ex = load_dspec (bs);
		if (DE_BOOL (bs)) {
			NAMESPACE pns;
			LIST (TOKEN) dargs;
			LIST (IDENTIFIER) pids;
			pns = make_namespace (NULL_id, nspace_templ_tag, 0);
			pids = load_param_list (bs, pns, id_token_tag);
			set_proc_token (pids);
			dargs = load_tok_list (bs, 1);
			MAKE_tok_templ (ex, pns, tok);
			COPY_list (tok_templ_pids (tok), pids);
			COPY_list (tok_templ_dargs (tok), dargs);
		} else {
			MAKE_tok_templ (ex, NULL_nspace, tok);
		}
		break;
	}
	}
	return (tok);
}


/*
 *    READ AN IDENTIFIER
 *
 *    This routine reads a member of the namespace ns from the bitstream bs.
 */

static IDENTIFIER
load_id(BITSTREAM *bs, NAMESPACE ns)
{
	ulong d;
	HASHID nm;
	unsigned n;
	unsigned tag;
	DECL_SPEC ds;
	IDENTIFIER qid;
	IDENTIFIER *pid;
	IDENTIFIER id = NULL_id;
	IDENTIFIER lid = NULL_id;

	/* Read identifier number */
	d = DE_INT (bs);
	if (d == 0) {
		/* Null identifiers */
		return (id);
	}

	/* Read identifier tag */
	n = DE_BITS (bs, BITS_id);
	if (n == 0) {
		/* Null identifiers */
		return (id);
	}
	if (n > ORDER_id) {
		SPEC_ERROR ();
		return (id);
	}

	/* Check previous look-up */
	pid = id_lookup (d);
	qid = *pid;
	if (!IS_NULL_id (qid)) {
		if (!IS_id_pending (qid)) {
			SPEC_ERROR ();
			qid = NULL_id;
		}
	}

	/* Read identifier independent information */
	nm = load_hashid (bs, ns);
	if (IS_NULL_hashid (nm)) {
		SPEC_ERROR ();
		return (id);
	}
	tag = n - 1;
	ds = load_dspec (bs);
	load_loc (bs);
	if (DE_BOOL (bs)) {
		/* Read alias */
		lid = load_use (bs, tag);
	}

	/* Read identifier dependent information */
	CT_ASSERT (ORDER_id == 30);
	switch (tag) {

	case id_dummy_tag : {
		id = DEREF_id (hashid_id (nm));
		id = underlying_id (id);
		break;
	}

	case id_keyword_tag :
	case id_c99_keyword_tag :
	case id_iso_keyword_tag :
	case id_reserved_tag : {
		int key = load_lex (bs);
		id = make_keyword (nm, key, NULL_id);
		break;
	}

	case id_builtin_tag : {
		TYPE r = load_type (bs, NULL_id);
		if (!IS_NULL_type (r)) {
			LIST (TYPE) p = load_type_list (bs);
			MAKE_id_builtin (nm, ds, ns, crt_loc, r, p, id);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_obj_macro_tag : {
		PPTOKEN *def = load_pptoks (bs);
		MAKE_id_obj_macro (nm, ds, ns, crt_loc, def, id);
		break;
	}

	case id_func_macro_tag : {
		PPTOKEN *def = load_pptoks (bs);
		LIST (HASHID) pars = load_hashid_list (bs, NULL_nspace);
		unsigned npars = LENGTH_list (pars);
		MAKE_id_func_macro (nm, ds, ns, crt_loc, def, pars, npars, 0, id);
		break;
	}

	case id_predicate_tag : {
		/* NOT YET IMPLEMENTED */
		MAKE_id_undef (nm, ds, ns, crt_loc, id);
		break;
	}

	case id_class_name_tag : {
		/* Class names */
		TYPE t = type_error;
		MAKE_id_class_name (nm, ds, ns, crt_loc, t, id);
		if (ds & dspec_implicit) {
			if (!IS_NULL_id (lid) && IS_id_class_name (lid)) {
				t = DEREF_type (id_class_name_defn (lid));
			}
		} else {
			*pid = id;
			t = load_type (bs, id);
		}
		if (type_tag (t) == type_compound_tag) {
			COPY_type (id_class_name_defn (id), t);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_enum_name_tag : {
		/* Enumeration names */
		TYPE t = type_error;
		MAKE_id_enum_name (nm, ds, ns, crt_loc, t, id);
		t = load_type (bs, id);
		if (type_tag (t) == type_enumerate_tag) {
			COPY_type (id_enum_name_defn (id), t);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_class_alias_tag :
	case id_enum_alias_tag :
	case id_type_alias_tag : {
		/* Type aliases */
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			id = make_typedef (ns, nm, t, ds);
			if (TAG_id (id) != tag) SPEC_ERROR ();
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_nspace_name_tag : {
		/* Namespace names */
		NAMESPACE pns = NULL_nspace;
		unsigned ntag = nspace_named_tag;
		if (IS_hashid_anon (nm)) ntag = nspace_unnamed_tag;
		MAKE_id_nspace_name (nm, ds, ns, crt_loc, pns, id);
		pns = make_namespace (id, ntag, 50);
		COPY_nspace (id_nspace_name_defn (id), pns);
		break;
	}

	case id_nspace_alias_tag : {
		/* Namespace aliases */
		IDENTIFIER nid = load_use (bs, id_nspace_name_tag);
		if (!IS_NULL_id (nid)) {
			NAMESPACE pns = find_namespace (nid);
			if (!IS_NULL_nspace (pns)) {
				MAKE_id_nspace_alias (nm, ds, ns, crt_loc, pns, id);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}

	case id_variable_tag :
	case id_parameter_tag :
	case id_stat_member_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			MAKE_id_variable_etc (tag, nm, ds, ns, crt_loc, t, id);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_function_tag :
	case id_mem_func_tag :
	case id_stat_mem_func_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			MAKE_id_function_etc (tag, nm, ds, ns, crt_loc, t,
								  NULL_id, id);
			*pid = id;
			if (DE_BOOL (bs)) {
				/* Read function template form */
				TYPE form = load_type (bs, NULL_id);
				COPY_type (id_function_etc_form (id), form);
			}
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_member_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			MAKE_id_member (nm, ds, ns, crt_loc, t, id);
			break;
		}
		SPEC_ERROR ();
		break;
	}

	case id_enumerator_tag : {
		TYPE t = load_type (bs, NULL_id);
		if (!IS_NULL_type (t)) {
			EXP e = load_exp (bs, t);
			if (!IS_NULL_exp (e)) {
				MAKE_id_enumerator (nm, ds, ns, crt_loc, t, e, id);
				break;
			}
		}
		SPEC_ERROR ();
		break;
	}

	case id_label_tag :
	case id_weak_param_tag : {
		/* NOT YET IMPLEMENTED */
		MAKE_id_undef (nm, ds, ns, crt_loc, id);
		break;
	}

	case id_token_tag : {
		TOKEN tok = load_tok (bs, 0);
		if (!IS_NULL_tok (tok)) {
			MAKE_id_token (nm, ds, ns, crt_loc, tok, NULL_id, id);
			COPY_id (id_token_alt (id), id);
			break;
		}
		break;
	}

	case id_ambig_tag : {
		LIST (IDENTIFIER) ids = load_use_list (bs);
		int over = DE_BOOL (bs);
		MAKE_id_ambig (nm, ds, ns, crt_loc, ids, over, id);
		break;
	}

	case id_undef_tag : {
		MAKE_id_undef (nm, ds, ns, crt_loc, id);
		if (DE_BOOL (bs)) {
			TYPE form = load_type (bs, NULL_id);
			COPY_type (id_undef_form (id), form);
		}
		break;
	}

	case id_pending_tag : {
		/* This shouldn't happen */
		SPEC_ERROR ();
		break;
	}
	}

	/* Set identifier look up */
	if (!IS_NULL_id (id)) {
		if (!IS_NULL_id (lid)) {
			COPY_id (id_alias (id), lid);
		}
		if (!IS_NULL_id (qid)) {
			COPY_id (id_alias (qid), id);
			ids_pending--;
		}
		*pid = id;
	}
	return (id);
}


/*
 *    READ NAMESPACE MEMBERS
 *
 *    This routine reads the members of a class or namespace and the instances
 *    of a template class or template function.
 */

static void
load_members(BITSTREAM *bs, IDENTIFIER id)
{
	switch (TAG_id (id)) {
	case id_class_name_tag : {
		/* Read class members */
		DECL_SPEC ds = DEREF_dspec (id_storage (id));
		if (!(ds & dspec_implicit)) {
			int templ = 0;
			TYPE t = DEREF_type (id_class_name_defn (id));
			while (IS_type_templ (t)) {
				templ = 1;
				t = DEREF_type (type_templ_defn (t));
			}
			if (IS_type_compound (t)) {
				CLASS_TYPE ct = DEREF_ctype (type_compound_defn (t));
				NAMESPACE cns = DEREF_nspace (ctype_member (ct));
				load_nspace (bs, cns, 0);
				if (templ) {
					/* Read template class instances */
					NAMESPACE ns = DEREF_nspace (id_parent (id));
					load_nspace (bs, ns, 1);
				}
			}
		}
		break;
	}
	case id_nspace_name_tag : {
		/* Read namespace members */
		NAMESPACE cns = DEREF_nspace (id_nspace_name_defn (id));
		load_nspace (bs, cns, 0);
		break;
	}
	case id_function_tag :
	case id_mem_func_tag :
	case id_stat_mem_func_tag : {
		TYPE t = DEREF_type (id_function_etc_type (id));
		if (IS_type_templ (t)) {
			/* Read template function instances */
			NAMESPACE ns = DEREF_nspace (id_parent (id));
			load_nspace (bs, ns, 1);
		}
		break;
	}
	}
	return;
}


/*
 *    READ A LIST OF NAMESPACE MEMBERS
 *
 *    This routine reads the members of the namespace ns from the bitstream
 *    bs.  The list is terminated by a null identifier.  The routine is
 *    also used with inst true to read a list of template instances.
 */

static void
load_nspace(BITSTREAM *bs, NAMESPACE ns, int inst)
{
	int v = verbose;
	for (;;) {
		/* Read identifier */
		IDENTIFIER id = load_id (bs, ns);
		if (IS_NULL_id (id) || spec_error) break;
		if (v) commentary (id);

		/* Set namespace member */
		if (!IS_NULL_nspace (ns) && !inst) {
			DECL_SPEC ds = DEREF_dspec (id_storage (id));
			if ((ds & dspec_extern) || IS_nspace_block_etc (ns)) {
				/* External linkage */
				HASHID nm = DEREF_hashid (id_name (id));
				MEMBER mem = search_member (ns, nm, 1);
				IDENTIFIER pid = DEREF_id (member_id (mem));
				if (is_tagged_type (id)) {
					/* Type members */
					COPY_id (member_alt (mem), id);
					if (IS_NULL_id (pid)) {
						COPY_id (member_id (mem), id);
					}
				} else {
					/* Non-type members */
					if (!IS_NULL_id (pid) && IS_id_function_etc (pid)) {
						if (IS_id_function_etc (id)) {
							/* Allow for overloaded functions */
							COPY_id (id_function_etc_over (id), pid);
						}
					}
					COPY_id (member_id (mem), id);
				}
			} else {
				/* Internal linkage */
				LIST (IDENTIFIER) ids;
				ids = DEREF_list (nspace_named_etc_extra (ns));
				CONS_id (id, ids, ids);
				COPY_list (nspace_named_etc_extra (ns), ids);
			}
		}

		/* Check for classes, namespaces and templates */
		load_members (bs, id);
	}
	return;
}


/*
 *    READ A SPEC FILE
 *
 *    This routine reads a spec file from the input file.  It returns zero
 *    for a legal spec file.  The identifiers are initially read into a
 *    dummy namespace which is then merged with the existing namespace.
 */

int
read_spec(void)
{
	/* Read file identifier */
	int e = 0;
	char buff [20];
	const char *msg = NULL;
	NAMESPACE gns = NULL_nspace;
	BITSTREAM *bs = tdf_fstream_createf (input_file, strlit (input_name));

	tdf_de_magic(bs, tdf_spec_magic);
	if (1) {
		unsigned long n1 = DE_INT (bs);
		unsigned long n2 = DE_INT (bs);
		unsigned long n3 = DE_INT (bs);
		DE_ALIGN (bs);
		if (n1 == SPEC_major && n2 <= SPEC_minor) {
			/* Read main file body */
			if (n3 > LANGUAGE_CPP) {
				msg = "bad source language";
				e = 1;
			}
			if (e == 0) {
				int d = do_dump;
				do_dump = 0;
				spec_error = 0;
				gns = make_global_nspace ("<global>", 50);
				load_nspace (bs, gns, 0);
				if (ids_pending) SPEC_ERROR ();
				crt_class = NULL_ctype;
				e = spec_error;
				if (e == 0) {
					DE_ALIGN (bs);
					tdf_stream_expect_eof (bs);
				} else {
					sprintf_v (buff, "code %d", e);
					msg = buff;
				}
				do_dump = d;
			}
		} else {
			msg = "bad version number";
			e = 1;
		}
	} else {
		msg = "bad magic number";
		e = 1;
	}

	/* Check for errors */
	if (msg) fail (ERR_fail_spec_bad (input_name, ustrlit (msg)));
	if (!output_spec) e = 1;
	xfree (id_table);
	id_table_size = 0;
	id_table = NULL;
	spec_error = 0;

	/* Merge read identifiers */
	if (!IS_NULL_nspace (gns)) {
		merge_namespaces (global_namespace, gns);
	}
	return (e);
}
