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
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:16  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/


/******************************************************************
                             constmacs.h

  This file contains macros used in repeat_list

 *****************************************************************/


/* "no_alias" flag - set in consts.c and used by foralls.c */
#define set_noalias(x) props(x) = (prop)(props(x) | 0x01)
#define clr_noalias(x) props(x) &= 0xfe
#define is_noalias(x) (props(x) & 0x01)

/* "dist" flag
   when x is an element of the repeat_list,
   if is_dist(x), then no(x) is maximum distance from a leaf repeat
   otherwise it is the count of repeats in the next level down
   (as set in dexp.c)
*/
#define set_dist(x) (props(x) = (prop)(props(x) | 0x02))
#define is_dist(x) (props(x) & 0x02)

#define max_loop_depth 6
