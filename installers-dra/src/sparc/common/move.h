/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MOVEDECS_INCLUDED
#define MOVEDECS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "addrtypes.h"
#include "sparcins.h"

extern ins_p i_ld_sz(int, int);
extern ins_p i_st_sz(int);

extern void ld_addr(instore, int);
extern int addr_reg(instore, long);

extern int move(ans, where, long, bool);

#endif /* MOVEDECS_INCLUDED */
