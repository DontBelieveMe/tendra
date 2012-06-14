/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* main.h */

#ifndef MAIN
#define MAIN

#include <stdio.h>

#include "config.h"

#include "installtypes.h"

extern int use_umulh_for_div;
extern bool fail_with_denormal_constant;
extern bool treat_denorm_specially;
extern bool trap_all_fops;

extern FILE * as_file;
extern FILE * ba_file;

extern int majorno ;
extern int minorno ;

extern int currentfile;	/* our source fileno 0.. */
extern int mainfile;		/* would be best if it  
			       actually contained main ! */
extern bool do_extern_adds;
extern dec** main_globals;
#endif
