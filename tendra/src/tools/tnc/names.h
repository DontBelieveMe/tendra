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


#ifndef NAMES_INCLUDED
#define NAMES_INCLUDED


/*
 *    MACROS GIVING CHARACTER TYPES
 *
 *    These macros determine the character types for input text
 */

#include <ctype.h>

#define white_space(X)	((X) == ' ' || (X) == '\n' || (X) == '\t')
#define octal_digit(X)	((X) >= '0' && (X) <= '7')
#define dec_digit(X)		((X) >= '0' && (X) <= '9')
#define terminator(X)		(white_space (X) || (X) == '(' ||\
				  (X) == ')' || (X) == '#' || (X) == ',' ||\
				  (X) == EOF)
#define alpha(X)		(isalpha ((X)) ||\
				  (X) == '_' || (X) == '~' || (X) == '.')
#define alphanum(X)		(alpha (X) || dec_digit (X))


/*
 *    BASIC CONSTRUCT NAMES
 *
 *    These macros give the names of the basic constructs used in
 *    input text.
 */

#define MAKE_ALDEC		"make_al_tagdec"
#define MAKE_ALDEF		"make_al_tagdef"
#define MAKE_ID_TAGDEC		"make_id_tagdec"
#define MAKE_VAR_TAGDEC		"make_var_tagdec"
#define COMMON_TAGDEC		"common_tagdec"
#define MAKE_ID_TAGDEF		"make_id_tagdef"
#define MAKE_VAR_TAGDEF		"make_var_tagdef"
#define COMMON_TAGDEF		"common_tagdef"
#define MAKE_TOKDEC		"make_tokdec"
#define MAKE_TOKDEF		"make_tokdef"
#define MAKE_SORT		"make_token_sort"


/*
 *    INCLUDE CONSTRUCT NAMES
 *
 *    These macros give the names of the constructs used to include
 *    code in input text.
 */

#define INCLUDE_CODE		"code"
#define INCLUDE_LIB		"lib"
#define INCLUDE_TEXT		"include"
#define USE_CODE		"use_code"
#define USE_LIB			"use_lib"


/*
 *    OTHER NAMES
 *
 *    These macros gives other names used in input text.
 */

#define LOCAL_DECL		"local"
#define MAKE_STRING_EXTERN	"string_extern"
#define MAKE_UNIQUE_EXTERN	"unique_extern"
#define MAKE_CHAIN_EXTERN	"chain_extern"
#define MAKE_STRING		"multi_string"


#endif
