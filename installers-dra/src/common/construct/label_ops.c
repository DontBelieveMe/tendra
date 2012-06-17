/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include "config.h"

#include "exptypes.h"
#include "expmacs.h"

#include <reader/externs.h>

#include <construct/tags.h>
#include <construct/label_ops.h>
#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>


/* label_is_next returns 1 if lab is a labst which immediately
   follows e, otherwise 0. e will not be nilexp
*/
int
label_is_next(exp lab, exp e)
{
	if (~optim & OPTIM_JUMPS) {
		return 0;
	}
	while (last(e)) {
		e = bro(e);
		if (e == nilexp || name(e) >= ass_tag || name(sh(e)) != bothd) {
			return 0;
		}
	}
	if (name(bro(e)) == labst_tag) {
		return bro(e) == lab;
	}
	return 0;
}


static exp
is_jumper(exp e)
{
	if (name(e) == test_tag || name(e) == goto_tag ||
	    name(e) == testbit_tag || name(e) == res_tag) {
		return e;
	}
	return nilexp;
}


static exp
down(exp e)
{
	if (name(e) == seq_tag) {
		return down(son(son(e)));
	}
	if (name(e) == cond_tag) {
		return down(son(e));
	}
	return e;
}


/* next_jump delivers a goto, res, test or testbit exp if this
   is certain to be the next thing obeyed after e. nilexp
   otherwise.
*/
static exp
next_jump(exp e)
{
	if (~optim & OPTIM_JUMPS) {
		return nilexp;
	}

	do {
		while (last(e)) {
			e = bro(e);
			if (e == nilexp || name(e) >= goto_tag) {
				return nilexp;
			}
		}
		e = bro(e);
	} while (name(e) == labst_tag && (e = father(e), name(e) !=rep_tag));

	if (is_jumper(e)) {
		return e;
	}
	if (name(e) == seq_tag || name(e) == cond_tag) {
		return is_jumper(down(e));
	}
	if (name(e) == top_tag) {
		return next_jump(e);
	}
	return nilexp;
}


/* next_jump delivers a goto, res, test or testbit exp if this
   is certain to be the next thing obeyed after e and there is no
   other route to the goto (etc.). nilexp otherwise.
*/
exp
short_next_jump(exp e)
{
	if (~optim & OPTIM_JUMPS) {
		return nilexp;
	}

	while (last(e)) {
		e = bro(e);
		if (e == nilexp || name(e) >= cond_tag) {
			return nilexp;
		}
	}
	e = bro(e);

	if (is_jumper(e)) {
		return e;
	}
	if (name(e) == seq_tag || name(e) == cond_tag) {
		return is_jumper(down(e));
	}
	if (name(e) == top_tag) {
		return short_next_jump(e);
	}
	return nilexp;
}


exp
jump_dest(exp lab)
{
	return next_jump(son(lab));
}


exp
final_dest(exp lab)
{
	exp final = lab;
	exp temp, ll;
	while (name(final) == labst_tag) {
		temp = jump_dest(final);
		if (temp != nilexp && name(temp) == goto_tag &&
		    pt(temp) != final) {
			ll = lab;
			while (ll != final) {
				if (pt(temp) == ll) {
					/* pathological loop */
					return final;
				}
				ll = pt(jump_dest(ll));
			}
			final = pt(temp);
		} else {
			break;
		}
	}
	return final;
}


/* delivers 1 iff when a jumps, b also jumps
   a and b will be test or testbit */
static int
subsumes(exp a, exp b)
{
	if (name(a) == name(b) && test_number(a) == test_number(b) &&
	    eq_exp(son(a), son(b)) && eq_exp(bro(son(a)), bro(son(b)))) {
		return 1;
	}
	return 0;
}


exp
final_dest_test(exp lab, exp e)
{
	exp final = lab;
	exp temp, ll;
	while (name(final) == labst_tag) {
		temp = jump_dest(final);
		if (temp == nilexp || final == pt(temp)) {
			return final;
		}
		if (name(temp) == goto_tag ||
		    (name(temp) == name(e) && subsumes(e, temp))) {
			ll = lab;
			while (ll != final) {
				if (pt(temp) == ll) {
					/* pathological loop */
					return final;
				}
				ll = pt(jump_dest(ll));
			}
			final = pt(temp);
		} else {
			break;
		}
	}
	return final;
}
