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


#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "access.h"
#include "basetype.h"
#include "class.h"
#include "declare.h"
#include "file.h"
#include "function.h"
#include "initialise.h"
#include "macro.h"
#include "namespace.h"
#include "parse.h"
#include "predict.h"
#include "rewrite.h"
#include "statement.h"
#include "syntax.h"


/*
 *    COUNT OF NUMBER OF SKIPPED FUNCTIONS
 *
 *    This value is used to keep track of the number of functions skipped
 *    and subsequently compiled.
 */

static int functions_pending = 0;


/*
 *    SKIP A FUNCTION DEFINITION
 *
 *    This routine skips the function definition for the function id given by
 *    the current sequence of lexical tokens.  Note that last_lex_token is
 *    set to lex_func_Hop to indicate that a function definition has been
 *    skipped.
 */

void
skip_function(IDENTIFIER id)
{
    EXP e;
    LOCATION loc;
    int t = crt_lex_token;
    PPTOKEN *p = crt_token;
    PPTOKEN *q = p;
    int brackets = 0;
    int try_block = 0;
	
    /* Check for previous definition */
    if (!IS_NULL_id (id)) {
		PTR (LOCATION) ploc = id_loc (id);
		COPY_loc (ploc, decl_loc);
		e = DEREF_exp (id_function_etc_defn (id));
		if (!IS_NULL_exp (e)) {
			/* Function already defined */
			report (crt_loc, ERR_basic_odr_def_func (id, ploc));
		}
    }
	
    /* Skip definition */
    loc = crt_loc;
    if (t == lex_try) try_block = 1;
    for (;;) {
		if (t == lex_open_Hbrace_H1 || t == lex_open_Hbrace_H2) {
			/* Start of block */
			brackets++;
		} else if (t == lex_close_Hbrace_H1 || t == lex_close_Hbrace_H2) {
			/* End of block */
			brackets--;
			if (brackets <= 0) {
				q = crt_token;
				t = expand_preproc (EXPAND_AHEAD);
				if (t != lex_catch || !try_block) {
					/* End of function */
					break;
				}
			}
		} else if (t == lex_semicolon && brackets == 0) {
			/* Premature end of function */
			break;
		} else if (t == lex_eof) {
			/* Premature end of file */
			report (loc, ERR_class_mfct_eof (id));
			crt_lex_token = t;
			return;
		}
		q = crt_token;
		t = expand_preproc (EXPAND_AHEAD);
    }
    last_lex_token = lex_func_Hop;
    crt_lex_token = t;
    snip_tokens (p, q);
	
    /* Create the definition */
    MAKE_exp_uncompiled (type_void, loc, p, e);
    if (!IS_NULL_id (id)) {
		COPY_exp (id_function_etc_defn (id), e);
		functions_pending++;
    }
    return;
}


/*
 *    SKIP A DEFAULT ARGUMENT VALUE
 *
 *    This routine skips the default argument value for the function parameter
 *    id given by the current sequence of lexical tokens.  It returns an
 *    expression giving the skipped value which is associated with id by
 *    init_param.
 */

EXP
skip_default_arg(IDENTIFIER id)
{
    EXP e;
    LOCATION loc;
    int brackets = 0;
    int t = crt_lex_token;
    PPTOKEN *p = crt_token;
    PPTOKEN *q = p;
	
    /* Skip definition */
    loc = crt_loc;
    for (;;) {
		if (t == lex_open_Hround || t == lex_open_Htemplate) {
			brackets++;
		} else if (t == lex_close_Hround || t == lex_close_Htemplate) {
			if (brackets == 0) break;
			brackets--;
		} else if (t == lex_comma) {
			if (brackets == 0) break;
		} else if (t == lex_eof) {
			/* Premature end of file */
			report (loc, ERR_class_mfct_eof (id));
			crt_lex_token = t;
			return (NULL_exp);
		}
		q = crt_token;
		t = expand_preproc (EXPAND_AHEAD);
    }
    crt_lex_token = t;
    snip_tokens (p, q);
	
    /* Create the definition */
    MAKE_exp_uncompiled (type_error, loc, p, e);
    functions_pending++;
    return (e);
}


/*
 *    BRING A SET OF TEMPLATE ARGUMENTS INTO SCOPE
 *
 *    When rescanning a template member function it is necessary to bring
 *    the template parameters back into scope.  This routine performs this
 *    operation for the template type t.  It returns the non-template
 *    component of t.
 */

TYPE
begin_templ_scope(TYPE t)
{
    if (!IS_NULL_type (t) && IS_type_templ (t)) {
		TYPE s = DEREF_type (type_templ_defn (t));
		TOKEN sort = DEREF_tok (type_templ_sort (t));
		NAMESPACE ns = DEREF_nspace (tok_templ_pars (sort));
		if (!IS_NULL_nspace (ns)) {
			record_location++;
			in_template_decl++;
			add_namespace (ns);
		}
		t = begin_templ_scope (s);
    }
    return (t);
}


/*
 *    TAKE A SET OF TEMPLATE ARGUMENTS OUT OF SCOPE
 *
 *    This routine removes any template parameters brought into scope by
 *    begin_templ_scope.
 */

void
end_templ_scope(TYPE t)
{
    if (!IS_NULL_type (t) && IS_type_templ (t)) {
		TYPE s = DEREF_type (type_templ_defn (t));
		TOKEN sort = DEREF_tok (type_templ_sort (t));
		NAMESPACE ns = DEREF_nspace (tok_templ_pars (sort));
		end_templ_scope (s);
		if (!IS_NULL_nspace (ns)) {
			remove_namespace ();
			in_template_decl--;
			record_location--;
		}
    }
    return;
}


/*
 *    COMPILE A FUNCTION DEFINITION
 *
 *    This routine compiles any previously skipped definition for the
 *    function id.
 */

static void
rescan_function(IDENTIFIER id)
{
    EXP e = DEREF_exp (id_function_etc_defn (id));
    if (!IS_NULL_exp (e) && IS_exp_uncompiled (e)) {
		PPTOKEN *p;
		PARSE_STATE s;
		TYPE fn = DEREF_type (id_function_etc_type (id));
		
		/* Mark function as inline */
		DECL_SPEC ds = DEREF_dspec (id_storage (id));
		ds |= dspec_inline;
		COPY_dspec (id_storage (id), ds);
		
		/* Save current compiler state */
		save_state (&s, 1);
		
		/* Set parser to stored definition */
		DEREF_loc (exp_uncompiled_start (e), crt_loc);
		crt_line_changed = 1;
		crt_file_changed = 1;
		p = DEREF_pptok (exp_uncompiled_defn (e));
		init_parser (p);
		
		/* Start function definition */
		in_class_defn = 0;
		in_function_defn++;
		really_in_function_defn++;
		COPY_exp (id_function_etc_defn (id), NULL_exp);
		DEREF_loc (id_loc (id), decl_loc);
		IGNORE begin_templ_scope (fn);
		begin_function (id);
		
		/* Parse the stored function definition */
		ADVANCE_LEXER;
		parse_func (&e);
		if (crt_lex_token != lex_eof && !have_syntax_error) {
			ERROR err = ERR_lex_parse (crt_token);
			report (crt_loc, err);
			unreached_code = 1;
		}
		
		/* End the function definition */
		IGNORE end_function (id, e);
		end_templ_scope (fn);
		
		/* Reset the parser */
		restore_state (&s);
		p = restore_parser ();
		free_tok_list (p);
		functions_pending--;
    }
    return;
}


/*
 *    COMPILE A DEFAULT ARGUMENT VALUE
 *
 *    This routine compiles any previously skipped default argument value
 *    for the parameter id.
 */

void
rescan_param(IDENTIFIER id, int rescan)
{
    EXP e = DEREF_exp (id_parameter_init (id));
    if (!IS_NULL_exp (e) && IS_exp_uncompiled (e)) {
		PPTOKEN *p;
		PARSE_STATE s;
		TYPE fn = NULL_type;
		NAMESPACE ns = DEREF_nspace (id_parent (id));
		IDENTIFIER pid = DEREF_id (nspace_name (ns));
		if (!IS_NULL_id (pid) && IS_id_function_etc (pid)) {
			fn = DEREF_type (id_function_etc_type (pid));
		} else {
			CLASS_TYPE ct = crt_class;
			if (!IS_NULL_ctype (ct)) {
				pid = DEREF_id (ctype_name (ct));
			} else {
				pid = NULL_id;
			}
		}
		
		/* Save current compiler state */
		save_state (&s, 1);
		
		/* Set parser to stored definition */
		DEREF_loc (exp_uncompiled_start (e), crt_loc);
		crt_line_changed = 1;
		crt_file_changed = 1;
		p = DEREF_pptok (exp_uncompiled_defn (e));
		init_parser (p);
		
		/* Start dafault argument value */
		in_class_defn = 0;
		COPY_exp (id_parameter_init (id), NULL_exp);
		if (rescan) {
			IGNORE begin_templ_scope (fn);
			push_namespace (ns);
		}
		
		/* Parse the stored expression */
		ADVANCE_LEXER;
		in_default_arg++;
		parse_exp (&e);
		in_default_arg--;
		if (crt_lex_token != lex_eof && !have_syntax_error) {
			ERROR err = ERR_lex_parse (crt_token);
			report (crt_loc, err);
		}
		
		/* End the default argument value */
		init_param (id, e);
		if (rescan) {
			IGNORE pop_namespace ();
			end_templ_scope (fn);
		}
		
		/* Reset the parser */
		if (crt_access_list.pending) {
			IGNORE report_access (pid);
		}
		restore_state (&s);
		p = restore_parser ();
		free_tok_list (p);
		functions_pending--;
    }
    return;
}


/*
 *    COMPILE ALL FUNCTIONS IN A NAMESPACE
 *
 *    This routine scans through the current class and any nested classes
 *    compiling any function definitions which remain uncompiled.
 */

void
rescan_functions()
{
    CLASS_TYPE ct = crt_class;
    LIST (IDENTIFIER) ft = DEREF_list (ctype_nest (ct));
    while (!IS_NULL_list (ft)) {
		IDENTIFIER id = DEREF_id (HEAD_list (ft));
		switch (TAG_id (id)) {
	    case id_class_name_tag : {
			/* Deal with nested classes */
			CLASS_TYPE cs;
			CLASS_INFO ci;
			NAMESPACE cns;
			TYPE t = DEREF_type (id_class_name_defn (id));
			TYPE s = begin_templ_scope (t);
			cs = DEREF_ctype (type_compound_defn (s));
			ci = DEREF_cinfo (ctype_info (cs));
			if (ci & cinfo_complete) {
				cns = DEREF_nspace (ctype_member (cs));
				push_class (cs);
				push_namespace (cns);
				rescan_functions ();
				IGNORE pop_namespace ();
				pop_class ();
			}
			end_templ_scope (t);
			break;
	    }
	    case id_function_tag :
	    case id_mem_func_tag :
	    case id_stat_mem_func_tag : {
			/* Deal with inline functions (including friends) */
			rescan_function (id);
			break;
	    }
	    case id_parameter_tag : {
			/* Deal with default arguments */
			rescan_param (id, 1);
			break;
	    }
		}
		ft = TAIL_list (ft);
    }
    return;
}
