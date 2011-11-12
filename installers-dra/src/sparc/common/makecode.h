/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAKECODE_INCLUDED
#define MAKECODE_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "proctypes.h"
#include "exptypes.h"

extern where nowhere;
extern bool last_param(exp);
extern int use_subvar(exp);
extern makeans make_code(exp, space, where, int);
extern void checknan(exp, int);
extern void setnovolatile(void);
extern void setvolatile(void);
extern void load_reg(exp,int,space);
extern void do_exception(int);

#ifdef NEWDIAGS
extern void diag_arg(exp, space, where);
#endif

/*
#define TDF_HANDLER "__TDFhandler"
#define TDF_STACKLIM "__TDFstacklim"
*/

/*
  Identify a 'trap' error handler.  This uses the system exception
  mechanism.
*/
#define error_treatment_is_trap(x)((errhandle(x) &3) ==3)


#if ADDUNDERSCORE
#define TDF_HANDLER "___sparc_errhandler"
#define TDF_STACKLIM "___sparc_stack_limit"
#else
#define TDF_HANDLER "__sparc_errhandler"
#define TDF_STACKLIM "__sparc_stack_limit"
#endif /* ADDUNDERSCORE */

#endif /* MAKECODE_INCLUDED */
