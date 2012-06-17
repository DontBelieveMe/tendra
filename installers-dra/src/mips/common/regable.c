/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include <construct/shapemacs.h>
#include <construct/tags.h>

#include "localtypes.h"
#include "expmacs.h"
#include "regable.h"

/***************************************************************
	fixregable

determines whether the exp e can fit in a single fixed point register. Uses
macros isvis, isglob, iscaonly from expmacs.h which examine the props
field. The iscaonly bit is set by proc independent if the tag is only used
by the contents operator or as the left hand side of an assignment. The
procedure also uses the macro is_floating from shapemacs.h which checks
the shape number is in the range for floating point shapes.
****************************************************************/


bool
valregable(shape s)
{
  int n = name(s);
  if (is_floating (n)) {	/* check shape to see if floating point */
    return 0;
  }
  else {
    ash a;
    a = ashof (s);		/* get ash corresponding to shape of e */

/* ALTERATION #1 */
    return a.ashsize <=32  && n!=cpdhd && n!= nofhd && n!=tophd;

  }
}

bool
fixregable(exp e)
{
  if (!isvis (e) && !isoutpar(e) && !isglob (e)
		&& name(son(e)) != caller_name_tag) {
    shape s = sh (son (e));	/* son of ident exp is def */
    return valregable (s);
  }
  else {
    return 0;
  }
}

/***************************************************************
	floatregable

determines whether the exp e can fit in a floating point register, single
or double.
***************************************************************/

bool
floatregable(exp e)
{
  if (!isvis (e) && !isoutpar(e) && !isglob (e)
	&& name(son(e)) != caller_name_tag) {
    shape s = sh (son (e));
    if is_floating
      (name (s)) {
      return 1;
      }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}
