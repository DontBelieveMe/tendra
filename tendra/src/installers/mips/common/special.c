/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
/*special.c
 *    inlines some of the simpler standard library functions
 */


#include "config.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "shapemacs.h"
#include "move.h"
#include "psu_ops.h"
#include "getregs.h"
#include "guard.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "mips_ins.h"
#include "labels.h"
#include "tags.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "special.h"
#include "basicread.h"


int
specno(char *n)
{	/* these are the procs I could do
	 *				   something about */
	if    (strcmp (n, "strcpy") == 0)
		return - 1;
	if (strcmp (n, "strlen") == 0)
		return 2;
	if (strcmp (n, "strcmp") == 0)
		return - 3;
	return 0;
}

static  needs strcpyneeds = {
	0, 0, 0, 0
};
static  needs strlenneeds = {
	3, 0, uses2_bit, 0
};
static  needs strcmpneeds = {
	2, 0, 0, 0
};

needs
specialneeds(int i)
{	/* these are the needs for their expansion
	 */
	switch (i) {
    case 1:
		return strcpyneeds;
    case 2:
		return strlenneeds;
    case 3:
		return strcmpneeds;
    default:
		failer ("not special fn");
	}
	return strcpyneeds;
}

int
specialfn(exp fn)
{	/* could I treat this function load
	 *				   specially ? */
	if (name (fn) == name_tag && name (son (fn)) == ident_tag &&
		isglob (son (fn)) && son (son (fn)) == nilexp) {
		char *extname = brog(son (fn)) -> dec_u.dec_val.dec_id;
		return specno (extname);
	}
	return 0;
}





int
specialmake(int n, exp par, space sp, where dest,
			int exitlab)
{
	switch (n) {
    case  2:			/* translate strlen in the obvious manner
						 */
	{
		where w;
		ans aa;
		int   lstart = new_label ();
		int   r;
		int   r1;
		baseoff ind3;
		int r3;
		r = (dest.answhere.discrim == inreg) ? regalt (dest.answhere)
			: getreg (sp.fixed);
		if (r == 0) r = 2; /* can be called like proc on lhs of ass */
		sp = guardreg(r,sp);
		r3 = getreg(sp.fixed);
		ind3.base = r3; ind3.offset = 0;
		setregalt (w.answhere, r3);
		w.ashwhere = ashof (sh (par));
		code_here (par, sp, w);
		
		r1 = getreg (guardreg (r3, sp).fixed);
		
		rri_ins (i_add, r, r3, 1);
		set_label (lstart);
		
		ls_ins (i_lb, r1, ind3);
		rri_ins (i_add, r3, r3, 1);
		condr_ins (i_bnez, r1, lstart);
		
		rrr_ins (i_sub, r, r3, r);
		setregalt (aa, r);
		move (aa, dest, sp, 1);
		return exitlab;
	}
    default:
		failer ("not special");
	}
	return exitlab;
}
