/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

    
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/exptypes.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: exptypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:52  ma
First version.

Revision 1.2  1997/09/25 06:45:03  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:12  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:30  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:53  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:11  john
 *
 * Revision 1.3  93/11/19  16:20:53  16:20:53  ra (Robert Andrews)
 * Added unsigned integral field to exp union.
 * 
 * Revision 1.2  93/04/19  13:33:30  13:33:30  ra (Robert Andrews)
 * Added extra field to expno to allow for new representation of alignments.
 * 
 * Revision 1.1  93/02/22  17:15:39  17:15:39  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef EXPTYPES_INCLUDED
#define EXPTYPES_INCLUDED

#include "config.h"

#include "codetypes.h"

#include "dg_first.h"
#include "diaginfo.h"


/*
    STRUCTURE REPRESENTING EXPRESSION PROPERTIES

    This is basically a bitfield, with different bits representing
    different properties.  See expmacs.h for details.
*/

typedef unsigned short prop ;


/*
    UNION REPRESENTING A EXPRESSION CONSTITUENT

    An expression constituent can be another expression, a string, a
    numerical value, a floating-point value or an external declaration.
*/

typedef union {
#ifndef tdf3
   long l ;
   unsigned long ui ;
#else
    int l ;
    unsigned int ui ;
#endif
    float fp ;
    char *str ;
    struct exp_t *expr ;
    struct dec_t *glob ;
    diag_info *d ;
    struct aldef_t *ald ;
} expno ; 


/*
    STRUCTURE REPRESENTING EXPRESSIONS

    An expression has a number of constituents given by the sonf, brof,
    ptrf and numf fields, a shape (which is another expression), a
    name representing the expression type, a properties field, and a
    single byte as an end marker.
*/

struct exp_t {
    unsigned char namef ;
    unsigned char lastf ;
    unsigned char park ;
    prop propsf ;
    expno sonf ;
    expno brof ;
    expno ptf ;
    expno numf ;
    struct exp_t *shf ;
} ;


/*
    THE EXPRESSION TYPE

    The type exp is a pointer to the structure given above.  Access to the
    fields of the structure is by means of the macros given in expmacs.h.
*/

typedef struct exp_t *exp ;

#endif




