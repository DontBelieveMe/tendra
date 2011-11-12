/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <stddef.h>

#ifndef CONFIG_INCLUDED
#include "config.h"
#endif

/*
    PROCEDURE DECLARATIONS

    These routines are concerned with error reporting, memory allocation
    and system calls.
*/

extern char *string_printf(char *, ...);
extern void create_dir(char *);
extern void check_name(char *);
extern time_t date_stamp(char *);
extern void set_filename(char *);


/*
    INPUT BUFFER

    This buffer is used to store input in various contexts.
*/

extern char *buffer;
#define buffsize		5000


/*
    ERROR VARIABLES

    These variables are concerned with error reporting.
*/

extern int warnings;
extern time_t progdate;
extern char *filename;


/*
    GENERAL ALLOCATION ROUTINE

    This routine allocates a variable V of type T, allocating N at a time.
*/

#define alloc_variable(V, T, N)\
    {\
	static int no_free = 0 ;\
	static T *free_list = NULL;\
	if (no_free == 0) {\
	    no_free = N ;\
	    free_list = xmalloc_nof(T, N);\
	}\
	V = free_list + (--no_free);\
    }


#endif
