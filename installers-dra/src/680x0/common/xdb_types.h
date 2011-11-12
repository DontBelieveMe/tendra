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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/xdb_types.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: xdb_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:03  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:23  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:02  john
 *
 * Revision 1.2  1996/07/05  14:37:15  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:36  ra
 * Added missing files.
 *
 * Revision 1.2  94/02/21  16:09:56  16:09:56  ra (Robert Andrews)
 * Introduce NULL_POSN_STR.
 *
 * Revision 1.1  93/02/22  17:17:32  17:17:32  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef XDB_TYPES_INCLUDED
#define XDB_TYPES_INCLUDED


/*
    TYPE REPRESENTING POSITIONS IN THE DIAGNOSTICS NAME TABLE
*/

typedef unsigned long posn_t;

typedef struct {
    int is_lab;
    posn_t posn;
    long size;
} table_posn;


/*
    TYPE REPRESENTING DIAGNOSTIC SCOPES
*/

typedef struct {
    posn_t posn;
    int dscope_type;
} dscope;


/*
    STANDARD TABLE POSITIONS
*/

#define  NULL_POSN		((posn_t)0xffffffff)
#define  NULL_POSN_STR		"0xffffffff"
#define  CHAR_POSN		((posn_t)0xc2000000)
#define  SIGNED_POSN		((posn_t)0xc3000000)
#define  UNSIGNED_POSN		((posn_t)0xc4000000)
#define  FLOATING_POSN		((posn_t)0xc5000000)
#define  LOCAL_POSN		((posn_t)0x80000000)
#define  GLOBL_POSN		((posn_t)0xa0000000)


extern posn_t out_dd(FILE *, int, int);
extern void out_posn(FILE *, table_posn *, int);
extern void fill_gap(FILE *, long, posn_t);
extern table_posn * analyse_diag_type(FILE *, diag_type, int);

extern void push_dscope(posn_t, int);
extern dscope * pop_dscope(void);

#endif
