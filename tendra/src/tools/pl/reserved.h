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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
#define no_of_terminals 103

/* note that the table is sorted into alphabetical order */
static Terminals terminals[no_of_terminals] = {
	{"!<", lex_relop},
	{"!<=", lex_relop},
	{"!=", lex_relop},
	{"!>", lex_relop},
	{"!>=", lex_relop},
	{"!Comparable", lex_relop},
	{"#", lex_hash},
	{"%", lex_arithop},
	{"%1", lex_arithop},
	{"*", lex_star},
	{"*+.", lex_addrop},
	{"*-*", lex_addrop},
	{"*?", lex_ptr__query},
	{"+", lex_arithop},
	{"-", lex_minus__term},
	{"->", lex_goesto},
	{".*", lex_addrop},
	{".+.", lex_addrop},
	{".-.", lex_addrop},
	{"...", lex_dotdotdot},
	{"./", lex_addrop},
	{"./.", lex_addrop},
	{".?", lex_offset__query},
	{".max.", lex_addrop},
	{"/", lex_arithop},
	{"/1", lex_arithop},
	{"<", lex_relop},
	{"<<", lex_arithop},
	{"<=", lex_relop},
	{"==", lex_relop},
	{">", lex_relop},
	{">=", lex_relop},
	{">>", lex_arithop},
	{"ACCESS", lex_access__sort},
	{"ALIGNMENT", lex_alignment__sort},
	{"AL_TAG", lex_al__tag__sort},
	{"Al_tagdef", lex_al__tagdef},
	{"And", lex_logop},
	{"BITFIELD_VARIETY", lex_bitfield__variety__sort},
	{"BOOL", lex_bool__sort},
	{"Base", lex_base},
	{"Case", lex_case__term},
	{"Char", lex_char__term},
	{"Check_stack", lex_check__stack},
	{"Common", lex_common__term},
	{"Commondec", lex_commondec__term},
	{"Comparable", lex_relop},
	{"Cons", lex_cons},
	{"Double", lex_double__term},
	{"Dynamic", lex_dynamic},
	{"E", lex_e__term},
	{"ERROR_TREATMENT", lex_error__treatment__sort},
	{"EXP", lex_exp__sort},
	{"F*", lex_arithop},
	{"F+", lex_arithop},
	{"F-", lex_arithop},
	{"F/", lex_arithop},
	{"F?", lex_float__query},
	{"FLOATING_VARIETY", lex_floating__variety__sort},
	{"Float", lex_float__term},
	{"General", lex_general},
	{"Iddec", lex_iddec},
	{"Int", lex_int__term},
	{"Keep", lex_keep},
	{"LABEL", lex_label__sort},
	{"LINE", lex_line__term},
	{"Labelled", lex_lab},
	{"Let", lex_let},
	{"Long", lex_long__term},
	{"Mantissa", lex_mantissa},
	{"Maxexp", lex_maxexp},
	{"Minexp", lex_minexp},
	{"NAT", lex_nat__sort},
	{"NTEST", lex_ntest__sort},
	{"Or", lex_logop},
	{"P?", lex_proc__query},
	{"Proc", lex_proc},
	{"Ptr", lex_ptr},
	{"ROUNDING_MODE", lex_rounding__mode__sort},
	{"Rep", lex_rep},
	{"SHAPE", lex_shape__sort},
	{"SIGNED_NAT", lex_signed__nat__sort},
	{"STRING", lex_string__sort},
	{"Same", lex_same},
	{"Short", lex_short__term},
	{"Signed", lex_signed__term},
	{"Sizeof", lex_size__term},
	{"String", lex_string__term},
	{"Struct", lex_struct__term},
	{"TAG", lex_tag__sort},
	{"TOKEN", lex_token__sort},
	{"TRANSFER_MODE", lex_transfer__mode__sort},
	{"Tail_call", lex_tail__call__term},
	{"Tokdec", lex_tokdec},
	{"Tokdef", lex_tokdef},
	{"Unsigned", lex_unsigned__term},
	{"Untidy", lex_untidy},
	{"Use", lex_use},
	{"VARIETY", lex_variety__sort},
	{"Var", lex_var},
	{"Vardec", lex_vardec},
	{"Varpar", lex_varpar},
	{"Xor", lex_logop}
};
