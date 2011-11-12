/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
$Log: shape_range.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/23  13:26:27  john
 * Changed 64 bit test
 *
 * Revision 1.1.1.1  1995/03/23  10:39:21  john
 * Entered into CVS
 *
 * Revision 1.3  1995/01/31  14:25:18  john
 * Minor changes
 *
*/
#ifndef SHAPE_RANGE_H
#define SHAPE_RANGE_H
#include "cross.h"
#if FS_64_BIT
#define scmm_max 127L
#define scmm_min -128L
#define uscmm_max 255L
#define uscmm_min 0L

#define shmm_max 32767L
#define shmm_min -32768L
#define ushmm_max 65535L
#define ushmm_min 0L

#define swmm_max 0x7fffffffL
#define swmm_min 0xffffffff80000000L
#define uswmm_max 0x00000000ffffffffL
#define uswmm_min 0L

#define s64mm_max 0x7fffffffffffffffL
#define s64mm_min 0x8000000000000000L
#define u64mm_max 0xffffffffffffffffL
#define u64mm_min 0L
#else
#define scmm_max {0,127}
#define scmm_min {0,0}
#define uscmm_max {0,255U}
#define uscmm_min {0,0}

#define shmm_max {0,0x0000ffff}
#define shmm_min {0xffffffff,0xffff8000}
#define ushmm_max {0,0x0000ffff}
#define ushmm_min {0,0}


#define swmm_max {0,0x7fffffff}
#define swmm_min {0xffffffff,0x80000000}
#define uswmm_max {0,0xffffffff}
#define uswmm_min {0,0}

#define s64mm_max {0x7fffffff,0xfffffff}
#define s64mm_min {0x80000000,0x0000000}
#define u64mm_max {0xffffffff,0xffffffff}
#define u64mm_min {0,0}
#endif /* ifdef alpha */
#endif
