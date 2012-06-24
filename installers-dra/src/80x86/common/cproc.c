/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
   cproc produces the code for the procedure defined by which has
   name pname.

**********************************************************************/

#include <shared/xalloc.h>

#include "config.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#include "diag_config.h"
#endif

#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>
#include <construct/install_fns.h>
#include <construct/installglob.h>
#include <construct/machine.h>

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#else
#include <diag/diag_fns.h>
#endif

#include "weights.h"
#include "codermacs.h"
#include "instr386.h"
#include "expmacs.h"
#include "operand.h"
#include "instr.h"
#include "instrmacs.h"
#include "out.h"
#include "codec.h"
#include "reg_record.h"
#include "localflags.h"
#include "messages_8.h"
#include "assembler.h"
#include "coder.h"
#include "scan2.h"
#include "cproc.h"

#ifdef NEWDWARF
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_basic.h>
#include "dw2_extra.h"
#endif

static exp returns_list;

int locals_offset;	/* global, needed for solaris stabs */
exp hasenvoff_list = nilexp;	/* global, used by coder */

/* MACROS */

#define GLOBALTABLEMASK 0x8

/* PROCEDURES */

static void add_odd_bits
(outofline * r)
{
  if (r != (outofline*)0) {
    if (r -> next == (outofline*)0)
      last_odd_bit = 1;
    add_odd_bits(r -> next);
  }
  else
    return;

  current_odd_bit = r;
  if (is80486)
    dot_align(4);
  simple_set_label(r->labno);
  clear_reg_record(crt_reg_record);
#ifdef NEWDWARF
  if (diag == DIAG_DWARF2) {
#if 1
    dw2_start_extra_bit(r->body);
#else
    dw2_start_extra_bit(r->dw2_slave);
#endif
    START_BB();
  }
#endif

  regsinuse = r->regsinuse;
  fstack_pos = r->fstack_pos;
  cond1_set = r->cond1_set;
  cond2_set = r->cond2_set;
  cond1 = r->cond1;
  cond2a = r->cond2a;
  cond2b = r->cond2b;
  repeat_level = r->repeat_level;
  scale = r->scale;
  coder(r->dest, r->stack, r->body);
  if (name(sh(r->body))!= bothd) {
    clean_stack();
    jump(r->jr, 0);
  }
  else
    stack_dec = 0;
#ifdef NEWDWARF
  if (diag == DIAG_DWARF2)
#if 1
    dw2_end_extra_bit(r->body);
#else
    dw2_end_extra_bit(r->dw2_hi);
#endif
#endif
  return;
}

static void out_pops
(int tot_sp, int push_space, int extra, int dpos)
{
#ifdef NEWDWARF
  long dwl0 = 0, dwl1 = 0, dwl2 = 0, dwl3 = 0, dwl4 = 0;
#endif
  tot_sp -= extra;
  if (no_frame && !stack_aligned_8byte) {
    if (tot_sp != push_space) {
      outs(" addl $");
      outn((long)(tot_sp - push_space));
      outs(",%esp");
      outnl();
#ifdef NEWDWARF
      if (diagnose && diag == DIAG_DWARF2)
	dwl0 = set_dw_text_label();
#endif
    };
  }
  else {
    if (tot_sp != push_space || has_alloca || stack_aligned_8byte) {
      outs(" leal -");
      outn((long)push_space);
      outs("(%ebp),%esp");
      outnl();
    };
  };

  /* pop the registers at the end */
  if (no_frame && (min_rfree & 0x40)) {
    outs(" pop %ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };
  if (min_rfree & 0x20) {
    outs(" pop %esi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl2 = set_dw_text_label();
#endif
  };
  if (min_rfree & 0x10) {
    outs(" pop %edi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl3 = set_dw_text_label();
#endif
  };
  if (min_rfree & 0x8) {
    outs(" pop %ebx");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl4 = set_dw_text_label();
#endif
  };

  if (!no_frame) {
    outs(" pop %ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };
  outnl();
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2) {
    out_set_pos(dpos);
    dw2_fde_restore_args(dwl0, dwl1, dwl2, dwl3, dwl4, push_space);
  }
#endif
  return;
}

static void out_untidy_pops
(int tot_sp, int push_space)
{
  if (no_frame) {
    int s_offset = tot_sp - push_space;
    if (min_rfree & 0x40) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%ebp");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x20) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%esi");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x10) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%edi");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x8) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%ebx");
      outnl();
      /* s_offset += 4; */
    };
  }
  else {
    int fm_offset = - push_space;
    if (min_rfree & 0x20) {
      outs(" movl ");
      outn((long)fm_offset);
      outs("(%ebp),%esi");
      outnl();
      fm_offset += 4;
    };
    if (min_rfree & 0x10) {
      outs(" movl ");
      outn((long)fm_offset);
      outs("(%ebp),%edi");
      outnl();
      fm_offset += 4;
    };
    if (min_rfree & 0x8) {
      outs(" movl ");
      outn((long)fm_offset);
      outs("(%ebp),%ebx");
      outnl();
      /* fm_offset += 4; */
    };
    outs(" movl 0(%ebp),%ebp");
    outnl();
  };
  return;
}


int cproc
(exp p, char *pname, int cname, int global, diag_global * diag_props)
{
  exp jr, t, body;
  ash stack;
  int  ms;
  int tot_sp;
  int param_pos;
  int byte_stack_align = stack_align / 8;
  long  old_pos1,
        old_pos1a,
        old_pos2,
        old_pos3,
        old_pos4,
        old_pos5,
        old_pos8,
        old_pos9,
        this_pos;
  int  push_space = 0;
#ifdef NEWDWARF
  long dwl0, dwl8, dw_entry_pos;
  long dwl1 = 0, dwl2 = 0, dwl3 = 0, dwl4 = 0;
  char * dw_labroom = "                 ";
		     /* .Ldw12345678:\n */
#endif

  int request_align_8byte;

  returns_list = nilexp;
  crt_proc_exp = p;
  crt_proc_id = next_lab();
  crt_ret_lab = next_lab ();	/* set up the return label for the
				   procedure */
  crt_ret_lab_used = 0;
  odd_bits = (outofline*)0;
  scale = (float)1.0;
  not_in_params = 1;
  not_in_postlude = 1;
  keep_short = 0;
  repeat_level = 0;
  callee_size = (proc_has_vcallees(p)? -1 : 0);
  ferrsize = 0;
  fpucon = normal_fpucon;

  has_dy_callees = 0;		/* set by scan2 when stack_dec indeterminable */
  has_tail_call = 0;		/* set by scan2, used in coder */
  has_same_callees = 0;		/* set by scan2, used in coder */
  proc_has_asm = 0;		/* set by scan2 if any asm operands */
  IGNORE scan2(1, p, p, 0);
  useful_double = 0;
  comp_weights(p);

/* 8byte align */
  request_align_8byte = permit_8byte_align && useful_double;

  if (pname[0]!= local_prefix[0])
    proc_type(pname);

  has_alloca = proc_has_alloca(p);

  must_use_bp = (has_alloca || proc_has_lv(p));

  regsinuse = 0;

  no_frame = 1;
  if (always_use_frame || do_profile || must_use_bp || has_dy_callees ||
        proc_uses_crt_env(p) || proc_has_setjmp(p) || proc_has_asm
    )
     no_frame = 0;

  if (request_align_8byte && no_frame) {
    no_frame = 0;
    stack_aligned_8byte = 1;
  }
  else
    stack_aligned_8byte = 0;

  if (!no_frame)
    regsinuse = 0x40; /* prevent ebp from being used as an ordinary
                          register */

  fstack_pos = first_fl_reg;

  max_stack = 0;		/* maximum stack value attained */
  max_extra_stack = 0;		/* maximum stack value attained */
  min_rfree = 0;		/* total registers used */
  stack_dec = 0;		/* current stack decrement */
  cond1_set = 0;
  cond2_set = 0;		/* state of condition flags is not known
				*/
  clear_reg_record(crt_reg_record);
  stack.ashsize = 0;
  stack.ashalign = 0;



  vc_pointer = nilexp;
				/* set up params before any diagnostics */
  t = son(p);
  param_pos = 0;
  while (name(t) == ident_tag && isparam(t) && name(son(t))!= formal_callee_tag)
   {
     t = bro(son(t));
   };
  if (name(t) == ident_tag && name(son(t)) == formal_callee_tag)
   {
     if (callee_size < 0)
	vc_pointer = t;
     while (name(t) == ident_tag && name(son(t)) == formal_callee_tag)
      {
	ptno(t) = par_pl;
	no(t) = param_pos;
	if (isenvoff(t))
	  set_env_off(param_pos+64, t);
	param_pos = rounder(param_pos + shape_size(sh(son(t))), param_align);
	t = bro(son(t));
      };
     if (callee_size == 0)
	callee_size = param_pos;
   };
   {
     exp pp = son(p);
     while (name(pp) == ident_tag && isparam(pp) && name(son(pp))!= formal_callee_tag)
      {
	ptno(pp) = par_pl;
	no(pp) = param_pos;
	if (isenvoff(pp))
	  set_env_off(param_pos+64, pp);
	param_pos = rounder(param_pos + shape_size(sh(son(pp))), param_align);
	pp = bro(son(pp));
      };
   };

  body = t;




  if (global) {
    outs(".globl ");
    outs(pname);
    outnl();
  };

  if (is80486)
    dot_align(16);
  else
    dot_align(4);

  if (diagnose)
    {
#ifdef NEWDWARF
    DIAG_PROC_BEGIN(diag_props, global, cname, pname, p);
#else
    diag_proc_begin(diag_props, global, cname, pname);
#endif
    };

  if (cname == -1)
    {
      outs(pname);
    }
  else
    {
      outs(local_prefix);
      outn((long)cname);
    };
  outs(":");
  outnl();
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2) {
    START_BB();
    dwl0 = set_dw_text_label();
  }
#endif

/* space for setting local displacement label */
  old_pos1 = out_tell_pos();
  outs("                          ");
     /* ".set .LdispNNNN, SSSSS\n" */
  outnl();
  old_pos1a = out_tell_pos();
  outs("                             ");
     /* ".set .LfcwdispNNNN, SSSSS\n" */
  outnl();

  if (!no_frame) {
    outs(" pushl %ebp");
    outnl();
    outs(" movl %esp,%ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };

/* space for pushing fixed point registers */
  old_pos2 = out_tell_pos();
  outs("               ");
     /* " pushl %ebx\n" */
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2)
    outs(dw_labroom);
#endif
  outnl();
  old_pos3 = out_tell_pos();
  outs("               ");
     /* " pushl %edi\n" */
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2)
    outs(dw_labroom);
#endif
  outnl();
  old_pos4 = out_tell_pos();
  outs("               ");
     /* " pushl %esi\n" */
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2)
    outs(dw_labroom);
#endif
  outnl();
  if (no_frame) {
    old_pos5 = out_tell_pos();
    outs("               ");
       /* " pushl %ebp\n" */
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      outs(dw_labroom);
#endif
    outnl();
  }

/* space for subtract from stack pointer */
  old_pos8 = out_tell_pos();
  outs("                     ");
     /* " subl $SSSSS,%esp\n" */
     /* " movl $SSSSS,%eax\n" */
  outnl();
  if (proc_has_checkstack(p)) {
    checkalloc_stack(reg0, 1);
  };
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2) {
    dwl8 = set_dw_text_label();
    dw_entry_pos = dw2_start_fde(dwl0, dwl1);
  }
#endif

  if (stack_aligned_8byte) {
    outs(" andl $-8,%esp");
    outnl();
  };

  old_pos9 = out_tell_pos();
  outs("                                    ");
     /* "movw $DDDD,0-.LfcwdispNNNN(%ebp)\n" */
  outnl();

#if !issol86
  if (format == FORMAT_AOUT) {
	if (pname[0]!= local_prefix[0] &&
	!strcmp(pname+prefix_length, "main")) {
      out_main_prelude();
    }
  }
#endif

  if (do_profile) {
    int  labl = next_lab ();	/* output profile procedure header */
    outs(".data");
    outnl();
    dot_align(4);
    outs(local_prefix);
    outs("P");
    outn((long)labl);
    outs(":");
    outnl();
    outs(" .long 0");
    outnl();
    outs(".text");
    outnl();
    outs(" leal ");
    outs(local_prefix);
    outs("P");
    outn((long)labl);
    outs(",%edx");
    outnl();
    outs(" call _mcount");
    outnl();
  };


  if (PIC_code && proc_uses_external(p))
   {
     regsinuse |= GLOBALTABLEMASK;
     min_rfree |= GLOBALTABLEMASK;
     pic_prelude();
   };

  need_preserve_stack = 0;
  if (proc_uses_crt_env(p) && proc_has_lv(p) && has_alloca)
   {
     need_preserve_stack = 1;
     stack.ashsize += 32;
     max_stack = stack.ashsize;
     save_stack();
   };

  scale = (float)1.0;
  last_odd_bit = 0;
  doing_odd_bits = 0;
  coder (zero, stack, body); /* code body of procedure */

  stack_dec = 0;
  doing_odd_bits = 1;
  while (odd_bits != (outofline*)0) {
    outofline * ol = odd_bits;
    odd_bits = (outofline*)0;
    last_odd_bit = 0;
    add_odd_bits(ol);
  }


  if (crt_ret_lab_used) {
    jr = getexp(f_bottom, nilexp, 0, nilexp, nilexp, 0,
                0, 0);
    sonno(jr) = stack_dec;
    ptno(jr) = crt_ret_lab;
    fstack_pos_of(jr) = (prop)first_fl_reg;
    set_label(jr);
  };

	/* If the procedure loads the current env and uses make_lv
	   it may be the destination of a long_jump. In that case
	   ebx, esi and edi must be saved at and restored at exit.
	   ebp will be saved and restored anyway because such a
	   procedure will have a frame pointer.
	*/
  if (proc_uses_crt_env(p) && proc_has_lv(p))
    min_rfree |= 0x38;

  /* compute space needed for local variables in memory */
  ms = ((max_stack + 31) / 32)* 4;
  /* compute space needed for pushing registers */
  if (no_frame && min_rfree & 0x40)
    push_space += 4;
  if (min_rfree & 0x20)
    push_space += 4;
  if (min_rfree & 0x10)
    push_space += 4;
  if (min_rfree & 0x8)
    push_space += 4;

  ferrsize /= 8;
  tot_sp = rounder(ms + push_space + ferrsize, byte_stack_align);

  if (crt_ret_lab_used) {
#ifdef NEWDWARF
    long over_lab;
    if (diagnose && diag == DIAG_DWARF2) {
      over_lab = next_dwarf_label();
      dw2_return_pos(over_lab);
    }
#endif
    restore_callregs(0);
    retins();
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dw2_after_fde_exit(over_lab);
#endif
  };
  outnl();

  this_pos = out_tell_pos();
  while (returns_list != nilexp) {
	  out_set_pos(no(returns_list)); /* XXX: no (macro) returns int */
    if (name(returns_list) == 1)
      out_untidy_pops(tot_sp, push_space);
    else
      out_pops(tot_sp, push_space, ptno(returns_list) /8, sonno(returns_list));
    returns_list = bro(returns_list);
  };
  out_set_pos(this_pos);

  locals_offset = tot_sp;
  if (diagnose) {
    no (p) = tot_sp;	/* may be used by delayed diagnostics */
#ifdef NEWDWARF
    DIAG_PROC_END(diag_props, p);
#else
    diag_proc_end(diag_props);
#endif
#ifdef NEWDWARF
  if (diag == DIAG_DWARF2)
    dw2_complete_fde();
#endif
  }

  /* now set in the information at the head of the procedure */
  {

    this_pos = out_tell_pos();
    out_set_pos(old_pos1);

    /* set the label which says how much the stack was decreased, in case
       frame pointer addressing is used  */
    outs(".set ");
    outs(local_prefix);
    outs("disp");
    outn((long)crt_proc_id);
    outs(", ");
    outn((long)tot_sp);

    if (ferrsize != 0) {
	/* set label for displacement to fpu control local store */
	    out_set_pos(old_pos1a);
      outs(".set ");
      outs(local_prefix);
      outs("fcwdisp");
      outn((long)crt_proc_id);
      outs(", ");
      outn((long)((no_frame)?(tot_sp - push_space - ferrsize):(push_space + ferrsize)));
    }

    out_set_pos(this_pos);
  };

  if (tot_sp != push_space || proc_has_checkstack(p)) {
    this_pos = out_tell_pos();
    out_set_pos(old_pos8);

    /* decrease the stack if necessary */
    if (proc_has_checkstack(p)) {
      outs(" movl $");
      outn((long)(tot_sp - push_space));
      outs(",%eax");
    }
    else {
      outs(" subl $");
      outn((long)(tot_sp - push_space));
      outs(",%esp");
    };
    outnl();

    if (ferrsize != 0) {	/* record FPU control word */
	    out_set_pos(old_pos9);
      move(uwordsh, mw(zeroe, normal_fpucon), mw(ferrmem, 0));
    }

    out_set_pos(this_pos);
  };

  /* push registers as necessary */
  if (min_rfree & 0x8) {
	  out_set_pos(old_pos2);
    outs(" pushl %ebx");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl2 = set_dw_text_label();
#endif
  };

  if (min_rfree & 0x10) {
	  out_set_pos(old_pos3);
    outs(" pushl %edi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl3 = set_dw_text_label();
#endif
  };


  if (min_rfree & 0x20) {
	  out_set_pos(old_pos4);
    outs(" pushl %esi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl4 = set_dw_text_label();
#endif
  };

  if (no_frame && (min_rfree & 0x40)) {
	  out_set_pos(old_pos5);
    outs(" pushl %ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };

#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2) {
	  out_set_pos(dw_entry_pos);
    dw2_fde_entry(dwl0, dwl1, dwl2, dwl3, dwl4, dwl8, tot_sp);
  };
#endif

  out_set_pos(this_pos);

  if (pname[0]!= local_prefix[0])
    proc_size(pname);

  if (proc_needs_envsize(p)) {
    outs(".set ");
    outs(local_prefix);
    outs("ESZ");
    outs(pname);
    outs(", ");
    outn((long)(tot_sp + 4 + max_extra_stack/8));
    outnl();
  }

#if !issol86
  if (format == FORMAT_AOUT) {
    if (pname[0]!= local_prefix[0] &&
	!strcmp(pname+prefix_length, "main")) {
      out_main_postlude();
    }
  }
#endif

  /* now prepare params with env_offset for possible constant evaluation */
  t = son(p);
  while (name(t) == ident_tag && isparam(t)) {
    if (isenvoff(t)) {
      no(t) += 64;
      name(t) = 0;
      ptno(t) = local_pl;
    }
    t = bro(son(t));
  }
  while (hasenvoff_list != nilexp) {
    exp id = son(hasenvoff_list);
    exp next = bro(hasenvoff_list);
    no(id) -= (locals_offset * 8);
    name(id) = 0;
    retcell(hasenvoff_list);
    hasenvoff_list = next;
  }

  if (no_frame)			/* hold info for later diagnostics */
    clear_proc_has_fp(p);
  else
    set_proc_has_fp(p);

  return proc_needs_envsize(p)? tot_sp + 4 + max_extra_stack/8 : 0;
}


/* Restore call_save registers (%ebp, %esi, %edi, %ebx)
   when we know which ones are reused.
   This preserves %eax, %ecx, %edx */
void restore_callregs
(int untidy)
{
  char *sp50 = "                                                  ";
  long retpos = out_tell_pos();
  outs("?");	/* will be overwritten, to cause assembler fail if sco bug */
  outs(sp50); outs(sp50); outs(sp50);
  outnl();
  returns_list = getexp(f_top, returns_list, 0, nilexp,
				nilexp, 0, 0,(unsigned char)untidy);
  no(returns_list) = (int)retpos;
  ptno(returns_list) = stack_dec;
#ifdef NEWDWARF
  if (diagnose && diag == DIAG_DWARF2)
    sonno(returns_list) = (int)dw2_prep_fde_restore_args(untidy);
#endif
  return;
}
