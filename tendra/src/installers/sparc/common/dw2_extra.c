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


/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/

#include "config.h"
#include "common_types.h"

#ifdef NEWDWARF

#include "myassert.h"
#include "dg_aux.h"
#include "dw2_config.h"
#include "dw2_codes.h"
#include "dw2_basic.h"
#include "szs_als.h"
#include "addrtypes.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "bitsmacs.h"
#include "tags.h"
#include "regmacs.h"
#include "locate.h"
#include "translat.h"
#include "basicread.h"
#include "codehere.h"
#include "eval.h"
#include "proc.h"
#include "procrec.h"
#include "dw2_entries.h"
#include "regable.h"
#include "const.h"
#include "flpttypes.h"
#include "f64.h"
#include "regexps.h"
#include "dw2_extra.h"
#include "dw2_locdata.h"

extern int call_base_reg;	/* declared in locate.c */



#define retaddr_column 64
#define DIAG_FREG 32

long instr_count = -1;
long fde_count = -1;


static long cie_pointer;
static long fde_end;
static long proc_end;

#ifdef NEEDS_DEBUG_ALIGN
static int calc_length;
#endif

static int extra_deref;
static int locate_param;
static int last_param_reg;
static int no_location;

static exp this_proc;

enum loctype { L_INREG = 1, L_REGOFF, L_GLOB, L_INDIRECT, L_SPLIT };

typedef struct {
	int key;
	int reg;
	long off;
} loc_s;



static void
outsep()
{
	outs (", ");
}


int
dw_is_const(exp e)
{
	switch (name(e)) {
    case val_tag:
    case null_tag:
    case real_tag:
		return 1;
    case name_tag:
		if (isdiscarded(e))
			return 0;
		if (isvar(son(e)))
			return 1;
		if (props (son(e)) & defer_bit)
			return dw_is_const (son(son(e)));
		return 0;
#if 0
    case cont_tag:
		return (name(son(e)) == name_tag && !isdiscarded(son(e)) &&
				!isvar(son(son(e))) && !isparam(son(son(e))));
#endif
    case reff_tag:
		return 1;
    default:
		return 0;
	}
}

exp
dw_has_location(exp e)
{			/* return ident or nilexp */
	switch (name(e)) {
    case name_tag: {
		if (isdiscarded(e) || isvar(son(e)))
			return nilexp;
		if (props (son(e)) & defer_bit)
			return dw_has_location (son(son(e)));
		return (son(e));
    }
    case cont_tag: {
		do {
			e = son(e);
			if (name(e) == name_tag && isdiscarded(e))
				return nilexp;
		}
		while (name(e) != ident_tag || (props(e) & defer_bit));
		return e;
    }
    default:
		return nilexp;
	}
}


static loc_s
find_in_store(exp dc, long off)
{
	loc_s l;
	baseoff b;
	assert (! (props (dc) & defer_bit));
	b = boff (dc);
	l.reg = b.base;
	l.off = off + b.offset;
	l.key = (isglob(dc) ? L_GLOB : L_REGOFF);
	return l;
}


static loc_s
find_loc(exp e)
{
	loc_s l;
	switch (name (e)) {
		
    case name_tag : {
		if (isdiscarded(e) || (isglob(son(e)) && no(son(e)) == 0 &&
							   !(brog(son(e))->dec_u.dec_val.extnamed))) {
			l.key = L_INREG;
			l.reg = 0;
			no_location = 1;
			return l;
		}
		if (isvar(son(e)))
			extra_deref--;
		if (props (son(e)) & defer_bit) {
			l = find_loc (son(son(e)));
			l.off += (no(e)/8);
		}
		else
			if (locate_param) {
				int r = no(son(son(e)))/32;
				if (!isparam(son(e))) {
					if (name(son(son(e))) == chvar_tag ||
						name(son(son(e))) == chfl_tag)
						return find_loc (son(son(son(e))));
					failer ("param inconsistency");
				}
				if (r > last_param_reg) {
					l.key = L_REGOFF;
					l.reg = R_SP;
					l.off = (no(son(son(e))) + no(e))/8 + 68;
				}
				else
					if (shape_size(sh(son(son(e)))) > 32) {
						l.key = L_SPLIT;
						l.reg = r;
					}
					else {
						l.key = L_INREG;
						l.reg = r + R_O0;
					}
			}
			else
				if (l.reg = regofval(e), l.reg >= 0 && l.reg < R_NO_REG) {
					l.key = L_INREG;
				}
				else
					if (l.reg = fregofval(e), l.reg >= 0 && l.reg < R_NO_REG) {
						l.reg = ((l.reg << 1) + DIAG_FREG);
						l.key = L_INREG;
					}
					else
						l = find_in_store (son(e), (long)no(e)/8);
		break;
    }
		
    case cont_tag :
    case contvol_tag : {
		if (name(son(e)) == name_tag && (isdiscarded(son(e)) ||
										 (isglob(son(son(e))) && no(son(son(e))) == 0 &&
										  !(brog(son(son(e)))->dec_u.dec_val.extnamed)))) {
			l.key = L_INREG;
			l.reg = 0;
			no_location = 1;
			return l;
		}
		if (name(son(e)) != name_tag || !isvar(son(son(e)))) {
			l = find_loc (son(e));
			if (l.key == L_INREG) {
				l.key = L_REGOFF;
				l.off = 0;
			}
			else
				l.key = L_INDIRECT;
		}
		else
			if (props (son(son(e))) & defer_bit) {
				l = find_loc (son(son(son(e))));
				l.off += (no(son(e))/8);
			}
			else
				if (locate_param) {
					int r = no(son(son(son(e))))/32;
					if (!isparam(son(son(e)))) {
						if (name(son(son(son(e)))) == chvar_tag ||
							name(son(son(son(e)))) == chfl_tag)
							return find_loc (son(son(son(son(e)))));
						failer ("param inconsistency");
					}
					if (r > last_param_reg) {
						l.key = L_REGOFF;
						l.reg = R_SP;
						l.off = (no(son(son(son(e)))) + no(son(e)))/8 + 68;
					}
					else
						if (shape_size(sh(son(son(son(e))))) > 32) {
							l.key = L_SPLIT;
							l.reg = r;
						}
						else {
							l.key = L_INREG;
							l.reg = r + R_O0;
						}
				}
				else
					if (l.reg = - regofval(son(e)), l.reg >= 0) {
						l.key = L_INREG;
					}
					else
						if (l.reg = fregofval(son(e)), l.reg < R_NO_REG) {
							l.reg = ((l.reg << 1) + DIAG_FREG);
							l.key = L_INREG;
						}
						else
							l = find_in_store (son(son(e)), (long)no(son(e))/8);
		break;
    }
		
    case reff_tag : {
		l = find_loc (son(e));
		if (l.key == L_GLOB || l.key == L_REGOFF)
			l.off += (no(e)/8);
		else
			if (l.key == L_INREG) {
				l.key = L_REGOFF;
				l.off = (no(e)/8);
				extra_deref--;
			}
			else
				l.key = L_INDIRECT;
		break;
    }
		
    default:
		failer ("unimplemented location condition");
	}
	return l;
}

static int
inreg_length(int r, int more)
{
	int ans = 1 + more;
	if (r >= 32)
		ans += uleb128_length((unsigned long)r);
	return ans;
}

static void
out_inreg(int r, int more)
{
	if (!more) {
		if (r < 32)
			outn ((long)(DW_OP_reg0 + r));
		else {
			outn ((long)DW_OP_regx); outsep(); uleb128((unsigned long)r);
		}
	}
	else {
		if (r < 32)
			outn ((long)(DW_OP_breg0 + r));
		else {
			outn ((long)DW_OP_bregx); outsep(); uleb128((unsigned long)r);
		}
		outsep(); outn ((long)0);
	}
	return;
}

static int
regoff_length(loc_s l)
{
	assert (l.reg >= 0 && l.reg < 32);
	return (1 + sleb128_length (l.off));
}

static void
out_regoff(loc_s l)
{
	outn ((long)(l.reg == R_FP ? DW_OP_fbreg : DW_OP_breg0 + l.reg)); outsep();
	sleb128 (l.off);
	return;
}

static int
split_length(loc_s l)
{
	int ans = inreg_length (l.reg + R_O0, 0) +4;
	if (l.reg == last_param_reg) {
		l.key = L_REGOFF;
		l.off = (l.reg * 4) + 72;
		l.reg = R_SP;
		ans += regoff_length (l);
	}
	else
		ans += inreg_length (l.reg + R_O1, 0);
	return ans;
}

static void
out_split(loc_s l)
{
	out_inreg (l.reg + R_O0, 0);
	outsep(); outn ((long)DW_OP_piece);
	outsep(); outn ((long)4); outsep();
	if (l.reg == last_param_reg) {
		l.key = L_REGOFF;
		l.off = (l.reg * 4) + 72;
		l.reg = R_SP;
		out_regoff (l);
	}
	else
		out_inreg (l.reg + R_O1, 0);
	outsep(); outn ((long)DW_OP_piece);
	outsep(); outn ((long)4);
	return;
}

static int
glob_length(loc_s l)
{
#ifdef NEEDS_DEBUG_ALIGN
	calc_length = 0;
#endif
	return 5;
}

static void
out_glob(loc_s l)
{
	outn ((long)DW_OP_addr); d_outnl ();
	out32 (); outlab (l.reg);
	if (l.off) {
		outs (" + ");
		outn ((long)l.off);
	}
	return;
}

static int
indirect_length(exp e)
{
	int length;
	loc_s l;
#ifdef NEEDS_DEBUG_ALIGN
	if (!calc_length)
		return 0;
#endif
	switch (name(e)) {
    case cont_tag: {
		length = 1;
		break;
    }
    case reff_tag: {
		if (no(e) >= 0)
			length = 1 + uleb128_length ((unsigned long)(no(e)/8));
		else
			length = 2 + uleb128_length ((unsigned long)(-no(e)/8));
		break;
    }
    case name_tag: {
		if (props(son(e)) & defer_bit) {
			return indirect_length (son(son(e)));
		}	/* else drop through to failure */
    }
    default: {
		failer ("unimplemented dwarf locate");
		return 0;
    }
	}
	l = find_loc (son(e));
	switch (l.key) {
    case L_INREG: {
		length += inreg_length (l.reg, 1);
		break;
    }
    case L_REGOFF: {
		length += regoff_length(l);
		break;
    }
    case L_SPLIT: {
		length += split_length(l);
		break;
    }
    case L_GLOB: {
		length += glob_length(l);
		break;
    }
    case L_INDIRECT: {
		length += indirect_length(son(e));
		break;
    }
	}
	return length;
}

static void
out_indirect(exp e)
{
	loc_s l;
	if (name(e) == name_tag) {
		assert (props(son(e)) & defer_bit);
		out_indirect (son(son(e)));
		return;
	}
	l = find_loc (son(e));
	switch (l.key) {
    case L_INREG: {
		out_inreg (l.reg, 1);
		outsep();
		break;
    }
    case L_REGOFF: {
		out_regoff (l);
		outsep();
		break;
    }
    case L_SPLIT: {
		out_split (l);
		outsep();
		break;
    }
    case L_GLOB: {
		out_glob (l);
		d_outnl(); out8();
		break;
    }
    case L_INDIRECT: {
		out_indirect(son(e));
		outsep();
		break;
    }
	}
	switch (name(e)) {
    case cont_tag: {
		outn ((long)DW_OP_deref);
		break;
    }
    case reff_tag: {
		if (no(e) >= 0) {
			outn ((long)DW_OP_plus_uconst); outsep();
			uleb128 ((unsigned long)(no(e)/8));
		}
		else {
			outn ((long)DW_OP_constu); outsep();
			uleb128 ((unsigned long)(-no(e)/8)); outsep();
			outn ((long)DW_OP_minus);
		}
		break;
    }
	}
	return;
}


void
dw2_locate_exp(exp e, int locate_const, int cx)
{
	loc_s l;
	int length;
	int within_loclist = (cx & 1);
#ifdef NEEDS_DEBUG_ALIGN
	long over_lab;
	calc_length = 1;
#endif
	locate_param = (cx & 2);
	extra_deref = locate_const;
	no_location = 0;
	l = find_loc (e);	/* may reduce extra_deref */
	length = extra_deref;
	switch (l.key) {
    case L_INREG: {
		length += inreg_length (l.reg, extra_deref);
		break;
    }
    case L_REGOFF: {
		length += regoff_length(l);
		break;
    }
    case L_SPLIT: {
		length += split_length(l);
		break;
    }
    case L_GLOB: {
		length += glob_length(l);
		break;
    }
    case L_INDIRECT: {
		length += indirect_length(e);
		break;
    }
	}
	if (no_location)
		length = 0;
	
	if (within_loclist)
		out16 ();
	else
		out8 ();
#ifdef NEEDS_DEBUG_ALIGN
	if (!calc_length) {
		over_lab = next_dwarf_label();
		out_dwf_label (over_lab, 0);
		if (within_loclist)
			outs (" - . - 2");
		else
			outs (" - . - 1");
	}
	else
#endif
		outn ((long)length);
	d_outnl();
	if (no_location)
		return;
	out8 ();
	switch (l.key) {
    case L_INREG: {
		out_inreg (l.reg, extra_deref);
		break;
    }
    case L_REGOFF: {
		out_regoff (l);
		break;
    }
    case L_SPLIT: {
		out_split (l);
		break;
    }
    case L_GLOB: {
		out_glob (l);
		break;
    }
    case L_INDIRECT: {
		out_indirect (e);
		break;
    }
	}
	while (extra_deref) {
		if (extra_deref < 0) {
			failer ("miscalculated location");
			break;
		}
#if 0
		if (locate_const)
			failer ("constant location???");
#endif
		outsep();
		outn ((long)DW_OP_deref);
		extra_deref--;
	}
	d_outnl ();
#ifdef NEEDS_DEBUG_ALIGN
	if (!calc_length)
		out_dwf_label (over_lab, 1);
#endif
	return;
}

static long current_pprops;

void
dw2_prepare_locate(exp id)
{
	/* set local proc conditions for local locations */
	exp e = son(id);	/* proc or general proc */
	procrec *pr = &procrecs [ no (e) ];
	needs *ndpr = &pr->needsproc;
	spacereq *sppr = &pr->spacereqproc;
	long pprops = (long) (ndpr->prps);
	/* bool leaf = (bool) ((pprops & anyproccall) == 0) ;	*/
	long maxargs = ndpr->maxargs ;/* maxargs of proc body in bits */
	long st = sppr->stack ;		/* space for locals in bits */
	
	Has_vcallees = (name(e) == general_proc_tag) && (proc_has_vcallees(e));
	/* callee_start_reg as initialisation */
	call_base_reg = R_NO_REG;	/* needs reset at apply_general */
	proc_state.params_offset = PARAMS_OFFSET;
	st = (st + 63) & ~63;
	proc_state.callee_size = ndpr->callee_size;
	proc_state.locals_space = st;
	proc_state.locals_offset = 0;
	proc_state.frame_size = maxargs + st;
	proc_state.maxargs = maxargs;
	last_param_reg = 5;
	if (proc_may_have_callees(e))
		last_param_reg = (Has_vcallees ? 3 : 4);
	this_proc = e;
	current_pprops = pprops;
	return;
}


void
dw2_locate_result(shape sha)
{
	out8 ();
	if (!valregable (sha) && name (sha) != tophd &&
		(!is_floating (name (sha)) || shape_size(sha) > 64)) {
		/* structure or union result, address of space to [ %fp+64 ] */
		loc_s l;
		l.key = L_REGOFF;
		l.reg = R_FP;
		l.off = 64;
		outn ((long)regoff_length (l)); outsep();
		out_regoff (l);
	}
	else {
		int r;
		if (is_floating (name (sha))) {
			/* proc has real result */
			r = R_F0 + DIAG_FREG;
		}
		else if (name (sha) > tophd ) {
			r = R_I0;
		}
		else {
			/* no result */
			failer ("inconsistent result");
			r = R_G0;
		}
		outn ((long)inreg_length (r, 0)); outsep();
		out_inreg (r, 0);
	}
	d_outnl ();
	return;
}

void
dw_at_procdetails()
{			/* return address and frame base */
	out8(); outn((long)2); outsep();
	outn((long)DW_OP_breg0 + R_I7); outsep();
	outn ((long)(has_struct_res (this_proc) ? 12 : 8)); d_outnl();
	out8(); outn((long)1); outsep();
	outn((long)DW_OP_reg0 + R_SP); d_outnl();
	return;
}


void
dw2_locate_val(dg_where v)
{
#ifdef NEEDS_DEBUG_ALIGN
	long over_lab;
	calc_length = 1;
#endif
	out8 ();
	switch (v.k) {
    case WH_CODELAB: {
		int length;
		loc_s l;
		l.key = L_GLOB;
		l.reg = v.u.l;
		l.off = v.o;
		length = glob_length (l);
#ifdef NEEDS_DEBUG_ALIGN
		if (!calc_length) {
			over_lab = next_dwarf_label();
			out_dwf_label (over_lab, 0);
			outs (" - . - 1");
		}
		else
#endif
			outn ((long)length);
		d_outnl();
		out8 ();
		out_glob (l);
		break;
    }
    case WH_REG: {
		int r = v.u.l;
		outn ((long)inreg_length (r, 0)); outsep();
		out_inreg (r, 0);
		break;
    }
    case WH_REGOFF: {
		loc_s l;
		l.key = L_REGOFF;
		l.reg = v.u.l;
		l.off = v.o;
		outn ((long)regoff_length (l)); outsep();
		out_regoff (l);
		break;
    }
    default:
		failer ("unexpected locate val");
	}
	d_outnl ();
#ifdef NEEDS_DEBUG_ALIGN
	if (!calc_length)
		out_dwf_label (over_lab, 1);
#endif
	return;
}


static int
dw_eval_exp(exp e, int line_started)
{
	if (line_started)
		outsep();
	else {
		out8 ();
		line_started = 1;
	}
	switch (name(e)) {
    case name_tag:
    case cont_tag:
    case contvol_tag:
    case reff_tag: {
		loc_s l;
		locate_param = extra_deref = no_location = 0;
		l = find_loc (e);
		if (no_location || extra_deref)
			failer ("value unobtainable by DWARF expression");
		switch (l.key) {
		case L_INREG: {
			out_inreg (l.reg, extra_deref);
			break;
		}
		case L_REGOFF: {
			out_regoff (l);
			break;
		}
		case L_GLOB: {
			out_glob (l);
			d_outnl ();
			line_started = 0;
			break;
		}
		case L_INDIRECT: {
			out_indirect (e);
			break;
		}
		}
		break;
    }
    case val_tag:
    case null_tag : {
		if (isbigval(e)) {
			flt64 x;
			int ov;
			x = flt_to_f64(no(e), is_signed(sh(e)), &ov);
			outn((long)(is_signed(sh(e)) ? DW_OP_const8s : DW_OP_const8u)); d_outnl();
			out32(); outn((long)(x.small)); outsep(); outn((long)(x.big)); d_outnl();
			line_started = 0;
		}
		else
			if (no(e) >= 0 && no(e) < 32)
				outn((long)(DW_OP_lit0 + no(e)));
			else
				if (is_signed(sh(e))) {
					outn((long)DW_OP_consts); outsep();
					sleb128 ((long)no(e));
				}
				else {
					outn((long)DW_OP_constu); outsep();
					uleb128 ((unsigned long)no(e));
				}
		break;
    }
    case plus_tag:
    case offset_add_tag : {
		line_started = dw_eval_exp (son(e), line_started);
		if (name(bro(son(e))) == val_tag && !is_signed(sh(e)) && !isbigval(bro(son(e)))) {
			if (line_started)
				outsep();
			else {
				out8 ();
				line_started = 1;
			}
			outn((long)DW_OP_plus_uconst); outsep();
			uleb128 ((unsigned long)no(e));
		}
		else {
			line_started = dw_eval_exp (bro(son(e)), line_started);
			if (line_started)
				outsep();
			else {
				out8 ();
				line_started = 1;
			}
			outn((long)DW_OP_plus);
		}
		break;
    }
    case minus_tag:
    case offset_subtract_tag : {
		line_started = dw_eval_exp (son(e), line_started);
		line_started = dw_eval_exp (bro(son(e)), line_started);
		if (line_started)
			outsep();
		else {
			out8 ();
			line_started = 1;
		}
		outn((long)DW_OP_minus);
		break;
    }
    case neg_tag:
    case offset_negate_tag : {
		line_started = dw_eval_exp (son(e), line_started);
		if (line_started)
			outsep();
		else {
			out8 ();
			line_started = 1;
		}
		outn((long)DW_OP_neg);
		break;
    }
    case mult_tag:
    case offset_mult_tag : {
		line_started = dw_eval_exp (son(e), line_started);
		line_started = dw_eval_exp (bro(son(e)), line_started);
		if (line_started)
			outsep();
		else {
			out8 ();
			line_started = 1;
		}
		outn((long)DW_OP_mul);
		break;
    }
    case div0_tag :
    case div1_tag :
    case div2_tag :
    case offset_div_by_int_tag :
    case offset_div_tag : {
		line_started = dw_eval_exp (son(e), line_started);
		line_started = dw_eval_exp (bro(son(e)), line_started);
		if (line_started)
			outsep();
		else {
			out8 ();
			line_started = 1;
		}
		outn((long)DW_OP_div);
		break;
    }
    default:
		failer ("unsupported operation for DWARF expression");
	}
	return line_started;
}


void
dw2_offset_exp(exp e)
{
	long block_end = next_dwarf_label ();
	if (name(sh(e)) != offsethd)
		failer ("wrong shape for offset expression");
	dw_at_form (DW_FORM_block2); d_outnl();
	out16 (); out_dwf_dist_to_label (block_end); d_outnl();
	if (dw_eval_exp (e, 0))
		d_outnl();
	if (name(sh(e)) == offsethd && al2(sh(e)) < 8) {
		out8 (); outn((long)(DW_OP_lit0 + 8)); outsep();
		outn((long)DW_OP_mul); d_outnl();
	}
	out_dwf_label (block_end, 1);
	return;
}


void
dw2_cie()
{
	long cie_end;
	int i;
	cie_pointer = next_dwarf_label();
	cie_end = next_dwarf_label();
	enter_section ("debug_frame");
	outnl_comment ("Common Information Entry");
	out_dwf_label (cie_pointer, 1);
	out32 (); out_dwf_dist_to_label (cie_end); d_outnl ();
	out32 (); outn ((long)DW_CIE_id); d_outnl ();
	out8 (); outn ((long)DW_CIE_MOD_VERSION); d_outnl ();
	out_string ("DERA/DDC-I");
	out8 (); uleb128 ((unsigned long)framecode_factor); d_outnl ();
	out8 (); sleb128 ((long)framedata_factor); d_outnl ();
	out8 (); outn ((long)retaddr_column); d_outnl ();	/* return address column */
	
	out8 (); outn ((long)DW_CFA_DD_sparc_restore_regwindow); outsep();
	sleb128 ((long) 8); d_outnl ();		/* sparc entry rules, ret offset 8 */
	
	for (i = R_FIRST; i <= R_LAST; i++) {
		if ((i > R_G0 && i <= (R_G0 + g_reg_max)) ||
			(i >= R_O0 && i <= R_O7 && i != R_SP)) {
			out8 (); outn ((long)DW_CFA_undefined); outsep();
			uleb128 ((unsigned long)i); d_outnl ();
		}
	}
	dot_align (PTR_SZ/8);
	out_dwf_label (cie_end, 1);
	exit_section ();
	return;
}


void
dw2_start_fde(exp e)
{
	long proc_start = next_dwarf_label();
	fde_end = next_dwarf_label();
	proc_end = next_dwarf_label();
	out_dwf_label (proc_start, 1);
	enter_section ("debug_frame");
	outnl_comment ("Frame Descriptor Entry");
	out32 (); out_dwf_dist_to_label (fde_end); d_outnl ();
	out32 (); out_dwf_label (cie_pointer, 0); d_outnl ();
	out32 (); out_dwf_label (proc_start, 0); d_outnl ();
	out32 (); out_dwf_labdiff (proc_start, proc_end); d_outnl ();
	this_proc = e;
	if (has_struct_res (this_proc)) {
		out8 (); outn ((long)DW_CFA_DD_location); outsep();
		uleb128 ((unsigned long)retaddr_column);  outsep();
		outn ((long)(2 + sleb128_length((long)12))); outsep();
		outn ((long)DW_OP_drop); outsep();
		outn ((long)(DW_OP_breg0 + R_O7)); outsep();
		sleb128 ((long) 12); d_outnl ();	/* return R_O7 offset 12 */
	}
	exit_section ();
	instr_count = -1;
	fde_count = 0;
	return;
}

static void
fde_advance(long here)
{
	if (fde_count < 0) {
		out8 (); outn ((long)DW_CFA_set_loc); d_outnl ();
		out32 (); out_dwf_label (here, 0);
	}
	else
		if (fde_count < 0x40) {
			out8 (); outn ((long)DW_CFA_advance_loc + fde_count);
		}
		else
			if (fde_count < 0x100) {
				out8 (); outn ((long)DW_CFA_advance_loc1); outsep();
				outn (fde_count);
			}
			else
				if (fde_count < 0x10000) {
					out8 (); outn ((long)DW_CFA_advance_loc2); d_outnl ();
					out16 (); outn (fde_count);
				}
				else {
					out8 (); outn ((long)DW_CFA_advance_loc4); d_outnl ();
					out32 (); outn (fde_count);
				}
	d_outnl ();
	fde_count = 0;
	return;
}

void
dw2_fde_save()
{
	long here = 0;
	if (fde_count < 0)
		here = set_dw_text_label();
	enter_section ("debug_frame");
	fde_advance (here);
	out8 (); outn ((long)DW_CFA_DD_sparc_save_regwindow); outsep();
	sleb128 ((long) (has_struct_res (this_proc) ? 12 : 8));
	d_outnl ();
	exit_section ();
	return;
}

void
dw2_fde_restore()
{
	long here = 0;
	if (fde_count < 0)
		here = set_dw_text_label();
	enter_section ("debug_frame");
	fde_advance (here);
	out8 (); outn ((long)DW_CFA_DD_sparc_restore_regwindow); outsep();
	sleb128 ((long) (has_struct_res (this_proc) ? 12 : 8));
	d_outnl ();
	exit_section ();
	return;
}

void
dw2_complete_fde()
{
	out_dwf_label (proc_end, 1);
	enter_section ("debug_frame");
	dot_align (PTR_SZ/8);
	out_dwf_label (fde_end, 1);
	exit_section ();
	return;
}


static exp lab_mark_list;

static void
mark_lab(exp labst)
{
	if (!dg_labmark (labst)) {
		set_dg_labmark (labst);
		if (son(son(labst)) != nilexp)
			failer ("strange labst");
		son(son(labst)) = lab_mark_list;
		lab_mark_list = labst;
	}
	return;
}

static void
trace_branch_aux(exp whole, exp e)
{
	exp t;
	switch (name(e)) {
    case test_tag:
    case goto_tag: {
		if (!intnl_to (whole, pt(e)))
			mark_lab (pt(e));
		break;
    }
    case case_tag: {
		t = bro(son(e));
		for (;;) {
			if (!intnl_to (whole, pt(t)))
				mark_lab (pt(t));
			if (last(t)) break;
			t = bro(t);
		}
		break;
    }
    case name_tag:
    case env_offset_tag:
    case general_env_offset_tag:
		return;
	}
	t = son(e);
	if (t) {
		for (;;) {
			trace_branch_aux (whole, t);
			if (last(t) || name(e) == case_tag) break;
			t = bro(t);
		}
	}
	return;
}

void
trace_dw_branch_exits(exp e)
{
	lab_mark_list = nilexp;
	trace_branch_aux (e, e);
	while (lab_mark_list) {
		exp holder = son(lab_mark_list);
		clear_dg_labmark (lab_mark_list);
		lab_mark_list = son(holder);
		son(holder) = nilexp;
		dw_entry (dwe_break, (long)0);
		out32 (); out_code_label ((long)no(holder)); d_outnl ();
	}
	return;
}


int
dw_loc_equivalence(exp a, exp b)
{
	return (int)sim_exp (a, b);
}

typedef struct
{
	dg_name	alloc;
	void *	share_set;
	dg_name	nm;
	long		start;
	long		end;
} dw_regdata;

#define TRACKREGS 32

static dw_regdata regassns [TRACKREGS];


void
dw_allocated(dg_name nm, exp id)
{
	int reg = no(id), i;
	exp x = son(nm->data.n_obj.obtain_val);
	if (!isglob(id) && (props(id) & inreg_bits) && reg < TRACKREGS) {
		dw_close_regassn (reg);
		regassns[reg].alloc = nm;
		regassns[reg].share_set = (void *)0;
	}
	for (i=0; i<TRACKREGS; i++) {
		if (regexps[i].keptexp && 
			(regexps[i].iscont ? (name(x) == cont_tag &&
								  sim_exp (son(x), regexps[i].keptexp))
			 : sim_exp (x, regexps[i].keptexp))) {
			regassns[i].nm = nm;
			regassns[i].start = set_dw_text_label ();
			regassns[i].end = (long)0;
			break;
		}
	}
	return;
}

void
dw_deallocated(dg_name nm)
{
	int i;
	for (i=0; i<TRACKREGS; i++) {
		if (regassns[i].alloc == nm) {
			dw_close_regassn (i);
			regassns[i].alloc = (dg_name)0;
			regassns[i].share_set = (void *)0;
		}
	}
	return;
}

void dw_all_deallocated		/* initialisation
							 */()
{
	int i;
	for (i=0; i<TRACKREGS; i++) {
		regassns[i].alloc = (dg_name)0;
		regassns[i].share_set = (void *)0;
		regassns[i].start = regassns[i].end = (long)0;
	}
	return;
}


void
dw_init_regassn(int reg)
{
	if (reg < TRACKREGS) {
		dg_name nm = find_equiv_object (regexps[reg].keptexp,
										regexps[reg].iscont);
		if (nm) {
			regassns[reg].nm = nm;
			regassns[reg].start = set_dw_text_label ();
			regassns[reg].end = (long)0;
		}
	}
	return;
}

void
dw_used_regassn(int reg)
{
	if (reg < TRACKREGS && regassns[reg].start)
		regassns[reg].end = set_dw_text_label ();
	return;
}

void
dw_close_regassn(int reg)
{
	if (reg >= TRACKREGS)
		return;
	if (regassns[reg].end) {
		if (!regassns[reg].share_set) {
			regassns[reg].share_set = (void *)
				dw_new_regshare (regassns[reg].alloc, reg);
		}
		dw_add_regshare (regassns[reg].share_set, regassns[reg].nm,
						 regassns[reg].start, regassns[reg].end);
		regassns[reg].end = (long)0;
		if (!regassns[reg].alloc)
			regassns[reg].share_set = (void *)0;
	}
	regassns[reg].start = (long)0;
	return;
}


#endif
