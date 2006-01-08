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
#include "msgcat.h"

#include "common_types.h"
#include "tags.h"
#include "basicread.h"
#include "exp.h"
#include "shapemacs.h"
#include "flpt.h"
#include "coder.h"
#include "instr.h"
#include "out.h"
#include "check.h"
#include "codermacs.h"
#include "externs.h"
#include "install_fns.h"
#include "table_fns.h"
#include "flags.h"
#include "instr386.h"
#include "machine.h"
#include "localflags.h"
#include "assembler.h"
#include "messages_8.h"
#include "diag_fns.h"
#include "operand.h"


/* VARIABLES */
/* All variables initialised */

int  crt_proc_id;	/* init by cproc */
int  stack_dec;		/* init by cproc */
/* current stack decrement */
exp const_list;		/* init by init_all */
/* list of constants belonging to current
 *				   procedure */

/* PROCEDURES */

/* turns an exp and an offset (in bits)
 *   into a where */
where
mw(exp e, int off)
{
	where w;
	w.where_exp = e;
	w.where_off = off;
	return (w);
}

/* compares wheres for equality of operand.
 *   This is also used by equiv_reg to detect
 *   invalidity of register copy, in which case
 *   we need to detect overlaps, this case
 *   determined by 'overlap' */
int
eq_where_exp(exp a, exp b, int first, int overlap)
{
	unsigned char  na;
	unsigned char  nb;

  rept:
	na = name(a);
	nb = name(b);

	if (a == b)
		return (1);
	if (na == nb) {		/* same kind of operation "equal names" */
		if (na == val_tag && !isbigval(a) && !isbigval(b))
			return (no (a) == no (b));
		if (na == ident_tag) {
			int good = son(a) != nilexp && son(b) != nilexp &&
				bro(son(a)) != nilexp && bro(son(b)) != nilexp;
			if (good) {
				exp bsa = bro(son(a));
				exp bsb = bro(son(b));
				if (name (bsa) == name_tag && son (bsa) == a &&
					name (bsb) == name_tag && son (bsb) == b) {
					a = son(a);
					b = son(b);
					first = 0;
					goto rept;
				}
				if (name (bsa) == reff_tag &&
					name (bsb) == reff_tag &&
					(overlap ? (no (bsa) & -32) == (no (bsb) & -32) : no (bsa) == no (bsb)) &&
					name (son (bsa)) == name_tag &&
					son (son (bsa)) == a &&
					name (son (bsb)) == name_tag &&
					son (son (bsb)) == b) {
					a = son(a);
					b = son(b);
					first = 0;
					goto rept;
				}
			}
			if (isglob(a) || isglob(b))
				return 0;
			return (pt (a) == pt (b) &&
					(overlap ? (no (a) & -32) == (no (b) & -32) : no (a) == no (b)));
		}
		if (na == name_tag) {
			if ((overlap ? (no (a) & -32) != (no (b) & -32) : no (a) != no (b)) ||
				(isvar (son (a)) != isvar (son (b))))
				return (0);
			a = son(a);
			b = son(b);
			first = 0;
			goto rept;
		}
		if (na == cont_tag || na == ass_tag) {
			a = son(a);
			b = son(b);
			first = 0;
			goto rept;
		}
		if (na == field_tag || na == reff_tag) {
			if (overlap ? (no (a) & -32) != (no (b) & -32) : no (a) != no (b))
				return (0);
			a = son(a);
			b = son(b);
			first = 0;
			goto rept;
		}
		if (na == real_tag && name (sh (a)) == name (sh (b))) {
			flt fa, fb;
			int  i;
			int is_zero = 1;
			fa = flptnos[no (a)];
			fb = flptnos[no (b)];

			for (i = 0; i < MANT_SIZE && (fa.mant)[i] == (fb.mant)[i];
				 i++) {
				if ((fa.mant)[i] != 0)
					is_zero = 0;
			}

			return (i == MANT_SIZE &&
					(is_zero || (fa.exp == fb.exp &&
								 fa.sign == fb.sign)));

		}
		return (0);
	}				/* end equal names */


	if (na == name_tag && nb == ident_tag && first) {
		if (overlap ? (no (a) & -32) != 0 : no (a) != 0)
			return (0);
		a = son(a);
		first = 0;
		goto rept;
	}
	if (na == ident_tag && nb == name_tag && first) {
		if (overlap ? (no (b) & -32) != 0 : no (b) != 0)
			return (0);
		b = son(b);
		first = 0;
		goto rept;
	}

	if (na == cont_tag && name(son(a)) == name_tag &&
		isvar(son(son(a))) && nb == ident_tag && first) {
		if (overlap ? (no (son(a)) & -32) != 0 : no (son(a)) != 0)
			return (0);
		a = son(son(a));
		first = 0;
		goto rept;
	}
	if (na == ident_tag && nb == cont_tag && name(son(b)) == name_tag
		&& isvar(son(son(b))) && first) {
		if (overlap ? (no (son(b)) & -32) != 0 : no (son(b)) != 0)
			return (0);
		b = son(b);
		first = 0;
		goto rept;
	}

	if ((na == cont_tag || na == ass_tag) &&
		name (son (a)) == name_tag &&
		isvar (son (son (a))) && nb == name_tag && !isvar (son (b))) {
		if (overlap ? (no (son(a)) & -32) != (no (b) & -32) : no (son(a)) != no (b))
			return (0);
		a = son (son (a));
		b = son (b);
		first = 0;
		goto rept;
	}
	if ((nb == cont_tag || nb == ass_tag) &&
		name (son (b)) == name_tag &&
		isvar (son (son (b))) && na == name_tag && !isvar (son (a))) {
		if (overlap ? (no (son(b)) & -32) != (no (a) & -32) : no (son(b)) != no (a))
			return (0);
		a = son (a);
		b = son (son (b));
		first = 0;
		goto rept;
	}
	if ((na == ass_tag && nb == cont_tag) ||
		(nb == ass_tag && na == cont_tag)) {
		a = son(a);
		b = son(b);
		first = 0;
		goto rept;
	}
	return (0);
}

/* compares wheres for equality of operand */
int
eq_where(where wa, where wb)
{
	exp a = wa.where_exp;
	exp b = wb.where_exp;
	if (a == nilexp || b == nilexp)
		return 0;
	if (wa.where_off != wb.where_off)
		return (0);
	return eq_where_exp (a, b, 1, 0);
}


/* find the first register in the register bit pattern r */
frr
first_reg(int r)
{
	frr t;
	t.regno = 1;
	t.fr_no = 0;
	if (r == 0)
		MSG_fatal_illegal_register();
	else {
		while (!(t.regno & r)) {
			t.regno = t.regno << 1;
			++t.fr_no;
		}
	}
	return (t);
}

/* output operand,  wh is a where Note
 *   that the pt field of a declaration now
 *   hold a code for the position of the
 *   value (eg. reg_pl for in a register,
 *   local_pl for relative to sp etc.). The
 *   no field hold the location, bit pattern
 *   for register, offset (in bits) for
 *   local etc. stack_dec hold the amount
 *   the stack is decremented from its
 *   position at the start of the procedure
 *   (ie the place where no is measured
 *   from). This is to allow for push
 *   operations. b is passed to extn to
 *   control whether a bracket is output
 *   (index instructions). addr is true if
 *   we need a literal address. */
void
operand(int le, where wh, int b, int addr)
{
	exp w = wh.where_exp;
	int  off = wh.where_off;
	unsigned char  n = name (w);

	if (n == val_tag && !isbigval(w)) {		/* integer constant */
		int  k = no (w) + off;
		if (name(sh(w)) == SH_OFFSET && al2(sh(w)) != 1)
			k = k / 8;
		int_operand (k, le);
		return;
	}

	if (n == ident_tag || n == labst_tag) {/* can only be dest */
		switch (ptno (w)) {
		case local_pl: {
			rel_sp ((no (w) + off - stack_dec) / 8, b);
			return;
		}
		case reg_pl: {
			regn (no (w), off, w, le);
			return;
		}
		default: {
			MSG_fatal_illegal_operand();
		}
		}
	}

	if (n == name_tag) {
		exp ident = son (w);
		int  noff = no (w) + off;
		int  ni = no (ident);

		if (isglob (ident)) {
			if (name (sh (w)) == SH_PROC)	/* special treatment for procedures */
			{
				const_extn (ident, noff);
				return;
			}

			if (isvar (ident))
				const_extn (ident, noff);
			else
				extn (ident, noff, b);
			return;
		}

		switch (ptno (ident)) {
		case local_pl: {		/* local so relative to stack pointer or fp */
			rel_sp ((ni + noff - stack_dec) / 8, b);
			return;
		}
		case callstack_pl: {	/* caller arg so relative to stack pointer */
			rel_cp ((ni + noff - stack_dec) / 8, b);
			return;
		}
		case par_pl: {		/* parameter so relative to fp */
			rel_ap ((ni + noff + 32) / 8, b);
			return;
		}
		case reg_pl: {		/* in a register */
			regn (ni, noff, w, le);
			return;
		}
		case ferr_pl: {		/* relative to fp, depending on push space */
			rel_ap1 ((ni + noff) / 8, b);
			return;
		}
		default: {		/* doesnt happen */
			MSG_fatal_illegal_operand();
		}
		}
	}

	if (n == cont_tag || n == ass_tag) {
		exp ref = son (w);
		unsigned char  s = name (ref);
		if (addr) {
			operand (le, mw (son (w), 0), b, 0);
			return;
		}
		if (s == name_tag) {	/* content of id */
			if (!isvar (son (ref))) {
				exp ident = son (ref);
				if (ptno (ident) != reg_pl && off != 0) {
					MSG_fatal_illegal_operand();
				}
				if (isglob (ident)) {
					if (name (sh (w)) != SH_PROC)
						MSG_fatal_illegal_operand();

					if (PIC_code)
						proc_extn (ident, no(ref));
					else
						extn (ident, no (ref), b);
					return;
				}
				switch (ptno (ident)) {
				case reg_pl: {	/* indirect from register */
					ind_reg (no (ident), no (ref), off, ref, b);
					return;
				}
				default:
					MSG_fatal_illegal_operand();
				}
			}
			else {			/* variable */

				exp ident = son (ref);
				int  noff = no (ref) + off;
				int  ni = no (ident);

				if (isglob (ident)) {
					extn (ident, noff, b);
					return;
				}
				switch (ptno (ident)) {
				case local_pl: {
					/* local so relative to stack pointer or fp */
					rel_sp ((ni + noff - stack_dec) / 8, b);
					return;
				}
				case callstack_pl: {
					/* caller arg so relative to stack pointer */
					rel_cp ((ni + noff - stack_dec) / 8, b);
					return;
				}
				case par_pl: {	/* parameter so relative to fp */
					rel_ap ((ni + noff + 32) / 8, b);
					return;
				}
				case reg_pl: {	/* in a register */
					regn (ni, noff, ref, le);
					return;
				}
				default:		/* doesnt happen */
					MSG_fatal_illegal_operand();
				}
			}
		}				/* end of cont(name) */

		if (s == cont_tag && name (son (ref)) == name_tag &&
			isvar (son (son (ref)))) {
			exp ident = son (son (ref));
			if (ptno (ident) != reg_pl && off != 0)
				MSG_fatal_illegal_operand();
			if (isglob (ident)) {
				if (name (sh (w)) != SH_PROC)
					MSG_fatal_illegal_operand();

				extn (ident, no (son (ref)), b);
				return;
			}
			switch (ptno (ident)) {
			case reg_pl: {		/* indirect from register */
				ind_reg (no (ident), no (son (ref)), off, ref, b);
				return;
			}
			default:
				MSG_fatal_illegal_operand();
			}
		}				/* end of cont(cont(var)) */


		if (s == reff_tag) {
			exp et = son (ref);
			unsigned char  t = name (et);
			if (t == name_tag) {
				if (isglob (son (et))) {
					extn (son (et), no (ref), b);
					return;
				}
				switch (ptno (son (et))) {
				case reg_pl: {
					ind_reg (no (son (et)), no (et), (no (ref) + off), et, b);
					return;
				}
				default:
					MSG_fatal_illegal_operand();
				}
			}			/* end of cont(reff(name)) */

			if (t == cont_tag) {
				switch (ptno (son (son (et)))) {
				case reg_pl: {
					ind_reg (no (son (son (et))), no (son (et)),
							 (no (ref) + off), son (et), b);
					return;
				}
				default:
					MSG_fatal_illegal_operand();
				}
			}			/* end of cont(ref(cont())) */

			if (t == addptr_tag) {
				where new_w;
				new_w.where_exp = et;
				new_w.where_off = off + no (ref);
				operand (le, new_w, b, 0);
				return;
			}			/* end of cont(reff(addptr())) */
			MSG_fatal_illegal_operand();
		}				/* end of cont(reff()) */

		if (s == addptr_tag) {
			exp u = bro (son (ref));
			exp c = getexp (f_bottom, nilexp, 0, son (ref), nilexp,
							0, 0, cont_tag);
			where wc, wu;
			wc.where_exp = c;
			wc.where_off = off;
			wu.where_exp = u;
			wu.where_off = 0;
			if (name (u) == name_tag || name (u) == cont_tag) {
				index_opnd (wc, wu, 1);
				return;
			}			/* end of cont(addptr(-, name)) */

			if (name (u) == offset_mult_tag) {
				int  k = no (bro (son (u)))/8;	/* cannot be bitfield */
				wu.where_exp = son (u);
				index_opnd (wc, wu, k);
				return;
			}			/* end of cont(addptr(-, mult)) */
		}				/* end of cont(addptr()) */


	}				/* end of cont */


	if (n == reff_tag) {
		exp se = son (w);
		unsigned char  s = name (se);
		if (s == name_tag) {
			if (isglob (son (se))) {
				extn (son (se), no (w), b);
				return;
			}
			switch (ptno (son (se))) {
			case reg_pl: {
				ind_reg (no (son (se)), no (son (se)), no (w), se, b);
				return;
			}
			default:
				MSG_fatal_illegal_operand();
			}
		}				/* end of reff(name)  */

		if (s == cont_tag) {
			if (isglob (son (son (se)))) {
				extn (son (son (se)), no (w), b);
				return;
			}
			switch (ptno (son (son (se)))) {
			case reg_pl: {
				ind_reg (no (son (son (se))), no (son (se)),
						 no (w), son (se), b);
				return;
			}
			default:
				MSG_fatal_illegal_operand();
			}
		}				/* end of reff(cont()) */

		if (s == addptr_tag) {
			where ww;
			ww.where_exp = se;
			ww.where_off = off + no (w);
			operand (le, ww, b, 0);
			return;
		}				/* end of reff(addptr()) */
	}				/* end of reff() */

	if (n == addptr_tag) {
		exp u = bro (son (w));
		exp c = getexp (f_bottom, nilexp, 0, son (w), nilexp, 0, 0, cont_tag);
		where wc, wu;
		wc.where_exp = c;
		wc.where_off = off;
		wu.where_exp = u;
		wu.where_off = 0;
		if (name (u) == name_tag || name (u) == cont_tag) {
			index_opnd (wc, wu, 1);
			return;
		}				/* end of addptr(-, name)  */

		if (name (u) == offset_mult_tag) {
			int  k = no (bro (son (u)))/8;	/* cannot be bitfield */
			wu.where_exp = son (u);
			index_opnd (wc, wu, k);
			return;
		}				/* end of addptr(-, mult) */
	}				/* end of addptr() */

	if (n == real_tag || n == val_tag || n == string_tag ||
		n == proc_tag || n == general_proc_tag) {
		int  ln;
		if (off == 0 || addr) {
			ln = next_lab ();
			const_list = getexp (f_bottom, const_list, 0, w, nilexp, 0, ln, 0);
			const_intnl ((addr || n == proc_tag || n == general_proc_tag), ln, 0);
			return;
		}
		/* assumes this is only used just after using the first part of the
		 *       constant */
		const_intnl (0, no (const_list), off);
		return;
	}

	if (n == res_tag) {
		const_intnl (0, no (w), off);
		return;
	}

	if (n == null_tag) {
		int_operand (no(w), le);
		return;
	}

	if (n == field_tag) {
		operand (le, mw (son (w), off + no (w)), b, addr);
		return;
	}

	if (n == make_lv_tag) {
		label_operand(w);
		return;
	}

	if (n == current_env_tag) {
		outbp();
		return;
	}

	if (n == env_offset_tag) {
		if (name(son(w))==0) {	/* must be caller arg with var_callees */
			int_operand(no(son(w))/8, le);
			return;
		}
		outs("$");
		envoff_operand(son(w), no(w));
		return;
	}

	if (n == env_size_tag) {
		outs("$");
		envsize_operand(son(son(w)));
		return;
	}

	if (n == local_free_all_tag) {
		ldisp();
		return;
	}

	if (n == clear_tag) {
		/* any legal operand will do! */
		if (name(sh(w)) >= SH_REAL_SHORT && name(sh(w)) <= SH_DOUBLE) {
			outs("%st");
			return;
		}
		switch (shape_size(sh(w))) {
		case 8:
			outs("%al");
			return;
		case 16:
			outs("%ax");
			return;
		default:
			outs("%eax");
			return;
		}
	}

	MSG_fatal_illegal_operand();
}
