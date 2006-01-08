/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *	(1) Its Recipients shall ensure that this Notice is
 *	reproduced upon any copies or amended versions of it;
 *
 *	(2) Any amended version of it shall be clearly marked to
 *	show both the nature of and the organisation responsible
 *	for the relevant amendment or amendments;
 *
 *	(3) Its onward transfer from a recipient to another
 *	party shall be deemed to be that party's acceptance of
 *	these conditions;
 *
 *	(4) DERA gives no warranty or assurance as to its
 *	quality or suitability for any purpose and DERA accepts
 *	no liability whatsoever in relation to any use to which
 *	it may be put.
 *
 * $TenDRA$
 */


/**/


#define HPPATRANS_CODE
/******************************************************************
 *		weights.c
 *
 *	The main procedure here is weightsv which determines
 *the allocation of s regs. It considers which of those tags not already
 *allocated to a t reg by scan, are best put in an s register. The same
 *conditions as for t regs apply as to the suitability of the tags for registers.
 *Weights estimates the usage of each tag and hence the amount that would
 *be saved if it were held in an s reg. Thus it computes break points for
 *register allocation for later use by reg_alloc.
 *	The type weights consists of two arrays of integers. In the first
 *array each integer corresponds to a fixpnt reg and the second arrays'
 *integers correspond to floating point regs.
 *	At the end of a call of weights on an ident exp the props field
 *of the ident may still contain inreg_bits or infreg_bits, set by scan, to
 *indicate that a t reg should be used. Otherwise number of ident is set up to
 *represent the break point for allocation. A similar process occurs for
 *proc parameters which have the break value in the forweights field
 *of the parapair of the corresponding procrec. This value has three
 *meanings:
 *	1) The ident (or parameter) defines a fixpnt value and number
 *of ident (forweights of parpair) is an integer brk with the interpretation
 *that if there are at least brk fixpt s registers unallocated at this point then
 *one will be used for this tag (parameter).
 *	2) As 1 but for floating point values.
 *	3) number of ident = 100 in which case allocate value on the
 *stack, (this is obviously always available for parameters).

******************************************************************/


#include "config.h"

#include "common_types.h"
#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"
#include "const.h"
#include "exp.h"
#include "tags.h"
#include "proctypes.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "comment.h"
#include "shapemacs.h"
#include "special.h"
#include "weights.h"



weights zeroweights =
{{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
},
 {
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 }
};

/* NB scale, throughout,  should be a float but mips cc V2.10 compiles calls and
 *		proc body inconsistently !! */

weights weightsv(double, exp);

weights
add_weights(weights * w1, weights * w2)
{
	/* sum of weights */
	weights r;
	long i;

	for (i = 0; i < wfixno; ++i)
	{
		(r.fix)[i] = (w1->fix)[i] + (w2->fix)[i];
	};
	for (i = 0; i < wfloatno; ++i)
	{
		(r.floating)[i] = (w1->floating)[i] + (w2->floating)[i];
	};
	return (r);
}

wp
max_weights(double loc, weights * ws, bool fix)
{

	/*
	 * loc is the usage count of a tag, ws is the weights computed for the scope
	 * of the tag and fix distinguishes between fix and float. This computes the
	 * weights for the declaration and a break point for register allocation
	 * which gives the number of available regs for which it is worthwhile to
	 * allocate this tag into a reg ("regged"). This proc is the source of all
	 * non-zero weights. NB loc may be negative since using a s-reg will involve
	 * a dump and restore
	 */
	long bk = wfixno + 1;
	long i;
	float *w = (ws->fix);
	/* w[i] = greatest usage of (i+1) inner fixed tags  */
	wp res;
	float *pw = &(((res.wp_weights).fix)[0]);

	if (fix)
	{
		for (i = 0; i < wfixno; ++i)
		{
			if (i == 0)
			{
				if (loc > w[i])
				{
					/* this tag has higher usage than any inner one ... */
					pw[i] = loc;
					bk = i;		/* ... so it's regged in pref to others */
				}
				else
					pw[i] = w[i];
			}
			else
			{
				if ((loc + w[i - 1]) > w[i])
				{

					/*
					 * this tag and i inner ones have higher usage than any other (i+1)
					 * inner ones ...
					 */
					pw[i] = loc + w[i - 1];
					if (i < bk)
						bk = i;

					/*
					 * ... so it and i inner ones are regged in preference to any other
					 * (i+1) inner ones
					 */
				}
				else
					pw[i] = w[i];
			};
		};

		res.fix_break = bk;
	}
	else
	{
		for (i = 0; i < wfixno; ++i)
		{
			pw[i] = w[i];
		}
	}

#if NO_SREG
	res.fix_break = wfixno + 1;
#else
	res.fix_break = bk;
#endif

	bk = wfloatno + 1;
	w = (ws->floating);
	pw = &(((res.wp_weights).floating)[0]);
	if (!fix)
	{				/* same algorithm for float regs as fixed regs */
		for (i = 0; i < wfloatno; ++i)
		{
			if (i == 0)
			{
				if (loc > w[i])
				{
					pw[i] = loc;
					bk = i;
				}
				else
					pw[i] = w[i];
			}
			else
			{
				if ((loc + w[i - 1]) > w[i])
				{
					pw[i] = loc + w[i - 1];
					if (i < bk)
						bk = i;
				}
				else
					pw[i] = w[i];
			};
		};
	}
	else
	{
		for (i = 0; i < wfloatno; ++i)
		{
			pw[i] = w[i];
		}
	}

	res.float_break = bk;
	return res;
}

weights
mult_weights(double m, weights * ws)
{

	/*
	 * multiply weights by scalar - non overflowing
	 */
	weights res;
	float *r = &(res.fix)[0];
	float *w = ws->fix;
	long i;

	for (i = 0; i < wfixno; ++i)
	{
		r[i] = w[i] * m;
	};

	r = &(res.floating)[0];
	w = ws->floating;
	for (i = 0; i < wfloatno; ++i)
	{
		r[i] = w[i] * m;
	};
	return (res);
}

weights
add_wlist(double scale, exp re)
{				/* sum of  weights of list re */
	weights w, w1;
	exp r = re;

	if (r == nilexp)
	{
		return zeroweights;
	}
	else if (last(r))
	{
		return (weightsv(scale, r));
	}
	else
	{
		w = weightsv(scale, r);
		do
		{
			r = bro(r);
			w1 = weightsv(scale, r);
			w = add_weights(&w, &w1);
		} while (!last(r));
		return w;
	}
}



/*****************************************************************
 *	weightsv
 *
 *This procedure estimates the usage of tags and parameters to help
 *determine whether they can advantageously be placed in s registers.
 *The parameter scale allows more importance to be placed on usage
 *inside 'for' loops for example. The procedure reg_alloc in reg_alloc.c
 *finally determines the actual choice of s reg and recodes the number
 *field of an ident.

******************************************************************/
weights
weightsv(double scale, exp e)
{
	unsigned char n;

  tailrecurse:
	n = name(e);


	switch (n)
	{
	case name_tag:
	{
		exp s = son(e);

		if (name(s) == ident_tag && !isglob(s))
		{
			if (is_floating(name(sh(e))) && name(sh(e)) != SH_REAL_SHORT)
			{
				fno(s) += scale * 2.0;
			}
			else
				fno(s) += scale;
		}
		/* usage of tag stored in number of son of load_name (decl) */
		return zeroweights;
	};

	case ident_tag:
	{
		if (son(e) != nilexp)
		{
			weights wdef;
			bool wdef_set;
			weights wbody;
			long noe = no(e) /* set by scan */;

#if 1
			if (isparam(e))
			{
				/* initialising is a use */
				fno(e) = scale;
				wdef_set = 0;
			}
			else
#endif
				if (name(son(e)) == clear_tag || props(e) & defer_bit)
				{
					wdef = zeroweights;
					fno(e) = 0.0;
					wdef_set = 0;
				}
				else
				{
					/* maybe needs a store to initialise */
					if (is_floating(name(sh(son(e)))) && name(sh(son(e))) != SH_REAL_SHORT)
					{
						fno(e) = scale * 2.0;
					}
					else
						fno(e) = scale;
					wdef = weightsv(scale, son(e));
					wdef_set = 1;
				}
			/* weights for initialisation of dec */

			wbody = weightsv(scale, bro(son(e)));
			/* weights of body of scan */

			if (props(e) & defer_bit)
			{			/* declaration will be treated transparently
						 * in code production */
				exp t = son(e);
				exp s;

				if ((name(t) == val_tag) || (name(t) == real_tag)) /* +++ string_tag too */
				{
					return wbody;
				}
				while (name(t) != name_tag)
				{
					t = son(t);
				}

				s = son(t);
				if (name(s) == ident_tag && !isglob(t))
				{
					fno(s) += fno(e);
				}
				/* usage of tag stored in number of son of load_name (decl) */

				return wbody;
			}			/* end deferred */

			if ((props(e) & inreg_bits) == 0 && fixregable(e))
			{
				wp p;

				p = max_weights(fno(e) - 2.0 * scale, &wbody, 1);

				no(e) = p.fix_break;
				if (wdef_set)
					return add_weights(&wdef, &p.wp_weights);
				else
					return p.wp_weights;
			}
			else if ((props(e) & infreg_bits) == 0 && floatregable(e))
			{
				wp p;

				p = max_weights(fno(e) - 3.0 * scale, &wbody, 0);

				/*
				 * usage decreased by 3 because of dump and restore of double s-reg
				 */
				no(e) = p.float_break /* was noe */;
				if (wdef_set)
					return add_weights(&wdef, &p.wp_weights);
				else
					return p.wp_weights;
			}
			else
			{
				no(e) = noe;

				if (wdef_set)
					return add_weights(&wdef, &wbody);
				else
					return wbody;
			}
		}
		else
			return zeroweights;
	};
	case rep_tag:
	{
		e = bro(son(e));
		goto tailrecurse;
	}

	case case_tag:
	{
		e = son(e);
		goto tailrecurse;
	};

	case labst_tag:
	{
		scale = fno(e) * scale;
		e = bro(son(e));
		goto tailrecurse;
	}


	case val_tag:
	{
		return zeroweights;
	};

	case ncopies_tag:
	{
		scale = no(e) * scale;
		e = son(e);
		goto tailrecurse;
	}




	default:
	{
		if (son(e) == nilexp || n == env_offset_tag
			|| n == general_env_offset_tag)
		{
			return zeroweights;
		}
		if (last(son(e)))
		{
			e = son(e);
			goto tailrecurse;
		}
		return (add_wlist(scale, son(e)));
	}
	}
}














