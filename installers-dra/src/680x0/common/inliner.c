/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1996

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/inliner.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: inliner.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:53  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:13  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:35  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:54  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:12  john
 *
 * Revision 1.1  94/06/29  14:22:10  14:22:10  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
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
