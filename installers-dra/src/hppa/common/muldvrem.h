/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MULDVREM_INCLUDED
#define MULDVREM_INCLUDED

#include "config.h"

#include "exptypes.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "exptypes.h"
#include <construct/installtypes.h>

extern bool is_muldivrem_call(exp);

extern needs multneeds(exp *, exp **);
extern needs divneeds(exp *, exp **);
extern needs remneeds(exp *, exp **);

extern int do_mul_comm_op(exp, space, where, bool);
extern int do_div_op(exp, space, where, bool);
extern int do_rem_op(exp, space, where, bool);
extern void clear_t_regs(void);
#endif /* MULDVREM_INCLUDED */
