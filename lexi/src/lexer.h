/* 
 *     		 Crown Copyright (c) 1997
 *     
 *     This TenDRA(r) Computer Program is subject to Copyright
 *     owned by the United Kingdom Secretary of State for Defence
 *     acting through the Defence Evaluation and Research Agency
 *     (DERA).  It is made available to Recipients with a
 *     royalty-free licence for its use, reproduction, transfer
 *     to other parties and amendment for any purpose not excluding
 *     product development provided that any such use et cetera
 *     shall be deemed to be acceptance of the following conditions:-
 *     
 *         (1) Its Recipients shall ensure that this Notice is
 *         reproduced upon any copies or amended versions of it;
 *     
 *         (2) Any amended version of it shall be clearly marked to
 *         show both the nature of and the organisation responsible
 *         for the relevant amendment or amendments;
 *     
 *         (3) Its onward transfer from a recipient to another
 *         party shall be deemed to be that party's acceptance of
 *         these conditions;
 *     
 *         (4) DERA gives no warranty or assurance as to its
 *         quality or suitability for any purpose and DERA accepts
 *         no liability whatsoever in relation to any use to which
 *         it may be put.
 * 
 */
/*
 *  AUTOMATICALLY GENERATED BY lexi VERSION 2.0
 */

#ifndef LEXI_GENERATED_HEADER__INCLUDED
#define LEXI_GENERATED_HEADER__INCLUDED

#include <stdint.h>

typedef uint8_t lexi_lookup_type;
extern lexi_lookup_type lookup_tab[257];

#ifndef LEX_EOF
#define LEX_EOF		256
#endif

extern void lexi_push(const int c);
extern int lexi_pop(void);
extern void lexi_flush(void);
extern int lexi_readchar(void);
#define lookup_char(C)	((int)lookup_tab[(C)])
#define is_white(T)	((T) & 0x01)
#define is_alpha(T)	((T) & 0x02)
#define is_digit(T)	((T) & 0x04)
#define is_alphanum(T)	((T) & 0x08)
#define is_comment_white(T)	((T) & 0x10)
#define is_line_comment_white(T)	((T) & 0x20)
/* lexer_state_definition */

typedef struct lexer_state_tag lexer_state;
extern int read_token(lexer_state*);
extern lexer_state* current_lexer_state;
extern int read_token(lexer_state* state);
#endif
