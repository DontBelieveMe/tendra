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


#ifndef LEX_INCLUDED
#define LEX_INCLUDED


/*
    LEXICAL ANALYSIS DECLARATIONS

    The routines in this module are concerned with the lexical analysis
    of the input, including its decomposition into preprocessing tokens
    using the routine read_token.
*/

extern void init_lex(void);
extern void init_char(void);
extern void process_file(void);
extern IDENTIFIER make_keyword(HASHID, int, IDENTIFIER);
extern void init_keywords(void);
extern int read_token(void);
extern int read_string(int, int);
extern int peek_char(int, int *);
extern int skip_to_end(void);
extern unsigned long skip_white(int);
extern void patch_white(unsigned long);
extern int get_digraph(int);
extern int primary_form(int);
extern int is_white_char(unsigned long);
extern int is_alpha_char(unsigned long);
extern int is_legal_char(unsigned long);
extern void set_char_lookup(int, int);
extern void set_character(EXP, EXP);


/*
    LEXICAL TOKEN INFORMATION

    These variables are used by read_token to hold information about the
    current lexical token.
*/

extern BUFFER token_buff;
extern HASHID token_hashid;
extern CONST char *token_names[];


/*
    LEXICAL ANALYSIS OPTIONS

    These variables are used to configure the lexical analysis routines.
*/

extern int allow_trigraphs;
extern int allow_digraphs;
extern int allow_unicodes;
extern int allow_multibyte;
extern int allow_cpp_comments;
extern int allow_dos_newline;
extern int allow_extra_symbols;
extern int allow_iso_keywords;
extern int analyse_comments;
extern unsigned long max_id_length;


/*
    TOKEN NAME LOOK-UP

    The macro token_name is used to look up the name associated with the
    lexical token number T.
*/

#define token_name(T)		(ustrlit(token_names[(T)]))


/*
    WHITE-SPACE INDICATORS

    These macros are used by skip_white to indicate the form of the white-
    space characters skipped.
*/

#define WHITE_SPACE		((unsigned long)0x01)
#define WHITE_NEWLINE		((unsigned long)0x02)
#define WHITE_ESC_NEWLINE	((unsigned long)0x04)
#define WHITE_MASK		(WHITE_SPACE | WHITE_NEWLINE)


#endif
