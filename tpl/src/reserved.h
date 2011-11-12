/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:25 $
$Revision: 1.1.1.1 $
$Log: reserved.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/08/15  16:14:35  currie
 * for build 4.0
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:35:48  currie
 * Added banner
 *
***********************************************************************/
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
