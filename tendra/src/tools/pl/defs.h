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


/**********************************************************************
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:32:02  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/06/08  09:13:48  currie
 * Added sigs to tokdecs/defs
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1994/12/05  10:12:59  currie
 * Extended size of input buffer
 *
 * Revision 1.2  1994/07/21  10:36:07  currie
 * Added banner
 *
***********************************************************************/
#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED

#include "namedecs.h"
#include "errors.h"
#include "util.h"
#include "includes.h"

typedef struct{
    int t; 
    union Lex_v{int v; char * name; Tokdec * tokname;} val; 
} LEX;

typedef struct{char *name; int t; void(*f) PROTO_S((void));} Constructs;
typedef struct{char *name; int t;} Terminals;

#define BUFFLEN 600
extern char buff[BUFFLEN];
extern unsigned long cLINE;
extern LEX lex_v;
extern long radix;
extern int lnum;
extern int bind;
extern long stoi PROTO_S((char * s, int n));

#define MINSI			0x80000000
#define MAXSI			0x7fffffff
#define MAXUSI			0xffffffff
#define MINSS			0x8000
#define MAXSS			0x7fff
#define MAXUSS			0xffff
#define MINSC			128
#define MAXSC			127
#define MAXUSC			255
#define MINSL			0x80000000
#define MAXSL			0x7fffffff
#define MAXUSL			0xffffffff
#define MANT_DOUBLE		53
#define MINEXP_DOUBLE		1022
#define MAXEXP_DOUBLE		1023
#define MANT_FLOAT		24
#define MINEXP_FLOAT		126
#define MAXEXP_FLOAT		127

#define UL(x)			((unsigned long)(x))
#define UI(x)			((unsigned int)(x))
#define UC(x)			((unsigned char)(x))

#define access_t		lex_access__cons
#define alignment_t		lex_alignment__cons
#define bitfield_variety_t	lex_bitfield__variety__cons
#define bool_t			lex_bool__cons
#define error_code_t		lex_error__code__cons
#define error_treatment_t	lex_error__treatment__cons
#define exp_t			lex_exp__cons
#define floating_variety_t	lex_floating__variety__cons
#define nat_t			lex_nat__cons
#define ntest_t			lex_ntest__cons
#define rounding_mode_t		lex_rounding__mode__cons
#define shape_t			lex_shape__cons
#define signed_nat_t		lex_signed__nat__cons
#define string_t		lex_string__cons
#define tag_t			lex_tag__cons
#define token_t			lex_token__cons
#define transfer_mode_t		lex_transfer__mode__cons
#define variety_t		lex_variety__cons

#define access_sort		lex_access__sort
#define al_tag_sort		lex_al__tag__sort
#define alignment_sort		lex_alignment__sort
#define bitfield_variety_sort	lex_bitfield__variety__sort
#define bool_sort		lex_bool__sort
#define error_treatment_sort	lex_error__treatment__sort
#define exp_sort		lex_exp__sort
#define floating_variety_sort	lex_floating__variety__sort
#define label_sort		lex_label__sort
#define nat_sort		lex_nat__sort
#define ntest_sort		lex_ntest__sort
#define rounding_mode_sort	lex_rounding__mode__sort
#define shape_sort		lex_shape__sort
#define signed_nat_sort		lex_signed__nat__sort
#define string_sort		lex_string__sort
#define tag_sort		lex_tag__sort
#define token_sort		lex_token__sort
#define transfer_mode_sort	lex_transfer__mode__sort
#define variety_sort		lex_variety__sort

#define access_tok		lex_access__tok
#define al_tag_tok		lex_al__tag__tok
#define alignment_tok		lex_alignment__tok
#define bitfield_variety_tok	lex_bitfield__variety__tok
#define bool_tok		lex_bool__tok
#define error_treatment_tok	lex_error__treatment__tok
#define exp_tok			lex_exp__tok
#define floating_variety_tok	lex_floating__variety__tok
#define label_tok		lex_label__tok
#define nat_tok			lex_nat__tok
#define ntest_tok		lex_ntest__tok
#define rounding_mode_tok	lex_rounding__mode__tok
#define shape_tok		lex_shape__tok
#define signed_nat_tok		lex_signed__nat__tok
#define string_tok		lex_string__tok
#define tag_tok			lex_tag__tok
#define token_tok		lex_token__tok
#define transfer_mode_tok	lex_transfer__mode__tok
#define variety_tok		lex_variety__tok


#endif
