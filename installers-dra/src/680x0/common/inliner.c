/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "exptypes.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "flags.h"
#include "shapemacs.h"
#include "inl_norm.h"

static int complexity(exp e, int count, int newdecs);


/*
    PARAMETERS
*/

#define crit_inline	50
#define decs_allowed	4
#define decs_with_apply	0


/*
    APPLY COMPLEXITY TO THE EXP e
*/

static int sbl
(exp e, int count, int newdecs)
{
    int c = complexity(e, count, newdecs);
    if (c < 0) return c;
    if (last(e)) return c;
    return sbl(bro(e), c, newdecs);
}


/*
    FIND COMPLEXITY OF THE EXP e
*/

static int complexity
(exp e, int count, int newdecs)
{
    unsigned char n = name(e);
    if (count < 0 || newdecs >= decs_allowed) return -1;
    if (son(e) == nilexp) return count;

    switch (n) {

	case apply_tag: {
	    if (newdecs > decs_with_apply) return -1;
	    return sbl(son(e), count - 1, newdecs);
	}

	case res_tag: {
	    return complexity(son(e), count - 1, newdecs);
	}

	case ident_tag: {
	    if (isloadparam(son(e))) {
		return sbl(son(e), count - 1, newdecs);
	    } else {
		return sbl(son(e), count - 1, newdecs + 1);
	    }
	}

	case top_tag:
	case clear_tag:
	case prof_tag: {
	    return count;
	}

	case case_tag: {
	    return complexity(son(e), count - 1, newdecs);
	}

	case name_tag:
	case string_tag:
	case env_offset_tag: {
	    return count - 1;
	}

	case labst_tag: {
	    return complexity(bro(son(e)), count, newdecs);
	}

	case solve_tag:
	case seq_tag: {
	    return sbl(son(e), count, newdecs);
	}

	default : {
	    return sbl(son(e), count - 1, newdecs);
	}
    }
}


/*
    FIND INLINING OPTIONS

    This delivers 0 if no uses of the procedure can be inlined, 1 if this
    use cannot be inlined and 2 if this use can be inlined.
*/

int inlinechoice
(exp t, exp def, int total_uses)
{
    exp apars;
    exp fpars;
    int newdecs = 0;
    UNUSED(total_uses);

    /* only uses are applications */
    apars = bro(t);
    fpars = son(def);
    for (; ;) {
	if (name(fpars)!= ident_tag || !isparam(fpars)) {
	    if (name(apars)!= top_tag)newdecs = 10;
	    break;
	}

	switch (name(apars)) {
	    case val_tag:
	    case real_tag:
	    case string_tag:
	    case name_tag: {
		break;
	    }
	    case cont_tag: {
		if (name(son(apars)) == name_tag &&
		     isvar(son(son(apars))) &&
		     !isvar(fpars))break;
		/* ... else continue */
	    }
	    default : {
		newdecs++;
	    }
	}

	fpars = bro(son(fpars));
	if (last(apars))break;
	apars = bro(apars);
    }

    /* newdecs is now the number of declarations (which will not be
       optimised out) arising from actual parameters */
#if is80x86
    if (!last(bro(t))) return 0;
#endif

    if (complexity(fpars, crit_inline, newdecs) >= 0) {
	return 2;
    } else if (newdecs == 0) {
	return 0;
    }
    return 1;
}
