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


#include "config.h"
#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "check.h"
#include "high.h"
#include "names.h"
#include "node.h"
#include "read.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
 *    ARE MULTIBYTE STRINGS ALLOWED
 *
 *    This flag is true to indicate that multibyte strings (other than
 *    8 bits per character) are allowed.
 */

boolean allow_multibyte = 1;


/*
 *    READ A TOKEN APPLICATION
 *
 *    A token application of sort s is read and appended to p.
 */

void
read_token(node *p, sortname s)
{
    char *ra;
    char *wtemp;
    sortname rs;
    construct *v;
    tok_info *info;
    boolean in_brackets = 0;
	
    /* Check bracket (1) */
    read_word ();
    if (!func_input && word_type == INPUT_OPEN) {
		in_brackets = 1;
		read_word ();
    }
	
    /* Read token identifier */
    if (word_type != INPUT_WORD) {
		input_error ("Token identifier expected");
		return;
    }
	
    /* Check bracket (2) */
    if (func_input) {
		wtemp = temp_copy (word);
		read_word ();
		if (word_type == INPUT_OPEN) {
			in_brackets = 1;
		} else {
			looked_ahead = 1;
		}
    } else {
		wtemp = word;
    }
	
    /* Look up token */
    v = search_var_hash (wtemp, SORT_token);
    if (v == null) {
		input_error ("Token %s not declared", wtemp);
		return;
    }
    info = get_tok_info (v);
    rs = info->res;
    ra = info->args;
    if (rs == SORT_unknown) {
		input_error ("Token %s not declared", wtemp);
		return;
    }
    if (is_high (rs)) {
		high_sort *h = high_sorts + high_no (rs);
		rs = h->res;
		ra = find_decode_string (h);
    }
    if (rs != s) {
		input_error ("Token %s returns %s, not %s", wtemp,
					 sort_name (rs), sort_name (s));
		return;
    }
    adjust_token (v);
	
    /* Decode arguments */
    p->son = new_node ();
    p->son->cons = v;
    if (ra) p->son->son = read_node (ra);
	
    /* Check end */
    if (in_brackets) {
		read_word ();
		if (word_type != INPUT_CLOSE) {
			is_fatal = 0;
			input_error ("End of token %s construct expected", v->name);
			looked_ahead = 1;
		}
    } else {
		if (p->son->son) {
			is_fatal = 0;
			input_error ("Token %s construct should be in brackets",
						 v->name);
		}
    }
    if (do_check) IGNORE set_token_args (info->pars, p->son->son, 0);
    return;
}


/*
 *    READ A TOKEN NAME
 *
 *    This routine reads a token name (as opposed to a token application).
 *    The token should have sort s.
 */

static node
*read_token_name(sortname s)
{
    node *p;
    boolean ok = 0;
    construct *v;
    high_sort *h;
    tok_info *info;
	
    /* Read token identifier */
    read_word ();
    if (word_type != INPUT_WORD) {
		input_error ("Token identifier expected");
		return (null);
    }
	
    /* Look up token */
    v = search_var_hash (word, SORT_token);
    if (v == null) {
		input_error ("Token %s not declared", word);
		return (null);
    }
    info = get_tok_info (v);
	
    /* Check consistency */
    h = high_sorts + high_no (s);
    if (h->res == info->res) {
		if (info->args == null) {
			if (h->no_args == 0) ok = 1;
		} else if (h->no_args) {
			char *ha = find_decode_string (h);
			if (streq (info->args, ha)) ok = 1;
		}
    } else if (h->id == info->res) {
		if (info->args == null) ok = 1;
    }
    if (!ok) {
		input_error ("Token %s has incorrect sort", v->name);
    }
	
    /* Return the construct */
    p = new_node ();
    p->cons = v;
    if (!text_output) {
		p->son = new_node ();
		p->son->cons = &token_cons;
    }
    return (p);
}


/*
 *    FIND BASIC CONSTRUCT FOR A VARIABLE SORT
 *
 *    This routine returns the construct for turning an identifier into
 *    an object of sort s.
 */

static long
make_obj(sortname s)
{
    long mk = -1;
    switch (s) {
	case SORT_al_tag : mk = ENC_make_al_tag ; break;
	case SORT_label : mk = ENC_make_label ; break;
	case SORT_tag : mk = ENC_make_tag ; break;
    }
    return (mk);
}


/*
 *    IS A VARIABLE SORT A USE OR AN INTRODUCTION?
 *
 *    This flag is true to indicate that the tag (or whatever) being read
 *    is a new one being introduced rather than an old one being used.
 *    The flag intro_tag_var is set to indicate that any tag so introduced
 *    is a variable.  The flag intro_visible is set to true whenever the
 *    visible access specifier is read.
 */

static boolean intro_var = 0;
static boolean intro_tag_var = 0;
boolean intro_visible = 0;


/*
 *    SEARCH FOR A VARIABLE SORT
 *
 *    This routine initializes, if appropriate, and returns the construct
 *    corresponding to the object named nm of sort s.
 */

static construct
*search_var_sort(char *nm, sortname s)
{
    construct *v = search_var_hash (nm, s);
    if (intro_var) {
		if (v == null) {
			v = make_construct (s);
			v->name = string_copy_aux (nm);
			/* Don't add to hash table yet */
			if (s == SORT_tag) {
				tag_info *info = get_tag_info (v);
				info->var = intro_tag_var;
				info->vis = intro_visible;
				intro_visible = 0;
			}
		} else {
			input_error ("%s %s already in scope", sort_name (s), nm);
		}
    } else {
		if (v == null) {
			if (!dont_check) {
				is_fatal = 0;
				input_error ("%s %s not in scope", sort_name (s), nm);
			}
			v = make_construct (s);
			v->name = string_copy_aux (nm);
			IGNORE add_to_var_hash (v, s);
		}
    }
    return (v);
}


/*
 *    READ A VARIABLE SORT
 *
 *    An identifier representing a construct of sort s is read.
 */

node
*read_var_sort(sortname s)
{
    node *p;
    construct *v;
    read_word ();
    if (word_type != INPUT_WORD) {
		input_error ("%s identifier expected", sort_name (s));
    }
    v = search_var_sort (word, s);
    p = new_node ();
    p->cons = v;
    return (p);
}


/*
 *    READ A SEQUENCE EXPRESSION
 *
 *    A sequence expression is read.  This is tricky because it is a list
 *    of exps followed by an exp, which may be read as a list of exps.
 */

void
read_seq_node(node *p)
{
    node *q = read_node ("*[x]?[x]");
    if (q->bro->son) {
		node *r = q->bro->son;
		q->bro = r;
		p->son = q;
		return;
    }
    q->bro = null;
    if (q->cons->encoding == 0) {
		is_fatal = 0;
		input_error ("exp expected");
		return;
    }
    (q->cons->encoding)--;
    p->son = q;
    q = q->son;
    if (q->bro == null) {
		p->son->son = null;
		p->son->bro = q;
    } else {
		while (q->bro->bro) q = q->bro;
		p->son->bro = q->bro;
		q->bro = null;
    }
    return;
}


/*
 *    READ SORT INDICATED BY A SINGLE DECODE LETTER
 *
 *    An object with sort given by the decode letter str is read.  If the next
 *    object is not of this sort then either an error is flagged (if strict
 *    is true) or null is returned.
 */

static node
*read_node_aux(char *str, int strict)
{
    sortname s;
    char *wtemp;
    node *p, *ps;
    construct *cons;
    read_func fn = null;
    boolean in_brackets = 0;
	
    /* Find the corresponding sort name */
    if (str [1] == '&') {
		/* Introduced variable */
		intro_var = 1;
		intro_tag_var = 1;
    } else if (str [1] == '^') {
		/* Introduced identity */
		intro_var = 1;
		intro_tag_var = 0;
    }
    switch (str [0]) {
	case 'i' : {
	    s = SORT_tdfint;
	    break;
	}
	case 'j' : {
	    s = SORT_tdfbool;
	    break;
	}
	case '$' : {
	    s = SORT_tdfstring;
	    break;
	}
	case 'F' : {
	    s = SORT_unknown;
	    break;
	}
	default : {
	    s = find_sort (str [0]);
	    fn = sort_read [s];
	    break;
	}
    }
	
    /* Read the next word */
    read_word ();
	
    /* Check for blanks */
    if (word_type == INPUT_BLANK && !strict) {
		word_type = INPUT_BLANK_FIRST;
		return (null);
    }
	
    /* Check for bars */
    if (word_type == INPUT_BAR && !strict) {
		word_type = INPUT_BAR_FIRST;
		return (null);
    }
	
    /* Deal with strings */
    if (s == SORT_tdfstring) {
		if (word_type == INPUT_STRING) {
			p = new_node ();
			p->cons = new_construct ();
			p->cons->sortnum = SORT_tdfstring;
			p->cons->encoding = word_length;
			p->cons->name = string_copy (word, (int) word_length);
			p->cons->next = null;
			return (p);
		} else {
			boolean is_multibyte = 0;
			if (func_input) {
				if (word_type == INPUT_WORD) {
					if (streq (word, MAKE_STRING)) {
						read_word ();
						if (word_type == INPUT_OPEN) is_multibyte = 1;
					}
				}
			} else {
				if (word_type == INPUT_OPEN) {
					read_word ();
					if (word_type == INPUT_WORD) {
						if (streq (word, MAKE_STRING)) is_multibyte = 1;
					}
				}
			}
			if (is_multibyte) {
				if (!allow_multibyte) {
					input_error ("Multibyte strings not allowed here");
				}
				p = new_node ();
				p->cons = &string_cons;
				p->son = read_node ("i*[i]");
				read_word ();
				if (word_type != INPUT_CLOSE) {
					input_error ("End of multibyte string expected");
				}
				return (p);
			}
		}
		if (strict) input_error ("String expected");
		return (null);
    }
	
    /* Deal with numbers */
    if (word_type == INPUT_NUMBER) {
		boolean negate = 0;
		if (*word == '-') {
			word++;
			negate = 1;
		}
		p = new_node ();
		p->cons = new_construct ();
		if (fits_ulong (word, 1)) {
			p->cons->sortnum = SORT_small_tdfint;
			p->cons->encoding = (long) octal_to_ulong (word);
		} else {
			p->cons->sortnum = SORT_tdfint;
			p->cons->name = string_copy_aux (word);
		}
		
		switch (s) {
	    case SORT_tdfint : {
			if (negate) {
				is_fatal = 0;
				input_error ("Negative nat");
			}
			return (p);
	    }
	    case SORT_tdfbool : {
			node *q = new_node ();
			q->cons = (negate ? &true_cons : &false_cons);
			q->bro = p;
			return (q);
	    }
	    case SORT_nat : {
			node *q = new_node ();
			if (negate) {
				is_fatal = 0;
				input_error ("Negative nat");
			}
			q->cons = cons_no (SORT_nat, ENC_make_nat);
			q->son = p;
			return (q);
	    }
	    case SORT_signed_nat : {
			node *q = new_node ();
			q->cons = cons_no (SORT_signed_nat, ENC_make_signed_nat);
			q->son = new_node ();
			q->son->cons = (negate ? &true_cons : &false_cons);
			q->son->bro = p;
			return (q);
	    }
	    default : {
			if (strict) input_error ("%s expected", sort_name (s));
			return (null);
	    }
		}
    }
	
    /* Deal with strings */
    if (word_type == INPUT_STRING) {
		if (s == SORT_string) {
			node *q;
			p = new_node ();
			p->cons = new_construct ();
			p->cons->sortnum = SORT_tdfstring;
			p->cons->encoding = word_length;
			p->cons->name = string_copy (word, (int) word_length);
			p->cons->next = null;
			q = new_node ();
			q->cons = cons_no (SORT_string, ENC_make_string);
			q->son = p;
			return (q);
		}
    }
	
    /* That was the last chance for numbers */
    if (fn == null) {
		if (strict) input_error ("Number expected");
		return (null);
    }
	
    /* Check for brackets (1) */
    if (!func_input && word_type == INPUT_OPEN) {
		in_brackets = 1;
		read_word ();
    }
	
    /* The next word should be the identifier */
    if (word_type != INPUT_WORD) {
		if (strict) input_error ("%s expected", sort_name (s));
		return (null);
    }
	
    /* Check for brackets (2) */
    if (func_input) {
		wtemp = temp_copy (word);
		read_word ();
		if (word_type == INPUT_OPEN) {
			in_brackets = 1;
		} else {
			looked_ahead = 1;
		}
    } else {
		wtemp = word;
    }
	
    if (s == SORT_string && streq (word, MAKE_STRING)) {
		node *q;
		p = new_node ();
		p->cons = &string_cons;
		p->son = read_node ("i*[i]");
		read_word ();
		if (word_type != INPUT_CLOSE) {
			input_error ("End of multibyte string expected");
		}
		q = new_node ();
		q->cons = cons_no (SORT_string, ENC_make_string);
		q->son = p;
		return (q);
    }
	
    /* Look up construct */
    cons = search_cons_hash (wtemp, s);
    if (cons) {
		p = fn (cons->encoding);
		ps = p->son;
    } else {
		boolean do_check_tag = 0;
		if (!in_brackets && (s == SORT_al_tag || s == SORT_label ||
							 s == SORT_tag)) {
			do_check_tag = 1;
		}
		/* Look up token */
		cons = search_var_hash (wtemp, SORT_token);
		if (cons) {
			tok_info *info = get_tok_info (cons);
			sortname rs = info->res;
			char *ra = info->args;
			if (rs == SORT_unknown) {
				if (do_check_tag) goto check_lab;
				input_error ("Token %s not declared", wtemp);
			}
			if (is_high (rs)) {
				high_sort *h = high_sorts + high_no (rs);
				rs = h->res;
				ra = find_decode_string (h);
			}
			if (rs != s) {
				if (do_check_tag) goto check_lab;
				if (!strict) return (null);
				input_error ("Token %s returns %s, not %s", wtemp,
							 sort_name (rs), sort_name (s));
			}
			adjust_token (cons);
			p = new_node ();
			p->cons = cons_no (s, sort_tokens [s]);
			p->son = new_node ();
			p->son->cons = cons;
			if (ra) p->son->son = read_node (ra);
			ps = p->son->son;
			if (do_check) {
				IGNORE set_token_args (info->pars, p->son->son, 0);
				if (s == SORT_exp) check_exp (p);
			}
		} else {
			/* Look up label, tag etc */
			if (do_check_tag) {
				check_lab : cons = search_var_sort (wtemp, s);
			}
			if (cons) {
				long mk = make_obj (s);
				p = new_node ();
				p->cons = cons_no (s, mk);
				p->son = new_node ();
				p->son->cons = cons;
				ps = null;
			} else {
				if (strict) {
					input_error ("Illegal %s, %s", sort_name (s), wtemp);
				}
				return (null);
			}
		}
    }
	
    /* Check end of construct */
    if (in_brackets) {
		read_word ();
		if (word_type != INPUT_CLOSE) {
			is_fatal = 0;
			input_error ("End of %s construct expected", cons->name);
			looked_ahead = 1;
		}
    } else {
		if (ps) {
			is_fatal = 0;
			input_error ("%s construct should be in brackets", cons->name);
		}
    }
    return (p);
}


/*
 *    BRING VARIABLES INTO AND OUT OF SCOPE
 *
 *    The tags, labels etc introduced in p are brought into (if end is
 *    false) or out of (if end is true) scope.  This only works because
 *    all the constructs which introduce these variables are of a fairly
 *    simple form.
 */

static void
adjust_scope(node *p, int end)
{
    node *p0 = p;
    while (p) {
		construct *v = p->cons;
		sortname s = v->sortnum;
		switch (s) {
			
	    case SORT_repeat :
	    case SORT_option : {
			/* Scan repeated and optional arguments */
			if (p->son) adjust_scope (p->son, end);
			break;
	    }
			
	    case SORT_al_tag :
	    case SORT_label :
	    case SORT_tag : {
			/* Variable found - adjust scope */
			if (v->encoding == make_obj (s)) {
				construct *u = p->son->cons;
				if (end) {
					if (s == SORT_tag) {
						/* Visible tags aren't removed */
						tag_info *info = get_tag_info (u);
						if (info->vis) break;
					}
					remove_var_hash (u->name, s);
				} else {
					if (add_to_var_hash (u, s)) {
						input_error ("%s %s already in scope",
									 sort_name (s), u->name);
					}
					if (do_check && s == SORT_tag) {
						/* Fill in shape of tag */
						node *ts;
						node *p1 = p->bro;
						tag_info *info = get_tag_info (u);
						if (p1 && p1->cons->sortnum == SORT_exp) {
							/* identity and variable have "t&x" */
							ts = p1->shape;
						} else if (p0->cons->sortnum == SORT_shape) {
							/* make_proc etc have "S?[u]t&" */
							ts = copy_node (p0);
						} else {
							/* don't know about other constructs */
							ts = null;
						}
						/* Declaration = ?[u]?[X]S from 4.0 */
						info->dec = new_node ();
						info->dec->cons = &false_cons;
						info->dec->bro = new_node ();
						info->dec->bro->cons = &false_cons;
						info->dec->bro->bro = ts;
					}
				}
			}
			break;
	    }
		}
		p = p->bro;
    }
    return;
}


/*
 *    CHECK FOR COMMA OR CLOSE BRACKET
 *
 *    The next word should be a comma, which is stepped over, or a close
 *    bracket.
 */

static void
check_comma()
{
    read_word ();
    if (word_type == INPUT_COMMA) {
		read_word ();
		looked_ahead = 1;
		if (word_type == INPUT_CLOSE) {
			is_fatal = 0;
			input_error ("Badly placed comma");
		}
		return;
    }
    if (word_type != INPUT_CLOSE) {
		is_fatal = 0;
		input_error ("Comma or close bracket expected");
    }
    looked_ahead = 1;
    return;
}


/*
 *    READ SORTS GIVEN BY A STRING OF DECODE LETTERS
 *
 *    A node corresponding to the decode string str is read from the
 *    input file.
 */

node
*read_node(char *str)
{
    char c;
    position store;
    node *p, *q = null, *qe = null;
    while (c = *str, (c != 0 && c != ']')) {
		switch (c) {
			
	    case '{' : {
			/* Start of scope */
			adjust_scope (q, 0);
			p = null;
			break;
	    }
			
	    case '}' : {
			/* End of scope */
			adjust_scope (q, 1);
			p = null;
			break;
	    }
			
	    case '[' :
	    case '|' :
	    case '&' :
	    case '^' : {
			/* Ignore these cases */
			p = null;
			break;
	    }
			
	    case '*' :
	    case '!' : {
			/* Repeats */
			char cr;
			char *sr;
			long n = 0;
			int opt = 0;
			node *pe = null, *pr;
			str += 2;
			cr = *str;
			sr = str;
			if (cr == '?') {
				/* Allow for lists of options */
				opt = 1;
				str += 2;
				cr = *str;
				sr = skip_text (str);
			}
			if (cr == '*' || cr == '!') {
				input_error ("Sorry, lists of lists not implemented");
			} else if (cr == '?') {
				input_error ("Sorry, lists of options not implemented");
			}
			p = new_node ();
			p->cons = new_construct ();
			p->cons->sortnum = SORT_repeat;
			do {
				store_position (&store);
				pr = read_node_aux (sr, 0);
				if (pr || (opt && word_type == INPUT_BLANK_FIRST)) {
					if (func_input) check_comma ();
					if (opt) {
						/* Allow for optionals */
						node *pt = pr;
						if (pt && str [1] != ']') {
							pt->bro = read_node (str + 1);
						}
						pr = new_node ();
						pr->cons = &optional_cons;
						pr->son = pt;
					}
					if (sr [1] != ']') {
						pr->bro = read_node (sr + 1);
					}
					if (pe == null) {
						p->son = pr;
					} else {
						pe->bro = pr;
					}
					pe = pr;
					while (pe->bro) pe = pe->bro;
					n++;
				} else {
					if (word_type == INPUT_BAR_FIRST) {
						if (func_input) check_comma ();
					} else if (c == '!' && n == 0 &&
							   word_type == INPUT_BLANK_FIRST) {
						if (func_input) check_comma ();
					} else {
						set_position (&store);
					}
				}
			} while (pr);
			p->cons->encoding = n;
			if (opt) sr++;
			str = skip_text (sr);
			if (c == '!') {
				/* Optional repeats */
				node *pt = p;
				p = new_node ();
				p->cons = &optional_cons;
				if (n) p->son = pt;
			}
			break;
	    }
			
	    case '?' : {
			/* Optionals */
			node *po;
			char co;
			str += 2;
			co = *str;
			if (co == '*' || co == '!') {
				input_error ("Sorry, optional lists not implemented");
			} else if (co == '?') {
				input_error ("Sorry, optional options not implemented");
			}
			intro_visible = 0;
			store_position (&store);
			po = read_node_aux (str, 0);
			if (po) {
				if (func_input) check_comma ();
				if (str [1] != ']') {
					po->bro = read_node (str + 1);
				}
			} else {
				if (word_type == INPUT_BLANK_FIRST) {
					if (func_input) check_comma ();
				} else {
					set_position (&store);
				}
			}
			p = new_node ();
			p->cons = &optional_cons;
			p->son = po;
			str = skip_text (str);
			break;
	    }
			
	    case '@' : {
			/* Conditionals */
			str += 2;
			p = new_node ();
			p->cons = &bytestream_cons;
			p->son = read_node (str);
			str = skip_text (str);
			break;
	    }
			
	    case 'T' : {
			/* Tokens */
			sortname sn;
			str = find_sortname (str, &sn);
			p = read_token_name (sn);
			break;
	    }
			
	    default : {
			/* Simple sort */
			p = read_node_aux (str, 1);
			if (func_input) check_comma ();
			break;
	    }
		}
		if (p) {
			if (qe == null) {
				q = p;
			} else {
				qe->bro = p;
			}
			qe = p;
			while (qe->bro) qe = qe->bro;
			intro_var = 0;
		}
		str++;
    }
    return (q);
}
