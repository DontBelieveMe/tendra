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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------
$Log$
Revision 1.1  2002/01/26 21:31:28  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:44  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:24  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:44  14:58:44  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MAXMINMACS_INCLUDED
#define MAXMINMACS_INCLUDED

#define MAX_OF( a, b )	( ( ( a ) >= ( b ) ) ? ( a ) : ( b ) )
#define MIN_OF( a, b )	( ( ( a ) <= ( b ) ) ? ( a ) : ( b ) )
#define ABS_OF( a )	( ( ( a ) < 0 ) ? -( a ) : ( a ) )

#endif /* MAXMINMACS_INCLUDED */
