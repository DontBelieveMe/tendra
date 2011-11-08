/*
    		 Crown Copyright (c) 1996
    
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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/localtypes.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: localtypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:54  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:14  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:36  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.1  93/02/22  17:15:58  17:15:58  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef LOCALTYPES_INCLUDED
#define LOCALTYPES_INCLUDED


#include "config.h"

#include "installtypes.h"
#include "exptypes.h"


/*
    STRUCTURE REPRESENTING THE LAYOUT OF THE STACK

    This is just a value giving the stack size.
*/

typedef long ash ;


/*
    STRUCTURE USED TO ADD A SHAPE TO THE STACK.

    The astash field gives the new stack.  The astoff field gives the
    offset of the last field (in bits), and the astadj field gives the
    endianness adjustment for the last field.
*/

typedef struct {
    ash astash ;
    long astoff ;
    long astadj ;
} ast ;


/*

    STRUCTURE REPRESENTING SPECIAL FUNCTIONS
*/

typedef struct {
    bool is_special ;
    exp special_exp ;
} speci ;


/*
    STRUCTURE USED IN REGISTER ALLOCATION
*/

typedef struct {
    long place ;
    long num ;
    ash new_stack ;
    bool is_new ;
} allocation ;

#endif
