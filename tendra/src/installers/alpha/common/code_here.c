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


/* 	$Id$	 */

#ifndef lint
static char vcid[] = "$Id$";
#endif /* lint */

/*
** code_here.c
*/

/*
$Log$
Revision 1.1  2002/01/26 21:31:14  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  08:42:55  john
 * Changed include files
 *
 * Revision 1.2  1995/05/23  10:53:17  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1995/03/23  10:39:02  john
 * Entered into CVS
 *
 * Revision 1.7  1995/03/23  09:59:49  john
 * Fixed so the assignment of a := (top_tag) gives zero.
 *
*/

#include "config.h"
#include "common_types.h"
#include "addresstypes.h"
#include "procrectypes.h"
#include "labels.h"
#include "expmacs.h"
#include "tags.h"
#include "coder.h"
#include "exp.h"
#include "bitsmacs.h"
#include "locate.h"
#include "inst_fmt.h"
#include "alpha_ins.h"
#include "shapemacs.h"
#include "special.h"
#include "handle_sregs.h"
#include "regexps.h"
#include "code_here.h"
#include "reg_defs.h"


/*
  regofval
  The procedure regofval checks to see if an exp is a load_tag
  that has been allocated into a fixpnt register and if so return 
  it or else 100.
*/
int   regofval
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  exp decx = son (e);
  if (name (e) == name_tag && name (decx) == ident_tag) {/* ident tag */
    if ((props (decx) & defer_bit) != 0) {
      return regofval (son (decx));
    }
    if ((props (decx) & inreg_bits) != 0) {
      return ((isvar (decx)) ? (-no (decx)) : (no (decx)));
    }
    return 100;
  }
  else
  if ((name (e) == val_tag && no (e) == 0) || name(e) == clear_tag ||
    name(e) == top_tag) {
	return 31;
  }
  else {
	return 100;
  }
}

/*
  add code to return 31 if fval is 0.0
*/
int   fregofval
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  exp decx = son (e);
  if (name (e) == name_tag && name (decx) == ident_tag) {
    if ((props (decx) & infreg_bits) != 0) {
      return no (decx);
    }
#if 0
    if((props(decx) & infreg_bits) != 0){
      return ((isvar(decx))?(-no(decx)):(no(decx)));
    }
#endif
    return 100;
  }
  else
    if(name(e) == clear_tag || name(e) == top_tag){
      return 0;
    }
    else {
      return 100;
    }
}
  
  
  

/*
  code_here
  The procedure code_here calls make_code and ensures that
  any internal exit labels are tied up after the call.
*/
int   code_here
    PROTO_N ( ( e, sp, dest ) )
    PROTO_T ( exp e X space sp X where dest )
{
  makeans mka;
#if DO_SCHEDULE && ENCAPSULATE_LABELS
  if(name(e) == rep_tag) start_new_capsule(true);
#endif
  mka = make_code (e, sp, dest, 0);
  if (mka.lab != 0) {
    (void)set_label (mka.lab);
#if DO_SCHEDULE && ENCAPSULATE_LABELS
    if(name(e) == rep_tag) close_capsule();
#endif    
  }
  return mka.regmove;
}

ash ash0 = {
  0, 0
};
ash ash32 = {
  32, 32
};

ash ash64 = {
  64,64
};


int reg_operand
    PROTO_N ( ( e, sp ) )
    PROTO_T ( exp e X space sp )
{
  
  int   x = regofval (e);
  ans aa;
  where w;
  if (x >= 0 && x < 100) {
    return x;
  }				/* x is a register for e */
  if (name (e) == cont_tag) {
    x = regofval (son (e));
    if (x < 0) {
      return (-x);
    }
  }
  else
    if (name (e) == apply_tag || (name(e) == apply_general_tag && 
	specialfn (son (e)) == 0)) {
				/* apply proc */
      setregalt (aa, RESULT_REG);
      w.answhere = aa;
      w.ashwhere = ash0;
      (void)make_code (e, sp, w, 0);
      return RESULT_REG;	/* simple proc calls give result in reg 0
				*/
    }

  aa = iskept (e);
  if (aa.discrim == inreg && regalt (aa) != NO_REG) {
				/* the same expression has already been
				   evaluated into a reg */
    return regalt (aa);
  }
  if (aa.discrim == notinreg) {
    instore is;
    is = insalt (aa);
    if (is.adval && is.b.offset == 0) {
      int   r = is.b.base;
      /* the same expression has already been evaluated into a reg */
      return r;
    }
  }

  {
    int   reg = -1;
    setsomeregalt (aa, &reg);
    /* allow code_here to evaluate e into reg of its choice */
    w.answhere = aa;
    w.ashwhere = ashof (sh (e));
    (void)code_here (e, sp, w);	
    Assert(reg!=-1);
    keepreg (e, reg);
    return reg;
  }
}


int   freg_operand
    PROTO_N ( ( e, sp ) )
    PROTO_T ( exp e X space sp )
{
  
  int   x = fregofval (e);
  ans aa;
  where w;
  freg fr;
  w.ashwhere = ashof (sh (e));
  if (x >= 0 && x < 100) {
    return x;
  }
  if (name (e) == cont_tag) {
    x = fregofval (son (e));
    if (x < 100) {
      return (x);
    }
  }
  else
    if (name (e) == apply_tag || name(e) == apply_general_tag) {
      if(is_floating(name(sh(e)))) {
	freg fr;
	fr.fr = 0;
	fr.type = (name(e)==realhd)?IEEE_double:IEEE_single;
	setfregalt(aa,fr);
      }
      else{
	setregalt (aa, 0);
      }
      w.answhere = aa;
      w.ashwhere = ash0;
      (void)make_code (e, sp, w, 0);
      return 0;
    }

  aa = iskept (e);
  if (aa.discrim == infreg) {	/* e already evaluated in fl reg */
    return regalt (aa) /* cheat */ ;
  }

 { int reg = -1;
   somefreg sfr;
   sfr.fr = &reg;
   if(w.ashwhere.ashsize==64)
     fr.type = IEEE_double;
   else
     fr.type = IEEE_single;
   sfr.type = fr.type;
   setsomefregalt (aa, sfr);
   w.answhere = aa;
  /* evaluate e into reg ... */
  (void)code_here (e, sp, w);
   fr.fr = reg;
   setfregalt(aa, fr);
   keepexp (e, aa);
   return reg;
 }
}
