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


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "basicread.h"
#include "check.h"
#include "exp.h"
#include "externs.h"
#include "install_fns.h"
#include "shapemacs.h"
#include "tags.h"
#include "mach.h"
#include "mach_ins.h"
#include "where.h"
#include "mach_op.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "coder.h"
#include "tests.h"
#include "operations.h"
#include "evaluate.h"
#include "utility.h"
#include "translate.h"
#include "ops_shared.h"


/*
 *    MARKERS FOR AND, OR AND XOR
 *
 *    The logical operations, and, or and xor are handled by a single
 *    routine with a flag to indicate which is meant.  The flag can take
 *    the following values.
 */

#define  AND		0
#define  OR		1
#define  XOR		2


/*
 *    AND/OR/XOR BY A CONSTANT
 *
 *    The value a of shape sha and size sz has the logical operator indicated
 *    by logop applied to it and the constant c.  The result is stored in
 *    dest.  instr is one of m_andl, m_orl, eorl.
 */

static void
andetc_const(int instr, shape sha, long sz,
			 long c, where a, where dest,
			 int logop)
{
    long whd;
	
    /* First check that a is not a constant */
    if (whereis (a) == Value) {
		long ca = nw (a);
		switch (logop) {
	    case AND : ca &= c ; break;
	    case OR  : ca |= c ; break;
	    case XOR : ca ^= c ; break;
		}
		move (sha, mnw (ca), dest);
		return;
    }
	
    /* Now look for some special values of c */
    switch (logop) {
		
	case AND : {
	    long cc;
	    if (c == 0) {
			move (sha, zero, dest);
			return;
	    }
	    cc = ~c;
	    if (sz == 32) {
			if (cc == 0) {
				change_var (sha, a, dest);
				return;
			}
			if (is_pow2 (cc)) {
				long p = log2 (cc);
				if (whereis (dest) == Dreg) {
					change_var (sha, a, dest);
					ins2n (m_bclr, p, sz, dest, 1);
					have_cond = 0;
					return;
				}
			}
	    }
	    break;
	}
		
	case OR : {
	    if (c == 0) {
			change_var (sha, a, dest);
			return;
	    }
	    if (is_pow2 (c)) {
			long p = log2 (c);
			if (whereis (dest) == Dreg) {
				change_var (sha, a, dest);
				ins2n (m_bset, p, sz, dest, 1);
				have_cond = 0;
				return;
			}
	    }
	    break;
	}
		
	case XOR : {
	    if (c == 0) {
			change_var (sha, a, dest);
			return;
	    }
	    break;
	}
    }
	
    whd = whereis (dest);
    if (whd != Areg && eq_where (a, dest)) {
		ins2h (instr, c, sz, dest, 1);
		set_cond (dest, sz);
		return;
    }
    if (whd == Dreg) {
		change_var (sha, a, dest);
		ins2h (instr, c, sz, dest, 1);
		set_cond (dest, sz);
		return;
    }
    if (whereis (a) == Dreg && last_use (a)) {
		ins2h (instr, c, sz, a, 1);
		change_var (sha, a, dest);
		set_cond (dest, sz);
		return;
    }
    change_var (sha, a, D0);
    ins2h (instr, c, sz, D0, 1);
    move (sha, D0, dest);
    set_cond (dest, sz);
    return;
}


/*
 *    AUXILIARY ROUTINE FOR AND/OR/XOR
 *
 *    The values a1 and a2 of shape sha have the logical operation indicated
 *    by logop applied to them and the result is stored in dest.  (opb,
 *    opw, opl) is an ordered triple giving the byte, word and long forms of
 *    the appropriate machine instruction.
 */

static void
andetc(int opb, int opw, int opl, shape sha,
	   where a1, where a2, where dest, int logop)
{
    int instr;
    long wha, whb, whd;
    long sz = shape_size (sha);
	
    if (eq_where (a1, a2)) {
		switch (logop) {
	    case AND : move (sha, a1, dest) ; return;
	    case OR  : move (sha, a1, dest) ; return;
	    case XOR : move (sha, zero, dest) ; return;
		}
    }
	
    instr = ins (sz, opb, opw, opl);
	
    wha = whereis (a1);
    whb = whereis (a2);
	
    if (wha == Freg) {
		move (sha, a1, D0);
		andetc (opb, opw, opl, sha, D0, a2, dest, logop);
		return;
    }
	
    if (whb == Freg) {
		move (sha, a2, D0);
		andetc (opb, opw, opl, sha, a1, D0, dest, logop);
		return;
    }
	
    if (wha == Value) {
		long c = nw (a1);
		andetc_const (instr, sha, sz, c, a2, dest, logop);
		return;
    }
	
    if (whb == Value) {
		long c = nw (a2);
		andetc_const (instr, sha, sz, c, a1, dest, logop);
		return;
    }
	
    whd = whereis (dest);
	
    if (eq_where (a1, dest) && whd != Areg) {
		if (whb == Dreg) {
			ins2 (instr, sz, sz, a2, dest, 1);
			return;
		}
		if (whd == Dreg) {
			if (logop == XOR || whb == Areg) {
				if (eq_where (dest, D0)) {
					regsinproc |= regmsk (REG_D1);
					move (sha, a2, D1);
					ins2 (instr, sz, sz, D1, dest, 1);
					set_cond (dest, sz);
					return;
				} else {
					move (sha, a2, D0);
					ins2 (instr, sz, sz, D0, dest, 1);
					set_cond (dest, sz);
					return;
				}
			} else {
				ins2 (instr, sz, sz, a2, dest, 1);
				set_cond (dest, sz);
				return;
			}
		} else {
			move (sha, a2, D0);
			ins2 (instr, sz, sz, D0, dest, 1);
			set_cond (dest, sz);
			return;
		}
    }
	
    if (eq_where (a2, dest) && whd != Areg) {
		if (wha == Dreg) {
			ins2 (instr, sz, sz, a1, dest, 1);
			set_cond (dest, sz);
			return;
		}
		if (whd == Dreg) {
			if (logop == XOR || wha == Areg || wha == Freg) {
				if (eq_where (dest, D0)) {
					regsinproc |= regmsk (REG_D1);
					move (sha, a1, D1);
					ins2 (instr, sz, sz, D1, dest, 1);
				} else {
					move (sha, a1, D0);
					ins2 (instr, sz, sz, D0, dest, 1);
				}
			} else {
				ins2 (instr, sz, sz, a1, dest, 1);
			}
		} else {
			move (sha, a1, D0);
			ins2 (instr, sz, sz, D0, dest, 1);
		}
		set_cond (dest, sz);
		return;
    }
	
    if (whd == Dreg) {
		if (!interfere (a2, dest)) {
			move (sha, a1, dest);
			andetc (opb, opw, opl, sha, a2, dest, dest, logop);
			return;
		}
		if (!interfere (a1, dest)) {
			move (sha, a2, dest);
			andetc (opb, opw, opl, sha, a1, dest, dest, logop);
			return;
		}
    }
	
    move (sha, a1, D0);
    andetc (opb, opw, opl, sha, a2, D0, D0, logop);
    move (sha, D0, dest);
    return;
}


/*
 *    AND INSTRUCTION
 *
 *    The values a1 and a2 of shape sha are anded and the result is stored
 *    in dested.
 */

void
and(shape sha, where a1, where a2, where dest)
{
    andetc (ml_and, sha, a1, a2, dest, AND);
    return;
}


/*
 *    OR INSTRUCTION
 *
 *    The values a1 and a2 of shape sha are ored and the result is stored
 *    in dested.
 */

void
or(shape sha, where a1, where a2, where dest)
{
    andetc (ml_or, sha, a1, a2, dest, OR);
    return;
}


/*
 *    XOR INSTRUCTION
 *
 *    The values a1 and a2 of shape sha are xored and the result is stored
 *    in dested.
 */

void
xor(shape sha, where a1, where a2, where dest)
{
    andetc (ml_eor, sha, a1, a2, dest, XOR);
    return;
}


/*
 *    LOGICAL NEGATION INSTRUCTION
 *
 *    The value a of shape sha is logically negated and the result is stored
 *    in dest.
 */

void
not(shape sha, where a, where dest)
{
    int instr;
    long sz = shape_size (sha);
    long wha = whereis (a);
    long whd = whereis (dest);
	
    if (wha == Value) {
		long c = nw (a);
		move (sha, mnw (~c), dest);
		return;
    }
	
    if (eq_where (a, dest) && whd != Areg) {
		instr = ins (sz, ml_not);
		ins1 (instr, sz, dest, 1);
		set_cond (dest, sz);
		return;
    }
	
    if (whd == Dreg) {
		move (sha, a, dest);
		not (sha, dest, dest);
		return;
    }
	
    if (wha == Dreg && last_use (a)) {
		not (sha, a, a);
		move (sha, a, dest);
		return;
    }
	
    move (sha, a, D0);
    not (sha, D0, D0);
    move (sha, D0, dest);
    return;
}


/*
 *    LOW LEVEL SHIFT
 *
 *    This routine outputs a simple shift instruction, taking overflow
 *    into account if necessary (not right yet).
 */

static void
shift_it(shape sha, shape shb, int instr,
		 where by, where to)
{
    long sz = shape_size (sha);
    ins2 (instr, L8, sz, by, to, 1);
    have_cond = 0;
    test_overflow(ON_OVERFLOW);
    return;
}


/*
 *    AUXILIARY SHIFT ROUTINE
 *
 *    The value from of shape sha is shifted, either left if sw is 0, or
 *    right otherwise, by the value by.  The result is stored in to.
 *    The dont_use_D1 flag indicates that register D1 should not be used.
 *    It is always false for simple shifts, but may be true for certain
 *    multiplications which are done by shifts.
 */

void
shift_aux(shape sha, where by, where from,
		  where to, int sw, int dont_use_D1)
{
    where w;
    long whb, wht;
    int instr, shift_plus, shift_minus;
	
    shape shb = sh (by.wh_exp);
    long sz = shape_size (sha);
    bool sig = is_signed (sha);
	
    switch (sz) {
	case 8 : {
	    shift_plus = (sig ? m_aslb : m_lslb);
	    shift_minus = (sig ? m_asrb : m_lsrb);
	    break;
	}
	case 16 : {
	    shift_plus = (sig ? m_aslw : m_lslw);
	    shift_minus = (sig ? m_asrw : m_lsrw);
	    break;
	}
	default : {
	    shift_plus = (sig ? m_asll : m_lsll);
	    shift_minus = (sig ? m_asrl : m_lsrl);
	    break;
	}
    }
	
    if (sw) {
		/* Switch shift_plus and shift_minus for right shifts */
		instr = shift_plus;
		shift_plus = shift_minus;
		shift_minus = instr;
    }
	
    whb = whereis (by);
    wht = whereis (to);
	
    if (whb == Value && !have_overflow ()) {
		long p = nw (by);
		if (p == 0) {
			/* A shift by 0 is a move */
			move (sha, from, to);
			return;
		}
		/* Reduce mod 64 to emulate instruction */
		p &= 0x3f;
		instr = shift_plus;
		/* Do the shift, at most eight at a time */
		if (p <= 8 || D1_is_special || dont_use_D1) {
			w = (wht == Dreg ? to : D0);
			move (sha, from, w);
			while (p) {
				long q = (p > 8 ? 7 : p);
				ins2n (instr, q, sz, w, 1);
				p -= q;
			}
			have_cond = 0;
			move (sha, w, to);
			return;
		}
		/* Fall through otherwise */
		shb = slongsh;
    }
	
    if (wht == Dreg) {
		if (whb == Dreg && !eq_where (by, to)) {
			move (sha, from, to);
			shift_it (sha, shb, shift_plus, by, to);
			return;
		}
		if (eq_where (D0, to)) {
			w = D1;
			regsinproc |= regmsk (REG_D1);
		} else {
			w = D0;
		}
		move (shb, by, w);
		move (sha, from, to);
		shift_it (sha, shb, shift_plus, w, to);
		return;
    }
	
    if (whb == Dreg) {
		if (eq_where (D0, by)) {
			w = D1;
			regsinproc |= regmsk (REG_D1);
		} else {
			w = D0;
		}
		move (sha, from, w);
		shift_it (sha, shb, shift_plus, by, w);
		move (sha, w, to);
		return;
    }
	
    regsinproc |= regmsk (REG_D1);
    move (shb, by, D0);
    move (sha, from, D1);
    shift_it (sha, shb, shift_plus, D0, D1);
    move (sha, D1, to);
    return;
}


/*
 *    MAIN LEFT SHIFT ROUTINE
 *
 *    The value from of shape sha is shifted left by the value by.  The
 *    result is stored in to.
 */

void
shift(shape sha, where by, where from, where to)
{
    shift_aux (sha, by, from, to, 0, 0);
    return;
}


/*
 *    MAIN RIGHT SHIFT ROUTINE
 *
 *    The value from of shape sha is shifted right by the value by.  The
 *    result is stored in to.
 */

void
rshift(shape sha, where by, where from, where to)
{
    shift_aux (sha, by, from, to, 1, 0);
    return;
}


/*
 *    ADJUST AN EXPRESSION READY FOR A BITFIELD OPERATION
 *
 *    The value in the no field of e is rounded down to a multiple of 32.
 *    The remainder is the bitfield offset and is returned.
 */

static long
adjust_bitf(exp e)
{
    long boff = no (e) % 32;
    no (e) -= boff;
    return (boff);
}


/*
 *    FIND POSITION OF A CONTENTS BITFIELD
 */

static long
contents_bitf(exp e)
{
    char n = name (e);
    if (n == name_tag || n == reff_tag) return (adjust_bitf (e));
    if (n == ident_tag) {
		exp s = son (e);
		exp b = bro (s);
		if (name (b) == reff_tag) return (adjust_bitf (b));
		if (name (b) == ident_tag) return (contents_bitf (b));
		if (name (b) == name_tag && son (b) == e &&
			name (s) == name_tag) {
			return (contents_bitf (son (s)));
		}
		if (name (s) == name_tag) return (adjust_bitf (s));
    }
    error ("Illegal bitfield operation");
    return (0);
}


/*
 *    FIND POSITION OF A BITFIELD OPERATION
 */

static long
bitf_posn(exp e)
{
    char n = name (e);
    if (n == name_tag) return (adjust_bitf (e));
    if (n == cont_tag || n == ass_tag) {
		return (bitf_posn (son (e)));
    }
    if (n == ident_tag) return (0);
    error ("Illegal bitfield operation");
    return (0);
}


/*
 *    EXTRACT A BITFIELD
 *
 *    The bitfield e of shape sha is extracted into dest.  The current state
 *    of the stack is also given.
 */

void
bitf_to_int(exp e, shape sha, where dest,
			ash stack)
{
    where bf, d;
    exp t = dest.wh_exp;
    shape dsha = sh (t);
	
    int extend = (is_signed (sha) ? 1 : 0);
    int instr = (extend ? m_bfexts : m_bfextu);
	
    long off, sz, bstart;
    bitpattern pmask;
    long nbits = shape_size (sha);
    long boff = bitf_posn (e);
	
    off = 8 * (boff / 8);
    sz = 8 * ((boff + nbits - 1) / 8) + 8 - off;
    if (sz == 24) { sz = 32 ; off -= 8 ; }
    bstart = boff - off;
	
    pmask = ((hi_bits [ nbits ]) >> bstart) >> (32 - sz);
	
    switch (name (t)) {
	case ident_tag : dsha = sh (son (t)) ; break;
	case ass_tag : dsha = sh (bro (son (t))) ; break;
    }
    if (name (dsha) == bitfhd) dsha = (extend ? slongsh : ulongsh);
    if (name (dsha) == tophd) warning ("Top in bitfield assignment");
	
    bf = mw (e, off);
	
    if (bstart == 0 && nbits == sz) {
		shape bsha;
		switch (sz) {
	    case 8 : bsha = scharsh ; break;
	    case 16 : bsha = swordsh ; break;
	    case 32 : bsha = slongsh ; break;
		}
		change_var_sh (dsha, bsha, bf, dest);
		return;
    }
	
    if (whereis (bf) == Dreg) {
		bitpattern m = (lo_bits [ nbits ] <<  boff);
		d = (whereis (dest) == Dreg ? dest : D0);
		and (slongsh, bf, mnw (m), d);
		if (extend) {
			long r = 32 - nbits - boff;
			if (r) {
				if (r <= 8) {
					ins2n (m_lsll, r, L32, d, 1);
					ins2n (m_asrl, r, L32, d, 1);
				} else {
					regsinproc |= regmsk (REG_D1);
					ins2n (m_moveq, r, L32, D1, 1);
					ins2 (m_lsll, L32, L32, D1, d, 1);
					ins2 (m_asrl, L32, L32, D1, d, 1);
				}
			}
		}
		have_cond = 0;
		change_var_sh (dsha, slongsh, d, dest);
		return;
    } else {
		mach_op *op1, *op2;
		d = (whereis (dest) == Dreg ? dest : D0);
		op1 = operand (L32, bf);
		op1 = make_bitfield_op (op1, (int) bstart, (int) nbits);
		op2 = operand (L32, d);
		make_instr (instr, op1, op2, regs_changed (op2, 1));
		have_cond = 0;
		change_var_sh (dsha, slongsh, d, dest);
		return;
    }
}


/*
 *    INSERT A BITFIELD
 *
 *    The value e is inserted into the bitfield d.  The state of the stack
 *    is also given.
 */

void
int_to_bitf(exp e, exp d, ash stack)
{
    shape sha;
    where dest, f;
	
    long off, sz, bstart, bend;
    bitpattern pmask, nmask, v;
    long nbits = shape_size (sh (e));
    long boff = bitf_posn (d);
	
    off = 8 * (boff / 8);
    sz = 8 * ((boff + nbits - 1) / 8) + 8 - off;
    if (sz == 24) { sz = 32 ; off -= 8 ; }
    bstart = boff - off;
    bend = sz - nbits - bstart;
	
    pmask = ((hi_bits [ nbits ]) >> bstart) >> (32 - sz);
    nmask = ~pmask;
	
    switch (sz) {
	case 8 : nmask &= 0xff ; sha = scharsh ; break;
	case 16 : nmask &= 0xffff ; sha = swordsh ; break;
	default : sha = slongsh ; break;
    }
	
    if (name (e) == int_to_bitf_tag) {
		exp s = son (e);
		if (is_o (name (s))) {
			e = s;
		} else {
			regsinproc |= regmsk (REG_D1);
			coder (D1, stack, s);
			if (shape_size (sh (s)) < 32) warning ("Think again!");
			e = D1.wh_exp;
		}
    }
	
    dest = mw (d, off);
	
    if (bstart == 0 && nbits == sz) {
		change_var_sh (sha, sh (e), zw (e), dest);
		return;
    }
	
    if ((bstart + nbits > 32) || (name (e) != val_tag)) {
		where dd;
		bitpattern ch;
		mach_op *op1, *op2;
		dd = zw (e);
		if (whereis (dd) != Dreg || shape_size (sh (e)) != 32) {
			change_var_sh (slongsh, sh (e), dd, D0);
			dd = D0;
		}
		op1 = operand (L32, dd);
		op2 = operand (L32, dest);
		ch = regs_changed (op2, 1);
		op2 = make_bitfield_op (op2, (int) bstart, (int) nbits);
		make_instr (m_bfins, op1, op2, ch);
		have_cond = 0;
		return;
    }
	
    v = (bitpattern) no (e);
    v = ((v << bend) & pmask);
	
    if (v == 0) {
		and (sha, mnw (nmask), dest, dest);
		return;
    }
	
    if (v == pmask) {
		or (sha, mnw (pmask), dest, dest);
		return;
    }
	
    f = ((whereis (dest) == Dreg) ? dest : D0);
    and (sha, mnw (nmask), dest, f);
    or (sha, mnw (v), f, dest);
    return;
}


/*
 *    TEST A NUMBER OF BITS
 *
 *    The value a1 of shape sha is tested to see if the bits indicated by
 *    the value a2 are set.  If a2 is a constant power of 2 then a bit
 *    test operation is used.  Otherwise a1 is anded with a2 and the
 *    result is stored in an unwanted D-register.
 */

void
bit_test(shape sha, where a1, where a2)
{
    long sz = shape_size (sha);
    long wh1 = whereis (a1);
    long wh2 = whereis (a2);
    if (wh2 == Value) {
		if (wh1 == External || wh1 == Parameter || wh1 == RegInd) {
			long v = nw (a2);
			if (is_pow2 (v)) {
				where w;
				long n = log2 (v);
				long off = sz - 8 * (1 + (n / 8));
				w = mw (a1.wh_exp, a1.wh_off + off);
				ins2n (m_btstb, n % 8, 8, w, 1);
				have_cond = 0;
				return;
			}
		}
		if (wh1 == Dreg) {
			long v = nw (a2);
			if (last_use (a1)) {
				and (sha, a2, a1, a1);
				return;
			}
			if (is_pow2 (v) && sz == 32) {
				long n = log2 (v);
				ins2n (m_btstl, n, sz, a1, 1);
				have_cond = 0;
				return;
			}
		}
    }
    if (wh1 == Dreg && last_use (a1)) {
		and (sha, a2, a1, a1);
		return;
    }
    if (wh2 == Dreg && last_use (a2)) {
		and (sha, a1, a2, a2);
		return;
    }
    move (sha, a1, D0);
    and (sha, a2, D0, D0);
    return;
}
