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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/ops_shared.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: ops_shared.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:57  ma
First version.
Revision 1.3  1997/10/13 08:50:06  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/09/25 06:45:30  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:16  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:57  john
 *
 * Revision 1.2  1996/07/05  14:25:35  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:16  john
 *
 * Revision 1.2  93/03/03  14:50:17  14:50:17  ra (Robert Andrews)
 * Added support for jump_overflow routine.
 *
 * Revision 1.1  93/02/22  17:16:28  17:16:28  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef OPS_SHARED_INCLUDED
#define OPS_SHARED_INCLUDED


/*
    KEY TO OVERFLOW JUMPS

    The argument to jump_overflow is one of the following.
*/

typedef enum {
   UNCONDITIONAL,
   ON_OVERFLOW,
   ON_CARRY,
   ON_FP_OVERFLOW,
   ON_FP_CARRY,
   ON_FP_OPERAND_ERROR
} overflow_type;

#define ON_SHAPE(s)	(is_signed(s)? ON_OVERFLOW : ON_CARRY)


/*
    PROTOTYPES

    This file is a relic of the old operations.c which was split into
    the four ops_*.c files.  These routines were previously static but
    now must be external.
*/

extern void branch(long, exp, int, int, int);
extern int branch_ins(long, int, int, int);
extern void jump_overflow(int);
extern void test_overflow(overflow_type);
extern void test_overflow2(int);
extern void push(shape, long, where);
extern void push_float(long, where);
extern void pop(shape, long, where);
extern void pop_float(long, where);
extern void shift_aux(shape, where, where, where, int, int);
extern void checkalloc_stack(where, int);
extern int set_overflow(exp);
extern int have_overflow(void);
extern void clear_overflow(int);
extern void reset_round_mode(void);
extern void cmp_zero(shape, long, where);


/*
    CONDITION CODES

    These condition codes are used to eliminate unnecessary comparison
    instructions.
*/

extern where last_cond;
extern where last_cond2;
extern where last_cond_alt;
extern long last_cond_sz;


/*
    SET CONDITION CODES

    This macro is used to set the condition codes for the where X of
    size Y.
*/

#define  set_cond(X, Y)		\
    {					\
	have_cond = 1; \
	last_cond = (X);		\
	last_cond_sz = (Y);		\
    }


/*
    SET ALTERNATIVE CONDITION CODES

    This macro is used to set the alterative last condition to X.
*/

#define  set_cond_alt(X)		\
    {					\
	have_cond = 3; \
	last_cond_alt = (X);		\
    }


/*
    OUTPUT A COMPARISON INSTRUCTION

    Some assemblers (e.g. HP) reverse the order of the operands in
    comparison instructions.  This macro handles this fact.
*/

#ifndef asm_cmp_reversed
#define ins2_cmp(I, S1, S2, X1, X2, M)ins2(I, S1, S2, X1, X2, M)
#else
#define ins2_cmp(I, S1, S2, X1, X2, M)ins2(I, S2, S1, X2, X1, M)
#endif


#endif
