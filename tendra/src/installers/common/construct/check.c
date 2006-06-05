/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: pwe $
$Date: 1998/03/11 11:03:19 $
$Revision: 1.3 $
$Log: check.c,v $
 * Revision 1.3  1998/03/11  11:03:19  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/11  16:56:36  pwe
 * corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.41  1998/01/09  09:28:25  pwe
 * prep restructure
 *
 * Revision 1.40  1997/12/04  19:38:53  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.39  1997/10/10  18:15:13  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.38  1997/08/23  13:24:00  pwe
 * no invert order, and NEWDIAGS inlining
 *
 * Revision 1.37  1997/08/06  10:58:22  currie
 * Catch overflowed constants, PlumHall requirement
 *
 * Revision 1.36  1996/10/01  08:59:19  currie
 * correct chvar exceptions ADA
 *
Revision 1.35  1996/06/24 17:26:57  currie
PIC code with name substitution

Revision 1.34  1996/06/13 09:24:55  currie
Bitfield alignments

Revision 1.33  1996/06/05 15:29:48  currie
parameter alignment in make_cmpd

 * Revision 1.32  1996/02/28  11:36:18  currie
 * assign to promoted pars
 *
 * Revision 1.31  1996/02/21  09:39:00  currie
 * hppa var_callers + inlined bug
 *
 * Revision 1.30  1996/01/22  14:25:31  currie
 * char parameters on bigendian
 *
 * Revision 1.29  1996/01/17  10:28:06  currie
 * param alignment + case bigval
 *
 * Revision 1.28  1996/01/10  14:58:43  currie
 * BIGEND var params chars & shorts
 *
 * Revision 1.27  1995/11/29  15:30:09  currie
 * computed signed nat
 *
 * Revision 1.26  1995/11/01  11:29:45  currie
 * 32 place shifts
 *
 * Revision 1.25  1995/10/26  10:14:22  currie
 * solve_tag - kill_exp scope reduced
 *
 * Revision 1.24  1995/10/17  12:59:23  currie
 * Power tests + case + diags
 *
 * Revision 1.24  1995/10/17  12:59:23  currie
 * Power tests + case + diags
 *
 * Revision 1.23  1995/10/13  15:14:58  currie
 * case + long ints on alpha
 *
 * Revision 1.22  1995/10/12  15:52:47  currie
 * inlining bug
 *
 * Revision 1.21  1995/10/11  17:09:56  currie
 * avs errors
 *
 * Revision 1.20  1995/10/06  14:41:53  currie
 * Env-offset alignments + new div with ET
 *
 * Revision 1.18  1995/10/04  09:17:26  currie
 * CR95_371 + optimise compounds
 *
 * Revision 1.17  1995/10/03  11:44:58  currie
 * field(compound)
 *
 * Revision 1.16  1995/10/02  10:55:54  currie
 * Alpha varpars + errhandle
 *
 * Revision 1.15  1995/09/19  16:06:43  currie
 * isAlpha!!
 *
 * Revision 1.14  1995/09/15  13:29:00  currie
 * hppa + add_prefix + r_w_m complex
 *
 * Revision 1.13  1995/09/11  15:35:32  currie
 * caller params -ve
 *
 * Revision 1.12  1995/08/31  14:18:56  currie
 * mjg mods
 *
 * Revision 1.11  1995/08/29  10:45:43  currie
 * Various
 *
 * Revision 1.10  1995/08/15  08:25:27  currie
 * Shift left + trap_tag
 *
 * Revision 1.10  1995/08/15  08:25:27  currie
 * Shift left + trap_tag
 *
 * Revision 1.9  1995/08/09  08:59:54  currie
 * round bug
 *
 * Revision 1.8  1995/08/02  13:17:57  currie
 * Various bugs reported
 *
 * Revision 1.7  1995/07/06  09:14:00  currie
 * rem & VERSION
 *
 * Revision 1.6  1995/07/05  09:26:30  currie
 * continue wrong
 *
 * Revision 1.5  1995/07/03  13:42:36  currie
 * Tail call needs fp
 *
 * Revision 1.4  1995/06/26  13:04:32  currie
 * make_stack_limit, env_size etc
 *
 * Revision 1.3  1995/06/22  09:16:19  currie
 * offset_mult bug + power
 *
 * Revision 1.2  1995/05/05  08:10:45  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/



/*********************************************************************

                             check.c

  The routine check performs the bottom-up TDF-to-TDF optimising
  transformations. When a new exp is created check is applied to
  see if a recognised situation has arisen. check assumes that
  all components of this new exp have already had check applied to them.
  It returns 1 if it has made a change, 0 if not.


  hold_check holds an exp as the son of a dummy exp and then
  applies check. the need for this operation is explained in
  the overall documentation.

  eq_exp compares two exp for equality of effect.

  dochvar takes the int, i, and delivers the number which results from
  changing its variety to that specified by the shape, t.

 *********************************************************************/


#include "config.h"
#include "common_types.h"
#include "xalloc.h"
#include "expmacs.h"
#include "exp.h"
#include "tags.h"
#include "flpt.h"
#include "flags.h"
#include "externs.h"
#include "install_fns.h"
#include "shapemacs.h"
#include "check_id.h"
#include "me_fns.h"
#include "basicread.h"
#include "szs_als.h"
#include "installglob.h"
#include "machine.h"
#include "messages_c.h"
#include "natmacs.h"
#include "f64.h"
#include "misc_c.h"
#include "readglob.h"
#include "misc_c.h"
#ifdef NEWDIAGS
#include "dg_aux.h"
#endif

#if is80x86
#include "localflags.h"
#endif

#include "check.h"

extern shape containedshape(int, int);

/* MACROS */

/* codes for error treaments */
#define impossible 1
#define ignore 2

/* IDENTITIES */

static int masks[33] = {
	0,
	0x1, 0x3, 0x7, 0xf,
	0x1f, 0x3f, 0x7f, 0xff,
	0x1ff, 0x3ff, 0x7ff, 0xfff,
	0x1fff, 0x3fff, 0x7fff, 0xffff,
	0x1ffff, 0x3ffff, 0x7ffff, 0xfffff,
	0x1fffff, 0x3fffff, 0x7fffff, 0xffffff,
	0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff,
	0x1fffffff, 0x3fffffff, 0x7fffffff, (int)0xffffffff
};

ntest int_inverse_ntest[] = {0, 4, 3, 2, 1, 6, 5};
ntest real_inverse_ntest[] = {0, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 12, 11, 14, 13};
ntest exchange_ntest[] = {0, 3, 4, 1, 2, 5, 6, 9, 10, 7, 8, 11, 12, 13, 14};

#if FBASE == 10
static char maxdigs[] = "4294967296";
#endif

/* PROCEDURES */

/***********************************************************************

  hold_check holds an exp as the son of a dummy exp and then
  applies check. After checking it retcells the dummy exp.

 ***********************************************************************/
/* puts body on a hold */
exp
hold(exp body)
{
	exp body_hold = next_exp();
	son(body_hold) = body;
	bro(body) = body_hold;
	setlast(body);
	bro(body_hold) = nilexp;

#if diagnose_registers
	setname(body_hold, hold_tag);
#else
	setname(body_hold, 102);
#endif

	return(body_hold);
}


exp
hold_check(exp r)
{
	exp h, sn;
	h = hold(r);
	IGNORE check(r, r);
	sn = son(h);
	bro(sn) = nilexp;
	retcell(h);
	return(sn);
}


exp
hold_const_check(exp r)
{
	exp ans;
	int old = all_variables_visible;
	all_variables_visible = 0;
	ans = hold_check(r);
	all_variables_visible = old;
	return ans;
}


static
exp varchange(shape s, exp e)
{
	/* applies a change_var operation to e, to get shape s */
	exp r = getexp(s, nilexp, 0, e, nilexp, 0, 0, chvar_tag);
	setlast(e);
	bro(e) = r;
	return(hold_check(r));
}


static int
flpt_power_of_2(flpt f)
{
	flt *r = &flptnos[f];
	unsigned short us = r->mant[0];
	int i;

	if ((us & (us - 1)) != 0) {
		return 0;
	}
	for (i = 1; i < MANT_SIZE; i++) {
		if (r->mant[i] != 0) {
			return 0;
		}
	}

	return 1;
}


/***********************************************************************
   eq_explist compares two descendant lists of exp for equality.
   The given values, their bro's, bro(bro)'s etc are compared until
   an unequal pair is found or the end of one of the lists (last) is
   found. In this case the lists are equal iff both ends have been
   reached.
 ***********************************************************************/

static int
eq_explist(exp al, exp bl)
{
	if (al == nilexp && bl == nilexp) {
		return(1);
	}
	if (al == nilexp || bl == nilexp) {
		return(0);
	}
	if (!eq_exp(al, bl)) {
		return(0);
	}
	if (last(al) && last(bl)) {
		return(1);
	}
	if (last(al) || last(bl)) {
		return(0);
	}
	return(eq_explist(bro(al), bro(bl)));
}


/***********************************************************************
    eq_exp compares two exp for equality of effect. If the name of either
    exp is in the side-effecting group (!is_a) the exp are not equal.
    This is a crude test, but if it says the exps are equal this is so.
    contvol is forbidden.
 ***********************************************************************/

int
eq_exp(exp a, exp b)
{
	if (name(a) == name(b)) {
		if (name(a) == name_tag) {
			return(son(a) == son(b) && no(a) == no(b) &&
			       eq_shape(sh(a), sh(b)));
		}
		if (!is_a(name(a)) || !eq_shape(sh(a), sh(b)) ||
		    name(a) == contvol_tag) {
			return(0);
		}
		if (name(a) == real_tag) {
			int res = flt_cmp(flptnos[no(a)], flptnos[no(b)]);
			return(res == 0);
		}
		if (name(a) == val_tag) {
			if (isbigval(a)) {
				int res;
				if (!isbigval(b)) {
					return 0;
				}
				res = flt_cmp(flptnos[no(a)], flptnos[no(b)]);
				return(res == 0);
			}
			if (isbigval(b)) {
				return 0;
			}
			return(no(a) == no(b));
		}
		return(no(a) == no(b) && eq_explist(son(a), son(b)));
	}
	return(0);
}


/**********************************************************************
   repbycont replaces e by the exp which loads top, ie. does nothing.
 **********************************************************************/

static void
repbycont(exp e, bool has_label, exp scope)
{
	exp n = getexp(f_top, bro(e), (int)(last(e)), nilexp, nilexp, 0, 0,
		       top_tag);
	if (has_label) {
		no(son(pt(e)))--;
		pt(e) = nilexp;
	}
#ifdef NEWDIAGS
	dgf(n) = dgf(e);
#endif
	replace(e, n, e);
	kill_exp(e, e);
	if (scope !=e) {
		altered(n, scope);
	}
}


/**********************************************************************
   repbygo replaces e by a goto the label.
 **********************************************************************/

static void
repbygo(exp e, exp lab, exp scope)
{
	exp g = getexp(f_bottom, nilexp, 0, nilexp, lab, 0, 0, goto_tag);
	exp n = getexp(f_top, g, 1, nilexp, nilexp, 0, 0, top_tag);
	son(g) = n;
	++no(son(lab));
#ifdef NEWDIAGS
	dgf(g) = dgf(e);
#endif
	replace(e, g, e);
	kill_exp(e, e);
	if (scope !=e) {
		altered(g, scope);
	}
}


/**********************************************************************
   nos tests the exp t to see if it is a construction that can be
   eliminated from a sequence.  It is ignorable or has no side effect.
 **********************************************************************/
static int nos(exp t);

static int
noslist(exp tl)
{
	if (tl == nilexp) {
		return(1);
	}
	if (last(tl)) {
		return(nos(tl));
	}
	return(nos(tl) && noslist(bro(tl)));
}


static int
nos(exp t)
{
	unsigned char n = name(t);
	if (n == top_tag || n == ignorable_tag) {
		return(1);
	}
	if (n == compound_tag || n == nof_tag) {
		return noslist(son(t));
	}

	return((is_a(n) && optop(t) &&
		((n == name_tag && !islastuse(t)) || n == val_tag ||
		 noslist(son(t)))) || (n == ident_tag && !isenvoff(t) &&
				       nos(son(t)) && nos(bro(son(t)))));
}


/**********************************************************************
   check_seq carries out transformations on sequences.
   Statements with no effect are removed.
   Anything after an unconditional goto, or any other statement
   producing a bottom shape, is removed.

   No changes are propagated outside the exp "scope".
 **********************************************************************/
static int maxes[] = {0, 0, 0, 127, 255, 32767, 65535, (int)0x7fffffff,
	(int)0xffffffff};
static int mins[] = {0, 0, 0, -128, 0, -32768, 0, (int)0xffffffff, 0};
static shape *us_shape[] = {&f_bottom, &f_bottom, &f_top, &ucharsh, &ucharsh,
	&uwordsh, &uwordsh, &ulongsh, &ulongsh};

static exp
make_test(ntest nt, exp lab, exp arg1, exp arg2, unsigned char nm)
{
	exp r;
	r = getexp(f_top, nilexp, 0, arg1, lab, 0, 0, nm);
	fno(r) = (float)0.5;
	settest_number(r, (int)nt);
	setbro(arg1, arg2);
	clearlast(arg1);
	++no(son(lab));
	setfather(r, arg2);
	return r;
}


static int
simple(exp e)
{
	if (name(e) == cont_tag && name(son(e)) == name_tag) {
		return 1;
	}
	if (name(e) == cont_tag && name(son(e)) == cont_tag &&
	    name(son(son(e))) == name_tag) {
		return 1;
	}
	if (name(e) == cont_tag && name(son(e)) == reff_tag &&
	    name(son(son(e))) == cont_tag &&
	    name(son(son(son(e)))) == name_tag) {
		return 1;
	}
	if (name(e) == name_tag && !isvar(son(e))) {
		return 1;
	}
	return 0;
}


static exp
tests_to_bounds(exp a, exp b)
{
	exp x = son(a);
	int na = no(bro(x));
	int nb = no(bro(son(b)));
	int ntemp;
	ntest nta = test_number(a);
	ntest ntb = test_number(b);
	ntest nttemp;
	exp lab = pt(a);
	shape sha = sh(x);

	if (simple(x)) {
		return nilexp;
	}

	if (nta == f_greater_than) {
		if (na == maxes[name(sha)]) {
			return nilexp;
		}
		nta = f_greater_than_or_equal;
		++na;
	}
	if (ntb == f_greater_than) {
		if (nb == maxes[name(sha)]) {
			return nilexp;
		}
		ntb = f_greater_than_or_equal;
		++nb;
	}
	if (ntb == f_greater_than_or_equal) {
		ntemp = na;
		na = nb;
		nb = ntemp;
		nttemp = nta;
		nta = ntb;
		ntb = nttemp;
	}
	if (nta != f_greater_than_or_equal) {
		return nilexp;
	}
	if (ntb != f_less_than_or_equal && ntb != f_less_than) {
		return nilexp;
	}

	if (ntb == f_less_than) {
		if (nb == mins[name(sha)]) {
			return nilexp;
		}
		ntb = f_less_than_or_equal;
		--nb;
	}

	UNUSED(ntb);

	if (is_signed(sha)) {
		if (nb < na) {
			return nilexp;
		}
	} else {
		if ((unsigned int)nb < (unsigned int)na) {
			return nilexp;
		}
	}
	no(son(lab)) -= 1; /* one is removed by kill_exp below */
	if (na == nb) {
		kill_exp(b, b);
		return make_test(f_equal, lab, x, me_shint(sha, na), test_tag);
	}
	{
		exp s = hold_check(me_b2(x, me_shint(sha, na), minus_tag));
		exp n = me_shint(sha, nb -na);
		shape new_sha = *us_shape[name(sha)];
		sh(s) = new_sha;
		sh(n) = new_sha;
		kill_exp(b, b);
		return make_test(f_less_than_or_equal, lab, s, n, test_tag);
	}
}


static int
check_seq(exp e, exp scope)
{
	exp z = son(e);
	exp t, k, kk;
	int changed = 0;

	if (name(sh(bro(son(e)))) == bothd && name(sh(e)) != bothd) {
		sh(e) = f_bottom;
		changed = 1;
	}

	while (name(sh(son(z))) == bothd || nos(son(z))) {
		if (name(sh(son(z))) == bothd) {
			if (!last(son(z))) {
				kk = bro(son(z));
				while (kk != nilexp) {
					k = kk;
					if (!last(k)) {
						kk = bro(k);
					} else {
						kk = nilexp;
					}
#ifdef NEWDIAGS
					dg_dead_code(k, son(z));
#endif
					kill_exp(k, k);
				}
			}
#ifdef NEWDIAGS
			if (diagnose) {
				dg_dead_code(bro(z), son(z));
				dg_whole_comp(e, son(z));
			}
#endif
			/* kill dead variable refs */
			kill_exp(bro(z), bro(z));

			/* before replace */
			setfather(e, z);
			replace(e, son(z), scope);
			retcell(z);
			retcell(e);
			return(1);
		}
		if (last(son(z))) {
#ifdef NEWDIAGS
			if (diagnose) {
				dg_rdnd_code(son(z), bro(z));
				dg_whole_comp(e, bro(z));
			}
#endif
			replace(e, bro(z), scope);
			kill_exp(son(z), son(z));
			retcell(z);
			retcell(e);
			return(1);
		}
#ifdef NEWDIAGS
		if (diagnose) {
			dg_rdnd_code(son(z), bro(son(z)));
		}
#endif
		k = son(z);
		son(z) = bro(son(z));
		kill_exp(k, k);
	}
	t = son(z);
	for (;;) {
		if (name(t) == test_tag && name(bro(son(t))) == val_tag &&
		    !isbigval(bro(son(t))) && name(sh(son(t))) <= ulonghd) {
			exp b;
			exp bnds;
			exp * ref;
			if (last(t)) {
				b = bro(bro(t));
				if (name(b) == test_tag &&
				    name(bro(son(b))) == val_tag &&
				    !isbigval(bro(son(b))) && pt(t) == pt(b) &&
				    eq_exp(son(t), son(b))) {
					bnds = tests_to_bounds(t, b);
					if (bnds == nilexp) {
						if (changed) {
							altered(e, scope);
						}
						return 0;
					}
					if (t == son(z)) {
#ifdef NEWDIAGS
						if (diagnose) {
							dg_whole_comp(e, bnds);
						}
#endif
						replace(e, bnds, scope);
						retcell(e);
						return 1;
					}
					ref = refto(father(t), t);
					bro(*ref) = bro(t);
					setlast(*ref);
					setlast(bnds);
					bro(bnds) = e;
					bro(z) = bnds;
					return 0;
				} else {
					if (changed) {
						altered(e, scope);
					}
					return 0;
				}
			}
			b = bro(t);
			if (name(b) == test_tag &&
			    name(bro(son(b))) == val_tag &&
			    !isbigval(bro(son(b))) && pt(t) == pt(b) &&
			    eq_exp(son(t), son(b))) {
				exp brob = bro(b);
				int lb = last(b);
				ref = refto(father(t), t);
				bnds = tests_to_bounds(t, b);
				if (bnds != nilexp) {
					bro(bnds) = brob;
					if (lb) {
						setlast(bnds);
					} else {
						clearlast(bnds);
					}
					*ref = bnds;
					t = bnds;
				}
			}
		}

		if (last(t)) {
			if (changed) {
				altered(e, scope);
			}
			return 0;
		}
		if (name(sh(bro(t))) == bothd) {
			if (!last(bro(t))) {
				kk = bro(bro(t));
				while (kk != nilexp) {
					k = kk;
					if (!last(k)) {
						kk = bro(k);
					} else {
						kk = nilexp;
					}
#ifdef NEWDIAGS
					if (diagnose) {
						dg_dead_code(k, bro(t));
					}
#endif
					kill_exp(k, k);
				}
			}
#ifdef NEWDIAGS
			if (diagnose) {
				dg_dead_code(bro(z), bro(t));
			}
#endif
			kill_exp(bro(z), bro(z));
			bro(z) = bro(t);
			setlast(bro(z));
			bro(bro(z)) = e;
			setlast(t);
			bro(t) = z;
			sh(e) = f_bottom;
			altered(e, scope);
			return 0;
		}
		if (nos(bro(t))) {
			if (last(bro(t))) {
#ifdef NEWDIAGS
				if (diagnose) {
					dg_rdnd_code(bro(t), bro(z));
				}
#endif
				kill_exp(bro(t), bro(t));
				setlast(t);
				bro(t) = z;
				return 0;
			}
			k = bro(t);
			bro(t) = bro(bro(t));
#ifdef NEWDIAGS
			if (diagnose) {
				dg_rdnd_code(k, bro(t));
			}
#endif
			kill_exp(k, k);
			changed = 1;
		} else {
			t = bro(t);
		}
	}
	/* UNREACHED */
}


/**********************************************************************

   comm_ass applies the commutative and associative laws to replace e
   by an improved version. op_tag is the operation involved. If
   the errtreat is not ignore or impossible, no change is made. C
   programs will always use ignore or impossible.

   All the arguments of sub-operations with the same op_tag (they will
   anyway have the same shape) are flattened into one argument list,
   provided that dive is 1.

   All the constants are combined into one, which is placed as the last
   constant. The parameter "one" is the unit for the given operation
   (0 for + , 1 for * , allones for and, 0 for or, 0 for xor) and this
   constant is eliminated. If the operation has a zero, "has_zero" is
   set and "zero" is the constant (0 for * , 0 for and, allones for or).

   No changes are propagated outside the exp "scope".

   If isreal is 1 the operation has real arguments and results, otherwise
   integer.

   fn(a, b) is applicable to exps defining constants of the correct type
   (integer or real) and delivers an exp defining a constant which is
   the result of the op_tag applied to these constants.


 **********************************************************************/
static int f_one(flpt f);
static int seq_distr(exp e, exp scope);

static int
comm_ass(exp e, unsigned char op_tag, void (*fn)(exp, exp, int), int one,
	 int has_zero, int zero, exp scope, int dive, int isreal)
{
	exp t = son(e);	/* starting element */
	int changed = last(t);
	exp cst;		/* start the accumulated constant */
	exp cst_u = nilexp;	/* holds exp representing one if created here */
	int looping;

	if (isreal) {
		cst = getexp(sh(e), nilexp, 0, nilexp, nilexp, 0, one,
			     real_tag);
	} else {
		cst = me_shint(sh(e), one);
		if (one == -1 && shape_size(sh(e)) == 64) {
			flpt f = new_flpt();
			flt *fp = &flptnos[f];
			int i;
			fp->sign = 1;
			fp->exp = 3;
			for (i = 0; i < 4; ++i) {
				fp->mant[i] = 65535;
			}
			no(cst) = f;
			setbigval(cst);
			cst_u = cst;
		}
	}

	if (!optop(e)) {
		return 0;
	}
	do {
		/* look to see if a change will be made */
		if ((name(t) == op_tag && optop(t)) || name(t) == val_tag ||
		    name(t) == real_tag) {
			changed = 1;
		}
		looping = !last(t);
		t = bro(t);
	} while (looping);

	if (changed) {
		/* continue if there will be a change */
		exp p, q;
		t = son(e);	/* start */
		q = getexp(sh(e), nilexp, 0, nilexp, nilexp, 0, 0, op_tag);
		seterrhandle(q, errhandle(e));
		/* start the result */
		p = q;
		/* p is used to point to the current place where the next item
		 * will be added (as bro). */
		do {
			while (name(t) == op_tag && optop(t) && dive) {
				t = son(t);	/* dive down same operator */
			}
			if (name(t) == val_tag || name(t) == real_tag) {
				/* accumulate constant value */
				fn (cst, t, errhandle(e));
#ifdef NEWDIAGS
				if (diagnose) {
					dg_detach_const(t, cst);
				}
#endif
			} else {
				/* add item at p and move p on */
				bro(p) = t;
				clearlast(p);
				p = bro(p);
			}
			while (last(t) && bro(t) != e) {
				/* ascend from sub-item */
				t = bro(t);
			}
		} while ((last(t)) ? 0 : (t = bro(t), 1));
		/* put q into correct form (we were using its bro) */
		son(q) = bro(q);

		if (p == q) {
			/* no items but constant */
			retcell(q);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, cst);
			}
#endif
			replace(e, cst, scope);
			retcell(e);
			return(1);
		}

		if (has_zero &&
		    ((!isreal && no(cst) == zero && !isbigval(cst)) ||
		     (isreal && flptnos[no(cst)].sign == 0))) {
			/* zero constant. Replace by a sequence of expressions
			 * delivering the zero, so as to keep side effects */
			exp r;
			setname(q, 0);		/* use q a seq holder */
			son(q) = bro(q);
			bro(p) = q;
			setlast(p);
			clearlast(q);
			bro(q) = cst;
			r = getexp(sh(e), nilexp, 0, q, nilexp, 0, 0, seq_tag);
#ifdef NEWDIAGS
			if (diagnose) {
				dgf(r) = dgf(e);
			}
#endif
			replace(e, hc(r, cst), scope);
			return(1);
		}

		if ((!isreal &&
		     (no(cst) != one || (isbigval(cst) && cst != cst_u))) ||
		    (isreal && cmpflpt(no(cst), one, 6))) {
			/* form result if there is a non-unit constant term */
			bro(p) = cst;
			clearlast(p);
			p = bro(p);
			son(q) = bro(q);
			bro(p) = q;
			setlast(p);
			sh(q) = sh(e);
#ifdef NEWDIAGS
			if (diagnose) {
				dgf(q) = dgf(e);
			}
#endif
			replace(e, q, scope);
			retcell(e);
			return(1);
		}

#ifdef NEWDIAGS
		if (diagnose) {
			dgf(e) = combine_diaginfo(dgf(e), dgf(cst));
		}
#endif
		retcell(cst);   /* there are no constants other than unit*/

		if (son(q) == p) {
			/* form result if single item and no constant */
			sh(p) = sh(e);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, p);
			}
#endif
			replace(e, hold_check(p), scope);
			retcell(e);
			return(1);
		}

		/* form result if no constant and more than one arg */
		bro(p) = q;

		setlast(p);
		sh(q) = sh(e);
#ifdef NEWDIAGS
		if (diagnose) {
			dg_whole_comp(e, q);
		}
#endif
		replace(e, q, scope);
		retcell(e);
		return(1);
	}

	return 0;	/* return from here if no change made */
}


/* dochvar takes the int, i, and delivers the number which results from
 * changing its variety to that specified by the shape, t. */

int
dochvar(int i, shape t)
{
	if (name(t) == bitfhd) {
		int m = masks[shape_size(t)];
		int x = i & m;
		if (is_signed(t)) {
			int sm = ((m + 1) >> 1) & x;
			x -= (sm << 1);
		}
		return x;
	}
	switch (shape_size(t)) {
	case 8:
		if (is_signed(t)) {
			int x = i & 0xff;
			if (x & 128) {
				return(i | (~0xff));
			}
			return(i & 0xff);
		} else {
			return(i & 0xff);
		}
	case 16:
		if (is_signed(t)) {
			int x = i & 0xffff;
			if (x & 32768) {
				return(i | (~0xffff));
			}
			return(i & 0xffff);
		} else {
			return(i & 0xffff);
		}
	case 32:
		if (is_signed(t)) {
			int x = i & (int)0xffffffff;
			if (x & (int)0x80000000)
				return(i | (~(int)0xffffffff));
			return(i & (int)0xffffffff);
		} else {
			return(i & (int)0xffffffff);
		}
	case 64:
		return(i);
	default:
		return(i & masks[shape_size(t)]);
	}
}


static void
dochvar_f(flt64 *xa, shape sha)
{
	if (shape_size(sha) == 64) {
		return;
	}
	*xa = int_to_f64(dochvar((int)xa->small, sha), is_signed(sha));
	return;
}


static void
bigres(exp a, flt64 *xp)
{
	int bg;
	dochvar_f(xp, sh(a));
	no(a) = f64_to_flpt(*xp, is_signed(sh(a)), &bg, shape_size(sh(a)));
	if (bg) {
		setbigval(a);
	} else {
		clearbigval(a);
	}
	return;
}


static int
check_size(flt64 a, int sg, int sz)
{
	int t = (int)a.small;
	if (sz > 32) {
		return 0;
	}

	if (sg && (t >> 31) == a.big &&
	    (sz == 32 || (t >> (sz - 1)) == a.big)) {
		return 0;
	}

	if (!sg && a.big == 0 && (sz == 32 || (t >> sz) == 0)) {
		return 0;
	}
	return 1;
}


/* used as a fn parameter for comm_ass q.v. */

static void
fplus_fn(exp ap, exp b, int et)
{
	int a = no(ap);
	int nob = no(b);
	flt resval;
	int status;
	UNUSED(et);

	status = flt_add(flptnos[a], flptnos[nob], &resval);
	if (status == OKAY) {
		flpt_round((int)f_to_nearest,
			   flpt_bits((floating_variety)(name(sh(b)) -
							shrealhd)), &resval);
		flptnos[nob] = resval;
		no(ap) = nob;
	} else {
		failer(ILLEGAL_FLADD);
	}
	return;
}


/* used as a fn parameter for comm_ass q.v. */

static void
fmult_fn(exp ap, exp b, int et)
{
	int a = no(ap);
	int nob = no(b);
	flt resval;
	int status;
	UNUSED(et);

	status = flt_mul(flptnos[a], flptnos[nob], &resval);
	if (status == OKAY) {
		flpt_round((int)f_to_nearest,
			   flpt_bits((floating_variety)(name(sh(b)) -
							shrealhd)), &resval);
		flptnos[nob] = resval;
		no(ap) = nob;
	} else {
		failer(ILLEGAL_FLMULT);
	}
	return;
}


/* auxiliary function used for comm_ass by plus */

static void
plus_fn(exp ap, exp b, int et)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_add(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */
	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	if (et != f_wrap.err_code &&
	    (ov || constovf(b) || check_size(x, sg, shape_size(sh(ap))))) {
		setconstovf(ap);
	}

	/* if (extra_checks && sg && !in_proc_def &&
	    (ov || (shape_size(sh(ap)) <= 32 && check_size(x, sg, 32)))) {
	    failer(ADD_OUT_OF_BOUNDS);
	    exit(EXIT_FAILURE);
	    };
	 */
	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
	return;
}


/* subtract constant from constant */

static void
minus_fn(exp ap, exp b, int et)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_sub(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */
	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	if (et != f_wrap.err_code &&
	    (ov || constovf(b) || check_size(x, sg, shape_size(sh(ap))))) {
		setconstovf(ap);
	}

	/* if (extra_checks && sg && !in_proc_def &&
	    (ov || (shape_size(sh(ap)) <= 32 && check_size(x, sg, 32)))) {
	    failer(ADD_OUT_OF_BOUNDS);
	    exit(EXIT_FAILURE);
	    };
	 */
	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
	return;
}


/* negate a constant exp, b, producing int */

static void
neg_fn(exp b)
{
	flt64 x;
	x = exp_to_f64(b);
	x.big = ~x.big;
	x.small = ~x.small;
	if (x.small == (unsigned int)0xffffffff) {
		++x.big;
	}
	++x.small;
	bigres(b, &x);
	return;
}


/* negate a constant exp, b, producing int */

static void
not_fn(exp b)
{
	flt64 x;
	x = exp_to_f64(b);
	x.big = ~x.big;
	x.small = ~x.small;
	bigres(b, &x);
	return;
}


/* auxiliary function used for comm_ass by mult */

static void
mult_fn(exp ap, exp b, int et)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_mul(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */
	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	if (et != f_wrap.err_code &&
	    (ov || constovf(b) || check_size(x, sg, shape_size(sh(ap))))) {
		setconstovf(ap);
	}

	if (sg && extra_checks &&
	    (ov || (shape_size(sh(ap)) <= 32 && check_size(x, sg, 32)))) {
		failer(MULT_OUT_OF_BOUNDS);
		exit(EXIT_FAILURE);
	}

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
	return;
}


/* auxiliary function used for comm_ass by and */

static void
and_fn(exp ap, exp b, int et)
{
	flt64 xa, xb;
	UNUSED(et);
	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	xa.small &= xb.small;
	xa.big &= xb.big;
	bigres(ap, &xa);
	return;
}


/* auxiliary function used for comm_ass by or */

static void
or_fn(exp ap, exp b, int et)
{
	flt64 xa, xb;
	UNUSED(et);
	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	xa.small |= xb.small;
	xa.big |= xb.big;
	bigres(ap, &xa);
	return;
}


/* auxiliary function used for comm_ass by xor */

static void
xor_fn(exp ap, exp b, int et)
{
	flt64 xa, xb;
	UNUSED(et);
	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	xa.small ^= xb.small;
	xa.big ^= xb.big;
	bigres(ap, &xa);
	return;
}


/* not used for comm_ass */

static void
domaxmin(exp ap, exp b, int mx)
{
	flt64 xa, xb;
	int use_a;
	xa = exp_to_f64(ap);
	xb = exp_to_f64(b);
	if (is_signed(sh(ap))) {
		if (xa.big > xb.big) {
			use_a = mx;
		}
		if (xa.big < xb.big) {
			use_a = !mx;
		}
		if (xa.big == xb.big) {
			if (xa.small >= xb.small) {
				use_a = mx;
			} else {
				use_a = !mx;
			}
		}
	} else {
		if ((unsigned int)xa.big > (unsigned int)xb.big) {
			use_a = mx;
		}
		if ((unsigned int)xa.big < (unsigned int)xb.big) {
			use_a = !mx;
		}
		if (xa.big == xb.big) {
			if (xa.small >= xb.small) {
				use_a = mx;
			} else {
				use_a = !mx;
			}
		}
	}
	SET(use_a);
	if (use_a) {
		bigres(ap, &xa);
	} else {
		bigres(ap, &xb);
	}
	return;
}


/* produce allones for integer length of shape of e. */

static int
all_ones(exp e)
{
	switch (shape_size(sh(e))) {
	case 8:
		return(0xff);
	case 16:
		return(0xffff);
	default:
		return(0xffffffff);
	}
}


/* obey div1 on constants */

static void
dodiv1(exp ap, exp b)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_div(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */
	IGNORE flpt_round_to_integer((int)f_toward_smaller, &resval);
	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
	return;
}


/* obey div2 on constants */

static void
dodiv2(exp ap, exp b)
{
	flt64 x;
	flpt fa, fb;
	int sg = is_signed(sh(ap));
	flt resval;
	int ov;

	fa = f64_to_flt(exp_to_f64(ap), sg);
	fb = f64_to_flt(exp_to_f64(b), sg);
	IGNORE flt_div(flptnos[fa], flptnos[fb], &resval);
	/* status cannot be wrong */

	IGNORE flpt_round_to_integer((int)f_toward_zero, &resval);

	flptnos[fa] = resval;
	x = flt_to_f64(fa, sg, &ov);

	flpt_ret(fa);
	flpt_ret(fb);

	bigres(ap, &x);
	return;
}


/* obey mod on constants */

static void
domod(exp ap, exp b)
{
	exp top = copy(ap);

	dodiv1(top, b);
	mult_fn(b, top, f_wrap.err_code);
	neg_fn(b);
	plus_fn(ap, b, f_wrap.err_code);
	return;
}


/* obey rem2 on constants */

static void
dorem2(exp ap, exp b)
{
	exp top = copy(ap);

	dodiv2(top, b);
	mult_fn(b, top, f_wrap.err_code);
	neg_fn(b);
	plus_fn(ap, b, f_wrap.err_code);
	return;
}


/* obey shift (places signed) on constants */

static void
doshl(exp e)
{
	flt64 x;
	exp arg1 = son(e);
	exp arg2 = bro(arg1);
	int pl = no(arg2);
	shape sha = sh(e);
	int sg = is_signed(sha);

	sh(arg1) = sh(e);

	x = exp_to_f64(arg1);

	if (name(e) == shl_tag) {
		/* shift left */
		if (isbigval(arg2) || pl >= shape_size(sha)) {
			no(arg1) = 0;
			clearbigval(arg1);
			return;
		}
		if (pl >= 32) {
			x.big = (int)(x.small << (pl - 32));
			x.small = 0;
		} else {
			x.big <<= pl;
			x.big |= (int)(x.small >> (32 - pl));
			x.small <<= pl;
		}
	} else {
		/* shift right */
		if (isbigval(arg2) || pl >= shape_size(sha)) {
			no(arg1) = 0;
			if (sg) {
				if (isbigval(arg1)) {
					if (flptnos[no(arg1)].sign == -1) {
						no(arg1) = -1;
					}
				} else if (no(arg1) < 0) {
						no(arg1) = -1;
				}
			}
			clearbigval(arg1);
			return;
		}
		if (pl >= 32) {
			if (sg) {
				x.small = (unsigned int)(x.big >> (pl - 32));
				x.big = x.big >> 31;
			} else {
				x.small = ((unsigned int)x.big) >> (pl - 32);
				x.big = 0;
			}
		} else {
			if (sg) {
				x.small >>= pl;
				x.small |= (unsigned int)(x.big << (32 - pl));
				x.big >>= pl;
			} else {
				x.small >>= pl;
				x.small |= (unsigned int)(x.big << (32 - pl));
				x.big = (int)(((unsigned int)x.big) >> pl);
			}
		}
	}
	bigres(arg1, &x);
	return;
}


#if has_setcc

 /* included if target has a setcc operation, to set a bit from the
    condition flags */

static exp
absbool(exp id)
{
	/* check if e is (let a = 0 in cond(test(L) = result; a = 1 | L:top); a)
	   If so, return the test, otherwise nilexp. */
	if (isvar(id) && name(son(id)) == val_tag && no(son(id)) == 0 &&
	    !isbigval(son(id)) && no(id) == 2) {
		/* name initially 0 only used twice */
		exp bdy = bro(son(id));
		if (name(bdy) == seq_tag && name(bro(son(bdy))) == cont_tag &&
		    name(son(bro(son(bdy)))) == name_tag &&
		    son(son(bro(son(bdy)))) == id) {
			/* one use is result of sequence body */
			exp c = son(son(bdy));
#ifndef NEWDIAGS
			if (name(c) == diagnose_tag) {
				c = son(c);
			}
#endif
			if (last(c) && name(c) == cond_tag) {
				/* seq is cond=c; id */
				exp first = son(c);
				exp second = bro(son(c));
				/* only one jump to else */
				if (no(son(second)) == 1 &&
				    name(bro(son(second))) == top_tag &&
				    name(first) == seq_tag) {
					/* cond is (seq = first | L: top) */
					exp s = son(son(first));
					exp r = bro(son(first));
					/* last of seq is id = 1 */
					/* start of seq is int test jumping to
					 * second */
					if (name(r) == ass_tag &&
					    name(son(r)) == name_tag &&
					    son(son(r)) == id &&
					    name(bro(son(r))) == val_tag &&
					    !isbigval(bro(son(r))) &&
					    no(bro(son(r))) == 1 &&
					    last(s) && name(s) == test_tag &&
					    pt(s) == second) {
						return s;
					}
				} /* cond is (seq= first | L: top) */
			} /* seq is cond=c; id */
			if (last(c) && name(c) == condassign_tag) {
				/* seq is condassign = c; id */
				exp s = son(c);
				exp r = bro(s);
				/* last of seq is id = 1 */
				if (name(son(r)) == name_tag &&
				    son(son(r)) == id &&
				    name(bro(son(r))) == val_tag &&
				    !isbigval(bro(son(r))) &&
				    no(bro(son(r))) == 1) {
					return s;
				}
			} /* seq is condassign = c; id */
		} /* one use is result of sequence body */
	} /* name initially 0 only used twice */
	return nilexp;
}
#endif


 /* distributes the operation e into a sequence, ie if e = op(seq(d ...;
    c), a) produces seq(d...; op(c, a)) */
static int
seq_distr(exp e, exp scope)
{
	exp x = son(e);
	exp y;
	if (last(x) || (!last(x) && last(bro(x)))) {
		if (name(x) == seq_tag || name(x) == ident_tag) {
			exp b = bro(son(x));
			exp r;
			if (name(x) == ident_tag) {
				clearinlined(x);
			}
			if (last(x)) {
				r = me_u3(sh(e), copy(b), name(e));
			} else {
#ifdef NEWDIAGS
				if (diagnose) {
					dg_restruct_code(x, bro(x), +1);
				}
#endif
				r = me_b3(sh(e), copy(b), bro(x), name(e));
			}
			pt(r) = pt(e);
			no(r) = no(e);
			props(r) = props(e);
			r = hold_check(r);
			sh(x) = sh(e);
			replace(b, r, r);	/* dgf preserved in copy */
			kill_exp(b, b);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, x);
			}
#endif
			replace(e, x, scope);
			return 1;
		}
	}
	if (!last(x) && last(bro(x))) {
		y = bro(x);
		if (name(y) == seq_tag || name(y) == ident_tag) {
			exp b = bro(son(y));
			exp r;
			if (name(y) == ident_tag) {
				clearinlined(y);
			}
#ifdef NEWDIAGS
			if (diagnose) {
				dg_restruct_code(y, x, -1);
			}
#endif
			r = me_b3(sh(e), x, copy(b), name(e));
			pt(r) = pt(e);
			no(r) = no(e);
			props(r) = props(e);
			r = hold_check(r);
			sh(y) = sh(e);
			replace(b, r, r);		/* dgf preserved in copy */
			kill_exp(b, b);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, y);
			}
#endif
			replace(e, y, scope);
			return 1;
		}
	}
	return 0;
}

 /* reverses (ie. nots) test numbers */
unsigned char revtest[6] = {
	4, 3, 2, 1, 6, 5
};


/* returns sign if |f|=1, otherwise 0 */

static int
f_one(flpt f)
{
	flt fconst;
	fconst = flptnos[f];

	if (fconst.mant[0] == 1 && fconst.exp == 0) {
		int i = 1;
		while (i < MANT_SIZE && fconst.mant[i] == 0) {
			++i;
		}
		if (i == MANT_SIZE) {
			return(fconst.sign);
		} else {
			return(0);
		}
	} else {
		return(0);
	}
}


/* applies fneg */

static exp
fneg(exp e)
{
	exp n = getexp(sh(e), nilexp, 0, e, nilexp, 0, 0, fneg_tag);
	setlast(e);
	bro(e) = n;
	return(n);
}


/* applies binary floating point operations */

static int
check_fp2(exp e, exp scope)
{
	exp a1 = son(e);
	exp a2 = bro(a1);
	flpt f1, f2;
	flt resval;
	int status;

	if (name(a1) == real_tag && name(a2) == real_tag) {
		/* this will condense to a single constant */
		f1 = no(a1);
		f2 = no(a2);

		switch (name(e))EXHAUSTIVE {
		case fplus_tag:
			status = flt_add(flptnos[f1], flptnos[f2], &resval);
			break;

		case fminus_tag:
			status = flt_sub(flptnos[f1], flptnos[f2], &resval);
			break;

		case fmult_tag:
			status = flt_mul(flptnos[f1], flptnos[f2], &resval);
			break;

		case fdiv_tag:
			status = flt_div(flptnos[f1], flptnos[f2], &resval);
			break;
		}

		if (status == OKAY) {
			flpt_round((int)f_to_nearest,
				   flpt_bits((floating_variety)(name(sh(e)) -
								shrealhd)),
				   &resval);
			flptnos[f1] = resval;
			flpt_ret(f2);
			replace(e, a1, scope);
			retcell(e);
			retcell(a2);
			return(1);
		} else {
			return(0);
		}
	} else {
		/* see if one arg is constant */
		exp v_arg, c_arg;

		if (name(a1) == real_tag) {
			f1 = no(a1);
			c_arg = a1;
			v_arg = a2;
		} else if (name(a2) == real_tag) {
			f1 = no(a2);
			c_arg = a2;
			v_arg = a1;
		} else {
			return (0);	/* no change possible */
		}

		switch (name(e)) {
		case fplus_tag:
			if (flptnos[f1].sign == 0) {
				/* x + 0 or 0 + x */
				flpt_ret(f1);
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return(1);
			} else {
				return(0);
			}

		case fminus_tag:
			if (flptnos[f1].sign == 0) {
				/* x - 0 or 0 - x */
				flpt_ret(f1);
				if (v_arg == a2) {
					/* 0 - x = -x */
					v_arg = fneg(v_arg);
				}
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return(1);
			} else {
				return(0);
			}

		case fmult_tag:
			if (flptnos[f1].sign == 0) {
				/* x * 0 or 0 * x */
				replace(e, c_arg, scope);
				retcell(e);
				kill_exp(v_arg, scope);
				return(1);
			} else {
				int u = f_one(f1);
				if (u == 0) {
					return(0);
				}
				/* x * 1 or x * (-1) or 1 * x or (-1) * x */
				if (u == -1) {
					v_arg = fneg(v_arg);
				}
				flpt_ret(f1);
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return(1);
			}

		case fdiv_tag:
			if (flptnos[f1].sign == 0 && v_arg == a2) {
				/* 0 / x */
				replace(e, c_arg, scope);
				retcell(e);
				kill_exp(v_arg, scope);
				return(1);
			} else {
				int u = f_one(f1);
				if (u == 0 || v_arg == a2) {
					return(0);
				}
				/* x / 1 or x / (-1) */
				if (u == -1) {
					v_arg = fneg(v_arg);
				}
				flpt_ret(f1);
				replace(e, v_arg, scope);
				retcell(e);
				retcell(c_arg);
				return(1);
			}
		}
	}
	return(0);
}


/* compares integer constants using the test given by test_no */

static int
docmp(shape sha, unsigned char test_no, int c1, int c2)
{
	int c;
	switch (shape_size(sha))EXHAUSTIVE {
	case 8:
		if (is_signed(sha)) {
			int d1 = (c1 & 0x80) ? (c1 | ~0x7f) : (c1 & 0xff);
			int d2 = (c2 & 0x80) ? (c2 | ~0x7f) : (c2 & 0xff);
			switch (test_no)EXHAUSTIVE {
			case 1:
				c = (d1 > d2);
				break;
			case 2:
				c = (d1 >= d2);
				break;
			case 3:
				c = (d1 < d2);
				break;
			case 4:
				c = (d1 <= d2);
				break;
			case 5:
				c = (d1 == d2);
				break;
			case 6:
				c = (d1 != d2);
				break;
			}
			break;
		} else {
			unsigned char d1 = (unsigned char)(c1 & 0xff);
			unsigned char d2 = (unsigned char)(c2 & 0xff);
			switch (test_no)EXHAUSTIVE {
			case 1:
				c = (d1 > d2);
				break;
			case 2:
				c = (d1 >= d2);
				break;
			case 3:
				c = (d1 < d2);
				break;
			case 4:
				c = (d1 <= d2);
				break;
			case 5:
				c = (d1 == d2);
				break;
			case 6:
				c = (d1 != d2);
				break;
			}
			break;
		}
	case 16:
		if (is_signed(sha)) {
			int d1 = (c1 & 0x8000) ? (c1 | ~0x7fff) : (c1 & 0xffff);
			int d2 = (c2 & 0x8000) ? (c2 | ~0x7fff) : (c2 & 0xffff);
			switch (test_no)EXHAUSTIVE {
			case 1:
				c = (d1 > d2);
				break;
			case 2:
				c = (d1 >= d2);
				break;
			case 3:
				c = (d1 < d2);
				break;
			case 4:
				c = (d1 <= d2);
				break;
			case 5:
				c = (d1 == d2);
				break;
			case 6:
				c = (d1 != d2);
				break;
			}
			break;
		} else {
			unsigned short d1 = (unsigned short)(c1 & 0xffff);
			unsigned short d2 = (unsigned short)(c2 & 0xffff);
			switch (test_no)EXHAUSTIVE {
			case 1:
				c = (d1 > d2);
				break;
			case 2:
				c = (d1 >= d2);
				break;
			case 3:
				c = (d1 < d2);
				break;
			case 4:
				c = (d1 <= d2);
				break;
			case 5:
				c = (d1 == d2);
				break;
			case 6:
				c = (d1 != d2);
				break;
			}
			break;
		}
	case 32:
		if (is_signed(sha)) {
			int d1 = c1;
			int d2 = c2;
			switch (test_no)EXHAUSTIVE {
			case 1:
				c = (d1 > d2);
				break;
			case 2:
				c = (d1 >= d2);
				break;
			case 3:
				c = (d1 < d2);
				break;
			case 4:
				c = (d1 <= d2);
				break;
			case 5:
				c = (d1 == d2);
				break;
			case 6:
				c = (d1 != d2);
				break;
			}
			break;
		} else {
			unsigned int d1 = (unsigned int)c1;
			unsigned int d2 = (unsigned int)c2;
			switch (test_no)EXHAUSTIVE {
			case 1:
				c = (d1 > d2);
				break;
			case 2:
				c = (d1 >= d2);
				break;
			case 3:
				c = (d1 < d2);
				break;
			case 4:
				c = (d1 <= d2);
				break;
			case 5:
				c = (d1 == d2);
				break;
			case 6:
				c = (d1 != d2);
				break;
			}
			break;
		}
	}
	return(c);
}


int
docmp_f(int test_no, exp a, exp b)
{
	shape sha = sh(a);
	flt64 xa, xb;
	int sg = is_signed(sha);
	int eq = 0;
	int less = 0;
	int gr = 0;
	int c;

	if (shape_size(sh(a)) <= 32) {
		return docmp(sha, (unsigned char)test_no, no(a), no(b));
	}

	xa = exp_to_f64(a);
	xb = exp_to_f64(b);

	if (xa.big == xb.big && xa.small == xb.small) {
		eq = 1;
	}

	if (sg && !eq) {
		if (xa.big < xb.big) {
			less = 1;
		} else if (xa.big > xb.big) {
			gr = 1;
		} else {
			if (xa.small < xb.small) {
				less = 1;
			} else {
				gr = 1;
			}
		}
	} else if (!eq) {
		if ((unsigned int)xa.big < (unsigned int)xb.big) {
			less = 1;
		} else if ((unsigned int)xa.big > (unsigned int)xb.big) {
			gr = 1;
		} else {
			if (xa.small < xb.small) {
				less = 1;
			} else {
				gr = 1;
			}
		}
	}

	switch (test_no)EXHAUSTIVE {
	case 1:
		c = gr;
		break;
	case 2:
		c = gr | eq;
		break;
	case 3:
		c = less;
		break;
	case 4:
		c = less | eq;
		break;
	case 5:
		c = eq;
		break;
	case 6:
		c = !eq;
		break;
	}
	return c;
}


/* main bottom-to-top optimise routine Optimises e. No change propagates
   outside scope */

int
check(exp e, exp scope)
{
	if (is_a(name(e))) {
		/* main op non-side effect */
		unsigned char n = name(e);
		if (son(e) != nilexp && n != name_tag && n != env_offset_tag &&
		    n != general_env_offset_tag && n != proc_tag &&
		    n != general_proc_tag) {
			exp temp = son(e);
			while (1) {
				if (name(sh(temp)) == bothd) {
					/* unordered; temp can be first, iwc
					 * all siblings unreachable */
#ifdef NEWDIAGS
					if (diagnose) {
						exp sib = son(e);
						for (;;) {
							if (sib != temp) {
								dg_dead_code(sib, temp);
							}
							if (last(sib)) {
								break;
							}
							sib = bro(sib);
						}
						dg_whole_comp(e, temp);
					}
#endif
					replace(e, temp, scope);
					retcell(e);
					return 1;
				}
				if (last(temp)) {
					break;
				}
				temp = bro(temp);
			}
		}

		switch (name(e)) {
		case component_tag: {
				exp v = son(e);
				exp a = bro(v);

				if (name(a) == val_tag) {
					exp res;
					if (no(a) == 0 &&
					    shape_size(sh(v)) ==
					    shape_size(sh(e))
#if dont_unpad_apply
					    && name(v) != apply_tag
#endif
					   ) { /* remove the operation if the
						  offset is zero and the size
						  is the same. This typically
						  happens in selecting from a
						  union if the component has
						  the maximum size in the union
						*/
						sh(v) = sh(e);
#ifdef NEWDIAGS
						if (diagnose) {
							dg_whole_comp(e, v);
						}
#endif
						replace(e, v, scope);
						retcell(a);
						retcell(e);
						return 1;
					}

					/* otherwise use field_tag */

					res = getexp(sh(e), nilexp, 0, v,
						     nilexp, 0, no(a),
						     field_tag);
					setfather(res, son(res));
#ifdef NEWDIAGS
					dgf(res) = dgf(e);
#endif
					replace(e, hold_check(res), scope);
					retcell(e);
					retcell(a);
					return 1;
				}
				if (name(v) == cont_tag) {
					/* replace selecting from contents by
					 * taking contents of reff selection */
					exp ap = hold_check(f_add_to_ptr(son(v),
									 a));
					ap = hold_check(f_contents(sh(e), ap));
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(v, ap);
						dg_whole_comp(e, ap);
					}
#endif
					replace(e, ap, scope);
					retcell(v);
					retcell(e);
					return 1;
				}
				{ /* always remove component_tag: use a
				      declaration */
					exp var = me_startid(sh(e), v, 1);
					exp ap, c;
					exp ob;
					ob = me_obtain(var);
					ap = hold_check(f_add_to_ptr(ob, a));
					c = hold_check(f_contents(sh(e), ap));
					var = me_complete_id(var, c);
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, var);
					}
#endif
					replace(e, var, scope);
					retcell(e);
					return 1;
				}
			}

		case offset_pad_tag:
			if (name(son(e)) == val_tag && !isbigval(son(e))) {
				/* constant evaluation */
				int al = al2(sh(e));
				if (al == 0) {
					al = 1;
				}
				if (al2_of(sh(e))->al.sh_hd > nofhd) {
					al = shape_align(f_pointer(al2_of(sh(e))));
				}
#if ishppa
				if ((al1_of(sh(e))->al.al_val.al_frame & 4) != 0) {
					no(son(e)) = -rounder(-no(son(e)), al);
				} else

#endif
					no(son(e)) = rounder(no(son(e)), al);
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case offset_add_tag:
				if (name(son(e)) == val_tag &&
				    name(bro(son(e))) == val_tag &&
				    !isbigval(son(e)) &&
				    !isbigval(bro(son(e)))) {
					/* both arguments constant */
					int n;
					exp a = son(e);
					exp b = bro(a);

					n = no(a) + no(b);

					no(a) = n;
					sh(a) = sh(e);
					retcell(b);
					replace(e, a, scope);
					retcell(e);
					return(1);
				}
				return 0;

		case offset_subtract_tag:
				if (name(son(e)) == val_tag &&
				    name(bro(son(e))) == val_tag &&
				    !isbigval(son(e)) &&
				    !isbigval(bro(son(e)))) {
					/* both arguments constant */
					no(son(e)) -= no(bro(son(e)));
					sh(son(e)) = sh(e);
					retcell(bro(son(e)));
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				}
				return 0;

		case offset_negate_tag:
				if (name(son(e)) == val_tag &&
				    !isbigval(son(e))) {
					/* argument constant */
					no(son(e)) = - no(son(e));
					sh(son(e)) = sh(e);
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, son(e));
					}
#endif
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				};
				return 0;

		case offset_max_tag:
				if (name(son(e)) == val_tag &&
				    name(bro(son(e))) == val_tag &&
				    !isbigval(son(e)) &&
				    !isbigval(bro(son(e)))) {
					/* both arguments constant */
					int n1 = no(son(e));
					int n2 = no(bro(son(e)));
					no(son(e)) = (n1 > n2)? n1 : n2;
					sh(son(e)) = sh(e);
					retcell(bro(son(e)));
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				}
				return 0;

		case offset_mult_tag:
				if (name(son(e)) == val_tag &&
				    name(bro(son(e))) == val_tag &&
				    !isbigval(son(e)) &&
				    !isbigval(bro(son(e)))) {
					/* both arguments constant */
					int n1 = no(son(e));
					int n2 = no(bro(son(e)));
					no(son(e)) = n1 * n2;
					sh(son(e)) = sh(e);
					retcell(bro(son(e)));
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				}
				if (name(son(e)) == val_tag &&
				    !isbigval(son(e)) &&
				    no(son(e)) == 1) {
					/* multiply by 1 */
					sh(bro(son(e))) = sh(e);
					replace(e, bro(son(e)), scope);
					retcell(e);
					return(1);
				}
				if (name(son(e)) == val_tag &&
				    !isbigval(son(e)) && no(son(e)) == 0) {
					/* multiply by 0 - replace by sequence
					 * - side-effects!*/
					exp_list el;
					el.start = bro(son(e));
					el.end = bro(son(e));
					el.number = 1;
					sh(son(e)) = sh(e);
					replace(e, f_sequence(el, son(e)),
						scope);
					retcell(e);
					return(1);
				}

				if (name(bro(son(e))) == val_tag &&
				    name(son(e)) == plus_tag) {
					/* distribute offset_mult over plus
					 * (giving offset_adds) */
					/* the plus operation */
					exp pl = son(e);

					/* the offset constant */
					exp b = bro(pl);

					/* the first plus operand */
					exp x = son(pl);

					exp bx = bro(x);
					exp res = hold_check(me_b3(sh(e), x,
						  copy(b), offset_mult_tag));
					exp temp;
					while (bx != pl) {
						x = bx;
						bx = bro(x);
						temp = hold_check(me_b3(sh(e),
							x, copy(b),
							offset_mult_tag));
						res = hold_check(me_b3(sh(e),
							res, temp,
							offset_add_tag));
					}
					retcell(b);
					replace(e, res, scope);
					retcell(e);
					return 1;
				}
				return 0;

		case offset_div_by_int_tag:
		case offset_div_tag:
				if (name(son(e)) == val_tag &&
				    name(bro(son(e))) == val_tag &&
				    !isbigval(son(e)) &&
				    !isbigval(bro(son(e)))) {
					/* both arguments constant */
					int n1 = no(son(e));
					int n2 = no(bro(son(e)));
					no(son(e)) = n1 / n2;
					sh(son(e)) = sh(e);
					retcell(bro(son(e)));
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				}
				return 0;

#if has_setcc
		case absbool_tag: {
				exp arg1 = son(e);
				exp arg2 = bro(arg1);
				ntest nt = test_number(e);
				if ((name(arg1) == val_tag ||
				     name(arg1) == null_tag) &&
				    (name(arg2) == val_tag ||
				     name(arg2) == null_tag)) {
					/* argument constant */
					no(arg1) = docmp_f((int)nt, arg1, arg2);
					setname(arg1, val_tag);
					sh(arg1) = sh(e);
					clearbigval(arg1);
					retcell(arg2);
					replace(e, arg1, scope);
					retcell(e);
					return(1);
				}
				if (name(arg1) == val_tag ||
				    name(arg1) == real_tag ||
				    name(arg1) == null_tag) {
					/* constant argument always second */
					son(e) = arg2;
					bro(arg2) = arg1;
					bro(arg1) = e;
					setlast(arg1);
					clearlast(arg2);
					nt = exchange_ntest[nt];
					settest_number(e, nt);
				}
				return 0;
			}
#endif

		/* apply commutative and associative laws */
		case plus_tag:
#if is80x86
			{
				exp arg1 = son(e);
				exp arg2 = bro(arg1);
				if (!optop(e)) {
					return 0;
				}
				if (name(arg1) == val_tag &&
				    name(arg2) == val_tag) {
					plus_fn(arg1, arg2, errhandle(e));
					sh(arg1) = sh(e);
#ifdef NEWDIAGS
					if (diagnose) {
						if (dgf(arg1)) {
							dg_detach_const(arg1,
									e);
						}
						if (dgf(arg2)) {
							dg_detach_const(arg2,
									e);
						}
						dgf(arg1) = dgf(e);
					}
#endif
					replace(e, arg1, scope);
					retcell(e);
					return 1;
				}
				if (name(arg1) == val_tag) {
					exp q = hold_check(f_plus(f_impossible,
								  arg2, arg1));
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, q);
					}
#endif
					replace(e, q, scope);
					retcell(e);
					return 1;
				}
				if (name(arg2) == plus_tag &&
				    name(bro(son(arg2))) == val_tag &&
				    optop(arg2)) {
					exp con = bro(son(arg2));
					exp x = hold_check(f_plus(f_impossible,
						hold_check(f_plus(f_impossible,
						arg1, son(arg2))), con));
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, x);
					}
#endif
					replace(e, x, scope);
					retcell(e);
					return 1;
				}
				if (name(arg1) == plus_tag &&
				    name(bro(son(arg1))) == val_tag &&
				    optop(arg1)) {
					exp x = hold_check(f_plus(f_impossible,
						son(arg1),
						hold_check(f_plus(f_impossible,
						arg2, bro(son(arg1))))));
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, x);
					}
#endif
					replace(e, x, scope);
					retcell(e);
					return 1;
				}
				if (name(arg2) == plus_tag &&
				    name(arg1) != plus_tag && optop(arg2)) {
					exp t = bro(son(arg2));
					exp x = hold_check(f_plus(f_impossible,
						hold_check(f_plus(f_impossible,
						arg1, son(arg2))), t));
#ifdef NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, x);
					}
#endif
					replace(e, x, scope);
					retcell(e);
					return 1;
				}

				return seq_distr(e, scope);
			}
#else
			return(comm_ass(e, plus_tag, plus_fn, 0, 0, 0, scope,
					1, 0));
#endif /* is80x86 */

		case fplus_tag:
			/* apply zero, unit and constant evaluation.  NB dive
			 * MUST be false, because floating point is not really
			 * commutative and associative */
			/* XXX: floating point is actually commutative, but
			 * not associative */
			return(comm_ass(e, fplus_tag, fplus_fn, fzero_no, 0, 0,
					scope, 0, 1));
		case addptr_tag:
				if ((name(son(e)) == null_tag ||
				     name(son(e)) == val_tag) &&
				    !isbigval(son(e)) && no(son(e)) == 0) {
					if (name(bro(son(e))) == val_tag &&
					    !isbigval(bro(son(e))) &&
					    al2(sh(bro(son(e)))) > 1) {
						/* constant evaluation */
						sh(bro(son(e))) = sh(e);
						no(bro(son(e))) /= 8;
#ifdef NEWDIAGS
						if (diagnose) {
							dg_whole_comp(e,
								bro(son(e)));
						}
#endif
						replace(e, bro(son(e)), scope);
						retcell(son(e));
						retcell(e);
						return(1);
					}
				}
#if isAlpha
				{ exp ptr = son(e);
					exp off = bro(ptr);
					if ((al1_of(sh(off))->al.al_val.al_frame & 4) != 0 &&
					    !is_floating(al2_of(sh(off))->al.sh_hd)) {
						exp r = getexp(sh(ptr), off, 0,
							       ptr, nilexp, 0,
							       6*64, reff_tag);
						sh(off) =
						    f_offset(al1_of(sh(off)),
						    long_to_al(al2(sh(off))));
						bro(ptr) =r;
						setlast(ptr);
						son(e) = r;
					}
				}

#endif
				if (name(bro(son(e))) == val_tag &&
				    !isbigval(bro(son(e)))) {
					/* replace addptr(x, const) by
					 * refffield operation */
					exp p = son(e);
					int k = no(bro(p));
					exp r;
					r = getexp(sh(e), nilexp, 0, p, nilexp,
						   0, k, reff_tag);
#ifdef NEWDIAGS
					dgf(r) = dgf(e);
#endif
					replace(e, hc(r, p), scope);
					retcell(e);
					return(1);
				}
				if (name(son(e)) == reff_tag &&
				    shape_size(sh(e)) == 32) {
					/* replace addptr(reff[n](a), b) by
					 * reff[n](addptr(a, b)) */
					exp p = son(son(e));
					exp a = bro(son(e));
					exp ap1 = getexp(sh(e), nilexp, 0, p,
							 nilexp, 0, 0,
							 addptr_tag);
					exp ap, r;
					bro(p) = a;
					clearlast(p);
#if NEWDIAGS
					if (diagnose) {
						dg_whole_comp(son(e), p);
					}
#endif
					ap = hc(ap1, a);
					r = hc(getexp(sh(e), nilexp, 0, ap,
						      nilexp, 0, no(son(e)),
						      reff_tag), ap);
#if NEWDIAGS
					if (diagnose) {
						dg_whole_comp(e, r);
					}
#endif
					replace(e, r, scope);
					retcell(son(e));
					retcell(e);
					return(1);
				}
				if (name(bro(son(e))) == offset_add_tag) {
					exp p = son(e);
					exp a = son(bro(p));
					exp c = bro(a);
					if (name(c) == val_tag &&
					    !isbigval(c)) {
						exp ap = hold_check(me_b3(f_pointer(long_to_al(al2(sh(a)))),
							 p, a, addptr_tag));
						exp r = getexp(sh(e), nilexp, 0,
							       ap, nilexp, 0,
							       no(c), reff_tag);
						setfather(r, ap);
#ifdef NEWDIAGS
						dgf(r) = dgf(e);
#endif
						replace(e, hold_check(r),
							scope);
						retcell(e);
						return 1;
					}
					if (al1(sh(p)) == al2(sh(c))) {
						exp inner, outer;
						inner = hold_check(me_b3(sh(e),
							p, a, addptr_tag));
#ifdef NEWDIAGS
						if (diagnose) {
							dg_whole_comp(bro(p),
								      inner);
						}
#endif
						outer = hold_check(me_b3(sh(e),
							inner, c, addptr_tag));
#ifdef NEWDIAGS
						if (diagnose) {
							dg_whole_comp(e, outer);
						}
						/* also represent movement of
						 * c! */
#endif
						replace(e, outer, scope);
						retcell(e);
						return 1;
					}
				}
				return 0;

		case chvar_tag:
#ifdef value_of_null
			if (name(son(e)) ==null_tag) {
				setname(son(e), val_tag);
				no(son(e)) = value_of_null;
				clearbigval(son(e));
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#endif
			if (name(son(e)) == val_tag && optop(e)) {
				/* evaluate chvar(const) */
				int bg;
				flt64 x;
				shape sha = sh(e);
				x = exp_to_f64(son(e));
				/*
#if has64bits
				int sg = is_signed(sha);
				if (extra_checks && sg && !in_proc_def &&
				    shape_size(sha) <= 32 &&
				    check_size(x, sg, 32)) {
					failer("Change_variety out of range");
					exit(EXIT_FAILURE);
				}
#endif
				 */
				dochvar_f(&x, sha);
				no(son(e)) = f64_to_flpt(x, is_signed(sha), &bg,
							 shape_size(sha));
				if (bg) {
					setbigval(son(e));
				} else {
					clearbigval(son(e));
				}
				sh(son(e)) = sha;
#ifdef NEWDIAGS
				if (diagnose)
					dg_whole_comp(e, son(e));
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (eq_shape(sh(e), sh(son(e)))) {
				/* replace identity chvar by argument */
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (name(son(e)) == chvar_tag &&
					shape_size(sh(e)) ==
					shape_size(sh(son(son(e)))) &&
					name(sh(son(e))) == bitfhd) {
				exp res = hold_check(me_u3(sh(e),
							son(son(e)),
							chvar_tag));
				replace(e, res, scope);
				retcell(e);
				return 1;
			}
			if (name(son(e)) == chvar_tag &&
					!is_signed(sh(e)) &&
					shape_size(sh(e)) ==
					shape_size(sh(son(e)))) {
				replace(e, hold_check(me_u3(sh(e),
								son(son(e)), chvar_tag)), scope);
				retcell(e);
				return 1;
			}
			if (name(son(e)) == chvar_tag &&
					!is_signed(sh(e)) &&
					shape_size(sh(e)) <
					shape_size(sh(son(e))) &&
					shape_size(sh(e)) ==
					shape_size(sh(son(son(e))))) {
				replace(e, hold_check(me_u3(sh(e),
								son(son(e)), chvar_tag)),
						scope);
				retcell(e);
				return 1;
			}
#if little_end & has_byte_regs
			/* only for little enders which have byte
			 * registers */
			if ((shape_size(sh(e)) <=
						shape_size(sh(son(e)))) && optop(e) &&
					(name(son(e)) == name_tag ||
					 name(son(e)) == cont_tag ||
					 name(son(e)) == cond_tag)) {
				/* if the chvar operation never needs
				 * any action for a little end machine,
				 * eliminate it */
#if is80x86
				if (shape_size(sh(e)) == 8) {
					if (name(son(e)) == name_tag) {
						setvis(son(son(e)));
					}
					if (name(son(e)) == cont_tag &&
							name(son(son(e))) ==
							name_tag) {
						setvis(son(son(son(e))));
					}
				}
#endif
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				/* should this retcell(e) ? */
				return(1);
			}
			/* only for little enders which have byte
			 * registers */
			if (name(son(e)) == chvar_tag &&
					shape_size(sh(e)) <=
					shape_size(sh(son(e)))) {
				/* if the chvar operation never needs
				 * any action for a little end machine,
				 * eliminate it */
				exp w;
				sh(son(e)) = sh(e);
				w = hold(son(e));
				IGNORE check(son(w), son(w));
				replace(e, son(w), scope);
				retcell(e);
				retcell(w);
				return(1);
			}
#endif
#if little_end & has_byte_ops
			/* only for little enders with byte and short
			 * operations */
			if (shape_size(sh(e)) <=
					shape_size(sh(son(e))) && optop(e) &&
					name(sh(e)) != bitfhd &&
					(name(son(e)) == plus_tag ||
					 name(son(e)) == minus_tag ||
					 name(son(e)) == and_tag ||
					 name(son(e)) == or_tag ||
					 name(son(e)) == neg_tag)) {
				/* replace chvar(op(a ...)) by
				 * op(chvar(a)...) if the changevar
				 * requires no action on a little end
				 * machine */
#if only_lengthen_ops
				exp p = son(e);
				exp r;
				exp a = son(p);
				exp n = bro(a);
				int l = (int)last(a);

				/* if (shape_size(sh(e)) >= 16) */
				/* this is to avoid allocating bytes to
				 * edi/esi in 80386 !!! bad
				 */
#endif
				{
					exp sha = sh(e);
					exp t = varchange(sha, a);
					exp q = t;

					while (!l) {
						l = (int)last(n);
						a = n;
						n = bro(n);
						setbro(q, varchange(sha,
									a));
						clearlast(q);
						q = bro(q);
					}

					r = getexp(sha, nilexp, 0, t,
							pt(p), 0, no(p),
							name(p));
					seterrhandle(r, errhandle(e));
					replace(e, hc(r, q), scope);
					retcell(e);
					return(1);
				}
			}
#endif
			if (name(son(e)) == ident_tag &&
					isvar(son(e))) {
				/* distribute chvar into variable declaration of simple form
				*/
				exp vardec = son(e);
				exp def = son(vardec);
				exp body = bro(def);
				exp res;
				bool go = 1;
				exp t, u, v;
				if (name(body) != seq_tag)
					return(0);
				res = bro(son(body));
				if (name(res) != cont_tag ||
						name(son(res)) != name_tag ||
						son(son(res)) != vardec)
					return(0);
				t = pt(vardec);
				while (t != nilexp && go) {
					if (t == son(res) ||
							(!last(t) &&
							 name(bro(bro(t))) ==
							 ass_tag)) {
						t = pt(t);
					} else {
						go = 0;
					}
				}
				if (!go) {
					return(0);
				}
				if (name(def) == clear_tag) {
					u = copy(def);
					sh(u) = sh(e);
				} else {
					u = varchange(sh(e), copy(def));
				}
				replace(def, u, u);
				kill_exp(def, def);
				sh(res) = sh(e);
				sh(body) = sh(e);
				t = pt(vardec);
				while (t != nilexp) {
					if (t != son(res)) {
						v = bro(t);
						u = varchange(sh(e), copy(v));
						replace(v, u, u);
						kill_exp(v, def);
					}
					t = pt(t);
				}
				sh(vardec) = sh(e);
				replace(e, vardec, scope);
				retcell(e);
				return(1);
			}
			return 0;

		case bitf_to_int_tag:
			if (newcode) {
				exp temp = son(e);
				int szbf = shape_size(sh(temp));
				shape sha;
				int sg = is_signed(sh(temp));
				int s;

				if (szbf <= 8) {
					sha = (sg)? scharsh : ucharsh;
				} else if (szbf <= 16) {
					sha = (sg)? swordsh : uwordsh;
				} else if (szbf <= 32) {
					sha = (sg)? slongsh : ulongsh;
				} else {
					sha = (sg)? s64sh : u64sh;
				}

				if (name(sh(temp)) == bitfhd &&
				    name(temp) == chvar_tag) {
					exp st = son(temp);
					int n = name(st);
					if ((n == cont_tag &&
					     szbf == shape_size(sh(st))) ||
					    (n == and_tag &&
					     name(bro(son(st))) == val_tag &&
					     no(bro(son(st))) == (1 << szbf) -1)
					    || (n == shr_tag &&
						name(bro(son(st))) == val_tag &&
						no(bro(son(st))) ==
						shape_size(sh(st)) -szbf)) {
						/* arises from bfcont_tag */
						replace(e,
							hold_check(me_u3(sh(e),
							st, chvar_tag)), scope);
						retcell(e);
						retcell(temp);
						return 1;
					}
				}


				sh(temp) = sha;

				if (sg) {
#if isAlpha
					s = shape_size(s64sh) - szbf;
					if (s != 0) {
						temp = hold_check(me_u3(s64sh,
						       temp, chvar_tag));
						temp = hold_check(me_b3(s64sh,
						       temp, me_shint(s64sh, s),
						       shl_tag));
						temp = hold_check(me_b3(s64sh,
						       temp, me_shint(s64sh, s),
						       shr_tag));
					}
#else
					s = shape_size(sha) - szbf;
					if (s != 0) {
						temp = hold_check(me_b3(sha,
						       temp, me_shint(sha, s),
						       shl_tag));
						temp = hold_check(me_b3(sha,
						       temp, me_shint(sha, s),
						       shr_tag));
					}
#endif
				} else {
					int mask = (szbf == 32) ? -1 :
					    (1 << szbf) - 1;
					temp = hold_check(me_b3(sha, temp,
					       me_shint(sha, mask), and_tag));
				}

				replace(e, hold_check(me_u3(sh(e), temp,
							    chvar_tag)), scope);
				retcell(e);
				return 1;
			}
			return 0;

		case int_to_bitf_tag:
			if (newcode) {
				exp temp = son(e);
				shape sha = sh(temp);
				int szbf = shape_size(sh(e));
				int sg = is_signed(sh(e));

				if (shape_size(sh(son(e))) < szbf) {
					if (szbf <= 32) {
						sha = (sg) ? slongsh : ulongsh;
					} else {
						sha = (sg) ? s64sh : u64sh;
					}

					temp = hold_check(me_u3(sha, temp,
								chvar_tag));
				} else {
					UNUSED(sha);
				}
				temp = hold_check(me_u3(sh(e), temp,
							chvar_tag));
				replace(e, temp, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case minptr_tag: {
			exp s = son(e);
			exp b = bro(s);
			if (name(s) == val_tag && name(b) == null_tag) {
				sh(s) = sh(e);
				no(s) -= no(b);
				no(s)*= 8;
				replace(e, s, scope);
				retcell(e);
				return(1);
			}
			if (name(s) == val_tag && name(b) == val_tag) {
				/* both constants */
				sh(s) = sh(e);
				no(s) -= no(bro(son(e)));
				no(s)*= 8;
				replace(e, s, scope);
				retcell(e);
				return(1);
			}
			if (name(b) == null_tag && no(b) == 0) {
				sh(s) = sh(e);
				replace(e, s, scope);
				retcell(e);
				return 1;
			}
			if (name(s) == name_tag && name(b) == name_tag &&
			    son(s) == son(b)) {
				int n = no(s) - no(b);
				exp r;
				r = getexp(sh(e), nilexp, 0, nilexp, nilexp, 0,
					   n, val_tag);
				kill_exp(s, s);
				kill_exp(b, b);
				replace(e, r, scope);
				retcell(e);
				return 1;
			}
			return 0;
		}

		case minus_tag: {
			exp z, a2, r;
			exp arg1 = son(e);
			exp arg2 = bro(arg1);
			if (!optop(e)) {
				return 0;
			}
			if (name(arg1) == val_tag && name(arg2) == val_tag) {
				minus_fn(arg1, arg2, errhandle(e));
				sh(arg1) = sh(e);
				replace(e, arg1, scope);
				retcell(e);
				return 1;
			}
			/* replace a - b by a + (-b) */
			z = getexp(sh(e), nilexp, 0, bro(son(e)), pt(e), 0, 0,
				   neg_tag);
			seterrhandle(z, errhandle(e));
			a2 = hc(z, bro(son(e)));
			r = getexp(sh(e), nilexp, 0, son(e), pt(e), 0, 0,
				   plus_tag);
			seterrhandle(r, errhandle(e));
#ifdef NEWDIAGS
			dgf(r) = dgf(e);
#endif
			bro(son(e)) = a2;
			replace(e, hc(r, a2), scope);
			retcell(e);
			return(1);
		}

		case mult_tag:
			if (!optop(e)) {
				return 0;
			}
			if (name(bro(son(e))) == val_tag &&
			    last(bro(son(e))) &&
			    name(son(e)) == plus_tag &&
			    name(bro(son(son(e)))) == val_tag) {
				/* replace mult(plus(a, const1), const2) by
				 * plus(mult(a, const2), const1*const2) */
				int k = no(bro(son(e)))* no(bro(son(son(e))));
				exp ke = me_shint(sh(e), k);
				exp m = getexp(sh(e), nilexp, 0, son(son(e)),
					       nilexp, 0, 0, mult_tag);
				exp m1, pa;
				setbro(son(m), copy(bro(son(e))));
				clearlast(son(m));
				m1 = hc(m, bro(son(m)));
				pa = getexp(sh(e), nilexp, 0, m1, nilexp, 0, 0,
					    plus_tag);
				bro(m1) = ke;
				clearlast(m1);
				replace(e, hc(pa, ke), scope);
				retcell(e);
				return(1);
			}

			/* apply commutative and associative laws */
#if is80x86
			return(comm_ass(e, mult_tag, mult_fn, 1, 1, 0, scope,
					0, 0));
#else
			return(comm_ass(e, mult_tag, mult_fn, 1, 1, 0, scope,
					1, 0));
#endif

		case subptr_tag: {
			/* replace subptr(a, b) by addptr(a, (-b)) */
			exp z = getexp(sh(e), nilexp, 0, bro(son(e)), nilexp,
				       0, 0, neg_tag);
			exp a2 = hc(z, bro(son(e)));
			exp r = getexp(sh(e), nilexp, 0, son(e), nilexp, 0,
				       0, addptr_tag);
			bro(son(e)) = a2;
#ifdef NEWDIAGS
			if (diagnose) {
				dgf(r) = dgf(e);
			}
#endif
			replace(e, hc(r, a2), scope);
			retcell(e);
			return(1);
		}

		case neg_tag: {
			if (!optop(e)) {
				return 0;
			}
			if (name(son(e)) == val_tag) {
				/* eval for const */
				neg_fn(son(e));
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (name(son(e)) == neg_tag && optop(e) &&
			    optop(son(e))) {
				/* replace --a by a if errtreat is impossible
				 * or ignore */
				sh(son(son(e))) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(son(e), son(son(e)));
					dg_whole_comp(e, son(son(e)));
				}
#endif
				replace(e, son(son(e)), scope);
				retcell(son(e));
				retcell(e);
				return(1);
			}
			if (name(son(e)) == plus_tag && optop(e) &&
			    optop(son(e))) {
				/* replace negate(plus(a, b ..)) by
				 * plus(negate(a), negate(b) ..)) */
				exp r = getexp(sh(e), nilexp, 0, nilexp, nilexp,
					       0, 0, plus_tag);
				exp t = son(son(e));
				exp p = r;
				int lst;
				do {
					exp q = hold(getexp(sh(e), nilexp, 0,
							    t, nilexp, 0, 0,
							    neg_tag));
					exp next = bro(t);
					lst = (int)last(t);
					bro(t) = son(q);
					setlast(t);
					IGNORE check(son(q), scope);
					bro(p) = son(q);
					retcell(q);
					p = bro(p);
					clearlast(p);
					t = next;
				} while (!lst);
				son(r) = bro(r);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, r);
				}
#endif
				replace(e, hc(r, p), scope);
				retcell(e);
				return(1);
			}
			return 0;
		}

		case shl_tag:
		case shr_tag:
			if (name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) == 0) {
				/* remove zero place shift */
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (name(son(e)) == val_tag &&
			    name(bro(son(e))) == val_tag) {
				/* evaluate if both args constant */
				doshl(e);
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#if ismips
			if (name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) == shape_size(sh(e))) {
				exp s1 = copy(e);
				no(bro(son(s1)))--;
				if (name(e) ==shl_tag) {
					s1 = f_shift_left(f_continue, s1,
					     me_shint(sh(bro(son(e))), 1));
				} else {
					s1 = f_shift_right(s1,
					     me_shint(sh(bro(son(e))), 1));
				}
				replace(e, s1, scope);
				kill_exp(e, scope);
				return 1;
			}
#endif
#if has_neg_shift
			/* only use if the shift left and shift right
			 * operations are performed by the same instruction,
			 * distinguished by the sign of the number of places */
			if (name(e) == shr_tag) {
				exp places = bro(son(e));
				exp r;
				exp neg = getexp(sh(places), nilexp, 0, places,
						 nilexp, 0, 0, neg_tag);
				neg = hc(neg, places);
				r = getexp(sh(e), nilexp, 0, son(e), nilexp, 0,
					   0, shl_tag);
				bro(son(e)) = neg;
				r = hc(r, neg);
				replace(e, r, scope);
				retcell(e);
				return(1);
			}
#endif
			if (name(e) == shr_tag && name(son(e)) == shl_tag &&
			    name(bro(son(e))) == val_tag) {
				exp arg1 = son(e);
				int r = no(bro(arg1));
				if (name(son(arg1)) == shr_tag &&
				    name(bro(son(arg1))) == val_tag) {
					exp arg11 = son(arg1);
					int q = no(bro(arg11));
					if (r >= q &&
					    name(bro(son(arg11))) == val_tag) {
						exp x = son(arg11);
						int p = no(bro(x));
						if (q >= p) {
						    exp temp =
						    hold_check(me_b3(sh(arg1),
						    x, me_shint(sh(arg1),
						    q - p), shl_tag));
						    replace(son(e), temp, temp);
						    /* DELIBERATE FALL THROUGH*/
						}
					}
				} else {
					if (name(bro(son(arg1))) == val_tag) {
						int q = no(bro(son(arg1)));
						int se = shape_size(sh(e));
						if (q == r &&
						    (q == (se - 16) ||
						     q == (se - 8)) &&
						    is_signed(sh(arg1))) {
							shape sc =
							    (q == se - 16) ?
							    swordsh : scharsh;
							exp temp1 =
							    me_u3(sc, son(arg1),
								  chvar_tag);
							exp temp2 =
							    me_u3(sh(e), temp1,
								  chvar_tag);
							replace(e,
							    hold_check(temp2),
							    scope);
							retcell(e);
							return 1;
						}
					}
				}
			}
			if (name(e) == shl_tag && name(son(e)) == and_tag &&
			    name(bro(son(e))) == val_tag) {
				exp arg1 = son(e);
				exp arg2 = bro(arg1); /* left_places */
				if (name(arg1) == and_tag &&
				    name(bro(son(arg1))) == val_tag) {
					exp arg11 = son(arg1);
					exp arg12 = bro(arg11); /* mask */
					if (name(arg11) == shr_tag &&
					    name(bro(son(arg11))) == val_tag) {
						exp arg111 = son(arg11);
						/* right places */
						exp arg112 = bro(arg111);

						shape sha = sh(e);
						{
							exp a = hold_check(me_b3(sha, arg111,
										 me_shint(sha,
											  no(arg12) << no(arg112)),
										 and_tag));
							exp res;
							if (no(arg2) >= no(arg112))
								res = me_b3(sha, a,
									    me_shint(sha, no(arg2) - no(arg112)), shl_tag);
							else
								res = me_b3(sha, a,
									    me_shint(sha, no(arg112) - no(arg2)), shr_tag);
							replace(e, hold_check(res), scope);
							retcell(e);
							return 1;
						};
					};
				};
			};
			return seq_distr(e, scope);

		case mod_tag:
			if (name(son(e)) == val_tag &&
			    name(bro(son(e))) == val_tag) {
				/* evaluate if both args constant */
				if (is_signed(sh(e)) && no(bro(son(e))) == -1) {
					replace(e, me_shint(sh(e), 0), scope);
					retcell(e);
					return(1);
				}
				if (no(bro(son(e))) != 0) {
					domod(son(e), bro(son(e)));
					sh(son(e)) = sh(e);
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				};
			};
			return 0;

		case rem0_tag:
		case rem2_tag:
			if (name(son(e)) == val_tag &&
			    name(bro(son(e))) == val_tag) {
				/* evaluate if both args constant */

				/* some compilers get the rem2 wrong */
				if (is_signed(sh(e)) && no(bro(son(e))) == -1) {
					replace(e, me_shint(sh(e), 0), scope);
					retcell(e);
					return(1);
				}
				if (no(bro(son(e))) != 0) {
					dorem2(son(e), bro(son(e)));
					sh(son(e)) = sh(e);
					replace(e, son(e), scope);
					retcell(e);
					return(1);
				}
			}
			return 0;

		case div1_tag:
			if (name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) == 1) {
				/* remove divide by 1 */
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (optop(e) && name(son(e)) == val_tag &&
			    name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) != 0) {
				/* evaluate if both args constant */
				dodiv1(son(e), bro(son(e)));
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			};
			return 0;

		case div0_tag:
		case div2_tag:
			if (name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) == 1) {
				/* remove divide by 1 */
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (optop(e) && name(son(e)) == val_tag &&
			    name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) != 0) {
				/* evaluate if both args constant */
				dodiv2(son(e), bro(son(e)));
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			return 0;

		case max_tag:
		case min_tag: {
			exp arg1 = son(e);
			exp arg2 = bro(arg1);
			if (name(arg1) == val_tag && name(arg2) == val_tag) {
				domaxmin(arg1, arg2, name(e) == max_tag);
				replace(e, son(e), scope);
				retcell(e);
				return 1;
			}
			return 0;
			      }

		case chfl_tag:
			if (!optop(e)) {
				return 0;
			}
			if (name(sh(e)) == name(sh(son(e)))) {
				/* eliminate redundant chfl */
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#if FBASE == 10
			if (name(son(e)) == real_tag &&
			    name(sh(e)) < name(sh(son(e)))) {
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#else
			if (name(son(e)) == real_tag) {
				if (name(sh(e)) < name(sh(son(e)))) {
				    flpt_round((int)f_to_nearest,
				      flpt_bits((floating_variety)(name(sh(e)) -
				      shrealhd)), &flptnos[no(son(e))]);
				}
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#endif
			if (name(son(e)) == chfl_tag &&
			    name(sh(son(son(e)))) == name(sh(e)) &&
			    name(sh(e)) < name(sh(son(e)))) {
				/* chfl(flsh1, chfl(flsh2, exp of shape flsh1))
				 * to internal exp iff flsh2 includes flsh1 */
				sh(son(son(e))) = sh(e);
				replace(e, son(son(e)), scope);
				retcell(son(e));
				retcell(e);
				return(1);
			}
			return 0;

		case round_tag:
			if (!optop(e)) {
				return 0;
			}

#if FBASE == 10
			if (name(son(e)) == real_tag) {
				/* apply if arg constant */
				flpt f = no(son(e));
				exp iexp = me_shint(sh(e), 0);

				int i, val = 0;
				flt res;
				if (round_number(e) == f_to_nearest) {
					flt_round(flptnos[f], &res);
				} else {
					flt_trunc(flptnos[f], &res);
				}

				for (i = 0; i <= res.exp; ++i) {
					val = (10 * val + res.mant[i]);
				}
				no(iexp) = val * res.sign;
				replace(e, iexp, scope);
				kill_exp(e, scope);
				return(1);
			}
#else
			if (name(son(e)) == real_tag) {
				/* apply if arg constant */
				flpt f = no(son(e));
				flt64 x;
				int ov, pr;
				int sg = is_signed(sh(e));
				exp iexp;
				IGNORE flpt_round_to_integer(round_number(e),
							     &flptnos[f]);
				x = flt_to_f64(f, sg, &ov);
				iexp = me_shint(sh(e), f64_to_flpt(x, sg, &pr,
						shape_size(sh(e))));
				if (pr) {
					setbigval(iexp);
				}
				replace(e, iexp, scope);
				kill_exp(e, scope);
				return(1);
			}
#endif

			return 0;

		case float_tag:
			if (!optop(e)) {
				return 0;
			}
#if FBASE == 10
			if (name(son(e)) == val_tag) {
				/* apply if arg constant */
				shape sha = sh(son(e));
				int k = no(son(e));
				int sz = shape_size(sha);

				if (PIC_code) {
					proc_externs = 1;
				}

				if (sz == 8) {
					no(son(e)) = floatrep(k & 0xff);
				} else if (sz == 16) {
					no(son(e)) = floatrep(k & 0xffff);
				} else {
					/* watch out for 64bits */
					no(son(e)) = floatrep(k);
					if (shape_size(sh(son(e))) == 32 &&
					    !is_signed(sh(son(e))) &&
					    (k & 0x80000000) != 0) {
						flt flongmaxr;
						int i;
						flt r;
						flongmaxr.sign = 1;
						flongmaxr.exp = 9;
						for (i = 0; i < MANT_SIZE;
						     i++) {
							(flongmaxr.mant)[i] =
							    (i < 10) ?
							    (maxdigs[i] - '0') :
								    0;
						}
						flt_add(flptnos[no(son(e))],
							flongmaxr, &r);
						flptnos[no(son(e))] = r;
					}
				}

				flpt_round((int)f_to_nearest,
				    flpt_bits((floating_variety)(name(sh(e)) -
				    shrealhd)), &flptnos[no(son(e))]);
				setname(son(e), real_tag);
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#else
			if (name(son(e)) == val_tag) {
				/* apply if arg constant */
				exp arg = son(e);
				shape sha = sh(arg);
				int k = no(arg);
				int sz = shape_size(sha);
				int sg = is_signed(sha);

				if (PIC_code) {
					proc_externs = 1;
				}

				if (sz == 8) {
					k = k & 0xff;
					if (sg && k >= 0x80) {
						k = (k | (int)0xffffff00);
					}
					no(arg) = floatrep(k);
				} else if (sz == 16) {
					k = k & 0xffff;
					if (sg && k >= 0x8000)
						k = (k | (int)0xffff0000);
					no(arg) = floatrep(k);
				} else if (sz == 32) {
					/* watch out for 64bits */
					if (sg) {
						no(arg) = floatrep(k);
					} else {
						no(arg) = floatrep_unsigned(uno(arg));
					}
					/* use unsigned selector for k */
				} else {
					if (!isbigval(arg)) {
						no(arg) =
						    f64_to_flt(exp_to_f64(arg),
							       is_signed(sha));
					}
					clearbigval(arg);
				}


				flpt_round((int)f_to_nearest,
				    flpt_bits((floating_variety)(name(sh(e)) -
				    shrealhd)), &flptnos[no(arg)]);
				setname(arg, real_tag);
				sh(arg) = sh(e);
				replace(e, arg, scope);
				retcell(e);
				return(1);
			}
#endif
			return 0;

		case fmult_tag:
			/* apply zero, unit and constant evaluation.  NB dive
			 * MUST be false, because floating point is not really
			 * commutative and associative */
			/* XXX: floating point is actually commutative, but
			 * not associative */

			return(comm_ass(e, fmult_tag, fmult_fn, fone_no, 1,
					fzero_no, scope, 0, 1));
		case fminus_tag:
			if (!optop(e)) {
				return 0;
			}
			/* constant evaluation */
			if (check_fp2(e, scope)) {
				return 1;
			}
			return 0;
		case fdiv_tag:
			if (!optop(e)) {
				return 0;
			}
			/* constant evaluation */
			if (check_fp2 (e, scope)) {
				return 1;
			}
			if (name(bro(son(e))) == real_tag &&
			    flptnos[no(bro(son(e)))].sign != 0 &&
			    (!strict_fl_div ||
			     flpt_power_of_2(no(bro(son(e)))))) {
				shape sha = sh(e);
				exp one;
				exp temp;
				flpt f = new_flpt();

				flt_copy(flptnos[fone_no], &flptnos[f]);
				one = getexp(sha, nilexp, 0, nilexp, nilexp, 0,
					     f, real_tag);
				temp = hold_check(me_b3(sha, one, bro(son(e)),
							fdiv_tag));
				temp = hold_check(me_b3(sha, son(e), temp,
							fmult_tag));
				seterrhandle(temp, errhandle(e));
				replace(e, temp, scope);
				retcell(e);
				return 1;
			}
			return 0;

		case fneg_tag:
			if (!optop(e)) {
				return 0;
			}
			if (name(son(e)) == real_tag) {
				/* apply if arg constant */
				int fn = no(son(e));
				flptnos[fn].sign = -flptnos[fn].sign;
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			} else if (name(son(e)) == fneg_tag) {
				/* --a = a (should check ignore overflow) */
				replace(e, son(son(e)), scope);
				retcell(son(e));
				retcell(e);
				return(1);
			}
			return 0;

		case fabs_tag:
			if (name(son(e)) == real_tag) {
				/* apply if arg constant */
				int fn = no(son(e));
				if (flptnos[fn].sign == -1) {
					flptnos[fn].sign = 1;
				}
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			return 0;

		case and_tag:
#if has_byte_ops
			if (name(bro(son(e))) == val_tag &&
			    no(bro(son(e))) == 0xff &&
			    name(son(e)) == shr_tag &&
			    name(son(son(e))) == cont_tag) {
				exp a1 = bro(son(son(e)));
				if (name(a1) == val_tag && !isbigval(a1) &&
				    (no(a1) & 0x7) == 0) {
					exp t = son(son(son(e)));
					exp r = me_u3(sh(t), t, reff_tag);
					exp c, v;
#if little_end
					no(r) = no(a1);
#else
					no(r) = shape_size(sh(e)) - no(a1) - 8;
#endif
					r = hold_check(r);
					c = hold_check(me_u3(ucharsh, r,
							     cont_tag));
					v = hold_check(me_u3(sh(e), c,
							     chvar_tag));
					replace(e, v, scope);
					retcell(e);
					return 1;
				}
			}
#endif
			if (name(son(e)) == and_tag &&
			    name(bro(son(e))) == val_tag &&
			    name(bro(son(son(e)))) == val_tag &&
			    !isbigval(bro(son(e))) &&
			    !isbigval(bro(son(son(e))))) {
				int mask = no(bro(son(e))) &
				    no(bro(son(son(e))));
				exp res = hold_check(me_b3(sh(e), son(son(e)),
					  me_shint(sh(e), mask), and_tag));
				replace(e, res, scope);
				retcell(e);
				return 1;
			}
			if (name(son(e)) == shr_tag &&
			    name(bro(son(e))) == val_tag &&
			    !isbigval(bro(son(e)))) {
				exp arg1 = son(e);
				exp arg2 = bro(arg1); /* mask */
				int m = no(arg2);
				int sz = shape_size(sh(arg1));
				if (m > 0 && name(bro(son(arg1))) == val_tag &&
				    !isbigval(bro(son(arg1))) &&
				    m <=
				    ((1 << (sz - no(bro(son(arg1))))) - 1)) {
					exp arg11 = son(arg1);
					/* right shift places */
					exp arg12 = bro(arg11);

					if (name(arg11) == shl_tag &&
					    name(bro(son(arg11))) == val_tag &&
					    !isbigval(bro(son(arg11)))) {
						exp arg111 = son(arg11);
						/* left shift places */
						exp arg112 = bro(arg111);

						if (no(arg112) <= no(arg12)) {
						  exp res =
						      hold_check(me_b3(sh(arg1),
						      arg111, me_shint(sh(arg1),
						      no(arg12) - no(arg112)),
						      shr_tag));
							replace(arg1, res, res);
							return check(e, scope);
						}
					}
				}
			}
			/* apply commutative and associative laws */
			return(comm_ass(e, and_tag, and_fn, all_ones(son(e)), 1,
					0, scope, 1, 0));
		case or_tag:
			/* apply commutative and associative laws */
			if (name(son(e)) == and_tag &&
			    name(bro(son(e))) == val_tag &&
			    !isbigval(bro(son(e))) &&
			    name(bro(son(son(e))))) {
				exp arg1 = son(e);
				int q = no(bro(arg1));
				exp arg11 = son(arg1);
				int p = no(bro(arg11));
				if ((q | p) == (int)0xffffffff) {
					exp res = me_b3(sh(e), arg11, bro(arg1),
							or_tag);
					replace(e, hold_check(res), scope);
					retcell(e);
					return 1;
				}
			}
			return(comm_ass(e, or_tag, or_fn, 0,
					shape_size(sh(e)) <= 32,
					all_ones(son(e)), scope, 1, 0));
		case xor_tag:
			/* apply commutative and associative laws */
			return(comm_ass(e, xor_tag, xor_fn, 0, 0, 0, scope, 1,
					0));
		case not_tag:
			if (name(son(e)) == val_tag) {
				/* eval for const */
				not_fn(son(e));
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (name(son(e)) == not_tag) {
				/* not(not(x))->x */
				sh(son(son(e))) = sh(e);
				replace(e, son(son(e)), scope);
				retcell(son(e));
				retcell(e);
				return(1);
			}
			return 0;

		case cont_tag:
#ifdef promote_pars
		{
			int x = al1_of(sh(son(e)))->al.sh_hd;

			if (x >= scharhd && x <= uwordhd && !little_end) {
				int disp = shape_size(ulongsh) -
				    ((x >= swordhd) ? 16 : 8);
				exp r = getexp(f_pointer(f_alignment(sh(e))),
					       nilexp, 1, son(e), nilexp, 0,
					       disp, reff_tag);
				bro(son(r)) = r;
				son(e) = hold_check(r);
				bro(son(e)) = e;
				setlast(son(e));
				return 1;
			}
		}
#endif

#ifndef NEWDIAGS
			if (name(son(e)) == diagnose_tag) {
				exp diag = son(e);
				exp p = son(diag);
				exp r = getexp(sh(e), nilexp, 0, p, nilexp, 0,
					       0, cont_tag);
				exp d;
				r = hc(r, p);
				d = getexp(sh(e), nilexp, 0, r, pt(diag),
					   props(diag), no(diag), diagnose_tag);
				setfather(d, r);
				replace(e, d, scope);
				retcell(son(e));
				retcell(e);
				return 1;
			}
#endif
			return 0;

		case field_tag:
			if (name(son(e)) == compound_tag && nos(son(e))) {
				exp s = son(son(e));
				for (;;) {
					if (no(s) ==no(e) &&
					    eq_shape(sh(e), sh(bro(s)))) {
						replace(e, copy(bro(s)), scope);
						kill_exp(e, scope);
						return 1;
					}
					if (last(bro(s))) {
						break;
					}
					s = bro(bro(s));
				}
			}
			if (name(son(e)) == nof_tag && nos(son(e))
			    && eq_shape(sh(e), sh(son(son(e))))) {
				exp s = son(son(e));
				int sz = rounder(shape_size(sh(s)),
						 shape_align(sh(s)));
				int n = 0;
				for (; no(e) <= n; n += sz) {
					if (no(e) ==n) {
						replace(e, copy(s), scope);
						kill_exp(e, scope);
						return 1;
					}
					if (last(s)) {
						break;
					}
					s = bro(s);
				}
			}

			if (name(son(e)) == name_tag) {
				/* replace field on name by name with offset in
				 * no */
				no(son(e)) += no(e);
				sh(son(e)) = sh(e);
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			if (name(son(e)) == cont_tag) {
				/* replace field[n](cont(x)) by
				 * cont(reff[n](x)) */
				exp arg = son(son(e));
				exp rf1 = getexp(sh(arg), nilexp, 0, arg,
						 nilexp, 0, no(e), reff_tag);
				exp rf = hc(rf1, arg);
				exp c = getexp(sh(e), nilexp, 0, rf, nilexp, 0,
					       0, cont_tag);
				replace(e, hc(c, rf), scope);
				retcell(son(e));
				retcell(e);
				return(1);
			}
			if (name(son(e)) == ident_tag && isvar(son(e)) &&
			    name(son(son(e))) == clear_tag &&
			    name(bro(son(son(e)))) == seq_tag) {
				exp var = son(e);
				exp sq = bro(son(var));
				if (name(bro(son(sq))) == cont_tag &&
				    name(son(bro(son(sq)))) == name_tag &&
				    son(son(bro(son(sq)))) == var) {
					int count = 0;
					int good = 0;
					exp p = son(son(sq));
					exp q;
					exp res;
					while (p != son(sq)) {
						if (name(p) != ass_tag ||
						    name(son(p)) != name_tag ||
						    son(son(p)) != var) {
							return 0;
						}
						++count;
						if (no(son(p)) == no(e)) {
							good = 1;
						}
						p = bro(p);
					}
					if ((count + 1) != no(var) || !good) {
						return 0;
					}
					p = son(son(sq));
					while (p != son(sq)) {
						q = bro(p);
						if (no(son(p)) == no(e)) {
							exp tp = f_make_top();
							res = bro(son(p));
							replace(p, tp, tp);
						} else {
							exp w = bro(son(p));
							replace(p, w, w);
						}
						p = q;
					}
					SET(res);
					replace(bro(son(sq)), res, res);
					replace(e, hold_check(sq), scope);
					return 1;
				}
				return 0;
			}
			return(0);

		case reff_tag:
			if (name(son(e)) == name_tag &&
			    isvar(son(son(e))) && al1(sh(e)) > 1) {
				/* replace reff on name of var by name with
				 * offset in no */
				no(son(e)) += no(e);
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}

			if (name(son(e)) == val_tag) {
				no(son(e)) += (no(e) / 8);
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}

#if !temp_mips
			/* confirm mips doesnt need this */
			if (name(son(e)) == reff_tag) {
				/* combine reff selections */
				sh(son(e)) = sh(e);
				no(son(e)) += no(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
#endif

#if remove_zero_offsets
			if (no(e) == 0 && al1(sh(e)) > 1) {
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return 1;
			}
#endif

			return(0);
		case bfcont_tag:
		case bfcontvol_tag: {
			exp p = son(e);
			int bsz = shape_size(sh(e));
			int rsz = al1(sh(p));
			int rsh;
			int sg = is_signed(sh(e));
			int off = no(e);
			exp ref;
			exp cont;
			exp eshift;
			shape ptr_sha;
			shape msh;
			int temp = off + bsz - 1;

			if (rsz>BF_STORE_UNIT)rsz = BF_STORE_UNIT;

			if (((off / 8) == (temp / 8)) &&
			    (bsz == 8 &&
			     ((little_end && (off % 8 == 0)) ||
			      (!little_end && ((8 - (off % 8) - bsz) == 0))))) {
				rsz = 8;
			} else if (((off / 16) == (temp / 16)) &&
				    (bsz == 16 &&
				     ((little_end && (off % 16 == 0)) ||
				      (!little_end &&
				       ((16 - (off % 16) - bsz) == 0))))) {
				rsz = 16;
			}
#if isAlpha
			else if (((off / 32) == (temp / 32)) &&
				 (!sg || (al1(sh(p)) < 64) ||
				  (bsz == 32 &&
				   ((little_end && (off % 32 == 0)) ||
				    (!little_end &&
				     ((32 - (off % 32) - bsz) == 0)))))) {
				rsz = 32;
			}
#endif
			else {
				/* all of bitfield must be within same integer
				 * variety */
				while ((off / rsz) != (temp / rsz)) {
					rsz = rsz << 1;
				}
			}

			msh = containedshape(rsz, sg);
			ptr_sha = f_pointer(long_to_al(rsz));
			if ((off / rsz) != 0) {
				ref = me_u3(ptr_sha, p, reff_tag);
				no(ref) = (off / rsz) * rsz;
				ref = hold_check(ref);
			} else {
				ref = p;
			}
#if little_end
			rsh = off % rsz;
#else
			rsh = rsz - (off % rsz) - bsz;
#endif
			cont = me_u3(msh, ref, (name(e) == bfcont_tag) ? 
				     (unsigned char)cont_tag :
				     (unsigned char)contvol_tag);
			if (rsh == 0 && !sg && bsz != rsz) {
				eshift = me_b3(msh, cont,
					       me_shint(slongsh, (1 << bsz) -1),
					       and_tag);
			} else {
				if (rsz - bsz - rsh != 0) {
					cont = me_b3(msh, cont,
						     me_shint(slongsh, rsz -
						     bsz - rsh), shl_tag);
				}

				if (rsz - bsz != 0) {
					eshift = me_b3(msh, cont,
						       me_shint(slongsh, rsz -
								bsz), shr_tag);
				} else {
					eshift = cont;
				}
			}
			eshift = me_u3(sh(e), eshift, chvar_tag);

			replace(e, eshift , scope);
			retcell(e);
			return 1;
		}

		case abs_tag:
			if (name(son(e)) == val_tag) {
				if (is_signed(sh(e)) &&
				    ((isbigval(son(e)) &&
				      flptnos[no(son(e))].sign) ||
				     (!isbigval(son(e)) &&
				      no(son(e)) < 0))) {
					/* eval for const */
					if (!optop(e)) {
						return 0;
					}
					neg_fn(son(e));
				}
				sh(son(e)) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, son(e));
				}
#endif
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
			return 0;

		case fmax_tag:
		case fmin_tag: {
			bool fmin = (name(e) ==fmin_tag);
			exp arg1 = son(e);
			exp arg2 = bro(arg1);
			/* identify arg1 */
			exp id1 = me_startid(sh(arg1), arg1, 0);
			/* identify arg2 */
			exp id2 = me_startid(sh(arg2), arg2, 0);

			exp seq;
			exp cond;
			exp zero;
			exp lab;
			exp clear;
			exp test;

			clear = getexp(f_bottom, nilexp, 0, nilexp, nilexp, 0,
				       0, clear_tag);
			lab = me_b3(sh(arg2), clear, me_obtain(id2), labst_tag);
			test = me_q2(no_nat_option, f_impossible,
				     fmin ? f_less_than : f_greater_than,
				     &lab, me_obtain(id1), me_obtain(id2),
				     test_tag);
			zero = me_u3(sh(test), test, 0);
			seq = me_b3(sh(arg1), zero, me_obtain(id1), seq_tag);
			cond = me_b3(sh(arg1), seq, lab, cond_tag);
			id2 = me_complete_id(id2, cond);
			id1 = me_complete_id(id1, id2);
			replace(e, id1, scope);
			retcell(e);
			return 1;
		}

		case name_tag: {
			exp s = son(e);
			if (!isvar(s) && isglob(s) && son(s) != nilexp &&
			    name(sh(e)) == name(sh(son(s))) &&
			    (name(son(s)) == val_tag ||
			     name(son(s)) == real_tag)) {
				exp c = copy(son(s));
				replace(e, c, scope);
				kill_exp(e, scope);
				return 1;
			} else {
				return 0;
			}

		}
		case fpower_tag:
		case imag_tag:
		case make_complex_tag:
			return 0;
		case rotl_tag:
		case rotr_tag:
		case env_offset_tag:
		case general_env_offset_tag:
		case proc_tag:
		case general_proc_tag:
		case top_tag:
		case val_tag:
		case real_tag:
		case current_env_tag:
		case make_lv_tag:
		case clear_tag:
		case null_tag:
		case string_tag:
		case power_tag:
		case contvol_tag:
			return 0;
		default:
			return 0;
		}
	}

	/* side effecting ops */
	switch (name(e)) {
	case compound_tag: {
		exp bse = bro(son(e));
		unsigned char shn = name(sh(bse));
		if (last(bse) && name(son(e)) == val_tag &&
		    no(son(e)) == 0 &&
		    shape_size(sh(e)) == shape_size(sh(bse)) &&
		    shn != prokhd && (shn < shrealhd || shn > doublehd)
#if dont_unpad_apply
		    && name(bse) != apply_tag
#endif
		   ) {
			/* remove the creation of a compound if it consists of
			 * a single value of the same size and provided that
			 * the component is not real (because it might be in
			 * the wrong place. */
			if (name(bse) == name_tag && isvar(son(bse)) &&
			    !isglob(son(bse)) &&
			    name(sh(son(son(bse)))) >= shrealhd &&
			    name(sh(son(son(bse)))) <= doublehd) {
				setvis(son(bse));
				props(e) = (prop)(props(e) & ~0x08);
			}
			sh(bse) = sh(e);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, bse);
			}
#endif
			replace(e, bse, scope);
			retcell(son(e));
			retcell(e);
			return 1;
		}
	}
#if replace_compound
		if (in_proc_def) {
			/* Provided that the exp is inside a procedure
			 * definition we always remove compound creation and
			 * replace it by a variable declaration for the
			 * compound, assignments to the components, and deliver
			 * the compound. */
			shape she = sh(e);
			exp var = me_start_clearvar(she, she);
			exp cont = getexp(she, nilexp, 0, nilexp, nilexp, 0, 0,
					  cont_tag);
			exp_list el;
			exp obt;
			exp t = son(e);
			exp seq;
			obt = me_obtain(var);
			son(cont) = obt;
			setfather(cont, obt);
			el = new_exp_list(0);

			while (1) {
				exp q = bro(t);	/* expression being assigned */
				exp n = bro(q);
				int end = (int)last(q);
				exp ass, p, ap;
				p = me_obtain(var);
				if (name(sh(q)) != bitfhd || !newcode) {
					/* destination */
					ap = hold_check(f_add_to_ptr(p, t));
					ass = hold_check(f_assign(ap, q));
				} else {
					ass = hold_check(f_bitfield_assign(p, t,
									   q));
				}
				el = add_exp_list(el, ass, 0);
				if (end) {
					break;
				}
				t = n;
			}
			seq = f_sequence(el, cont);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, var);
			}
#endif
			replace(e, me_complete_id(var, seq), scope);
			retcell(e);
			return 1;
		}
#endif
		return 0;
#ifndef NEWDIAGS
	case diagnose_tag:
#endif
	case prof_tag:
		return 0;
	case ident_tag:
		if (name(sh(son(e))) == bothd) {
			exp s = son(e);
			exp b = bro(s);
#ifdef NEWDIAGS
			if (diagnose) {
				dg_dead_code(b, s);
				dg_whole_comp(e, s);
			}
#endif
			kill_exp(b, b);
			replace(e, s, scope);
			retcell(e);
			return 1;
		}
#if has_setcc
		/* use if target has setcc instruction */
		if (!is80x86 || is80586) {
			exp abst = absbool(e);
			if (abst != nilexp &&
			    (!is80x86 || name(sh(son(abst))) <= u64hd)) {
				/* check if we can use setcc */
				exp a = copy(abst);
				setname(a, absbool_tag);
				pt(a) = nilexp;
				sh(a) = sh(e);
#ifdef NEWDIAGS
				if (diagnose) {
					dg_whole_comp(e, a);
				}
#endif
				replace(e, a, a);
				kill_exp(e, e);
				return(0);
			}
		}
#endif
		if (name(sh(bro(son(e)))) != name(sh(e))) {
			sh(e) = sh(bro(son(e)));
			IGNORE check_id(e, scope);
			return 1;
		}
		return (check_id (e, scope));	/* see check_id.c */

	case seq_tag:
		if (son(son(e)) == nilexp) {
			/* remove empty seq */
			exp s = son(e);
			sh(bro(s)) = sh(e);	/* unless bottom ? */

#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, bro(s));
			}
#endif
			replace(e, bro(s), scope);
			retcell(s);
			return(1);
		}
		return(check_seq(e, scope));

	case cond_tag:
		if (no(son(bro(son(e)))) == 0) {
			/* remove inaccessible statements */
			exp bs = bro(son(e));
#ifdef NEWDIAGS
			if (diagnose) {
				dg_dead_code(bro(son(bs)), son(e));
				dg_whole_comp(e, son(e));
			}
#endif
			replace(e, son(e), scope);
			kill_exp(bs, scope);
			retcell(e);
			return(1);
		}
		if (name(son(e)) == goto_tag && pt(son(e)) == bro(son(e))) {
			/* replace cond which has first a simple goto to the
			 * alt by the alt (removing the label) */
			exp x = bro(son(bro(son(e))));
#ifdef NEWDIAGS
			if (diagnose) {
				dg_rdnd_code(son(e), x);
				dg_whole_comp(e, x);
			}
#endif
			replace(e, x, scope);
			retcell(son(bro(son(e))));
			retcell(bro(son(e)));
			if (son(son(e)) != nilexp) {
				retcell(son(son(e)));
			}
			retcell(son(e));
			retcell(e);
			return(1);
		}

		if (name(son(e)) == seq_tag && no(son(bro(son(e)))) == 1 &&
		    name(bro(son(son(e)))) == goto_tag) {
			/* is e = cond(seq(..;goto m), l: x) and is only 1 use
			 * of l */
			exp t = son(son(son(e)));
			while (!last(t)) {
				t = bro(t);
			}
#ifndef NEWDIAGS
			if (name(t) == diagnose_tag) {
				t = son(t);
			}
#endif
			if ((name(t) == test_tag || name(t) == testbit_tag) &&
			    pt(t) == bro(son(e)) && test_number(t) <= 6) {
				/* look at last element of sequence before goto
				 * m to see if it is a conditional jump to l.
				 * If so reverse the test, make it jump to m
				 * and remove the goto */

				settest_number(t, revtest[test_number(t) - 1]);
				pt(t) = pt(bro(son(son(e))));
				sh(son(e)) = sh(bro(son(bro(son(e)))));
				replace(bro(son(son(e))), bro(son(bro(son(e)))),
					son(e));
				replace(e, son(e), scope);
				retcell(e);
				return(1);
			}
		}
#if maxmin_implemented
		{
			exp t;
			int bl = is_maxop(e, &t);
			int ismax = 0;
			int ismin = 0;
			ntest nt;
			if (bl) {
				nt = test_number(t);
				if (nt == f_greater_than ||
				    nt == f_greater_than_or_equal) {
					ismax = 1;
				}
				if (nt == f_less_than ||
				    nt == f_less_than_or_equal) {
					ismin = 1;
				}
			} else {
				bl = is_minop(e, &t);
				if (bl) {
					nt = test_number(t);
					if (nt == f_greater_than ||
					    nt == f_greater_than_or_equal) {
						ismin = 1;
					}
					if (nt == f_less_than ||
					    nt == f_less_than_or_equal) {
						ismax = 1;
					}
				}
			}
			if (ismax || ismin) {
				exp tq = me_b2(copy(son(t)), copy(bro(son(t))),
					       (ismax) ?
					       (unsigned char)max_tag :
					       (unsigned char)min_tag);
				replace(e, hold_check(tq), scope);
				kill_exp(e, e);
				return 1;
			}
		}
#endif

#if condassign_implemented
		{
			exp to_test;
			exp to_ass;

			if (is_condassign(e, &to_test, &to_ass) &&
			    is_floating(name(sh(son(to_test)))) ==
			    is_floating(name(sh(bro(son(to_ass)))))) {
				exp res = me_b3(sh(e), to_test, to_ass,
						condassign_tag);
				replace(e, res, scope);
				retcell(e);
				return 1;
			}
		}
#endif

		if (name(bro(son(bro(son(e))))) == top_tag) {
			exp first = son(e);
			exp alt = bro(first);
			int in_repeat = 0;
			if (crt_repeat != nilexp &&
			    (int)(props(crt_repeat)) == 1) {
				in_repeat = 1;
			}
			if (take_out_of_line(first, alt, in_repeat, 1.0)) {
				exp t = son(son(first));
				exp tst = (is_tester(t, 0))? t : bro(son(t));
				if (no(tst) == 1000) {
					no(tst) = 25;
				}
			}
		}
		return(0);

#if condassign_implemented
	case condassign_tag:
		if (name(bro(son(e))) != ass_tag &&
		    (name(son(e)) == test_tag ||
		     name(son(e)) == testbit_tag)) {
			exp sqz = me_b3(f_top, son(son(e)), bro(son(son(e))),
					0);
			exp sq = me_b3(sh(e), sqz, bro(son(e)), seq_tag);
			replace(e, hold_check(sq), scope);
			retcell(e);
			return 1;
		}
		if (name(son(e)) == goto_tag) {
			replace(e, getexp(f_top, nilexp, 0, nilexp, nilexp, 0,
					  0, top_tag), scope);
			retcell(e);
			return 1;
		}
		if (name(son(e)) == top_tag) {
			replace(e, bro(son(e)), scope);
			retcell(e);
			return 1;
		}
#endif

	case goto_tag:
	case return_to_label_tag:
	case trap_tag:
		return(0);
	case ass_tag:
#if 0
		if (0 && redo_structfns && !reg_result(sh(bro(son(e)))) &&
		    name(bro(son(e))) == ident_tag &&
		    isvar (bro(son(e)))) {
			/* prepare to replace the assignment of structure
			 * results of procedures.  If it decides to do so it
			 * will put the destination in as the first parameter
			 * of the procedure */
			exp id = bro(son(e));
			exp def = son(id);
			exp body = bro(def);
			if (name(def) == clear_tag && name(body) == seq_tag) {
				if (name(son(son(body))) == apply_tag &&
				    last(son(son(body))) &&
				    name(bro(son(body))) == cont_tag &&
				    name(son(bro(son(body)))) == name_tag &&
				    son(son(bro(son(body)))) == id) {
					exp ap = son(son(body));
					exp p1 = bro(son(ap));
					if (name(p1) == name_tag &&
					    son(p1) == id && last(ap)) {
						/* this is the assignment of a
						 * struct result of a proc */
						exp p2 = bro(son(ap));
						exp se = son(e);
						if (last(p2)) {
							setlast(se);
						}
						bro(se) = bro(p2);
						bro(son(ap)) = se;
						if (name(se) == name_tag &&
						    isvar(son(se)) &&
						    !isglob(son(se)) &&
						    shape_size(sh(id)) == shape_size(sh(son(son(se))))) {
							setreallyass(se);
						}
						replace(e, ap, scope);
						return(1);
					}
				}
			}
		}
#endif
#ifdef promote_pars
		{
			int x = al1_of(sh(son(e)))->al.sh_hd;

			if (x >= scharhd && x <= uwordhd && !little_end) {
				exp b = bro(son(e));
				int disp = shape_size(ulongsh) -
				    ((x >= swordhd) ? 16 : 8);
				exp r = getexp(f_pointer(f_alignment(sh(b))),
					       nilexp, 1, son(e), nilexp, 0,
					       disp, reff_tag);
				bro(son(r)) = r; setlast(son(r));
				r = hold_check(r);
				bro(r) = b; clearlast(r);
				son(e) = r;
				return 1;
			}
		}
#endif
		return(seq_distr(e, scope));

	case testbit_tag: {
		exp arg1 = son(e);
		exp arg2 = bro(arg1);
		if (name(arg1) == val_tag && name(arg2) == val_tag &&
		    !isbigval(arg1) && !isbigval(arg2)) {
			/* evaluate if args constant */
			int k = no(arg1) & no(arg2);
			if ((k != 0 && test_number(e) == 5) ||
			    (k == 0 && test_number(e) == 6)) {
				repbygo(e, pt(e), scope);
			} else {
				repbycont(e, 1, scope);
			}
			return(1);
		}
		if (name(arg1) == shr_tag && name(arg2) == val_tag &&
		    name(bro(son(arg1))) == val_tag &&
		    !isbigval(arg2) && !isbigval(bro(son(arg1)))) {
			exp x = son(arg1);
			exp nsh = bro(x);
			int places = no(nsh);
			exp res;
			sh(x) = sh(arg2);
			res = me_b3(sh(e), x,
				    me_shint(sh(arg2), no(arg2) << places),
				    testbit_tag);
			no(res) = no(e);
			pt(res) = pt(e);
			settest_number(res, test_number(e));
			replace(e, hold_check(res), scope);
			retcell(e);
			return 1;
		}
		return(0);
	}

	case test_tag: {
		exp arg1, arg2;
		int n;
		int bl;
		unsigned char nt = test_number(e);
		arg1 = son(e);
		arg2 = bro(arg1);

		if (flpt_always_comparable ||
		    (name(sh(arg1)) < shrealhd || name(sh(arg1)) > doublehd)) {
			switch (nt) {
			case 7:
				nt = f_greater_than;
				break;
			case 8:
				nt = f_greater_than_or_equal;
				break;
			case 9:
				nt = f_less_than;
				break;
			case 10:
				nt = f_less_than_or_equal;
				break;
			case 11:
				nt = f_not_equal;
				break;
			case 12:
				nt = f_equal;
				break;
			case 13:
				repbycont(e, 1, scope);
				return 1;
			case 14:
				repbygo(e, pt(e), scope);
				return 1;
			default:
				break;
			}
		}

		settest_number(e, nt);

		/* evaluate constant expressions */

		if ((name(arg1) == val_tag || name(arg1) == null_tag) &&
		    (name(arg2) == val_tag || name(arg2) == null_tag)) {
			/* see if we know which way to jump and replace by
			 * unconditional goto or nop. For integers. */
			int c = docmp_f((int)test_number(e), arg1, arg2);

			if (c) {
				repbycont(e, 1, scope);
			} else {
				repbygo(e, pt(e), scope);
			}
			return(1);
		}
		if (test_number(e) >= 5 &&
		    ((name(arg1) == null_tag && no(arg1) == 0 &&
		      name(arg2) == name_tag && isvar(son(arg2))) ||
		     (name(arg2) == null_tag && no(arg2) == 0 &&
		      name(arg1) == name_tag && isvar(son(arg1))))) {
			/* if we are comparing null with a variable we
			   know the way to jump. */
			if (test_number(e) == 6) {
				repbycont(e, 1, scope);
			} else {
				repbygo(e, pt(e), scope);
			}
			return 1;
		}
		if (name(arg1) == real_tag && name(arg2) == real_tag &&
		    test_number(e) <= 6) {
			/* similar for reals */
			if (cmpflpt(no(arg1), no(arg2),
				    (int)(test_number(e)))) {
				repbycont(e, 1, scope);
			} else {
				repbygo(e, pt(e), scope);
			}
			return(1);
		}

		/* end of constant expression evaluation */

		if (name(arg1) == val_tag || name(arg1) == real_tag ||
		    name(arg1) == null_tag) {
			/* constant argument always second */
			son(e) = arg2;
			bro(arg2) = arg1;
			bro(arg1) = e;
			setlast(arg1);
			clearlast(arg2);
			arg2 = arg1;
			arg1 = son(e);
			nt = exchange_ntest[nt];
			settest_number(e, nt);
		}

		if (name(arg1) == chvar_tag && name(arg2) == chvar_tag &&
		    name(sh(son(arg1))) == name(sh(son(arg2))) &&
		    shape_size(sh(son(arg1))) <= shape_size(sh(arg1)) &&

#if only_lengthen_ops
		    shape_size(sh(arg1)) >= 16 &&
#endif
		    (is_signed(sh(son(arg1))) == is_signed(sh(arg1)))) {
			exp ee;
#if is80x86 || ishppa
			/* optimise if both args are result of sign extension
			 * removal */
			if ((test_number(e) == f_equal ||
			     test_number(e) == f_not_equal) &&
			    name(sh(arg1)) == slonghd &&
			    name(son(arg1)) == cont_tag &&
			    name(son(arg2)) == cont_tag &&
			    shape_size(sh(son(arg1))) == 16 &&
			    name(son(son(arg1))) == name_tag &&
			    name(son(son(arg2))) == name_tag) {
				exp dec1 = son(son(son(arg1)));
				exp dec2 = son(son(son(arg2)));
				if (isse_opt(dec1) && isse_opt(dec2)) {
					son(e) = son(arg1);
					sh(son(arg1)) = slongsh;
					clearlast(son(arg1));
					bro(son(arg1)) = son(arg2);
					sh(son(arg2)) = slongsh;
					setlast(son(arg2));
					bro(son(arg2)) = e;
					return 0;
				}
			}
#endif
			/* arrange to do test in smallest size integers by
			 * removing chvar and altering shape of test args */
			ee = copyexp(e);
			son(ee) = son(arg1);
			bro(son(arg1)) = son(arg2);
			clearlast(son(arg1));
			replace(e, hc(ee, bro(son(ee))), scope);
			retcell(arg1);
			retcell(arg2);
			retcell(e);
			return(1);
		}
#if little_end & has_byte_ops
		/* only for little enders with byte and short operations */
		if (name(arg2) == val_tag && !isbigval(arg2) && no(arg2) == 0 &&
		    name(arg1) == and_tag && test_number(e) >= 5) {
			/* e = test(val, and(a, b)) and test is == or != */
			exp r, t, q;
			if (last(bro(son(arg1)))) {
				if (name(son(arg1)) == chvar_tag &&
				    name(bro(son(arg1))) == val_tag) {
					/* e = test(val, and(chvar(x), val)) */
					exp v = bro(son(arg1));
					sh(v) = sh(son(son(arg1)));
					son(arg1) = son(son(arg1));
					clearlast(son(arg1));
					bro(son(arg1)) = v;
				}
				r = getexp(f_top, nilexp, 0, son(arg1), pt(e),
					   0, 0, testbit_tag);
				no(r) = no(e);
				settest_number(r, test_number(e));
				replace(e, hc(r, bro(son(r))), scope);
				retcell(e);
				return(1);
			}

			t = son(arg1);
			while (!last(bro(t))) {
				t = bro(t);
			}
			q = bro(t);
			setlast(t);
			bro(t) = arg1;
			r = getexp(f_top, nilexp, 0, q, pt(e), 0, 0,
				   testbit_tag);
			no(r) = no(e);
			settest_number(r, test_number(e));
			clearlast(q);
			bro(q) = arg1;
			setlast(arg1);
			bro(arg1) = r;
			replace(e, r, scope);
			retcell(e);
			return(1);
		}
		/* use if little end machine */
		if (name(arg2) == val_tag && !isbigval(arg2) &&
		    ((name(arg1) == chvar_tag &&
		      name(sh(arg1)) > name(sh(son(arg1))) &&
		      is_signed(sh(arg1)) == is_signed(sh(son(arg1)))) ||
		     (name(arg1) == bitf_to_int_tag &&
		      name(son(arg1)) == cont_tag &&
		      (shape_size(sh(son(arg1))) == 8 ||
		       shape_size(sh(son(arg1))) == 16) &&
		      name(son(son(arg1))) == reff_tag &&
		      (no(son(son(arg1))) & 7) == 0))) {
			/* e = test(chvar(x), val) and chvar lengthens */
			n = no(arg2);
			switch (shape_size(sh(son(arg1)))) {
			case 8:
				if (is_signed(sh(son(arg1)))) {
					bl = (n >= -128) & (n <= 127);
					break;
				} else {
					bl = (n >= 0) & (n <= 255);
					break;
				}
			case 16:
				if (is_signed(sh(son(arg1)))) {
					bl = (n >= -32768) & (n <= 32767);
					break;
				} else {
					bl = (n >= 0) & (n <= 65536);
					break;
				}
			default:
				bl = 0;
				break;
			}
			if (bl) {
				exp ee = copyexp(e);
				son(ee) = son(arg1);
				bro(son(arg1)) = arg2;
				clearlast(son(arg1));
				sh(arg2) = sh(son(arg1));
				replace(e, hc(ee, bro(son(ee))), scope);
				retcell(arg1);
				retcell(e);
				return(1);
			}
			return(0);
		}

		if (name(arg2) == val_tag && !isbigval(arg2) && no(arg2) == 0 &&
		    test_number(e) >= 5 && name(arg1) == bitf_to_int_tag &&
		    shape_size(sh(arg1)) == 32 && name(son(arg1)) == cont_tag &&
		    name(son(son(arg1))) == reff_tag) {
			exp rf = son(son(arg1));

			if (al1(sh(son(rf))) >= 32) {
				int pos = no(rf) % 32;
				exp c = son(arg1);
				int nbits = shape_size(sh(c));
				exp r;

				no(rf) -= pos;
				sh(rf) = getshape(0, const_al32, const_al32,
						  PTR_ALIGN, PTR_SZ, ptrhd);
				sh(c) = slongsh;

				if (no(rf) == 0) {
					sh(son(rf)) = sh(rf);
					son(c) = son(rf);
					setfather(c, son(c));
				}

				sh(arg2) = slongsh;
				no(arg2) = ~(- (1 << nbits)) << pos;

				r = getexp(f_top, nilexp, 0, c, pt(e), 0, 0,
					   testbit_tag);
				no(r) = no(e);
				settest_number(r, test_number(e));
				clearlast(c);
				bro(c) = arg2;
				replace(e, hc(r, arg2), scope);
				retcell(e);
				return 1;
			}
		}

		if (name(arg1) == shr_tag && name(arg2) == val_tag &&
		    no(arg2) == 0 && nt >= 5) {
			exp arg11 = son(arg1);
			/* no of places shifted right */
			exp arg12 = bro(arg11);

			if (name(arg11) == shl_tag && name(arg12) == val_tag) {
				exp arg111 = son(arg11);
				/* no places shifted left */
				exp arg112 = bro(arg111);

				if (name(arg112) == val_tag &&
				    no(arg112) <= no(arg12)) { 
					/* right shift */
					int n2 = no(arg12);
					/* left shift */
					int n12 = no(arg112);
					int sz = shape_size(sh(arg1));
					int mask = ((1 << (sz - n2)) - 1) <<
					    (n2 - n12);
					exp res = me_b3(sh(arg1), arg111,
						  me_shint(sh(arg1), mask),
						  and_tag);
					res = hold_check(res);
					replace(arg1, res, res);
					return check(e, scope);
				}
			}
		}

		if (name(arg1) == chvar_tag && name(arg2) == val_tag &&
		    !isbigval(arg2) &&
		    shape_size(sh(arg1)) > shape_size(sh(son(arg1))) &&
		    name(son(arg1)) == cont_tag &&
		    (name(son(son(arg1))) != name_tag ||
		     !isvar(son(son(son(arg1)))))) {
			exp q = son(arg1);
			shape sha = sh(q);
			int shsz = shape_size(sha);
			int n = no(arg2);
			if (n >= 0 &&
			    is_signed(sha) == is_signed(sh(arg1)) &&
			    ((shsz == 16 && n <= 32768) ||
			     (shsz == 8 && n <= 128))) {
				sh(arg2) = sha;
				son(e) = q;
				clearlast(q);
				bro(q) = arg2;
				retcell(arg1);
				return 1;
			}
		}
#endif
		return(seq_distr(e, scope));
	}
		
	/* eliminate dead code */
	case solve_tag: {
		exp t = son(e);
		exp q;
		int changed = 0;
		int looping;

		if (last(t)) {
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, t);
			}
#endif
			replace(e, copy(t), scope);
			kill_exp(e, e);
			return(1);
		}

		if (name(t) == goto_tag && no(son(pt(t))) == 1) {
			exp lab = pt(t);
			q = bro(t);
			while (q != e) {
				if (q == lab) {
					break;
				}
				q = bro(q);
			}
			if (q != e) {
				exp rep = copy(bro(son(lab)));
#ifdef NEWDIAGS
				/* note copy, in case original is removed ! */
#endif
				replace(t, rep, rep);
				kill_exp(t, t);
				t = rep;
			}
		}

		do {
			if (no(son(bro(t))) == 0) {
				changed = 1;
				q = bro(t);
				bro(t) = bro(q);
				if (last(q)) {
					setlast(t);
				} else {
					clearlast(t);
				}
#ifdef NEWDIAGS
				if (diagnose) {
					dg_dead_code(bro(son(q)), t);
				}
#endif
				kill_exp(q, q);
				looping = !last(t);
			} else {
				looping = !last(bro(t));
				t = bro(t);
			}
		} while (looping);

		if (last(son(e))) {
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(e, son(e));
			}
#endif
			replace(e, copy(son(e)), scope);
			kill_exp(e, e);
			return(1);
		}

		if (changed) {
			return(1);
		}
		return(0);
	}

	case case_tag:
		if (name(son(e)) == val_tag) {
			/* if we know the case argument select the right case
			 * branch and replace by goto. Knock on effect will be
			 * to eliminate dead code. */
			exp n = son(e);
			int changed = 0;
			exp t = son(e);
			exp z;
			do {
				exp up;
				t = bro(t);
				if (son(t) == nilexp) {
					up = t;
				} else {
					up = son(t);
				}

				if (docmp_f((int)f_less_than_or_equal, t, n) &&
				    docmp_f((int)f_less_than_or_equal, n, up)) {
					changed = 1;
					z = pt(t);
				}
				/*	  else
					  --no(son(pt(t)));
				 */
			} while (!last(t));

			if (!changed) {
				repbycont(e, 0, scope);
			} else {
				SET(z);
				repbygo(e, z, scope);
			}
			return(1);
		}
		return(0);
		
	case rep_tag:
	case apply_general_tag:
	case set_stack_limit_tag:
	case give_stack_limit_tag:
	case env_size_tag:
	case apply_tag:
	case res_tag:
	case goto_lv_tag:
	case assvol_tag:
	case local_free_all_tag:
	case local_free_tag:
	case last_local_tag:
	case long_jump_tag:
	case movecont_tag:
		return(0);
		
	case alloca_tag:
		if (name(son(e)) == chvar_tag &&
		    name(sh(son(son(e)))) == ulonghd) {
			replace(son(e), son(son(e)), son(e));
		}
		return(0);
		
	case nof_tag:
	case labst_tag:
		return 0;

	case concatnof_tag: {
		exp a1 = son(e);
		exp a2 = bro(a1);
		exp r;
		nat n;
		if (name(a1) == string_tag && name(a2) == string_tag) {
			/* apply if args constant */
			char *s1 = nostr(son(e));
			char *s2 = nostr(bro(son(e)));
			/* note NOT zero termination convention !! */
			int sz1, sz2, i;
			char *newstr;
			char *p2;
			shape newsh;
			sz1 = shape_size(sh(son(e))) / 8;
			sz2 = shape_size(sh(bro(son(e)))) / 8;
			newstr = (char *)xcalloc((sz1 + sz2), sizeof(char));
			p2 = &newstr[sz1];
			nat_issmall(n) = 1;
			natint(n) = sz1 + sz2;
			newsh = f_nof(n, scharsh);
			for (i = 0; i < sz1; ++i) {
				newstr[i] = s1[i];
			}
			for (i = 0; i < sz2; ++i) {
				p2[i] = s2[i];
			}
			r = getexp(newsh, nilexp, 0, nilexp, nilexp, 0, 0,
				   string_tag);
			nostr(r) = newstr;
			replace(e, r, scope);
			kill_exp(e, scope);
			return(1);
		}
		return 0;
	}

	case ncopies_tag:
	case ignorable_tag:
		return 0;

	case bfass_tag:
	case bfassvol_tag: {
		exp p = son(e);
		exp val = bro(p);
		int bsz = shape_size(sh(val));
		int rsz;
		int rsh;
		int sg = is_signed(sh(val));
		int posmask;
		int negmask;
		int off = no(e);
		exp ref;
		exp cont;
		exp eshift;
		exp res;
		exp id;
		exp idval;
		shape ptr_sha;
		shape msh;
		int temp = off + bsz - 1;

		if (((off / 8) == (temp / 8)) && bsz <= 8
#if 0
		    (bsz == 8 &&
		     ((little_end && (off%8 == 0)) ||
		      (!little_end && ((8 - (off % 8) - bsz) == 0))))
#endif
		   ) {
			rsz = 8;
			if (sg) {
				msh = scharsh;
			} else {
				msh = ucharsh;
			}
		} else if (((off / 16) == (temp / 16)) && bsz <= 16
#if 0
			   (bsz == 16 &&
			    ((little_end && (off%16 == 0)) ||
			     (!little_end && ((16 - (off % 16) - bsz) == 0))))
#endif
			  ) {
			rsz = 16;
			if (sg) {
				msh = swordsh;
			} else {
				msh = uwordsh;
			}
		} else if ((off / 32) == (temp / 32)) {
			rsz = 32;
			if (sg) {
				msh = slongsh;
			} else {
				msh = ulongsh;
			}
		} else {
			rsz = 64;
			if (sg) {
				msh = s64sh;
			} else {
				msh = u64sh;
			}
		}
		ptr_sha = f_pointer(long_to_al(rsz));

		if ((off / rsz) != 0) {
			ref = me_u3(ptr_sha, p, reff_tag);
			no(ref) = (off / rsz) * rsz;
			ref = hold_check(ref);
		} else {
			ref = p;
		}
		id = me_startid(f_top, ref, 0);
#if little_end
		rsh = off % rsz;
#else
		rsh = rsz - (off % rsz) - bsz;
#endif
		posmask = (bsz == 32) ? -1 : (1 << bsz) -1;
		negmask = ~(posmask << rsh);
		cont = me_u3(msh, me_obtain(id), (name(e) == bfass_tag) ?
			     (unsigned char)cont_tag :
			     (unsigned char)contvol_tag);
		val = hold_check(me_u3(msh, val, chvar_tag));
		val = hold_check(me_b3(msh, val, me_shint(msh, posmask),
				       and_tag));
		if (rsh != 0) {
			eshift = hold_check(me_b3(msh, val, me_shint(slongsh,
								rsh), shl_tag));
		} else {
			eshift = val;
			sh(eshift) = msh;
		}
		idval = me_startid(f_top, eshift, 0);

		if (rsz != bsz) {
			cont = me_b3(msh, cont, me_shint(msh, negmask),
				     and_tag);
			cont = hold_check(me_b3(msh, cont, me_obtain(idval),
						or_tag));
		} else {
			kill_exp(cont, cont);
			cont = me_obtain(idval);
		}
		res = me_b3(f_top, me_obtain(id), cont,
			    (name(e) == bfass_tag) ? (unsigned char)ass_tag :
			    (unsigned char)assvol_tag);
		res = hold_check(me_complete_id(idval, res));
		replace(e, hold_check(me_complete_id(id, res)), scope);
		retcell(e);
		return 1;
	}
	default:
		return(0);
	}
}
