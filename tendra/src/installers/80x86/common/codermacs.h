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


/* 80x86/codermacs.h */

/**********************************************************************
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:11  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1995/08/30  16:06:21  pwe
 * prepare exception trapping
 *
 * Revision 1.4  1995/08/23  09:42:34  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.3  1995/08/04  08:29:06  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.2  1995/01/30  12:56:03  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:29:03  jmf
 * Initial revision
 *
**********************************************************************/


#ifndef codermacs_key
#define codermacs_key 1

#define local_pl 1
#define callstack_pl 2
#define par_pl 3
#define reg_pl 4
#define ext_pl 5
#define nowhere_pl 6
#define ferr_pl 7

#define no_fixed_regs 7
#define no_low_fixed_regs 3

#define check_stack_max if (max_extra_stack < extra_stack - stack_dec) \
	max_extra_stack = extra_stack - stack_dec

#endif
