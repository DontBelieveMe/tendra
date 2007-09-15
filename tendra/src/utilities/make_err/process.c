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

#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "entry_ops.h"
#include "map_ops.h"
#include "msg_ops.h"
#include "name_ops.h"
#include "param_ops.h"
#include "error.h"
#include "lex.h"
#include "process.h"
#include "xalloc.h"


/*
    DATABASE HEADER INFORMATION

    These variables are used to store the standard header information.
*/

char *db_name = "ERRORS";
char *db_name_alt = "ERRORS";
char *rig_name = "ERR_";
char *rig_comp_output = "ERR_";
char *rig_from_comp = "ERR_USE_";
char *rig_from_db = "ERR_NO_";


/*
    DATABASE SECTION LISTS

    These variables are used to store the various lists of information
    built up by the parser.
*/

LIST(ENTRY)all_entries = NULL_list(ENTRY);
LIST(KEY)all_keys = NULL_list(KEY);
LIST(PROPERTY)all_props = NULL_list(PROPERTY);
LIST(TYPE)all_types = NULL_list(TYPE);
LIST(USAGE)all_usages = NULL_list(USAGE);
LIST(KEY)all_keys_aux = NULL_list(KEY);
LIST(PROPERTY)all_props_aux = NULL_list(PROPERTY);
LIST(TYPE)all_types_aux = NULL_list(TYPE);
LIST(USAGE)all_usages_aux = NULL_list(USAGE);
LIST(KEY)all_keys_alt = NULL_list(KEY);
LIST(PROPERTY)all_props_alt = NULL_list(PROPERTY);
LIST(TYPE)all_types_alt = NULL_list(TYPE);
LIST(USAGE)all_usages_alt = NULL_list(USAGE);


/*
    FIND CODE LETTER

    This routine finds a code letter corresponding to the number n.  It
    assumes the ASCII character set.
*/

static int
code_letter(int n)
{
	if (n < 10) {
		return ('0' + n);
	}
	if (n < 36) {
		return ('A' + (n - 10));
	}
	if (n < 72) {
		return ('a' + (n - 36));
	}
	return (n + 128);
}


/*
    LOOK UP AN ERROR MAP

    This routine looks up the value of the property named s in the list
    of property mappings p.
*/

static MAP
find_map(LIST(MAP)p, string s)
{
	while (!IS_NULL_list(p)) {
		MAP m = DEREF_map(HEAD_list(p));
		NAME n = DEREF_name(map_key(m));
		if (!IS_NULL_name(n)) {
			string t = DEREF_string(name_id(n));
			if (!strcmp(s, t)) {
				return (m);
			}
		}
		p = TAIL_list(p);
	}
	return (NULL_map);
}


/*
    OUTPUT A MESSAGE LIST

    This routine prints the message list p to the file f.
*/

static void
output_msg(FILE *f, LIST(MESSAGE) p)
{
	int sp = 0;
	(void) fputc('"', f);
	while (!IS_NULL_list(p)) {
		MESSAGE m = DEREF_msg(HEAD_list(p));
		if (!IS_NULL_msg(m)) {
			if (IS_msg_param(m)) {
				PARAM a = DEREF_param(msg_param_arg(m));
				int an = DEREF_int(param_number(a));
				an = code_letter(an);
				if (sp) {
					(void) fputc(' ', f);
					sp = 0;
				}
				(void) fprintf(f, "%%%c", an);
			} else {
				char c;
				string s = DEREF_string(msg_text_arg(m));
				while (c = *(s++), c != 0) {
					if (c == ' ' || c == '\t' ||
					    c == '\n') {
						sp = 1;
					} else {
						if (sp) {
							(void) fputc(' ', f);
							sp = 0;
						}
						(void) fputc(c, f);
					}
				}
			}
		}
		p = TAIL_list(p);
	}
	(void) fputc('"', f);
	return;
}


/*
    OUTPUT ERROR DEFINITIONS

    This routine outputs all the error definitions to the file f.
*/

static void
output_defn(FILE *f)
{
	/* Print error catalog */
	LIST(NAME) p;
	char *d1 = db_name;
	char *d2 = db_name_alt;
	char *pre = rig_comp_output;
	char *pre_comp = rig_from_comp;
	LIST(ENTRY) q = all_entries;

	/* Print each catalogue entry */
	(void) fprintf ( f, "/* Error catalogue */\n\n" ) ;
	if (!strcmp(d1, d2)) {
		(void) fprintf(f, "%sCONST char *%sNAME = \"%s\" ;\n", pre, pre, d1);
	} else {
		(void) fprintf(f, "#ifndef %sALTERNATE\n", pre);
		(void) fprintf(f, "%sCONST char *%sNAME = \"%s\" ;\n", pre, pre, d1);
		(void) fprintf(f, "#else\n");
		(void) fprintf(f, "%sCONST char *%sNAME = \"%s\" ;\n", pre, pre, d2);
		(void) fprintf(f, "#endif\n");
	}
	(void) fprintf(f, "\n%sDATA %sCATALOG [] = {\n", pre, pre);
	while (!IS_NULL_list(q)) {
		unsigned u = 0;
		char *suff = ",\n";
		ENTRY e = DEREF_entry(HEAD_list(q));
		string en = DEREF_string(entry_name(e));
		USAGE eu = DEREF_name(entry_use(e));
		USAGE ev = DEREF_name(entry_alt_use(e));
		LIST(MAP) em = DEREF_list(entry_maps(e));
		LIST(PROPERTY) eq = DEREF_list(entry_props(e));
		LIST(PARAM) ep = DEREF_list(entry_signature(e));

		/* Print error name */
		(void) fprintf(f, "    {\n\t\"%s\",\n", en);

		/* Print error signature */
		if (IS_NULL_list(ep)) {
			(void) fprintf(f, "\tNULL,\n");
		} else {
			(void) fprintf(f, "\t\"");
			while (!IS_NULL_list(ep)) {
				PARAM a = DEREF_param(HEAD_list(ep));
				TYPE at = DEREF_name(param_type(a));
				int an = DEREF_int(name_number(at));
				an = code_letter(an);
				(void) fputc(an, f);
				ep = TAIL_list(ep);
			}
			(void) fprintf(f, "\",\n");
		}

		/* Print error usage */
		if (!EQ_name(eu, ev)) {
			(void) fprintf(f, "#ifndef %sALTERNATE\n", pre);
		}
		if (IS_NULL_name(eu)) {
			(void) fprintf(f, "\t0,\n");
		} else {
			string un = DEREF_string(name_id(eu));
			(void) fprintf(f, "\t%s%s,\n", pre_comp, un);
		}
		if (!EQ_name(eu, ev)) {
			(void) fprintf(f, "#else\n");
			if (IS_NULL_name(ev)) {
				(void) fprintf(f, "\t0,\n");
			} else {
				string vn = DEREF_string(name_id(ev));
				(void) fprintf(f, "\t%s%s,\n", pre_comp, vn);
			}
			(void) fprintf(f, "#endif\n");
		}

		/* Print error properties */
		p = all_keys;
		if (IS_NULL_list(p)) {
			suff = "\n";
		}
		while (!IS_NULL_list(eq)) {
			PROPERTY nq = DEREF_name(HEAD_list(eq));
			unsigned n = (unsigned)DEREF_int(name_number(nq));
			u |= (((unsigned)1) << n);
			eq = TAIL_list(eq);
		}
		(void) fprintf(f, "\t%u%s", u, suff);

		/* Print error keys */
		while (!IS_NULL_list(p)) {
			NAME n = DEREF_name(HEAD_list(p));
			string pn = DEREF_string(name_id(n));
			MAP pm = find_map(em, pn);
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				suff = "\n";
			}
			if (IS_NULL_map(pm)) {
				(void) fprintf(f, "\tNULL%s", suff);
			} else {
				LIST(MESSAGE)m1 = DEREF_list(map_msg(pm));
				LIST(MESSAGE)m2 = DEREF_list(map_alt_msg(pm));
				if (!EQ_list(m1, m2)) {
					(void) fprintf(f, "#ifndef %sALTERNATE\n",
						  pre);
				}
				(void) fprintf(f, "\t");
				output_msg(f, m1);
				(void) fprintf(f, "%s", suff);
				if (!EQ_list(m1, m2)) {
					(void) fprintf(f, "#else\n\t");
					output_msg(f, m2);
					(void) fprintf(f, "%s#endif\n", suff);
				}
			}
		}
		(void) fprintf(f, "    },\n");
		q = TAIL_list(q);
	}

	/* Print dummy end marker */
	(void) fprintf(f, "    {\n");
	(void) fprintf(f, "\tNULL,\n");
	(void) fprintf(f, "\tNULL,\n");
	(void) fprintf(f, "\t0,\n");
	(void) fprintf(f, "\t0");
	p = all_keys;
	while (!IS_NULL_list(p)) {
		(void) fprintf(f, ",\n\tNULL");
		p = TAIL_list(p);
	}
	(void) fprintf(f, "\n    }\n");
	(void) fprintf(f, "} ;\n");
	return;
}


/*
    OUTPUT ERROR DECLARATIONS

    This routine outputs all the error declarations to the file f.
*/

static void
output_decl(FILE *f)
{
	int qn = 0;
	LIST(ENTRY) q = all_entries;

	/* Print main type definition */
	char *pre = rig_comp_output;
	char *pre_comp = rig_from_comp;
	LIST(NAME) p = all_keys;
	(void) fprintf(f, "#ifndef %sINCLUDED\n", pre);
	(void) fprintf(f, "#define %sINCLUDED\n\n\n", pre);
	(void) fprintf(f, "/* Error data structure */\n\n");
	(void) fprintf(f, "#ifndef %sCONST\n", pre);
	(void) fprintf(f, "#define %sCONST\n", pre);
	(void) fprintf(f, "#endif\n\n");
	if (LENGTH_list(all_props) < 16) {
		(void) fprintf(f, "typedef unsigned %sPROPS ;\n\n", pre);
	} else {
		(void) fprintf(f, "typedef unsigned long %sPROPS ;\n\n", pre);
	}
	(void) fprintf(f, "typedef struct {\n");
	(void) fprintf(f, "    %sCONST char *name ;\n", pre);
	(void) fprintf(f, "    %sCONST char *signature ;\n", pre);
	(void) fprintf(f, "    int usage ;\n");
	(void) fprintf(f, "    %sPROPS props ;\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		(void) fprintf(f, "    %sCONST char *key_%s ;\n", pre, tn);
		p = TAIL_list(p);
	}
	(void) fprintf(f, "} %sDATA ;\n\n", pre);
	(void) fprintf(f, "extern %sDATA %sCATALOG [] ;\n", pre, pre);
	(void) fprintf(f, "extern %sCONST char *%sNAME ;\n\n\n", pre, pre);

	/* Print type keys */
	p = all_types;
	(void) fprintf(f, "/* Error type keys */\n\n");
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		int n = DEREF_int(name_number(t));
		n = code_letter(n);
		(void) fprintf(f, "#define %sKEY_%s '%c'\n", pre, tn, n);
		p = TAIL_list(p);
	}
	(void) fprintf(f, "\n\n");

	/* Print usage keys */
	p = all_usages;
	(void) fprintf(f, "/* Error usage keys */\n\n");
	(void) fprintf(f, "#ifndef %sUSE\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		int n = DEREF_int(name_number(t));
		(void) fprintf(f, "#define %s%s %d\n", pre_comp, tn, n);
		p = TAIL_list(p);
	}
	(void) fprintf(f, "#endif\n\n\n");

	/* Print property keys */
	p = all_props;
	(void) fprintf(f, "/* Error property keys */\n\n");
	(void) fprintf(f, "#ifndef %sPROP\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		unsigned n = (unsigned)DEREF_int(name_number(t));
		unsigned u = (((unsigned)1) << n);
		(void) fprintf(f, "#define %sPROP_%s ( ( %sPROPS ) 0x%x )\n",
			  pre, tn, pre, u);
		p = TAIL_list(p);
	}
	(void) fprintf(f, "#endif\n\n\n");

	/* Print type checking macros */
	p = all_types;
	(void) fprintf(f, "/* Error type checking */\n\n");
	(void) fprintf(f, "#if defined ( %sCHECK ) && defined ( __STDC__ )\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		int n = DEREF_int(name_number(t));
		n = code_letter(n);
		(void) fprintf(f, "extern %s chk_%c ( %s ) ;\n", tn, n, tn);
		p = TAIL_list(p);
	}
	(void) fprintf(f, "#else\n");
	p = all_types;
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		int n = DEREF_int(name_number(t));
		n = code_letter(n);
		(void) fprintf(f, "#define chk_%c( A ) ( A )\n", n);
		p = TAIL_list(p);
	}
	(void) fprintf(f, "#endif\n\n\n");

	/* Print error macros */
	(void) fprintf ( f, "/* Error message macros */\n\n" ) ;
	(void) fprintf(f, "#ifdef %sGEN\n\n", pre);
	while (!IS_NULL_list(q)) {
		ENTRY e = DEREF_entry(HEAD_list(q));
		string en = DEREF_string(entry_name(e));
		LIST(PARAM) ep = DEREF_list(entry_signature(e));
		size_t np = LENGTH_list(ep);
		(void) fprintf(f, "#define %s%s(", pre, en);
		if (!IS_NULL_list(ep)) {
			/* Print parameter list */
			int arg = 0;
			LIST(PARAM)eq = ep;
			while (!IS_NULL_list(eq)) {
				if (arg) {
					(void) fputc(',', f);
				}
				(void) fprintf(f, " %c", 'A' + arg);
				eq = TAIL_list(eq);
				arg++;
			}
			(void) fputc(' ', f);
		}
		(void) fprintf(f, ")\\\n");
		(void) fprintf(f, "\t%sGEN ( %d", pre, qn);
		if (np) {
			/* Print error definition */
			int arg = 0;
			LIST(PARAM) eq = ep;
			while (!IS_NULL_list(eq)) {
				PARAM a = DEREF_param(HEAD_list(eq));
				TYPE at = DEREF_name(param_type(a));
				int an = DEREF_int(name_number(at));
				an = code_letter(an);
				(void) fprintf(f, ", chk_%c ( %c )", an, 'A' + arg);
				eq = TAIL_list(eq);
				arg++;
			}
		}
		(void) fprintf(f, " )\n\n");
		q = TAIL_list(q);
		qn++;
	}
	(void) fprintf(f, "\n#endif\n#endif\n");
	return;
}


/*
    OUTPUT ERROR NUMBERS

    This routine outputs all the error numbers to the file f.
*/

static void
output_number(FILE *f)
{
	int qn = 0;
	LIST(ENTRY) q = all_entries;
	char *pre = rig_comp_output;
	char *pre_db = rig_from_db;
	(void) fprintf(f, "#ifndef %sNO_INCLUDED\n", pre);
	(void) fprintf(f, "#define %sNO_INCLUDED\n\n\n", pre);
	(void) fprintf(f, "/* Error message macros */\n\n");
	while (!IS_NULL_list(q)) {
		ENTRY e = DEREF_entry(HEAD_list(q));
		string en = DEREF_string(entry_name(e));
		(void) fprintf(f, "#define %s%s %d\n", pre_db, en, qn);
		q = TAIL_list(q);
		qn++;
	}
	(void) fprintf(f, "\n#endif\n");
	return;
}


/*
    OUTPUT USAGES

    This routine output all the usages to the file f.
*/

static void
output_usage(FILE *f)
{
	char *pre = rig_comp_output;
	char *pre_comp = rig_from_comp;
	LIST(USAGE) p = all_usages;
	LIST(USAGE) q = all_usages_aux;
	LIST(USAGE) r = all_usages_alt;
	while (!IS_NULL_list(p)) {
		USAGE u = DEREF_name(HEAD_list(p));
		USAGE v = DEREF_name(HEAD_list(q));
		USAGE w = DEREF_name(HEAD_list(r));
		string s = DEREF_string(name_id(u));
		string t = DEREF_string(name_id(v));
		if (!EQ_name(v, w)) {
			(void) fprintf(f, "#ifndef %sALTERNATE\n", pre);
		}
		(void) fprintf(f, "{ \"%s\", %sVALUE_%s },\n", s, pre_comp, t);
		if (!EQ_name(v, w)) {
			t = DEREF_string(name_id(w));
			(void) fprintf(f, "#else\n");
			(void) fprintf(f, "{ \"%s\", %sVALUE_%s },\n", s, pre_comp,
				  t);
			(void) fprintf(f, "#endif\n");
		}
		r = TAIL_list(r);
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return;
}


/*
    OUTPUT ALL INFORMATION

    This routine outputs all the information gained into the file nm using
    the action indicated by act.  If nm is the null string then the standard
    output is used.
*/

void
output_all(char *nm, int act)
{
	/* Open output file */
	FILE *f;
	if (nm == NULL || !strcmp(nm, "-")) {
		f = stdout;
		nm = NULL;
	} else {
		f = fopen(nm, "w");
		if (f == NULL) {
			error(ERROR_SERIOUS, "Can't open output file, '%s'",
			      nm);
			return;
		}
	}

	/* Print header comment */
	if (first_comment) {
		(void) fprintf(f, "%s\n\n", first_comment);
	}
	(void) fprintf ( f, "/* AUTOMATICALLY GENERATED BY %s FROM %s */\n\n\n",
		    progname, db_name);

	/* Print appropriate information */
	switch (act) {
	case 0:
		output_decl(f);
		break;
	case 1:
		output_defn(f);
		break;
	case 2:
		output_number(f);
		break;
	case 3:
		output_usage(f);
		break;
	}

	/* Close output file */
	if (nm != NULL) {
		(void) fclose(f);
	}
	return;
}
