/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/******************************************************************

                            checkextdecs.h

   checkext looks to see if it can improve the definition (exp)
   of an globally declared item. If it makes a change it returns 1,
   otherwise 0.

   The most important transformation is inlining of procedures.

 *******************************************************************/

extern void checkext(exp e);

