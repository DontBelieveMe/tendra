/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

    
    
    
    
    
/*
 * check.h - Primitive definitions common to several interfaces.
 *
 * This file specifies an interface to the host system's compiler for
 * compiler-specific features related to checking.
 */

#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED

/*
 * This is the return type of a function that doesn't return (e.g.
 * ``longjmp'').
 */
# if defined __TenDRA__
#  pragma TenDRA type NORETURN for bottom
# elif defined __GNUC__
#  define NORETURN __attribute__((noreturn)) void
# else
#  define NORETURN void
# endif

/*
 * This macro documents the fact that the specified variable will no longer be
 * used.  One use is to indicate function parameters that are not used.  On
 * most compilers it will do nothing, but on compilers that support it it will
 * tell the compiler that the variable is not expected to be used.
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword UNUSED for discard variable
# else
#  define UNUSED(v) ((void) (v))
# endif /* defined (__TenDRA__) */

/*
 * This macro documents the fact that the current case of a switch statement
 * should follow through into the next (immediately following) case.  It is
 * used as follows:
 *
 *	case 1:
 *	  ...
 *	  FALL_THROUGH;
 *	case 2:
 *	  ...
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword FALL_THROUGH for fall into case
# else
#  define FALL_THROUGH
# endif /* defined (__TenDRA__) */

/*
 * This macro documents the fact that the location that it occurs in should be
 * unreachable.
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword UNREACHED for set unreachable
# else
#  include <assert.h>
#  include <stdlib.h>
#  define UNREACHED do { assert(!"unreachable"); abort(); } while (0)
# endif /* defined (__TenDRA__) */

/*
 * This macro documents the fact that the switch statement in which it appears
 * is meant to be exhaustive.  It is used as follows:
 *
 *  switch (expression) EXHAUSTIVE { ... }
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword EXHAUSTIVE for exhaustive
# else
#  define EXHAUSTIVE
# endif

/*
 * A weak prototype contains function parameter type information, but has none
 * of the automatic argument conversions associated with a normal prototype.
 * Instead weak prototypes imply the usual argument promotion passing rules for
 * non-prototyped functions.
 */
# ifdef __TenDRA__
#  pragma TenDRA keyword WEAK for weak
# else
#  define WEAK
# endif

#endif /* CHECK_INCLUDED */
