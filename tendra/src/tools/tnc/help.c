/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
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
#include "read_types.h"
#include "analyser.h"
#include "help.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    FLAG

    Should help information be printed in functional form?
*/

boolean func_help = 0;


/*
    PRINT A LIST OF ARGUMENTS

    This routine prints the arguments corresponding to the argument
    string str.  The flag num is true to indicate an actual TDF
    integer, rather than the identifier for a tag, token etc.
*/

static void
help_args(char *str, boolean num)
{
    char c;
    boolean started = 0;
    while (c = *str, c != 0 && c != ']') {
	if (func_help && started)IGNORE putchar(',');
	switch (c) {

	    case '[':
	    case '{':
	    case '}':
	    case '&':
	    case '^':
	    case '|': {
		/* Ignore these cases */
		break;
	    }

	    case 'i': {
		/* Numbers or identifiers */
		if (num) {
		    IGNORE printf(" number");
		} else {
		    IGNORE printf(" identifier");
		}
		break;
	    }

	    case 'j': {
		/* Ignore bits */
		break;
	    }

	    case '$': {
		/* Strings */
		IGNORE printf(" tdfstring");
		break;
	    }

	    case '*': {
		/* Repeated arguments */
		str += 2;
		help_args(str, 0);
		if (func_help) {
		    IGNORE printf(", ...,");
		} else {
		    IGNORE printf(" ...");
		}
		help_args(str, 0);
		str = skip_text(str);
		break;
	    }

	    case '?': {
		/* Optional arguments */
		str += 2;
		IGNORE printf(" [");
		help_args(str, 0);
		IGNORE printf(" ]");
		str = skip_text(str);
		break;
	    }

	    case '@': {
		/* Conditional arguments */
		str += 2;
		help_args(str, 0);
		str = skip_text(str);
		break;
	    }

	    case '!': {
		/* Token applications */
		if (func_help) {
		    IGNORE printf(" identifier ( arg, ..., arg )");
		} else {
		    IGNORE printf(" ( identifier arg ... arg )");
		}
		break;
	    }

	    case 'F': {
		is_fatal = 0;
		input_error("Foreign sorts not supported");
		break;
	    }

	    default : {
		sortname s = find_sort(c);
		IGNORE printf(" %s", sort_name(s));
		break;
	    }
	}
	if (c != 'j')started = 1;
	str++;
    }
    return;
}


/*
    OUTPUT HELP INFORMATION

    The help information on the construct p is output.
*/

static void
output_help(construct *p)
{
    char *args = get_char_info(p);
    IGNORE printf((func_help ? "%s" : "( %s"), p->name);
    if (args) {
	boolean num = 0;
	if ((p->sortnum == SORT_nat && p->encoding == ENC_make_nat) ||
	    (p->sortnum == SORT_signed_nat &&
	       p->encoding == ENC_make_signed_nat)) {
	    num = 1;
	}
	if (func_help)IGNORE printf(" (");
	help_args(args, num);
	if (func_help)IGNORE printf(" )");
    }
    if (!func_help)IGNORE printf(" )");
    IGNORE printf(" -> %s\n", sort_name(p->sortnum));
    return;
}


/*
    PRINT HELP ON A TDF CONSTRUCT

    The help information on the construct named nm is output.
*/

void
help(char *nm)
{
    sortname s;
    construct *p;
    static int sorted = 0;
    func_help = func_input;

    /* Check for "help all" */
    if (streq(nm, "all")) {
	for (s = 0; s < SORT_no; s++) {
	    if (s != SORT_sortname) {
		sort_table(cons_hash_tables, s);
		sorted = 1;
		p = cons_hash_tables[hash_size * s];
		if (p) {
		    for (; p; p = p->next)output_help(p);
		    IGNORE printf("\n");
		}
	    }
	}
	return;
    }

    /* Check for "help construct" */
    for (s = 0; s < SORT_no; s++) {
	if (s != SORT_sortname) {
	    p = search_cons_hash(nm, s);
	    if (p) {
		output_help(p);
		return;
	    }
	    if (sorted) {
		p = cons_hash_tables[hash_size * s];
		for (; p; p = p->next) {
		    if (streq(nm, p->name)) {
			output_help(p);
			return;
		    }
		}
	    }
	}
    }

    /* Check for "help sort" */
    if (streq(nm, "alignment_sort"))nm = "alignment";
    p = search_cons_hash(nm, SORT_sortname);
    if (p) {
	s = (sortname)p->encoding;
	sort_table(cons_hash_tables, s);
	sorted = 1;
	p = cons_hash_tables[hash_size * s];
	for (; p; p = p->next)output_help(p);
	return;
    }

    /* Unknown construct */
    is_fatal = 0;
    input_error("Unknown construct, %s", nm);
    return;
}
