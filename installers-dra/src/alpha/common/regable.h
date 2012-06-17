/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   regabledecs.h
   declares fixregable and floatregable
*/


#include "config.h"

#include <construct/installtypes.h>

extern  bool fixregable(exp e);
extern  bool floatregable(exp e);
extern  bool valregable(shape s);
