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

#include <string.h>

#include <shared/error.h>
#include <shared/xalloc.h>

#include "obj_c/tdf.h"
#include "obj_c/cons_ops.h"
#include "obj_c/info_ops.h"
#include "obj_c/link_ops.h"
#include "obj_c/par_ops.h"
#include "obj_c/sort_ops.h"
#include "input.h"


/*
    ARRAY OF KNOWN SORT NAMES

    This table gives the mapping from sort names to sort codes.  Sorts
    not in this list, or with a sort code of zero, have sort codes
    automatically generated for them.
*/

static struct {
    char *name;
    int code;
} sort_names[] = {
    /* Built-in sorts */
    { "tdfint", 'i' },
    { "tdfstring", '$' },
    { "tdfident", '=' },
    { "tdfbool", 'j' },
    { "bitstream", '@' },
    { "bytestream", '#' },

    /* Basic sorts */
    { "access", 'u' },
    { "alignment", 'a' },
    { "al_tag", 'A' },
    { "bitfield_variety", 'B' },
    { "bool", 'b' },
    { "callees", 'q' },
    { "error_code", 'c' },
    { "error_treatment", 'e' },
    { "exp", 'x' },
    { "floating_variety", 'f' },
    { "label", 'l' },
    { "nat", 'n' },
    { "ntest", 'N' },
    { "procprops", 'P' },
    { "rounding_mode", 'r' },
    { "shape", 'S' },
    { "signed_nat", 's' },
    { "string", 'X' },
    { "tag", 't' },
    { "token", 'T' },
    { "transfer_mode", 'm' },
    { "variety", 'v' },

    /* Unit sorts */
    { "al_tagdef", 0 },
    { "diag_tagdef", 0 },
    { "external", 0 },
    { "sortname", '~' },
    { "tagdec", 0 },
    { "tagdef", 0 },
    { "tokdec", 0 },
    { "tokdef", 0 },

    /* Diagnostic and linkage sorts */
    { "diag_descriptor", 'D' },
    { "diag_tag", 'I' },
    { "diag_tq", 'g' },
    { "diag_type", 'd' },
    { "filename", 'Q' },
    { "linkinfo", 'L' },
    { "sourcemark", 'M' },
    { "version", 'V' },

    /* New diagnostic sorts */
    { "dg", 'G' },
    { "dg_accessibility", 'o' },
    { "dg_append", 'H' },
    { "dg_bound", 'w' },
    { "dg_classmem", 'z' },
    { "dg_class_base", 'y' },
    { "dg_compilation", 'C' },
    { "dg_dim", 'O' },
    { "dg_discrim", 'K' },
    { "dg_enum", 'E' },
    { "dg_field", 'R' },
    { "dg_filename", 'U' },
    { "dg_idname", 'Y' },
    { "dg_macro", 'Z' },
    { "dg_name", 'h' },
    { "dg_namelist", 'k' },
    { "dg_param", 'p' },
    { "dg_param_mode", 0 },
    { "dg_qualifier", 0 },
    { "dg_sourcepos", 'W' },
    { "dg_tag", 'J' },
    { "dg_type", 0 },
    { "dg_variant", 0 },
    { "dg_varpart", 0 },
    { "dg_virtuality", 0 }
};

#define NO_BUILTIN_SORTS	6
#ifndef array_size
#define array_size(x) (sizeof (x) / sizeof *(x))
#endif
#define NO_SORTS		array_size(sort_names)


/*
    LIST OF ALL SORTS

    A list of all sorts (in alphabetical order) is maintained.
*/

static LIST(SORT)all_sorts = NULL_list(SORT);


/*
    DEFINE A SORT

    This routine defines the sort s to be info.
*/

static void
define_sort(SORT s, SORT_INFO info, int code)
{
    static int next_code = 1;
    SORT_INFO old = DEREF_info(sort_info(s));
    if (!IS_NULL_info(old)) {
	string nm = DEREF_string(sort_name(s));
	error(ERROR_SERIOUS, "Sort '%s' already defined", nm);
    }
    COPY_info(sort_info(s), info);
    if (code == 0) code = next_code++;
    COPY_int(sort_code(s), code);
    return;
}


/*
    FIND A SORT

    This routine looks up a sort named nm, creating it if it does not
    already exist if create is true.
*/

SORT
find_sort(string nm, int create)
{
    SORT s;
    string cnm;
    SORT_INFO info = NULL_info;
    LIST(SORT)p = all_sorts;
    LIST(SORT)q = NULL_list(SORT);
    while (!IS_NULL_list(p)) {
	int cmp;
	string n;
	s = DEREF_sort(HEAD_list(p));
	n = DEREF_string(sort_name(s));
	cmp = strcmp(n, nm);
	if (cmp == 0) return s;
	if (cmp > 0) break;
	q = p;
	p = TAIL_list(p);
    }
    cnm = to_capitals(nm);
    MAKE_sort_basic(nm, cnm, NULL, NULL, 0, 0, 0, 0, info, s);
    if (!create) {
	error(ERROR_SERIOUS, "Sort '%s' not defined", nm);
	MAKE_info_builtin(nm, info);
	define_sort(s, info, 0);
    }
    CONS_sort(s, p, p);
    if (IS_NULL_list(q)) {
	all_sorts = p;
    } else {
	COPY_list(PTR_TAIL_list(q), p);
    }
    return s;
}


/*
    MARK A CONSTRUCT AS USED

    This routine marks the parameter sorts of the constructs c with the
    value m.
*/

void
mark_construct(CONSTRUCT c, int m)
{
    if (!IS_NULL_cons(c)) {
	LIST(PARAMETER)p = DEREF_list(cons_pars(c));
	while (!IS_NULL_list(p)) {
	    PARAMETER a = DEREF_par(HEAD_list(p));
	    SORT s = DEREF_sort(par_type(a));
	    mark_sort(s, m);
	    p = TAIL_list(p);
	}
    }
    return;
}


/*
    MARK A SORT AS USED

    This routine marks the sort s and all its constructs with the value m.
*/

void
mark_sort(SORT s, int m)
{
    int mark = DEREF_int(sort_mark(s));
    if (mark != m) {
	SORT_INFO info = DEREF_info(sort_info(s));
	COPY_int(sort_mark(s), m);
	if (!IS_NULL_info(info)) {
	    switch (TAG_info(info)) {
		case info_basic_tag: {
		    LIST(CONSTRUCT)p;
		    p = DEREF_list(info_basic_cons(info));
		    while (!IS_NULL_list(p)) {
			CONSTRUCT c = DEREF_cons(HEAD_list(p));
			mark_construct(c, m);
			p = TAIL_list(p);
		    }
		    break;
		}
		case info_dummy_tag: {
		    CONSTRUCT c = DEREF_cons(info_dummy_cons(info));
		    mark_construct(c, m);
		    break;
		}
		case info_clist_tag:
		case info_slist_tag:
		case info_option_tag: {
		    SORT p = DEREF_sort(info_clist_etc_arg(info));
		    mark_sort(p, m);
		    break;
		}
	    }
	}
    }
    return;
}


/*
    MARK ALL SORTS AS USED

    This routine marks all sorts with the value m.
*/

void
mark_all_sorts(int m)
{
    LIST(SORT)p = all_sorts;
    while (!IS_NULL_list(p)) {
	SORT s = DEREF_sort(HEAD_list(p));
	COPY_int(sort_mark(s), m);
	p = TAIL_list(p);
    }
    return;
}


/*
    DOES A STRING HAVE A GIVEN ENDING?

    This routine checks whether the string s ends in the string e.  If so
    it returns a copy of s with this ending removed.  Otherwise it returns
    the null string.
*/

string
ends_in(string s, string e)
{
    unsigned n = (unsigned)strlen(s);
    unsigned m = (unsigned)strlen(e);
    if (n >= m) {
	unsigned d = n - m;
	if (!strcmp(s + d, e)) {
	    s = xstrcpy(s);
	    s[d] = 0;
	    return s;
	}
    }
    return NULL;
}


/*
    CONVERT A STRING TO CAPITALS

    This routine returns a copy of the string s with all the lower case
    letters converted to upper case.
*/

string
to_capitals(string s)
{
    char c;
    string t;
    s = xstrcpy(s);
    t = s;
    while (c = *t, c != 0) {
	if (c >= 'a' && c <= 'z') {
	    *t = (char)('A' + (c - 'a'));
	}
	t++;
    }
    return s;
}


/*
    DEFINE A BASIC SORT

    This routine defines the basic sort s to have b bits (extended if e
    is true) and constructs p.
*/

void
basic_sort(SORT s, unsigned b, unsigned e, LIST(CONSTRUCT)p)
{
    int code = 0;
    SORT_INFO info;
    string n = DEREF_string(sort_name(s));
    if (b == 0 && e == 0 && LENGTH_list(p) == 1) {
	/* Dummy sort */
	CONSTRUCT c = DEREF_cons(HEAD_list(p));
	MAKE_info_dummy(n, c, info);
	code = 'F';
    } else {
	size_t i;
	for (i = NO_BUILTIN_SORTS; i < NO_SORTS; i++) {
	    if (!strcmp(n, sort_names[i].name)) {
		code = sort_names[i].code;
		break;
	    }
	}
	MAKE_info_basic(n, b, e, 0, p, NULL_cons, info);
    }
    define_sort(s, info, code);
    return;
}


/*
    CREATE A CONSTRUCT

    This routine creates a construct named nm with result sort s, parameter
    sorts p and encoding e.
*/

CONSTRUCT
make_construct(string nm, unsigned e, SORT s, LIST(PARAMETER)p)
{
    CONSTRUCT c;
    unsigned kind = KIND_simple;
    if (ends_in(nm, "_apply_token")) kind = KIND_token;
    if (ends_in(nm, "_cond")) kind = KIND_cond;
    MAKE_cons_basic(nm, e, s, p, kind, c);
    return c;
}


/*
    DEFINE A COMPOUND SORT

    This routine defines the compound sort s with standard suffix suff
    and sort type tag.
*/

void
compound_sort(SORT s, string suff, unsigned tag, int code)
{
    string nm = DEREF_string(sort_name(s));
    string snm = ends_in(nm, suff);
    if (snm) {
	SORT_INFO info;
	SORT t = find_sort(snm, 1);
	MAKE_info_clist_etc(tag, nm, t, info);
	define_sort(s, info, code);
    } else {
	error(ERROR_SERIOUS, "Sort '%s' doesn't end in '%s'", nm, suff);
    }
    return;
}


/*
    FIND A CONSTRUCT

    This routine searches for a construct named c in the sort s.
*/

CONSTRUCT
find_construct(SORT s, string c)
{
    SORT_INFO info = DEREF_info(sort_info(s));
    if (!IS_NULL_info(info) && IS_info_basic(info)) {
	LIST(CONSTRUCT)p = DEREF_list(info_basic_cons(info));
	while (!IS_NULL_list(p)) {
	    CONSTRUCT a = DEREF_cons(HEAD_list(p));
	    string b = DEREF_string(cons_name(a));
	    if (!strcmp(b, c)) return a;
	    p = TAIL_list(p);
	}
    }
    return NULL_cons;
}


/*
    SET A CONSTRUCT KIND

    This routine sets the kind of the construct c of sort s to be kind.
*/

void
set_special(SORT s, string c, unsigned kind)
{
    CONSTRUCT a = find_construct(s, c);
    if (!IS_NULL_cons(a)) {
	COPY_unsigned(cons_kind(a), kind);
    } else {
	string nm = DEREF_string(sort_name(s));
	error(ERROR_SERIOUS, "Can't find construct '%s' for sort '%s'",
		c, nm);
    }
    return;
}


/*
    FIND A CONSTRUCT OF A GIVEN KIND

    This routine searches for a construct of the sort s of the given kind.
*/

CONSTRUCT
get_special(SORT s, unsigned kind)
{
    SORT_INFO info = DEREF_info(sort_info(s));
    if (!IS_NULL_info(info) && IS_info_basic(info)) {
	LIST(CONSTRUCT)p = DEREF_list(info_basic_cons(info));
	while (!IS_NULL_list(p)) {
	    CONSTRUCT a = DEREF_cons(HEAD_list(p));
	    unsigned b = DEREF_unsigned(cons_kind(a));
	    if (b == kind) return a;
	    p = TAIL_list(p);
	}
    }
    return NULL_cons;
}


/*
    DEFINE THE BUILT-IN SORTS

    This routine defines the built-in sorts.
*/

void
builtin_sorts(void)
{
    size_t i;
    for (i = 0; i < NO_BUILTIN_SORTS; i++) {
	SORT_INFO info;
	char *nm = sort_names[i].name;
	SORT s = find_sort(nm, 1);
	MAKE_info_builtin(nm, info);
	define_sort(s, info, sort_names[i].code);
    }
    return;
}


/*
    CHECK THE LIST OF ALL SORTS

    This routine checks the list of all sorts for undefined sorts,
    returning the reordered list.
*/

LIST(SORT)
check_sorts(void)
{
    LIST(SORT)p = all_sorts;
    while (!IS_NULL_list(p)) {
	SORT s = DEREF_sort(HEAD_list(p));
	SORT_INFO info = DEREF_info(sort_info(s));
	if (IS_NULL_info(info)) {
	    string nm = DEREF_string(sort_name(s));
	    error(ERROR_SERIOUS, "Sort '%s' not defined", nm);
	    MAKE_info_builtin(nm, info);
	    define_sort(s, info, 0);
	}
	if (IS_info_basic(info)) {
	    unsigned m = 0;
	    LIST(CONSTRUCT)q = DEREF_list(info_basic_cons(info));
	    while (!IS_NULL_list(q)) {
		CONSTRUCT a = DEREF_cons(HEAD_list(q));
		unsigned n = DEREF_unsigned(cons_encode(a));
		if (n > m) m = n;
		q = TAIL_list(q);
	    }
	    COPY_unsigned(info_basic_max(info), m);
	}
	p = TAIL_list(p);
    }
    return all_sorts;
}


/*
    FIND FOREIGN SORTS

    This routine finds all the foreign sorts.
*/

LIST(LINKAGE)
foreign_sorts(void)
{
    unsigned e = 0;
    LIST(SORT)p = all_sorts;
    LIST(LINKAGE)q = NULL_list(LINKAGE);
    LIST(PARAMETER)pars = NULL_list(PARAMETER);
    SORT t = find_sort("sortname", 0);
    SORT_INFO info = DEREF_info(sort_info(t));
    if (IS_info_basic(info)) {
	e = DEREF_unsigned(info_basic_max(info));
    }
    while (!IS_NULL_list(p)) {
	SORT s = DEREF_sort(HEAD_list(p));
	info = DEREF_info(sort_info(s));
	if (IS_info_basic(info)) {
	    string nm = DEREF_string(sort_name(s));
	    CONSTRUCT c = get_special(s, KIND_token);
	    if (!IS_NULL_cons(c)) {
		/* Sort can be tokenised */
		string snm = nm;
		if (!strcmp(nm, "alignment")) {
		    snm = "alignment_sort";
		}
		c = find_construct(t, snm);
		if (IS_NULL_cons(c)) {
		    /* Doesn't have a sort name */
		    LINKAGE a;
		    if (!strcmp(nm, "diag_type")) {
			snm = "diag_type";
		    } else if (!strcmp(nm, "filename")) {
			snm = "~diag_file";
		    } else {
			snm = to_capitals(nm);
		    }
		    MAKE_cons_basic(snm, ++e, t, pars, KIND_foreign, c);
		    MAKE_link_basic(snm, s, a);
		    CONS_link(a, q, q);
		}
	    } else {
		MAKE_cons_basic(nm, ++e, t, pars, KIND_dummy, c);
	    }
	    COPY_cons(info_basic_sortname(info), c);
	}
	p = TAIL_list(p);
    }
    q = REVERSE_list(q);
    return q;
}


/*
    FIND A PARAMETER

    This routine returns the nth parameter of the construct c.
*/

PARAMETER
find_param(CONSTRUCT c, unsigned n)
{
    LIST(PARAMETER)p = DEREF_list(cons_pars(c));
    while (n) {
	if (IS_NULL_list(p)) {
	    string nm = DEREF_string(cons_name(c));
	    error(ERROR_SERIOUS, "Bad parameter number for '%s'", nm);
	    return NULL_par;
	}
	p = TAIL_list(p);
	n--;
    }
    return DEREF_par(HEAD_list(p));
}
