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
		 Crown Copyright (c) 1997

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


#include "config.h"
#include "types.h"
#include "alignment.h"
#include "check.h"
#include "eval.h"
#include "node.h"
#include "read.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    SHAPE CHECKING FLAG

    This flag is true to indicate that shape checking should be applied.
*/

boolean do_check = 0;


/*
    THE NAME OF THE CURRENT EXPRESSION BEING CHECKED

    The shape checking does not always take place immediately.  By
    printing the name of the expression being checked it is easier
    to find any errors.
*/

char *checking = "????";


/*
    SHAPE CHECKING FOR EXP_APPLY_TOKEN

    The shape checking for the exp_apply_token construct p is implemented
    by this routine.
*/

static void
chk_token(node *p)
{
    tok_info *info = get_tok_info(p->son->cons);
    node *d = info->def;
    if (d) {
	if (d->cons->sortnum == SORT_completion)d = d->son;
	p->shape = normalize(d->shape);
    } else {
	p->shape = new_node();
	p->shape->cons = &shape_of;
	p->shape->son = copy_node(p->son);
    }
    return;
}


/*
    SHAPE CHECKING FOR EXP_COND

    The shape checking for the exp_cond construct p is implemented by
    this routine.  Checking that the control argument is an integer is
    carried out for all _cond constructs as part of the main reading
    and decoding routines for the decode letter '@'.
*/

static void
chk_cond(node *p)
{
    node *s;
    node *q1 = p->son->bro->son;
    node *q2 = p->son->bro->bro->son;
    node *s1 = q1->shape;
    node *s2 = q2->shape;
    if (q1->cons->encoding == ENC_fail_installer) {
	p->shape = normalize(s2);
	return;
    }
    if (q2->cons->encoding == ENC_fail_installer) {
	p->shape = normalize(s1);
	return;
    }
    s = lub(s1, s2);
    if (s == null) {
	p->shape = null;
    } else {
	long n = s->cons->encoding;
	if (n == ENC_bottom || n == ENC_top) {
	    p->shape = null;
	} else {
	    p->shape = normalize(s);
	}
    }
    return;
}


/*
    SHAPE CHECKING FOR OBTAIN_TAG

    The shape checking for the obtain_tag construct p is implemented by
    this routine.  a gives the actual tag.
*/

static void
chk_tag(node *p, node *a, int intro)
{
    if (!intro && a->cons->encoding == ENC_make_tag) {
	tag_info *info = get_tag_info(a->son->cons);
	node *d = info->dec;
	if (d && d->cons->sortnum == SORT_completion)d = d->son;
	if (d)d = d->bro;
	if (d)d = d->bro;
	switch (info->var) {
	    case 0: {
		p->shape = normalize(d);
		break;
	    }
	    case 1:
	    case 2: {
		p->shape = sh_pointer(d);
		break;
	    }
	    default : {
		if (text_input) {
		    char *nm = a->son->cons->name;
		    is_fatal = 0;
		    input_error("Tag %s used but not declared", nm);
		}
		p->shape = null;
		break;
	    }
	}
    } else {
	p->shape = null;
    }
    return;
}


/*
    SHAPE CHECKING MACRO DEFINITIONS

    The main body of the shape checking for expressions is in the
    automatically generated file check_exp.h.  This calls a macro of
    the form check_<cons> for each construct <cons>.  The actual
    definitions of these macros (which vary between TDF specification
    releases) are in check_def.h.
*/

#include "check_def.h"
#include "check_exp.h"


/*
    SHAPE CHECK A SHAPE

    The construct compound has an exp argument which needs to be
    shape checked.
*/

void
check_shape_fn(node *p)
{
    if (p && p->cons->encoding == ENC_compound) {
	if (do_check) {
	    checking = p->cons->name;
	    IGNORE check1(ENC_offset, p->son);
	}
    }
    return;
}


/*
    SHAPE CHECK A NAT

    The construct computed_nat has an exp argument which needs to be
    shape checked.
*/

void
check_nat_fn(node *p)
{
    if (p && p->cons->encoding == ENC_computed_nat) {
	if (do_check) {
	    checking = p->cons->name;
	    IGNORE check1(ENC_integer, p->son);
	}
    }
    return;
}


/*
    SHAPE CHECK A SIGNED NAT

    The construct computed_signed_nat has an exp argument which needs
    to be shape checked.
*/

void
check_snat_fn(node *p)
{
    if (p && p->cons->encoding == ENC_computed_signed_nat) {
	if (do_check) {
	    checking = p->cons->name;
	    IGNORE check1(ENC_integer, p->son);
	}
    }
    return;
}


/*
    SHAPE CHECK AN ACCESS

    The flag intro_visible is set whenever a visible construct is
    encountered.
*/

void
check_access_fn(node *p)
{
    if (p && p->cons->encoding == ENC_visible)intro_visible = 1;
    return;
}


/*
    IS A SHAPE COMPLETELY KNOWN?

    This routine returns true if p is not null and does not contain
    any unknown constructs.  In encode mode we can't have any constructs
    which introduce local tags or tokens either.
*/

static boolean
is_known(node *p)
{
    if (p == null) return(0);
    while (p) {
	sortname s = p->cons->sortnum;
	if (s == SORT_unknown) return(0);
	if (!text_output && s == SORT_exp) {
	    switch (p->cons->encoding) {
		case ENC_conditional: return(0);
		case ENC_identify: return(0);
		case ENC_labelled: return(0);
		case ENC_make_proc: return(0);
		case ENC_repeat: return(0);
		case ENC_variable: return(0);
	    }
	}
	if (p->son && !is_known(p->son)) return(0);
	p = p->bro;
    }
    return(1);
}


/*
    CHECK THAT A TAG DECLARATION AND DEFINITION MATCH

    The construct p, representing a declared and defined tag, is checked
    for shape correctness.
*/

void
check_tagdef(construct *p)
{
    char *nm = p->name;
    tag_info *info = get_tag_info(p);
    node *dc = info->dec;
    node *df = info->def;
    if (df == null) return;
    if (df->cons->sortnum == SORT_completion)df = df->son;
    if (info->var)df = df->bro;
    if (dc == null) {
	if (is_known(df->shape)) {
	    /* Declaration = ?[u]?[X]S (from 4.0) */
	    node *q = new_node();
	    q->cons = &false_cons;
	    q->bro = new_node();
	    q->bro->cons = &false_cons;
	    q->bro->bro = df->shape;
	    info->dec->bro = completion(q);
	} else {
	    is_fatal = 0;
	    input_error("Can't deduce shape of %s from definition", nm);
	}
    } else {
	if (dc->cons->sortnum == SORT_completion)dc = dc->son;
	/* Declaration = ?[u]?[X]S (from 4.0) */
	dc = dc->bro->bro;
	checking = nm;
	IGNORE check_shapes(dc, df->shape, 1);
    }
    return;
}
