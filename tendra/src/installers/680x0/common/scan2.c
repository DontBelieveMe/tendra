/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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
 *    		 Crown Copyright (c) 1996
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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


/*
 *    SCAN2
 *
 *    Scans through the program and puts all the arguments of operations
 *    into a suitable 68000 operand form.
 
*/


#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "tags.h"
#include "install_fns.h"
#ifndef tdf3
#include "68k_globals.h"
#include "special_exps.h"
#endif

void scan2(bool, exp, exp) ;

/*
 *    MACROS TO SET OR GET THE SON OR BRO
 */

#define  assexp(I, P, V)	if (I) setson (P, V) ; else setbro (P, V)
#define  contexp(I, P)	((I) ? son (P) : bro (P))


/*
 *  Transform a non-bit offset into a bit offset.
 *  (borrowed from trans386)
 */
static void
make_bitfield_offset(exp e, exp pe, int spe,
					 shape sha)
{
	exp omul;
	exp val8;
	if (name(e) == val_tag){
		no(e) *= 8;
		return;
	}
	omul = getexp (sha, bro(e), (int)(last (e)), e, nilexp, 0, 0, offset_mult_tag);
	val8 = getexp (slongsh, omul, 1, nilexp, nilexp, 0, 8, val_tag);
	clearlast(e);
	setbro(e, val8);
	if (spe) {
		son(pe) = omul;
	}
	else{
		bro(pe) = omul;
	}
	return;
}


/*
 *    INSERT AN IDENTITY DECLARATION
 *
 *    This routine inserts an identity declaration of x at to and replaces
 *    x by a use of this identity.
 */

static void
cca(bool sto, exp to, bool sx, exp x)
{
	exp d, a, id, tg;
	d = contexp (sx, x);
#ifndef tdf3
	if (name(d)==caller_tag) {	/* position sensitive */
		cca (sto, to, 1, d);
		return;
	}
#endif
	d = contexp (sx, x);
	a = contexp (sto, to);
	id = getexp (sh (a), bro (a), last(a), d, nilexp, 0, L1, ident_tag);
	tg = getexp (sh (d), bro (d), last(d), id, nilexp, 0, L0, name_tag);
	pt (id) = tg;
	clearlast (d);
	if (d != a) {
		bro (d) = a;
		bro (a) = id;
		setlast (a);
		assexp (sto, to, id);
		assexp (sx, x, tg);
	} else {
		bro (d) = tg;
		bro (tg) = id;
		setlast (tg);
		clearlast (d);
		assexp (sto, to, id);
	}
	return;
}


/*
 *    INSERT AN IDENTITY DECLARATION IN A BRO-LIST
 *
 *    Keeping the same to, cc scans along the bro list e, applying cca to
 *    introduce an identity declaration when doit is 1.  It keeps count as
 *    the index position along the list in order to pass it to doit.  If it
 *    uses cca it scans the resulting declaration, using the same to.  If it
 *    doesn't, it scans the list element, still using the same to.  This keeps
 *    all operations in the same order.
 */

static void
cc(bool sto, exp to, bool se, exp e, bool (*doit)(exp, int),
   int count)
{
	exp ec = contexp (se, e);
	
	if (last (ec)) {
		if (doit (ec, count)) {
			cca (sto, to, se, e);
			ec = contexp (sto, to);
			scan2 (1, ec, son (ec));
		} else {
			scan2 (sto, to, ec);
		}
	} else {
		cc (sto, to, 0, ec, doit, count + 1);
		ec = contexp (se, e);
		if (doit (ec, count)) {
			cca (sto, to, se, e);
			ec = contexp (sto, to);
			scan2 (1, ec, son (ec));
		} else {
			scan2 (sto, to, ec);
		}
	}
	return;
}


/*
 *    INSERT AN IDENTITY DECLARATION
 *
 *    This routine is the same as cca, but forces the declaration into
 *    a register.
 */

static void
ccp(bool sto, exp to, bool sx, exp x)
{
    exp xc = contexp (sx, x);
    exp toc;
    if (name (xc) != name_tag || !isusereg (son (xc))) {
		cca (sto, to, sx, x);
		toc = contexp (sto, to);
		setusereg (toc);
		scan2 (1, toc, son (toc));
    }
    return;
}


/*
 *    IS THE EXP e AN OPERAND?
 */

static bool
is_opnd(exp e)
{
    switch (name (e)) {
		
	case name_tag : {
	    exp s = son (e);
	    return (!isvar (s) && (son(son(e))!=nilexp) && !isparam (son (son (e))));
	}
		
	case val_tag :
	case real_tag :
	case env_size_tag :
	case general_proc_tag:
	case proc_tag :
	case cont_tag :
	case string_tag :
	case null_tag : {
	    return (1);
	}
    }
    return (0);
}


/*
 *    CHECK THE POINTER ARGUMENT OF AN ADDPTR
 */

static void
ap_arg1(bool sto, exp to, bool sa, exp a,
		bool b)
{
    exp ac = contexp (sa, a);
	
    if (!b && name (ac) == cont_tag && name (son (ac)) == name_tag &&
		isvar (son (son (ac)))) return;
	
    if (!b && name (ac) == name_tag) return;
	
    /* The pointer has to go into a register */
    ccp (sto, to, sa, a);
    return;
}


/*
 *    CHECK THE INTEGER ARGUMENT OF AN ADDPTR
 */

static void
ap_argsc(bool sto, exp to, bool se, exp e,
		 int sz, bool b)
{
    exp ec = contexp (se, e);
    exp p = son (ec);
    exp a = bro (p);
    exp temp;
	
    /* Check for multiplication by constant scale factor */
    if (name (a) == offset_mult_tag &&
		name (bro (son (a))) == val_tag) {
		
		long k = no (bro (son (a)));
		if ((k == 8 || k == 16 || k == 32 || k == 64) && k == sz) {
			ccp (sto, to, 1, a);
			ap_arg1 (sto, to, 1, ec, b);
			return;
		}
		
    }
	
    if (sz == 8) {
		ccp (sto, to, 0, son (ec));
		ap_arg1 (sto, to, 1, ec, b);
		return;
    }
	
    if (b) {
		ccp (sto, to, se, e);
		return;
    }
	
    cca (sto, to, se, e);
    temp = contexp (sto, to);
    scan2 (1, temp, son (temp));
    return;
}


/*
 *    CHECK THE ARGUMENT OF A CONT OR THE DESTINATION OF AN ASSIGN
 */

static void
cont_arg(bool sto, exp to, exp e, shape sa)
{
    unsigned char n = name (son (e));
    if (n == name_tag) return;
	
    if (n == cont_tag) {
		exp s = son (son (e));
		if (name (s) == name_tag &&
			(isvar (son (s)) || isglob (son (s)) ||
			 isusereg (son (s)))) return;
		
		if (name (s) == reff_tag &&
			name (son (s)) == name_tag &&
			(isvar (son (son (s))) || isglob (son (son (s))) ||
			 isusereg (son (son (s))))) return;
		
		ccp (sto, to, 1, e);
		return;
    }
	
    if (n == reff_tag) {
		exp s = son (e);
		if (name (son (s)) == name_tag &&
			isusereg (son (son (s)))) return;
		
		if (name (son (s)) == addptr_tag) {
			ap_argsc (sto, to, 1, s, shape_size (sa), 1);
			return;
		}
		
		ccp (sto, to, 1, s);
		return;
    }
	
    if (n == addptr_tag) {
		ap_argsc (sto, to, 1, e, shape_size (sa), 0);
		return;
    }
	
    ccp (sto, to, 1, e);
    return;
}


/*
 *    DOIT ROUTINE, IS t NOT AN OPERAND?
 */

static bool
notopnd(exp t, int i)
{
    return (i >= 0 && !is_opnd (t));
}

#ifndef tdf3
static int scan_for_alloca(exp) ;

static int
scan_alloc_args(exp s)
{
	if (scan_for_alloca(s))
		return 1;
	if (last(s))
		return 0;
	return scan_alloc_args(bro(s));
}

static int
scan_for_alloca(exp t)
{
	switch (name(t)) {
	case local_free_all_tag:
	case local_free_tag:
	case last_local_tag:
	case alloca_tag:
	case make_lv_tag:
		return 1;
	case case_tag:
		return scan_for_alloca(son(t));
	case labst_tag:
		return scan_for_alloca(bro(son(t)));
	case env_offset_tag:
	case string_tag:
	case name_tag:
		return 0;
	case apply_general_tag:
		if call_is_untidy(t)
							 return 1;
		return scan_alloc_args(son(t));
	default:
		if (son(t) == nilexp)
			return 0;
		return scan_alloc_args(son(t));
	};
}

static bool
no_alloca(exp t, int i)
{
    UNUSED (i);
    return (scan_for_alloca (t));
}

#endif

/*
 *    APPLY cc, DOING IT WITH OPERANDS
 */

static void
all_opnd(bool sto, exp to, exp e)
{
#if 0
	if (!last(bro(son(e)))) {
		
		/* Operation has more than two parameters.  Make it diadic */
		exp opn = getexp(sh(e),e,0,bro(son(e)),nilexp,0,0,name(e));
		exp nd = getexp(sh(e),bro(e),last(e),opn,nilexp,0,1,ident_tag);
		exp id = getexp(sh(e),e,1,nd,nilexp,0,0,name_tag);
		pt(nd) = id;
		bro(son(e)) = id;
		setlast(e);
		bro(e) = nd;
		while (!last(bro(son(e)))) {
			bro(son(e)) = bro(bro(son(e)));
		}
		bro(bro(son(e))) = opn;
		e = nd;
		scan2(sto,e,e);
	}
#endif
	cc (sto, to, 1, e, notopnd, 1);
	return;
}


/*
 *    IS e ASSIGNABLE?
 */

static bool
is_assable(exp e)
{
    long sz;
    unsigned char n = name (e);
    if (is_a (n)) return (1);
    if (n != apply_tag && n != apply_general_tag) return (0);
    n = name (sh (e));
    sz = shape_size (sh (e));
    return (n <= ulonghd || (n == ptrhd && sz == 32));
}


/*
 *    DOIT ROUTINE, IS t NOT ASSIGNABLE?
 */

static bool
notass(exp t, int i)
{
    return (i >= 0 && !is_assable (t));
}


/*
 *    APPLY cc, DOING IT WITH ASSIGNABLES
 */

static void
all_assable(bool sto, exp to, exp e)
{
    cc (sto, to, 1, e, notass, 1);
    return;
}


/*
 *    IS e DIRECTLY ADDRESSABLE?
 */

static bool
is_direct(exp e)
{
    unsigned char s = name (e);
    return ((s == name_tag && !isglob (son (e)) &&
			 !isvar (son (e))) ||
			(s == cont_tag && name (son (e)) == name_tag &&
			 !isglob (son (son (e))) &&
			 isvar (son (son (e)))));
}


/*
 *    IS e INDIRECTLY ADDRESSABLE?
 */

static bool
is_indable(exp e)
{
    unsigned char s = name (e);
    if (s == name_tag) return (1);
	
    if (s == cont_tag) {
		unsigned char t = name (son (e));
		return ((t == name_tag && isvar (son (son (e)))) ||
				(t == cont_tag && name (son (son (e))) == name_tag &&
				 isvar (son (son (son (e))))) ||
				(t == reff_tag && is_direct (son (son (e)))));
    }
	
    return ((s == reff_tag && is_direct (son (e))) ||
			s == addptr_tag);
}

#ifndef tdf3
/*
 *    MAKES son (e) INDIRECTLY ADDRESSABLE
 */
static void
indable_son(bool sto, exp to, exp e)
{
	if (!is_indable (son (e))) {
		exp ec;
		cca (sto, to, 1, e);
		ec = contexp (sto, to);
		scan2 (1, ec, son (ec));
	}
	else
		scan2 (sto, to, son (e));
	return;
}

#endif

/*
 *    APPLY scan2 TO A BRO LIST
 */

static void
scanargs(bool st, exp e)
{
    exp t = e;
    exp temp;
	
    while (temp = contexp (st, t), scan2 (st, t, temp),
		   temp = contexp (st, t), !last (temp)) {
		t = contexp (st, t);
		st = 0;
    }
    return;
}


/*
 *    DOIT ROUTINE FOR APPLY
 */

#if 0
static bool
apdo(exp t, int i)
{
    /* The first argument needs special treatment */
    if (i == 1) return (!is_indable (t));
    return (0);
}
#endif


/*
 *    DOIT ROUTINE FOR PLUS
 */

static bool
plusdo(exp t, int i)
{
    /* Can't negate first argument */
    if (i == 1) return (!is_opnd (t));
    /* But can negate the rest */
    if (name (t) == neg_tag) return (0);
    return (!is_opnd (t));
}


/*
 *    DOIT ROUTINE FOR MULT
 */

static bool
multdo(exp t, int i)
{
    return (i >= 0 && !is_o (name (t)));
}


/*
 *    DOIT ROUTINE FOR AND
 */

static bool
anddo(exp t, int i)
{
#if 0
    /* Can't negate first argument */
    if (i == 1) return (!is_o (name (t)));
    /* But can negate the rest */
    if (name (t) == not_tag) return (0);
#endif
    return (!is_o (name (t)));
}


/*
 *    DOIT ROUTINE FOR XOR
 */

static bool
notado(exp t, int i)
{
    return (i >= 0 && !is_o (name (t)));
}


/*
 *    MAIN SCAN ROUTINE
 */

void
scan2(bool sto, exp to, exp e)
{
    switch (name (e)) {
		
	case cond_tag :
	case rep_tag :
	case compound_tag :
#ifdef rscope_tag
	case rscope_tag :
#endif
	case solve_tag :
	case concatnof_tag :
	case nof_tag :
	case diagnose_tag :
#ifndef tdf3
	case caller_tag: {
        if (son(e) == nilexp) /* empty make_nof */
			return;
        scanargs (1, e);
        return;
	};
#else
	{
	    scanargs (1, e);
	    return;
	}
#endif
	case labst_tag : {
	    scan2 (0, son (e), bro (son (e)));
	    return;
	}
		
	case ident_tag : {
	    scan2 (0, son (e), bro (son (e)));
	    scan2 (1, e, son (e));
	    return;
	}
		
	case seq_tag : {
	    scanargs (1, son (e));
	    scan2 (0, son (e), bro (son (e)));
	    return;
	}
		
#if 0
	case diag_tag :
	case cscope_tag :
	case fscope_tag : {
	    scanargs (1, e);
	    return;
	}
#endif
		
	case local_free_tag :
	case long_jump_tag :
	case ncopies_tag : {
	    all_assable (sto, to, e);
	    return;
	}
		
	case alloca_tag : {
	    all_opnd (sto, to, e);
	    return;
	}
#ifndef tdf3
	case set_stack_limit_tag: {
		exp lim = get_stack_limit();
		setbro (lim, son(e));
		setson (e, lim);
		setname (e, ass_tag);
		scan2 (sto, to, e);
		return;
	};
#endif
		
	case offset_add_tag :
	case offset_subtract_tag : {
		if ((al2(sh(son(e))) == 1) && (al2(sh(bro(son(e)))) != 1)){
			make_bitfield_offset(bro(son(e)),son(e),0,sh(e));
		}
		if ((al2(sh(son(e))) != 1) && (al2(sh(bro(son(e)))) == 1)){
			make_bitfield_offset(son(e),e,1,sh(e));
		}
	}
	case test_tag :
	case absbool_tag :
	case testbit_tag :
	case make_stack_limit_tag:
	case minus_tag :
	case subptr_tag :
	case div0_tag :
	case div1_tag :
	case div2_tag :
	case shl_tag :
	case shr_tag :
	case rem0_tag :
	case mod_tag :
	case rem2_tag :
	case round_tag :
	case max_tag :
	case offset_max_tag :
	case min_tag :
	case offset_div_by_int_tag :
	case offset_negate_tag :
	case offset_pad_tag :
	case minptr_tag :
	case fplus_tag :
	case fminus_tag :
	case fmult_tag :
	case fdiv_tag :
	case fneg_tag :
	case fabs_tag :
	case chfl_tag :
	case float_tag :
	case offset_mult_tag :
	case offset_div_tag :
	case movecont_tag : {
	    all_opnd (sto, to, e);
	    return;
	}
	case not_tag :
	case neg_tag :
	case abs_tag :
	case chvar_tag : {
	    all_opnd (sto, to, e);
	    return;
	}
		
	case bitf_to_int_tag :
	case int_to_bitf_tag : {
	    all_opnd (sto, to, e);
	    return;
	}
		
	case ass_tag :
	case assvol_tag : {
	    exp toc;
	    /* Change assvol into ass */
	    if (name (e) == assvol_tag) setname (e, ass_tag);
	    if (!is_assable (bro (son (e)))) {
			cca (sto, to, 0, son (e));
			toc = contexp (sto, to);
			scan2 (1, toc, son (toc));
	    } else {
			scan2 (sto, to, bro (son (e)));
	    }
	    cont_arg (sto, to, e, sh (bro (son (e))));
	    return;
	}
		
#ifndef tdf3
	case tail_call_tag: {
		exp cees = bro(son(e));
		cur_proc_has_tail_call = 1;
		cur_proc_use_same_callees  = (name(cees) == same_callees_tag);
		
		if (son(cees) != nilexp)
			cc (sto, to, 1, cees, no_alloca, 1);
		
		indable_son (sto, to, e);
		
		return;
	};
		
	case apply_general_tag : {
		
		exp cees = bro(bro(son(e)));
		exp p_post = cees;	/* bro(p_post) is postlude */
		
		cur_proc_use_same_callees  = (name(cees) == same_callees_tag);
		
		while (name(bro(p_post)) == ident_tag && name(son(bro(p_post))) == caller_name_tag)
			p_post = son(bro(p_post));
		scan2 (0, p_post, bro(p_post));
		if (son(cees) != nilexp)
			scanargs (1, cees);
		if (no(bro(son(e))) != 0)
			scanargs (1, bro(son(e)));
		
		if (!is_indable (son(e))) {
			exp ec;
			cca (sto, to, 1, e);
			ec = contexp (sto, to);
			scan2 (1, ec, son (ec));
		} else {
			scan2 (sto, to, son (e));
		}
		return;
	}
#endif
		
	case apply_tag : {
	    scanargs (1, e);
	    /* Fall through */
	}
		
	case goto_lv_tag : {
	    if (!is_indable (son (e))) {
			exp ec;
			cca (sto, to, 1, e);
			ec = contexp (sto, to);
			scan2 (1, ec, son (ec));
	    } else {
			scan2 (sto, to, son (e));
	    }
	    return;
	}
		
#ifndef tdf3
	case untidy_return_tag:
#endif
	case res_tag : {
	    long sz;
		
	    if (name (son (e)) == apply_tag
			|| name (son (e)) == apply_general_tag)
		{
			scan2 (sto, to, son (e));
			return;
	    }
		
	    sz = shape_size (sh (son (e)));
		
	    if (sz <= 64) {
			all_assable (sto, to, e);
			return;
	    }
	    all_opnd (sto, to, e);
	    return;
	}
		
	case case_tag : {
	    exp toc;
	    if (!is_opnd (son (e))) {
			cca (sto, to, 1, e);
			toc = contexp (sto, to);
			scan2 (1, toc, son (toc));
	    } else {
			scan2 (sto, to, son (e));
	    }
	    return;
	}
		
	case plus_tag : {
	    if (name (son (e)) == neg_tag &&
			name (bro (son (e))) == val_tag) {
			scan2 (sto, to, son (e));
			return;
	    }
	    cc (sto, to, 1, e, plusdo, 1);
	    return;
	}
		
	case addptr_tag : {
	    exp a = bro (son (e));
		
	    if (name (a) == offset_mult_tag &&
			name (bro (son (a))) == val_tag) {
			long k = no (bro (son (a))) / 8;
			if (k == 1 || k == 2 || k == 4 || k == 8) {
				ccp (sto, to, 1, a);
				ap_arg1 (sto, to, 1, e, 0);
				return;
			}
	    }
		
	    ccp (sto, to, 0, son (e));
	    ap_arg1 (sto, to, 1, e, 0);
	    return;
	}
		
	case mult_tag : {
	    cc (sto, to, 1, e, multdo, 1);
	    return;
	}
		
	case and_tag : {
	    cc (sto, to, 1, e, anddo, 1);
	    return;
	}
		
	case or_tag :
	case xor_tag : {
	    cc (sto, to, 1, e, notado, 1);
	    return;
	}
		
	case cont_tag :
	case contvol_tag : {
	    /* Change contvol into cont */
	    if (name (e) == contvol_tag) setname (e, cont_tag);
	    cont_arg (sto, to, e, sh (e));
	    return;
	}
		
	case field_tag : {
	    if (!is_o (name (son (e))) || name (e) == cont_tag) {
			exp temp;
			cca (sto, to, 1, e);
			temp = contexp (sto, to);
			scan2 (1, temp, son (temp));
	    } else {
			scan2 (sto, to, son (e));
	    }
	    return;
	}
		
	case reff_tag : {
	    exp s = son (e);
	    if (name (s) == name_tag ||
			(name (s) == cont_tag &&
			 name (son (s)) == name_tag)) return;
	    ccp (sto, to, 1, e);
	    return;
	}
		
	case general_proc_tag:
	case proc_tag : {
	    scan2 (1, e, son (e));
	    return;
	}
#if 0
	case val_tag :{
		if (name(sh(e)) == offsethd && al2(sh(e))>=8){
			no(e) = no(e)>>3;
		}
		return;
	}
#endif
		
	default : return;
    }
}
