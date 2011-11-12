/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/weights.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: weights.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:01  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:20  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:48  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:57:00  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:19  john
 *
 * Revision 1.2  94/02/21  16:06:33  16:06:33  ra (Robert Andrews)
 * Declare functions with no arguments using ( void ).
 *
 * Revision 1.1  93/02/22  17:17:02  17:17:02  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef WEIGHTS_INCLUDED
#define WEIGHTS_INCLUDED

extern void init_weights(void);
extern void comp_weights(exp);

#endif
