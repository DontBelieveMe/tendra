/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* 80x86/spec.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: spec.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/06  16:29:32  pwe
 * exceptions now OK
 *
 * Revision 1.3  1995/09/05  16:25:12  pwe
 * specials and exception changes
 *
 * Revision 1.2  1995/01/30  12:56:51  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.2  1994/07/12  15:21:29  jmf
 * exit, abort and longjmp produce bottom shape.
 *
 * Revision 1.1  1994/07/12  14:41:19  jmf
 * Initial revision
 *
**********************************************************************/


/**********************************************************************

                               spec.c

  Defines special_fn which recognises and replaces some special
  function calls.

**********************************************************************/

#include "config.h"

#include "exptypes.h"
#include "tags.h"
#include "externs.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "exp.h"
#include "basicread.h"
#include "flags.h"
#include "table_fns.h"
#include "installglob.h"
#include "check.h"
#include "localflags.h"
#include "me_fns.h"
#include "spec.h"


/* PROCEDURES */

speci special_fn
(exp a1, exp a2, shape s)
{
				/* look for special functions */
  speci spr;
  dec* dp = brog(son(a1));
  char *id = dp -> dec_u.dec_val.dec_id;
  spr.is_special = 0;
  if (id == (char *)0)
    return spr;
  id += prefix_length;

  if (a2 != nilexp && last(a2) && !strcmp(id, "__trans386_special")) {
    exp r = me_b3(s, a1, a2, apply_tag);
    setbuiltin(r);	/* dummy proc, so ignore state of do_special_fns */
    spr.is_special = 1;
    spr.special_exp = r;
    return spr;
  };

  if (!strcmp(id, "setjmp")) {
    has_setjmp = 1;
    module_has_setjmp = 1;
  };

  if (!strcmp(id, "longjmp")) {
    exp r = getexp(f_bottom, nilexp, 0, a1, nilexp, 0, 0,apply_tag);
    has_setjmp = 1;
    if (last(a2) || bro(a2) == nilexp)
      return spr;
    bro(a1) = a2;
    clearlast(a1);
    parked(a2) = 0;
    clearlast(a2);
    a2 = bro(a2);
    setlast(a2);
    parked(a2) = 0;
    bro(a2) = r;
    spr.is_special = 1;
    spr.special_exp = r;
  };

     /* we must always set has_setjmp if it is longjmp,
        otherwise registers are not reset.
        so don't do do_special_fns test until after longjmp test. */
  if (!do_special_fns)
    return spr;

  if (a2 != nilexp && last(a2) && !strcmp(id, "__builtin_alloca")) {
    exp r = getexp(s, nilexp, 0, a2, nilexp, 0,
	0, alloca_tag);
    setfather(r, son(r));
    has_alloca = 1;
    spr.is_special = 1;
    spr.special_exp = r;
    kill_exp(a1, a1);
    return spr;
  };

  if (a2 != nilexp && last(a2) && !strcmp(id, "exit")) {
    exp r = me_b3(f_bottom, a1, a2, apply_tag);
    spr.is_special = 1;
    spr.special_exp = r;
    return spr;
  };

  if (a2 == nilexp && !strcmp(id, "abort")) {
    exp r = me_u3(f_bottom, a1, apply_tag);
    spr.is_special = 1;
    spr.special_exp = r;
    return spr;
  };

  return spr;
}
