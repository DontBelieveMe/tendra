/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef lint
static char vcid[] = "frames.c,v 1.5 1995/09/29 09:45:02 john Exp";
#endif /* lint */
#include "config.h"
#include "frames.h"
#include "procrecs.h"
#include "expmacs.h"
#include "tags.h"
#include "bitsmacs.h"
#include "reg_defs.h"
#include "fail.h"
#include "cross.h"
#include "bool.h"
extern int bitsin(int32);
extern exp father(exp);

bool Has_fp = FALSE;
bool Has_tos = FALSE;
bool No_S = FALSE;
bool Has_vcallees = FALSE;
bool Has_no_vcallers = TRUE;

int local_reg = 14;
int callee_size;

#define max(x,y)	(x>y)?x:y

#define min(x,y)      (x>y)?y:x

void setframe_flags
(exp e, bool leaf)
{
   /* e is proc_tag */
  No_S = (!leaf && (name(e)!= general_proc_tag || !proc_has_nolongj(e))
	  && proc_uses_crt_env(e) && proc_has_lv(e));
  Has_fp = (No_S || proc_has_alloca(e) || name(e) == general_proc_tag);
  Has_tos = (No_S && proc_has_alloca(e));
  Has_vcallees = (name(e) == general_proc_tag && proc_has_vcallees(e));
  Has_no_vcallers = (name(e) == proc_tag || !proc_has_vcallers(e));
#ifdef Try_No_S
  No_S = TRUE;
#endif
#ifdef Try_Has_fp
  Has_fp = !leaf;
#endif
#ifdef Try_Has_tos
  Has_tos = TRUE;
#endif
}

/*
  sets up the size of the frame, and the positions in which to
  save the registers.
*/
void setframe_info
(exp e)
{
  procrec * pr = & procrecs[no(e)];
  needs * ndpr = & pr->needsproc;
  spacereq *sppr = & pr->spacereqproc;
  long pprops = (ndpr->propsneeds);
  bool leaf = (pprops & anyproccall) == 0;
  int ma = ndpr->maxargs;	/* maxargs of proc body in bits */
  int pa = ndpr->numparams;
  long st = sppr->stack;	/* space for locals in bits */
  int nofixdump;
  int nofloatdump;
  int save_offset;
  setframe_flags(e, leaf);

  if (has_c_vararg(e) || !Has_no_vcallers) {
    pa=12*64;	/* should be 11 */
  }
  else{
    pa=min(pa,6*64);
  }

  st = (st + 32) & ~63;
  pa = (pa+32) &~63;
  ma = (ma + 32) & ~63;	/* put on 64 bit boundaries */
  pr->max_args = ma;
  save_offset=max(ma-384,0);
  /* locate the register to be saved */
  pr->fixdump = sppr->fixdump<<9;/* 8 */
  if (!leaf) {
    pr->fixdump |= 1 << RA;
  }	/* space for return address */
  if (No_S) {
    pr->fixdump |= (Has_fp)?0x7e00:0xfe00;
  }
  pr->floatdump = (sppr->fltdump<<1);	/* wrong! */
  nofixdump = bitsin(pr->fixdump);
  nofloatdump = bitsin(pr->floatdump);
  /* no of fixed s-regs to be dumped */
  pr->frame_size=pa+st+save_offset+ (nofixdump+nofloatdump)*64;
  pr->frame_size+= ((has_float(e)!=0 || !optop(e))?64:0);
  /* reserve an extra quadword for float reg <-> general reg
     transfers */

  if (Has_fp) {
    pr->frame_size +=64; /* extra word for old fp  */
/*    pr->callee_size += 128;*/
  }

  pr->dumpstart=save_offset>>3;
  pr->fldumpstart=pr->dumpstart+8*nofixdump;
  pr->locals_offset = (pr->fldumpstart + 8*(nofloatdump+ (has_float(e)!=0 ||
							 !optop(e)))) <<3;

  pr->paramsdumpstart = pr->locals_offset+st + ((Has_fp)?64:0);
  return;
}

int frame_offset
(exp id)
{
  exp p;
  procrec * pr;
  int  x = no(id);
  int  b = x & 0x3f;

  Assert(name(id) == ident_tag);
  for (p = father(id); name(p)!=proc_tag && name(p)!=general_proc_tag;
		       p = father(p));
  pr = & procrecs[no(p)];
  if ((b == SP) || (b == FP)) {
    return((x - b) >> 4) +
     ((pr->locals_offset - pr->frame_size - pr->callee_size) >>3);
  }
  else if (b == local_reg) {
    return((x-b) >>4) + (pr->locals_offset>>3) - (pr->frame_size>>3)
      /*- (pr->callee_size>>3)*/;
  }
  else{
    bool Has_vcallees = (name(p) == general_proc_tag && proc_has_vcallees(p));
    int n = -8 - (no(son(id)) >>3);
    if (isparam(id) && name(son(id))!= formal_callee_tag) {
      return n;
    }
    else if (isparam(id) && name(son(id)) == formal_callee_tag) {
      return (Has_vcallees)?n:((pr->callee_size>>3) - n);
    }
    else{
      failer("Illegal frame offset");
      return 0;
    }
  }
}

