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

#include "msgcat.h"

#include "c_types.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "error.h"
#include "destroy.h"
#include "exception.h"
#include "macro.h"


/*
 *    FREE A LOCAL IDENTIFIER
 *
 *    This routine frees the local identifier id.
 */

static void
free_id(IDENTIFIER id, int force)
{
    if (IS_NULL_id (id)) return;
    switch (TAG_id (id)) {
	case id_variable_tag : {
	    DECL_SPEC ds = DEREF_dspec (id_storage (id));
	    if (ds & dspec_auto) {
			EXP e = DEREF_exp (id_variable_init (id));
			EXP d = DEREF_exp (id_variable_term (id));
			if (!IS_NULL_exp (e)) free_exp (e, force);
			if (!IS_NULL_exp (d)) free_exp (d, force);
			COPY_exp (id_variable_init (id), NULL_exp);
			COPY_exp (id_variable_term (id), NULL_exp);
	    }
	    break;
	}
	case id_label_tag : {
	    LIST (VARIABLE) v = DEREF_list (id_label_vars (id));
	    DESTROY_list (v, SIZE_var);
	    COPY_list (id_label_vars (id), NULL_list (VARIABLE));
	    COPY_exp (id_label_stmt (id), NULL_exp);
	    COPY_exp (id_label_gotos (id), NULL_exp);
	    break;
	}
    }
    return;
}


/*
 *    FREE A NAMESPACE
 *
 *    This routine frees the block namespace ns.
 */

void
free_nspace(NAMESPACE ns)
{
    if (!IS_NULL_nspace (ns)) {
		MEMBER mem = DEREF_member (nspace_last (ns));
		while (!IS_NULL_member (mem)) {
			IDENTIFIER id;
			IDENTIFIER alt;
			DESTROY_member_small (destroy, id, alt, mem, mem);
			UNUSED (id);
			UNUSED (alt);
		}
		COPY_member (nspace_last (ns), NULL_member);
		COPY_member (nspace_prev (ns), NULL_member);
    }
    return;
}


/*
 *    FREE AN OFFSET
 *
 *    This routine frees the offset off.  Note that member and base offsets
 *    are linked directly to the classes they represent and so are not
 *    destroyed here.
 */

void
free_offset(OFFSET off, int force)
{
    if (IS_NULL_off (off)) return;
    CT_ASSERT (ORDER_off == 13);
    switch (TAG_off (off)) {
	case off_zero_tag : {
	    TYPE t;
	    DESTROY_off_zero (destroy, t, off);
	    UNUSED (t);
	    break;
	}
	case off_type_tag : {
	    TYPE t;
	    DESTROY_off_type (destroy, t, off);
	    UNUSED (t);
	    break;
	}
	case off_extra_tag : {
	    int n;
	    TYPE t;
	    DESTROY_off_extra (destroy, t, n, off);
	    UNUSED (n);
	    UNUSED (t);
	    break;
	}
	case off_array_tag : {
	    TYPE t;
	    unsigned n;
	    DESTROY_off_array (destroy, t, n, off);
	    UNUSED (n);
	    UNUSED (t);
	    break;
	}
	case off_ptr_mem_tag : {
	    EXP a;
	    DESTROY_off_ptr_mem (destroy, a, off);
	    free_exp (a, force);
	    break;
	}
	case off_negate_tag : {
	    OFFSET a;
	    DESTROY_off_negate (destroy, a, off);
	    free_offset (a, force);
	    break;
	}
	case off_mult_tag : {
	    EXP b;
	    OFFSET a;
	    DESTROY_off_mult (destroy, a, b, off);
	    free_offset (a, force);
	    free_exp (b, force);
	    break;
	}
	case off_ptr_diff_tag : {
	    EXP a, b;
	    DESTROY_off_ptr_diff (destroy, a, b, off);
	    free_exp (a, force);
	    free_exp (b, force);
	    break;
	}
	case off_base_tag :
	case off_deriv_tag :
	case off_member_tag :
	case off_plus_tag :
	case off_token_tag : {
	    /* Don't free these cases */
	    break;
	}
    }
    return;
}


/*
 *    DESTROY A LIST OF EXPRESSIONS
 *
 *    This routine frees the list of expressions p.
 */

void
free_exp_list(LIST (EXP) p, int force)
{
    while (!IS_NULL_list (p)) {
		EXP e;
		DESTROY_CONS_exp (destroy, e, p, p);
		free_exp (e, force);
    }
    return;
}


/*
 *    FREE AN EXPRESSION
 *
 *    This routine frees the expression e.  It is possible for the same
 *    sub-expression to be reused twice in an expression, so freed expressions
 *    are marked by having their type set to the rule type.  This exploits
 *    some knowledge about about how destroy_c_class works.
 */

void
free_exp(EXP e, int force)
{
    TYPE t;
    EXP a, b;
    int force1 = force;
    if (force1 == 0) force1 = 1;
	
    /* Check expression type */
    if (IS_NULL_exp (e)) return;
    t = DEREF_type (exp_type (e));
    if (IS_NULL_type (t) || IS_type_error (t)) return;
    COPY_type (exp_type (e), NULL_type);
	
    /* Deal with the various cases */
    CT_ASSERT (ORDER_exp == 88);
    switch (TAG_exp (e)) {
	case exp_identifier_tag :
	case exp_member_tag :
	case exp_ambiguous_tag :
	case exp_undeclared_tag : {
	    IDENTIFIER id;
	    QUALIFIER qual;
	    DESTROY_exp_identifier_etc (destroy, t, id, qual, e);
	    UNUSED (qual);
	    UNUSED (id);
	    break;
	}
	case exp_int_lit_tag : {
	    NAT n;
	    unsigned etag;
	    DESTROY_exp_int_lit (destroy, t, n, etag, e);
	    UNUSED (etag);
	    UNUSED (n);
	    break;
	}
	case exp_float_lit_tag : {
	    FLOAT f;
	    DESTROY_exp_float_lit (destroy, t, f, e);
	    UNUSED (f);
	    break;
	}
	case exp_char_lit_tag : {
	    int r;
	    STRING s;
	    DESTROY_exp_char_lit (destroy, t, s, r, e);
	    UNUSED (s);
	    UNUSED (r);
	    break;
	}
	case exp_string_lit_tag : {
	    STRING s;
	    DESTROY_exp_string_lit (destroy, t, s, e);
	    UNUSED (s);
	    break;
	}
	case exp_value_tag : {
	    DESTROY_exp_value (destroy, t, e);
	    break;
	}
	case exp_null_tag : {
	    int ptr_const;
	    DESTROY_exp_null (destroy, t, ptr_const, e);
	    UNUSED (ptr_const);
	    break;
	}
	case exp_zero_tag : {
	    int ptr_const;
	    DESTROY_exp_zero (destroy, t, ptr_const, e);
	    UNUSED (ptr_const);
	    break;
	}
	case exp_paren_tag : {
	    DESTROY_exp_paren (destroy, t, a, e);
	    free_exp (a, force1);
	    break;
	}
	case exp_copy_tag : {
	    DESTROY_exp_copy (destroy, t, a, e);
	    UNUSED (a);
	    break;
	}
	case exp_assign_tag : {
	    DESTROY_exp_assign (destroy, t, a, b, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    break;
	}
	case exp_init_tag : {
	    IDENTIFIER id;
	    DESTROY_exp_init (destroy, t, id, a, e);
	    if (force == 2) {
			DECL_SPEC ds = DEREF_dspec (id_storage (id));
			if (ds & dspec_temp) {
				/* Remove temporary variable */
				ds |= dspec_ignore;
				COPY_dspec (id_storage (id), ds);
			}
	    }
	    free_exp (a, force1);
	    break;
	}
	case exp_preinc_tag : {
	    int bc;
	    DESTROY_exp_preinc (destroy, t, a, b, bc, e);
	    free_exp (b, force1);
	    UNUSED (bc);
	    UNUSED (a);
	    break;
	}
	case exp_postinc_tag : {
	    EXP c;
	    DESTROY_exp_postinc (destroy, t, a, b, c, e);
	    free_exp (c, force1);
	    UNUSED (a);
	    UNUSED (b);
	    break;
	}
	case exp_indir_tag : {
	    int i;
	    DESTROY_exp_indir (destroy, t, a, i, e);
	    free_exp (a, force1);
	    UNUSED (i);
	    break;
	}
	case exp_contents_tag : {
	    DESTROY_exp_contents (destroy, t, a, e);
	    free_exp (a, force1);
	    break;
	}
	case exp_address_tag : {
	    DESTROY_exp_address (destroy, t, a, e);
	    free_exp (a, force1);
	    break;
	}
	case exp_address_mem_tag : {
	    int paren;
	    DESTROY_exp_address_mem (destroy, t, a, paren, e);
	    UNUSED (paren);
	    free_exp (a, force1);
	    break;
	}
	case exp_func_tag : {
	    unsigned n;
	    LIST (EXP) p;
	    DESTROY_exp_func (destroy, t, a, p, n, e);
	    free_exp_list (p, force1);
	    free_exp (a, force1);
	    UNUSED (n);
	    break;
	}
	case exp_func_id_tag : {
	    unsigned n;
	    IDENTIFIER id;
	    LIST (EXP) p;
	    DESTROY_exp_func_id (destroy, t, id, p, b, n, e);
	    free_exp_list (p, force1);
	    UNUSED (id);
	    UNUSED (b);
	    UNUSED (n);
	    break;
	}
	case exp_call_tag : {
	    GRAPH gr;
	    DESTROY_exp_call (destroy, t, a, b, gr, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    UNUSED (gr);
	    break;
	}
	case exp_negate_tag :
	case exp_compl_tag :
	case exp_not_tag :
	case exp_abs_tag : {
	    DESTROY_exp_negate_etc (destroy, t, a, e);
	    free_exp (a, force1);
	    break;
	}
	case exp_plus_tag :
	case exp_minus_tag :
	case exp_mult_tag :
	case exp_div_tag :
	case exp_rem_tag :
	case exp_and_tag :
	case exp_or_tag :
	case exp_xor_tag :
	case exp_log_and_tag :
	case exp_log_or_tag :
	case exp_lshift_tag :
	case exp_rshift_tag :
	case exp_max_tag :
	case exp_min_tag : {
	    DESTROY_exp_plus_etc (destroy, t, a, b, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    break;
	}
	case exp_test_tag : {
	    NTEST tst;
	    DESTROY_exp_test (destroy, t, tst, a, e);
	    free_exp (a, force1);
	    UNUSED (tst);
	    break;
	}
	case exp_compare_tag : {
	    NTEST tst;
	    DESTROY_exp_compare (destroy, t, tst, a, b, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    UNUSED (tst);
	    break;
	}
	case exp_cast_tag : {
	    unsigned conv;
	    DESTROY_exp_cast (destroy, t, conv, a, e);
	    free_exp (a, force1);
	    UNUSED (conv);
	    break;
	}
	case exp_base_cast_tag : {
	    OFFSET off;
	    unsigned conv;
	    DESTROY_exp_base_cast (destroy, t, conv, a, off, e);
	    free_exp (a, force1);
	    free_offset (off, force1);
	    UNUSED (conv);
	    break;
	}
	case exp_dyn_cast_tag : {
	    DESTROY_exp_dyn_cast (destroy, t, a, b, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    break;
	}
	case exp_add_ptr_tag : {
	    int v;
	    OFFSET off;
	    DESTROY_exp_add_ptr (destroy, t, a, off, v, e);
	    free_exp (a, force1);
	    free_offset (off, force1);
	    UNUSED (v);
	    break;
	}
	case exp_offset_size_tag : {
	    TYPE s;
	    int pad;
	    OFFSET off;
	    DESTROY_exp_offset_size (destroy, t, off, s, pad, e);
	    free_offset (off, force1);
	    UNUSED (pad);
	    UNUSED (s);
	    break;
	}
	case exp_constr_tag : {
	    int i;
	    EXP c;
	    DESTROY_exp_constr (destroy, t, a, b, c, i, e);
	    free_exp (a, force1);
	    UNUSED (b);
	    UNUSED (c);
	    UNUSED (i);
	    break;
	}
	case exp_destr_tag : {
	    EXP c;
	    DESTROY_exp_destr (destroy, t, a, b, c, e);
	    free_exp (a, force1);
	    free_exp (c, force1);
	    UNUSED (b);
	    break;
	}
	case exp_alloc_tag : {
	    EXP c, d;
	    DESTROY_exp_alloc (destroy, t, a, b, c, d, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    UNUSED (d);
	    break;
	}
	case exp_dealloc_tag : {
	    EXP c, d;
	    DESTROY_exp_dealloc (destroy, t, a, b, c, d, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    free_exp (d, force1);
	    UNUSED (c);
	    break;
	}
	case exp_rtti_tag : {
	    int op;
	    DESTROY_exp_rtti (destroy, t, a, b, op, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    UNUSED (op);
	    break;
	}
	case exp_rtti_type_tag : {
	    int op;
	    TYPE s;
	    DESTROY_exp_rtti_type (destroy, t, s, op, e);
	    UNUSED (s);
	    UNUSED (op);
	    break;
	}
	case exp_rtti_no_tag : {
	    TYPE s;
	    DESTROY_exp_rtti_no (destroy, t, s, e);
	    UNUSED (s);
	    break;
	}
	case exp_dynamic_tag : {
	    DESTROY_exp_dynamic (destroy, t, a, e);
	    free_exp (a, force1);
	    break;
	}
	case exp_aggregate_tag : {
	    LIST (EXP) p;
	    LIST (OFFSET) q;
	    DESTROY_exp_aggregate (destroy, t, p, q, e);
	    DESTROY_list (q, SIZE_off);
	    free_exp_list (p, force1);
	    break;
	}
	case exp_initialiser_tag : {
	    int n;
	    LIST (EXP) p;
	    unsigned nv, nb;
	    LIST (OFFSET) q;
	    DESTROY_exp_initialiser (destroy, t, p, q, n, nv, nb, e);
	    DESTROY_list (q, SIZE_off);
	    free_exp_list (p, force1);
	    UNUSED (nv);
	    UNUSED (nb);
	    UNUSED (n);
	    break;
	}
	case exp_nof_tag : {
	    NAT n;
	    EXP c;
	    DESTROY_exp_nof (destroy, t, a, n, b, c, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    UNUSED (n);
	    break;
	}
	case exp_comma_tag : {
	    LIST (EXP) p;
	    DESTROY_exp_comma (destroy, t, p, e);
	    free_exp_list (p, force1);
	    break;
	}
	case exp_set_tag :
	case exp_unused_tag : {
	    DESTROY_exp_set_etc (destroy, t, a, e);
	    free_exp (a, force1);
	    break;
	}
	case exp_reach_tag :
	case exp_unreach_tag : {
	    DESTROY_exp_reach_etc (destroy, t, a, b, e);
	    free_exp (b, force1);
	    UNUSED (a);
	    break;
	}
	case exp_sequence_tag : {
	    int bl;
	    NAMESPACE ns;
	    LIST (EXP) p, q;
	    DESTROY_exp_sequence (destroy, t, a, p, q, ns, bl, e);
	    if (force) free_nspace (ns);
	    free_exp_list (p, force1);
	    UNUSED (bl);
	    UNUSED (q);
	    UNUSED (a);
	    break;
	}
	case exp_solve_stmt_tag : {
	    LIST (IDENTIFIER) lb;
	    LIST (IDENTIFIER) vr;
	    DESTROY_exp_solve_stmt (destroy, t, a, b, lb, vr, e);
	    DESTROY_list (lb, SIZE_id);
	    DESTROY_list (vr, SIZE_id);
	    free_exp (b, force);
	    UNUSED (a);
	    break;
	}
	case exp_decl_stmt_tag : {
	    IDENTIFIER id;
	    DESTROY_exp_decl_stmt (destroy, t, a, id, b, e);
	    free_exp (b, force);
	    free_id (id, force);
	    UNUSED (a);
	    break;
	}
	case exp_if_stmt_tag : {
	    EXP c, d;
	    IDENTIFIER lb;
	    DESTROY_exp_if_stmt (destroy, t, a, b, c, d, lb, e);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    free_exp (d, force1);
	    free_id (lb, force1);
	    UNUSED (a);
	    break;
	}
	case exp_while_stmt_tag : {
	    EXP c;
	    IDENTIFIER bk, ct, lp;
	    LIST (IDENTIFIER) cn;
	    DESTROY_exp_while_stmt (destroy, t, a, b, c, bk, ct, lp, cn, e);
	    DESTROY_list (cn, SIZE_id);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    free_id (bk, force1);
	    free_id (ct, force1);
	    free_id (lp, force1);
	    UNUSED (a);
	    break;
	}
	case exp_do_stmt_tag : {
	    EXP c;
	    IDENTIFIER bk, ct, lp;
	    DESTROY_exp_do_stmt (destroy, t, a, b, c, bk, ct, lp, e);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    free_id (bk, force1);
	    free_id (ct, force1);
	    free_id (lp, force1);
	    UNUSED (a);
	    break;
	}
	case exp_switch_stmt_tag : {
	    EXP c;
	    int ex;
	    LIST (NAT) p;
	    IDENTIFIER df, bk;
	    LIST (IDENTIFIER) q;
	    DESTROY_exp_switch_stmt (destroy, t, a, b, c, p, q,
								 df, ex, bk, e);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    free_id (df, force1);
	    free_id (bk, force1);
	    DESTROY_list (p, SIZE_nat);
	    DESTROY_list (q, SIZE_id);
	    UNUSED (ex);
	    UNUSED (a);
	    break;
	}
	case exp_hash_if_tag : {
	    EXP c, d, f;
	    DESTROY_exp_hash_if (destroy, t, a, b, c, d, f, e);
	    free_exp (c, force1);
	    free_exp (d, force1);
	    UNUSED (f);
	    UNUSED (a);
	    UNUSED (b);
	    break;
	}
	case exp_return_stmt_tag : {
	    DESTROY_exp_return_stmt (destroy, t, a, b, e);
	    free_exp (b, force1);
	    UNUSED (a);
	    break;
	}
	case exp_goto_stmt_tag : {
	    EXP c;
	    IDENTIFIER lb;
	    DESTROY_exp_goto_stmt (destroy, t, a, lb, b, c, e);
	    free_id (lb, force1);
	    UNUSED (c);
	    UNUSED (b);
	    UNUSED (a);
	    break;
	}
	case exp_label_stmt_tag : {
	    IDENTIFIER lb;
	    IDENTIFIER nt;
	    DESTROY_exp_label_stmt (destroy, t, a, lb, b, nt, e);
	    free_id (lb, force1);
	    free_exp (b, force1);
	    UNUSED (nt);
	    UNUSED (a);
	    break;
	}
	case exp_try_block_tag : {
	    int f;
	    EXP c;
	    ulong n;
	    LIST (EXP) p;
	    LIST (TYPE) q, r;
	    LIST (LOCATION) s;
	    LIST (TYPE) u = univ_type_set;
	    LIST (TYPE) v = empty_type_set;
	    DESTROY_exp_try_block (destroy, t, a, b, f, p, q, c, r, s, n, e);
	    if (!EQ_list (q, r)) {
			if (!EQ_list (q, u) && !EQ_list (q, v)) {
				DESTROY_list (q, SIZE_type);
			}
	    }
	    if (!EQ_list (r, u) && !EQ_list (r, v)) {
			DESTROY_list (r, SIZE_type);
	    }
	    DESTROY_list (s, SIZE_loc);
	    free_exp_list (p, force1);
	    free_exp (b, force);
	    free_exp (c, force1);
	    UNUSED (f);
	    UNUSED (n);
	    UNUSED (a);
	    break;
	}
	case exp_handler_tag : {
	    ulong n;
	    IDENTIFIER id;
	    DESTROY_exp_handler (destroy, t, a, id, b, n, e);
	    free_exp (b, force1);
	    free_id (id, force1);
	    UNUSED (n);
	    UNUSED (a);
	    break;
	}
	case exp_exception_tag : {
	    int d;
	    EXP c;
	    DESTROY_exp_exception (destroy, t, a, b, c, d, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    free_exp (c, force1);
	    UNUSED (d);
	    break;
	}
	case exp_thrown_tag : {
	    int d;
	    DESTROY_exp_thrown (destroy, t, d, e);
	    UNUSED (d);
	    break;
	}
	case exp_op_tag : {
	    int op;
	    DESTROY_exp_op (destroy, t, op, a, b, e);
	    free_exp (a, force1);
	    free_exp (b, force1);
	    UNUSED (op);
	    break;
	}
	case exp_opn_tag : {
	    int op;
	    LIST (EXP) p;
	    DESTROY_exp_opn (destroy, t, op, p, e);
	    free_exp_list (p, force1);
	    UNUSED (op);
	    break;
	}
	case exp_assembler_tag : {
	    STRING s;
	    LIST (EXP) p;
	    DESTROY_exp_assembler (destroy, t, s, p, e);
	    free_exp_list (p, force1);
	    UNUSED (s);
	    break;
	}
	case exp_uncompiled_tag : {
	    PPTOKEN *p;
	    LOCATION loc;
	    DESTROY_exp_uncompiled (destroy, t, loc, p, e);
	    free_tok_list (p);
	    UNUSED (loc);
	    break;
	}
	case exp_location_tag : {
	    LOCATION loc;
	    DESTROY_exp_location (destroy, t, loc, a, e);
	    free_exp (a, force1);
	    UNUSED (loc);
	    break;
	}
	case exp_fail_tag : {
	    string s;
	    DESTROY_exp_fail (destroy, t, s, e);
	    UNUSED (s);
	    break;
	}
	case exp_token_tag : {
	    IDENTIFIER id;
	    LIST (TOKEN) p;
	    DESTROY_exp_token (destroy, t, a, id, p, e);
	    UNUSED (id);
	    UNUSED (p);
	    UNUSED (a);
	    break;
	}
	case exp_dummy_tag : {
	    int v;
	    ulong n;
	    int cnt;
	    OFFSET off;
	    DESTROY_exp_dummy (destroy, t, a, n, off, v, cnt, e);
	    free_exp (a, force1);
	    free_offset (off, force1);
	    UNUSED (cnt);
	    UNUSED (n);
	    UNUSED (v);
	    break;
	}
    }
    UNUSED (t);
    return;
}


/*
 *    FREE A FUNCTION DEFINITION
 *
 *    This routine frees the definition of the function id, replacing it
 *    by a dummy definition.
 */

void
free_function(IDENTIFIER id)
{
    EXP e = DEREF_exp (id_function_etc_defn (id));
    if (!IS_NULL_exp (e)) {
		TYPE t = DEREF_type (id_function_etc_type (id));
		free_exp (e, 0);
		MAKE_exp_value (t, e);
		COPY_exp (id_function_etc_defn (id), e);
    }
    return;
}
