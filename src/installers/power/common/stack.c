/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
$Author: release $
$Date: 1998/02/04 15:49:09 $
$Revision: 1.2 $
$Log: stack.c,v $
 * Revision 1.2  1998/02/04  15:49:09  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:27  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translat.h"
#include "makecode.h"
#include "machine.h"
#include "flags.h"
#include "myassert.h"
#include "comment.h"
#include "proc.h"
#include "stack.h"
/* All measurements in bytes */
long p_frame_size=0;		/* total size of frame */  
long p_locals_offset=0;	/* where the locals live  */
long p_maxargbytes=0;	/* the largest size of the param area */
long p_args_and_link_size=0;	/* used by alloca */
bool p_has_fp=0;

bool p_leaf=0;
bool p_has_back_chain=0;
bool p_save_all_sregs=0;
bool p_has_alloca=0;
bool p_has_vcallees=0;
bool p_has_no_vcallers=0;

long p_fixed_params=0;
long p_float_params=0;
long p_sreg_first_save=0;
long p_sfreg_first_save=0;

bool p_has_saved_sp=0;
long p_saved_sp_offset=0;
int p_return_label=0; /* the number of the label which contains the return */
ans p_result;
long p_callee_size;

bool p_has_tp;

exp p_current;
long p_no_of_returns =0;

/*
 * The function of this file is to keep a lot of the stack controlling 
 * functions in the same place, so that they can be easily and consistently
 * maintained. I have introduced several new variables to make things easier
 * to follow.
 *
	|              |
	|              |
------->|--------------|<======R_FP                v
	|   Saved      |                           |
	|    FPR       |                           |
	|              |                           |
	|--------------|                           |
	|   Saved      |                           |< p_frame_size(bytes)
	|    GPR       |                           |
	|              |                           |
	|--------------|                           |
	| Possible word|for 8 byte alignment       |
	|--------------|                           |
	|              |                           |
	|--------------|                           |
	|  Saved SP    |<-- If have saved_sp       |
	|--------------|  this is where it lives   |
	|              |                           | 
	|              |                           | 
	|              |                           | 
	|              |                           |
    >56 |--------------|         v                 | 
	|    Pn        |         |                 |                 
	|     .        |         |                 |       
	|     .        |         |                 |                 
	|     .        |         |                 |  
	|     .        |         |                 |     
	|    P1        |         |< PROC_ARGS_AND_ |                 
      24|--------------|         |     LINK_SIZE   |                 
	|   Saved TOC  |         |     (bytes)     |                 
      20|--------------|         |                 |                 
	|   Reserved2  |         |                 |                 
      16|--------------|         |                 |                 
	|   Reserved1  |         |                 |                 
      12|--------------|         |                 |                 
	|   Saved LR   |         |                 |                 
       8|--------------|         |                 |                 
	|   Saved CR   |         |                 |                 
       4|--------------|         |                 |                 
	|  Back Chain  |         |                 |                 
-----> 0|--------------|<=====R_SP                 ^
          STACK_TEMP
*/
void initialise_procedure PROTO_N ((pr)) PROTO_T ( procrec *pr )
{
  p_sreg_first_save= pr->sreg_first_save;
  p_sfreg_first_save = pr->sfreg_first_save;
  p_has_alloca = pr->alloca_proc;
  p_save_all_sregs = pr->save_all_sregs;
  p_frame_size = pr->frame_size>>3; /* in bytes */
  p_locals_offset = pr->locals_offset>>3; /* in bytes */
  p_maxargbytes = pr->maxargs>>3; /* in bytes */
  p_has_fp = pr->has_fp;
  p_has_tp = pr->has_tp;
  p_has_saved_sp = pr->has_saved_sp;
  p_leaf = pr->leaf_proc;
  p_callee_size = pr->callee_size>>3;
  p_has_vcallees = pr->has_vcallees;
  p_has_no_vcallers = pr->has_no_vcallers;
  p_no_of_returns = pr->no_of_returns;
  
  p_fixed_params = 0;		/* Updated in make_ident_tag_code */
  p_float_params = 0;		/* Updated in make_ident_tag_code */
  p_has_back_chain = p_leaf ? 0 : diagnose;
  p_args_and_link_size = p_leaf ? 0 : STACK_LINK_AREA_SIZE + p_maxargbytes;
  ASSERT(pr->frame_size>=0 && (pr->frame_size&63) == 0);
  ASSERT(pr->frame_size>=pr->maxargs);
  return;
}


void generate_procedure_prologue PROTO_Z ()
{
  int r;
  baseoff stackpos;

  stackpos.base = R_SP;
  stackpos.offset = 0;
  
  /* Get LR for non leaf */
  if( !p_leaf)
  {
    mf_ins(i_mflr,R_0);
  }
  /* 
   * Save floating point s-regs
   */
  if(p_sfreg_first_save != FR_NO_REG)
  {
    for(r = p_sfreg_first_save; r <= FR_LAST; r++)
    {
      if (IS_FLT_SREG(r))
      {
	stackpos.offset -= 8;
	stf_ro_ins(i_stfd, r, stackpos);
      }
    }
    ASSERT(stackpos.offset >= -STACK_FLOAT_REG_DUMP_AREA_SIZE);
  }
  /*
   * Save fixed point s-regs
   */
  if (p_sreg_first_save != R_NO_REG)
  {
    if (p_sreg_first_save < R_28)
    {
      /* Use the stm instruction */
      stackpos.offset -= 4*(R_31+1-p_sreg_first_save);
      st_ro_ins(i_stm, p_sreg_first_save, stackpos);comment("save fixed point s-regs");
    }
    else
    { 
      /* Less than or 4 stores so do individually */
      for (r=R_31;r>=p_sreg_first_save;r--)
      { 
	stackpos.offset -= 4;
	st_ro_ins(i_st,r,stackpos);comment("save fixed point s-reg");
      }
    }
    ASSERT(stackpos.offset >= -STACK_REG_DUMP_AREA_SIZE);
  }
  /* Align to next 8 byte boundary */
  stackpos.offset= -ALIGNNEXT(-stackpos.offset,8);
  /*
   * Make room for saved sp if we have one
   */
  if ( p_has_saved_sp )
  {
    stackpos.offset -= 8;
    p_saved_sp_offset = stackpos.offset;
  }
  /* 
   * Initialise the top pointer if needed 
   */
  if( p_has_tp )
  {
    baseoff a;
    
    /* This is where the backward pointing chain is held */
    a.base = R_SP;
    a.offset = 0;
    ld_ro_ins(i_l,a,R_TP);comment("set up TP");
  }
  
  /* 
   * Initialize the frame pointer if needed
   */
  if ( p_has_fp )
  {
    mov_rr_ins( R_SP, R_FP );comment("set up FP");
  }

  
  /*
   * Save the Link Register
   */
  if ( ! p_leaf )
  {
    if ( p_has_tp)
    {
      stackpos.base = R_TP;
    }
    else
    {
      stackpos.base = R_SP;
    }
    
    stackpos.offset = STACK_SAVED_LR;
    st_ro_ins(i_st, R_0, stackpos);comment("save LR");
  }
  
  /* 
   * Decrease the stack pointer
   */
  
  stackpos.base = R_SP;
  
  if( p_has_back_chain )
  {
    stackpos.offset = - p_frame_size;
    st_ro_ins( i_stu , R_SP , stackpos );comment("pull stack down with back chain");
  }
  else
  {
    if (p_frame_size !=0)
    {
      rir_ins(i_a, R_SP, -p_frame_size ,R_SP);
    }
  }
  /* Save sp on stack if necessary */
  if( p_has_saved_sp )
  {
    save_sp_on_stack();
  }

  return;
}


void generate_procedure_epilogue PROTO_Z ()
{
  baseoff saved_lr;
  
  if ( p_frame_size !=0 )
  {
    if ( p_has_fp )
    {
      /* Use frame pointer to collapse stack frame */
      mov_rr_ins( R_FP, R_SP );comment("collapse frame using FP");
    }
    else if ( p_has_back_chain )
    {
	/* Use back chain to collapse stack frame */
      baseoff back_chain;
      back_chain.base=R_SP;
      back_chain.offset=0;
      ld_ro_ins(i_l, back_chain, R_SP);comment("collapse stack frame");
    }
    else
    {
      /* Use frame size to collapse stack frame */
      rir_ins(i_a, R_SP, p_frame_size , R_SP );
    }
  }
  /* At this point the stack pointer is collapsed to where the s-regs 
     are stored */
  if(p_has_tp)
  {
    mov_rr_ins(R_TP,R_TEMP_TP);comment("copy TP to TEMP_TP");
    restore_sregs(R_SP,0);
    mov_rr_ins(R_TEMP_TP,R_SP);comment("collapse frame using TEMP_TP");
  }
  else
  {
    restore_sregs(R_SP,0);
  }
  /* At this point the stack pointer is in its return position */
  if (!p_leaf)
  {
    saved_lr.base = R_SP;
    saved_lr.offset = STACK_SAVED_LR;
    ld_ro_ins(i_l, saved_lr , R_TMP0);comment("restore LR");
    mt_ins(i_mtlr, R_TMP0);
  }	
  z_ins(i_br);
  return;
}
void generate_untidy_procedure_epilogue PROTO_Z ()
{
  baseoff saved_lr;
  
  /* The stack pointer is not collapsed at all */
  if (p_has_tp && !p_leaf)/*We need R_TP later for the link */
  {
    mov_rr_ins(R_TP,R_TEMP_TP);comment("copy TP to TEMP_TP");
  }
  /* load up R_TEMP_FP with the value of where the s-regs are stored */
  if(p_has_fp)
  {
    mov_rr_ins(R_FP,R_TEMP_FP);comment("copy FP ro TEMP_FP");
    restore_sregs(R_TEMP_FP,0);
  }
  else if (p_has_back_chain)
  {
    baseoff back_chain;
    back_chain.base = R_SP;
    back_chain.offset = 0;
    ld_ro_ins(i_l,back_chain,R_TEMP_FP);comment(NIL);
    restore_sregs(R_TEMP_FP,0);
  }
  else
  {
    restore_sregs(R_SP,p_frame_size);
  }
  /* s-regs are restored */
  if (!p_leaf)
  {
    if(p_has_tp)
    {
      saved_lr.base = R_TEMP_TP;
      saved_lr.offset = STACK_SAVED_LR;
    }
    else if(p_has_fp)
    {
      saved_lr.base = R_TEMP_FP;
      saved_lr.base = STACK_SAVED_LR;
    }
    else
    {
      saved_lr.base = R_SP;
      saved_lr.offset = STACK_SAVED_LR + p_frame_size;
    }
    ld_ro_ins(i_l,saved_lr,R_TMP0);comment("restore LR");
    mt_ins(i_mtlr,R_TMP0);
  }
  z_ins(i_br);
  return;
}

	      
  
void save_sp_on_stack PROTO_Z ()
{
  baseoff saved_sp;
  
  /* Saves the value of the stack pointer on stack */
  ASSERT(p_has_saved_sp);
  ASSERT(p_has_fp);
  saved_sp.base = R_FP;
  saved_sp.offset = p_saved_sp_offset;
  st_ro_ins(i_st,R_SP,saved_sp);comment("save sp on stack");
  return;
}
void get_sp_from_stack PROTO_Z ()
{
  baseoff saved_sp;
  
  /* Restores the stack pointer from the stack */
  ASSERT(p_has_saved_sp);
  ASSERT(p_has_fp);
  saved_sp.base = R_FP;
  saved_sp.offset = p_saved_sp_offset;
  ld_ro_ins(i_l,saved_sp,R_SP);comment("get SP of stack");
  return;
}
void save_back_chain_using_frame_pointer PROTO_Z ()
{
  /* saves back chain using frame pointer */
  baseoff back_chain;
  back_chain.base = R_SP;
  back_chain.offset = 0;
  ASSERT(p_has_fp);
  st_ro_ins(i_st,R_FP,back_chain);comment("save back chain");
  return;
}

void restore_sregs PROTO_N ((start_base,start_offset)) PROTO_T (int start_base X int start_offset)
{
  baseoff stackpos;
  int r;
  
  ASSERT(IS_TREG(start_base) || start_base == R_SP);
  ASSERT(start_base!=R_TMP0);
  stackpos.base = start_base;
  stackpos.offset = start_offset;
  COMMENT2("restore s-regs using %d offset %d bytes",start_base,start_offset);
  
  
  if (p_sfreg_first_save != FR_NO_REG)
  {
    for (r = p_sfreg_first_save; r <= FR_LAST; r++)
    {
      if (IS_FLT_SREG(r))
      {
	stackpos.offset -= 8;
	ldf_ro_ins(i_lfd, stackpos, r);
      }
    }
  }
  
  /* 
   * Restore fixed point s-regs 
   */
  if (p_sreg_first_save != R_NO_REG)
  {
    if (p_sreg_first_save < R_28)
    {
      /* Use lm instruction */
      stackpos.offset -= 4*(R_31+1-p_sreg_first_save);
      ld_ro_ins(i_lm, stackpos, p_sreg_first_save);comment("restore fixed s-regs");
    }
    else
    {
      /* Less than or 4 loads so do individually */ 
      for (r=R_31;r>=p_sreg_first_save;r--)
      {
	stackpos.offset -=4;
	ld_ro_ins(i_l,stackpos,r);comment("restore fixed s-reg");
      }
    }
  }
  return;
}
void restore_link_register PROTO_Z ()
{
  /* this function is only used by tail_call */
  baseoff saved_lr;
  COMMENT("restore link register");
  if (!p_leaf)
  {
    if (p_has_tp)
    {
      saved_lr.base = R_TP;
      saved_lr.offset = STACK_SAVED_LR;
    }
    else if(p_has_fp)
    {
      saved_lr.base = R_FP;
      saved_lr.offset = STACK_SAVED_LR;
    }
    else 
    {
      fail("Shouldn't be calling this function without R_TP or R_FP");
    }
    ld_ro_ins(i_l,saved_lr,R_TMP0);comment("restore LR");
    mt_ins(i_mtlr,R_TMP0);
  }
}
