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
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:25  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.2  1998/02/04  15:48:40  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:41  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef BITMACS_H
#define BITMACS_H
/*
 * props of needs 
 */
#define morefix 0x100
#define morefloat 0x200
#define hasproccall 0x400
#define usesproccall 0x800	/* hasproccall << 1 */
#define anyproccall 0xc00
#define long_result_bit 0x1000
#define has_result_bit 0x2000
#define regsused 0xd00		/* morefix | usesproccall | hasproccall */
#define fregsused 0xe00		/* morefix | usesproccall | hasproccall */
#define realresult_bit  0x4000
#define longrealresult_bit  0x8000
#define uses_R_RESULT_bit 0x2
#define uses_FR_RESULT_bit 0x1

/*
 * props of ident 
 * (16 bits available, lower 8 used by common code) 
 */
/* #define subvar       0x0100  redefined as this in foralls.c*/
#define inreg_bits   0x0800
#define infreg_bits  0x1000
#define inanyreg     0x1800
#define defer_bit    0x2000
#define notparreg    0x4000
#define notresreg    0x8000
#define inlined      0x0200
#define vararg_bit   0x0400 /* Set for the last ident param if vararg */
/*
 * props of real operations 
 */
#define SetRev(e)	(props(e) |= 0x1000)
#define IsRev(e)	((props(e) & 0x1000)!=0)
#define ClearRev(e)	(props(e) &= ~0x1000)

#endif /* bitmacs.h */

