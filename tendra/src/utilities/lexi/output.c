/*
 * Copyright (c) 2002, 2003, The Tendra Project <http://www.tendra.org/>
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
 *  		 Crown Copyright (c) 1997
 *  
 *  This TenDRA(r) Computer Program is subject to Copyright
 *  owned by the United Kingdom Secretary of State for Defence
 *  acting through the Defence Evaluation and Research Agency
 *  (DERA).  It is made available to Recipients with a
 *  royalty-free licence for its use, reproduction, transfer
 *  to other parties and amendment for any purpose not excluding
 *  product development provided that any such use et cetera
 *  shall be deemed to be acceptance of the following conditions:-
 *  
 *      (1) Its Recipients shall ensure that this Notice is
 *      reproduced upon any copies or amended versions of it;
 *  
 *      (2) Any amended version of it shall be clearly marked to
 *      show both the nature of and the organisation responsible
 *      for the relevant amendment or amendments;
 *  
 *      (3) Its onward transfer from a recipient to another
 *      party shall be deemed to be that party's acceptance of
 *      these conditions;
 *  
 *      (4) DERA gives no warranty or assurance as to its
 *      quality or suitability for any purpose and DERA accepts
 *      no liability whatsoever in relation to any use to which
 *      it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "char.h"
#include "error.h"
#include "lex.h"
#include "output.h"


/*
 *    OUTPUT FILE
 *
 *    This variable gives the main output file.  out is used within this file
 *    as a shorthand for lex_output.
 */

FILE *lex_output;
#define out lex_output


/*
 *    OUTPUT INDENTATION
 *
 *    This routine outputs an indentation of d.
 */

static void
output_indent(int d)
{
    int n = 4 * d;
    for (; n >= 8 ; n -= 8) fputc_v ('\t', out);
    for (; n ; n--) fputc_v (' ', out);
    return;
}


/*
 *    FIND A CHARACTER LITERAL
 *
 *    This routine finds the character literal corresponding to c.
 */

static char*
char_lit(letter c)
{
    static char buff [10];
    switch (c) {
	case '\n':
		return ("'\\n'");
	case '\r':
		return ("'\\r'");
	case '\t':
		return ("'\\t'");
	case '\v':
		return ("'\\v'");
	case '\f':
		return ("'\\f'");
	case '\\':
		return ("'\\\\'");
	case '\'':
		return ("'\\''");
    }
    if (c == EOF_LETTER) return ("LEX_EOF");
    if (c > 127) return ("'?'");
    sprintf_v (buff, "'%c'", (char) c);
    return (buff);
}


/*
 *    OUTPUT OPTIONS
 *
 *    The flag in_pre_pass is used to indicate the preliminary pass to
 *    output_pass.  read_name gives the name of the character reading
 *    function used in the output routines.
 */

static int in_pre_pass = 0;
static char *read_name = "read_char";


/*
 *    OUTPUT PASS INFORMATION
 *
 *    This routine outputs code for the lexical pass indicated by p.  n
 *    gives the depth of recursion and d gives the indentation.
 */

static int
output_pass(character *p, int n, int d)
{
    character *q;
    int cases = 0;
    int classes = 0;
    char *ret = NULL;
    char *args = NULL;
    char *cond = NULL;
	
    /* First pass */
    for (q = p->next ; q != NULL ; q = q->opt) {
		letter c = q->ch;
		if (c == LAST_LETTER) {
			ret = q->defn;
			args = q->args;
			cond = q->cond;
		} else if (c <= SIMPLE_LETTER) {
			cases++;
		} else {
			classes++;
		}
    }
	
    /* Deal with cases */
    if (cases || classes) {
		int w1 = (n == 0 && !in_pre_pass);
		int w2 = (n == 0 && in_pre_pass);
		if (classes || w1) {
			output_indent (d);
			fprintf_v (out, "lookup_type t%d ;\n", n);
		}
		output_indent (d);
		fprintf_v (out, "int c%d = %s () ;\n", n, read_name);
		if (w1) {
			output_indent (d);
			fputs_v ("t0 = lookup_char (c0) ;\n", out);
			output_indent (d);
			fputs_v ("if (is_white (t0)) goto start ;\n", out);
		}
		if (w2) {
			output_indent (d);
			fputs_v ("restart : {\n", out);
			d++;
		}
		
		if (cases > 4) {
			/* Small number of cases */
			output_indent (d);
			fprintf_v (out, "switch (c%d) {\n", n);
			for (q = p->next ; q != NULL ; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c <= SIMPLE_LETTER) {
					output_indent (d + 1);
					fprintf_v (out, "case %s : {\n", char_lit (c));
					if (output_pass (q, n + 1, d + 2) == 0) {
						output_indent (d + 2);
						fputs_v ("break ;\n", out);
					}
					output_indent (d + 1);
					fputs_v ("}\n", out);
				}
			}
			output_indent (d);
			fputs_v ("}\n", out);
		} else {
			/* Large number of cases */
			int started = 0;
			for (q = p->next ; q != NULL ; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c <= SIMPLE_LETTER) {
					output_indent (d);
					if (started) fputs_v ("} else ", out);
					fprintf_v (out, "if (c%d == %s) {\n",
							   n, char_lit (c));
					IGNORE output_pass (q, n + 1, d + 1);
					started = 1;
				}
			}
			if (started) {
				output_indent (d);
				fputs_v ("}\n", out);
			}
		}
		
		if (classes) {
			/* Complex cases */
			int started = 0;
			if (!w1) {
				output_indent (d);
				fprintf_v (out, "t%d = lookup_char (c%d) ;\n", n, n);
			}
			for (q = p->next ; q != NULL ; q = q->opt) {
				letter c = q->ch;
				if (c != LAST_LETTER && c > SIMPLE_LETTER) {
					char *gnm;
					if (c == WHITE_LETTER) {
						gnm = "white";
					} else {
						int g = (int) (c - GROUP_LETTER);
						gnm = groups [g].name;
					}
					output_indent (d);
					if (started) fputs_v ("} else ", out);
					fprintf_v (out, "if (is_%s (t%d)) {\n", gnm, n);
					IGNORE output_pass (q, n + 1, d + 1);
					started = 1;
				}
			}
			output_indent (d);
			fputs_v ("}\n", out);
		}
		if (w2) {
			d--;
			output_indent (d);
			fputs_v ("}\n", out);
		}
		if (n) {
			output_indent (d);
			fprintf_v (out, "unread_char (c%d) ;\n", n);
		}
    }
	
    /* Deal with return */
    if (ret) {
		if (in_pre_pass) {
			int m = *ret;
			if (m) {
				char *str;
				if (m == '\\') {
					str = char_lit (find_escape (ret [1]));
					m = ret [2];
				} else {
					str = char_lit ((letter) m);
					m = ret [1];
				}
				if (m) {
					error (ERROR_SERIOUS, "Bad mapping string, '%s'", ret);
				}
				if (cond) {
					output_indent (d);
					fprintf_v (out, "if (%s) {\n", cond);
					output_indent (d + 1);
					fprintf_v (out, "c0 = %s ;\n", str);
					output_indent (d + 1);
					fputs_v ("goto restart ;\n", out);
					output_indent (d);
					fputs_v ("}\n", out);
				} else {
					output_indent (d);
					fprintf_v (out, "c0 = %s ;\n", str);
					output_indent (d);
					fputs_v ("goto restart ;\n", out);
				}
			} else {
				output_indent (d);
				if (cond) fprintf_v (out, "if (%s) ", cond);
				fputs_v ("goto start ;\n", out);
			}
		} else {
			output_indent (d);
			if (cond) fprintf_v (out, "if (%s) ", cond);
			fprintf_v (out, "return (%s", ret);
			if (args) {
				int i;
				fputs_v (" (c0", out);
				for (i = 1 ; i < n ; i++) fprintf_v (out, ", c%d", i);
				fputs_v (")", out);
			}
			fputs_v (") ;\n", out);
		}
    }
    return ((ret && (cond == NULL)) ? 1 : 0);
}


/*
 *    OUTPUT INITIAL COMMENT
 *
 *    This routine outputs a comment stating that the file is automatically
 *    generated.
 */

static void
output_comment()
{
    if (first_comment) {
		/* Print copyright comment, if present */
		fprintf_v (out, "%s\n\n", first_comment);
    }
    fputs_v ("/*\n    AUTOMATICALLY GENERATED", out);
    fprintf_v (out, " BY %s VERSION %s", progname, progvers);
    fputs_v ("\n*/\n\n\n", out);
    return;
}


/*
 *    MAIN OUTPUT ROUTINE
 *
 *    This routine is the entry point for the main output routine.
 */

static void
output_main(unsigned opts)
{
    int c, n;
    int no;
	
    CONST char *hex;
    CONST char *type;
	
    /* Character look-up table */
    if (no_groups >= 16) {
		type = "unsigned long";
		hex = "0x%08lxUL";
		no = 2;
    } else if (no_groups >= 8) {
		type = "unsigned short";
		hex = "ox%04lx";
		no = 4;
    } else {
		type = "unsigned char";
		hex = "0x%02lx";
		no = 8;
    }
    if (opts & OUTPUT_MACROS) {
		fputs_v ("/* LOOKUP TABLE */\n\n", out);
		fprintf_v (out, "typedef %s lookup_type ;\n", type);
		if (opts & OUTPUT_TABLE) {
			fprintf_v (out, "\nstatic ");
		} else {
			fprintf_v (out, "extern lookup_type lookup_tab [] ;\n\n");
		}
    }
    if (opts & OUTPUT_TABLE) {
		fprintf_v (out, "lookup_type lookup_tab [257] = {\n");
		for (c = 0 ; c <= 256 ; c++) {
			unsigned long m = 0;
			letter a = (c == 256 ? EOF_LETTER : (letter) c);
			if (in_group (white_space, a)) m = 1;
			for (n = 0 ; n < no_groups ; n++) {
				if (in_group (groups [n].defn, a)) {
            	    m |= (unsigned long) (1 << (n + 1));
				}
			}
			if ((c % no) == 0) fputs_v ("    ", out);
			fprintf_v (out, hex, m);
			if (c != 256) {
				if ((c % no) == no - 1) {
					fputs_v (",\n", out);
				} else {
					fputs_v (", ", out);
				}
			}
		}
		fputs_v ("\n} ;\n\n", out);
    }
	
    /* Macros for accessing table */
    if (opts & OUTPUT_MACROS) {
		fputs_v ("#ifndef LEX_EOF\n", out);
		fputs_v ("#define LEX_EOF\t\t\t256\n", out);
		fputs_v ("#endif\n\n", out);
		fputs_v ("#define lookup_char(C)\t", out);
		fputs_v ("(lookup_tab [ (C) ])\n", out);
		for (n = 0 ; n <= no_groups ; n++) {
			CONST char *gnm = "white";
			unsigned long m = (unsigned long) (1 << n);
			if (n > 0) gnm = groups [ n - 1].name;
			fprintf_v (out, "#define is_%s(T)\t", gnm);
			if ((int) strlen (gnm) < 8) fputc_v ('\t', out);
			fputs_v ("((T) & ", out);
			fprintf_v (out, hex, m);
			fputs_v (")\n", out);
		}
		fputs_v ("\n", out);
		fputs_v ("#ifndef PROTO_Z\n", out);
		fputs_v ("#ifdef __STDC__\n", out);
		fputs_v ("#define PROTO_Z()\t\t(void)\n", out);
		fputs_v ("#else\n", out);
		fputs_v ("#define PROTO_Z()\t\t()\n", out);
		fputs_v ("#endif\n", out);
		fputs_v ("#endif\n\n\n", out);
    }
	
    /* Lexical pre-pass */
    if (opts & OUTPUT_FUNCTIONS) {
		if (pre_pass->next) {
			in_pre_pass = 1;
			fputs_v ("/* PRE-PASS ANALYSER */\n\n", out);
			fputs_v ("static int read_char_aux PROTO_Z ()\n", out);
			fputs_v ("{\n", out);
			fputs_v ("    start : {\n", out);
			IGNORE output_pass (pre_pass, 0, 2);
			fputs_v ("\treturn (c0) ;\n", out);
			fputs_v ("    }\n", out);
			fputs_v ("}\n\n\n", out);
			read_name = "read_char_aux";
		}
    }
	
    /* Main pass */
    if (opts & OUTPUT_FUNCTIONS) {
		in_pre_pass = 0;
		fputs_v ("/* MAIN PASS ANALYSER */\n\n", out);
		fputs_v ("int read_token PROTO_Z ()\n", out);
		fputs_v ("{\n", out);
		fputs_v ("    start : {\n", out);
		IGNORE output_pass (main_pass, 0, 2);
		fputs_v ("\treturn (unknown_token (c0)) ;\n", out);
		fputs_v ("    }\n", out);
		fputs_v ("}\n", out);
    }
    return;
}


/*
 *    OUTPUT CODE FOR A SINGLE KEYWORD
 *
 *    This routine outputs code for the keyword p.
 */

static void
output_word(keyword *p)
{
    fprintf_v (out, "MAKE_KEYWORD (\"%s\", %s", p->name, p->defn);
    if (p->args) fputs_v (" ()", out);
    fputs_v (") ;\n", out);
    p->done = 1;
    return;
}


/*
 *    KEYWORD OUTPUT ROUTINE
 *
 *    This routine outputs code to generate all keywords.
 */

static void
output_keyword()
{
    keyword *p, *q;
    fputs_v ("/* KEYWORDS */\n\n", out);
    for (p = keywords ; p != NULL ; p = p->next) {
		if (p->done == 0) {
			char *cond = p->cond;
			if (cond) {
				fprintf_v (out, "if (%s) {\n    ", cond);
				output_word (p);
				for (q = p->next ; q != NULL ; q = q->next) {
					if (q->cond && streq (q->cond, cond)) {
						fputs_v ("    ", out);
						output_word (q);
					}
				}
				fputs_v ("}\n", out);
			} else {
				output_word (p);
				for (q = p->next ; q != NULL ; q = q->next) {
					if (q->cond == NULL) output_word (q);
				}
			}
		}
    }
    return;
}


/*
 *    MAIN OUTPUT ROUTINE
 *
 *    This routine is the entry point for the main output routine.
 */

void
output_all(unsigned opts)
{
    output_comment ();
    if (opts & OUTPUT_KEYWORDS) {
		output_keyword ();
    } else {
		output_main (opts);
    }
    return;
}
