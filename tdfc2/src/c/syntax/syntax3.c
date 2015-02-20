/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT
#line 169 "syntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"

#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "inttype.h"
#include "label.h"
#include "lex.h"
#include "literal.h"
#include "member.h"
#include "namespace.h"
#include "parse.h"
#include "pragma.h"
#include "predict.h"
#include "preproc.h"
#include "redeclare.h"
#include "rewrite.h"
#include "statement.h"
#include "symbols.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "typeid.h"
#include "variable.h"


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;


/*
    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include "syntax.h"


#line 95 "syntax3.c"

void
ZR821(BASE_TYPE *ZIbt, TYPE *ZIt, DECL_SPEC *ZIds, TYPE *ZIs, IDENTIFIER *ZIid)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER ZId;
		int ZIb;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_function */
		{
#line 1418 "syntax.act"

    (ZI0) = function_params ( (*ZIs) ) ;
#line 113 "syntax3.c"
		}
		/* END OF ACTION: is_function */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: define_func */
		{
#line 1169 "syntax.act"

    (ZId) = make_func_decl ( (*ZIds), (*ZIs), (*ZIid), 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 125 "syntax3.c"
		}
		/* END OF ACTION: define_func */
		/* BEGINNING OF ACTION: function_begin */
		{
#line 860 "syntax.act"

    (ZIb) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (ZId) ) ;
#line 137 "syntax3.c"
		}
		/* END OF ACTION: function_begin */
		ZRfunction_Hbody (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: function_end */
		{
#line 868 "syntax.act"

    IGNORE end_function ( (ZId), (ZIa) ) ;
    in_class_defn = (ZIb) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
#line 153 "syntax3.c"
		}
		/* END OF ACTION: function_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1467 "syntax.act"

    RESCAN_LEXER ;
#line 161 "syntax3.c"
		}
		/* END OF ACTION: rescan_token */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 36: case 42: case 77:
		{
			IDENTIFIER ZId;
			EXP ZIa;

			/* BEGINNING OF ACTION: declare_id */
			{
#line 1151 "syntax.act"

    if ( in_weak_param ) {
	(ZId) = make_param_decl ( (*ZIds), (*ZIs), (*ZIid), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (*ZIs) ) == type_func_tag ) {
	check_weak_func ( (*ZIs), 0 ) ;
	(ZId) = make_func_decl ( (*ZIds), (*ZIs), (*ZIid), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZId) = make_object_decl ( (*ZIds), (*ZIs), (*ZIid), def ) ;
    }
    if ( IS_id_type_alias ( (ZId) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZId) ) ) ;
	bs |= (*ZIbt) ;
	COPY_btype ( id_type_alias_rep ( (ZId) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 194 "syntax3.c"
			}
			/* END OF ACTION: declare_id */
			ZRinitialiser_Hopt (ZId, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: initialise_id */
			{
#line 1256 "syntax.act"

    int def = init_object ( (ZId), (ZIa) ) ;
    if ( do_dump ) dump_declare ( (ZId), &decl_loc, def ) ;
#line 208 "syntax3.c"
			}
			/* END OF ACTION: initialise_id */
			/* BEGINNING OF INLINE: 822 */
			{
				switch (CURRENT_TERMINAL) {
				case 42:
					{
						ADVANCE_LEXER;
						ZRinit_Hdeclarator_Hlist (*ZIds, *ZIbt, *ZIt);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					break;
				}
			}
			/* END OF INLINE: 822 */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
}

void
ZRand_Hexpression(EXP *ZO895)
{
	EXP ZI895;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRmaxmin_Hexpression (&ZIe);
		ZR896 (ZIe, &ZI895);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO895 = ZI895;
}

void
parse_exp(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRassignment_Hexpression (&ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1349 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 300 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 434 "syntax.act"

    (ZIe) = NULL_exp ;
#line 308 "syntax3.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZRtype_Hqualifier(BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 98: case 124:
		{
			ZRcv_Hqualifier (&ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: btype_none */
			{
#line 928 "syntax.act"
 (ZIbt) = btype_none ; 
#line 335 "syntax3.c"
			}
			/* END OF ACTION: btype_none */
			/* BEGINNING OF ACTION: type_none */
			{
#line 952 "syntax.act"

    (ZIt) = NULL_type ;
#line 343 "syntax3.c"
			}
			/* END OF ACTION: type_none */
		}
		break;
	case 2: case 25: case 97: case 102:
	case 104: case 106: case 110: case 111:
	case 114: case 115: case 118: case 121:
	case 122: case 123: case 156: case 185:
	case 286: case 299:
		{
			ZRtype_Hspecifier (&ZIbt, &ZIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cv_none */
			{
#line 897 "syntax.act"
 (ZIcv) = cv_none ; 
#line 363 "syntax3.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZR1077(EXP *ZI1075, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255: case 298:
	case 324: case 346:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 419 "syntax.act"

    CONS_exp ( (*ZI1075), (ZIq), (ZIp) ) ;
#line 410 "syntax3.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 469 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 418 "syntax3.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	default:
		{
			ZIe = *ZI1075;
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR952(EXP *ZI950, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 72:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRexpression (&ZIa);
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRconditional_Hexpression (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_cond */
			{
#line 473 "syntax.act"

    (ZIe) = make_cond_exp ( (*ZI950), (ZIa), (ZIb) ) ;
#line 472 "syntax3.c"
			}
			/* END OF ACTION: exp_cond */
		}
		break;
	default:
		{
			ZIe = *ZI950;
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1080(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 298:
		{
			EXP ZI1093;
			EXP ZI1094;

			ADVANCE_LEXER;
			ZRexpression (&ZI1093);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_set */
			{
#line 609 "syntax.act"

    (ZI1094) = make_set_exp ( (ZI1093) ) ;
#line 515 "syntax3.c"
			}
			/* END OF ACTION: exp_set */
			ZR1095 (&ZI1094, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 324:
		{
			EXP ZI1090;
			EXP ZI1091;

			ADVANCE_LEXER;
			ZRexpression (&ZI1090);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 621 "syntax.act"

    (ZI1091) = make_unused_exp ( (ZI1090) ) ;
#line 541 "syntax3.c"
			}
			/* END OF ACTION: exp_unused */
			ZR1095 (&ZI1091, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
parse_stmt(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		ZRstatement (&ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1349 "syntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 590 "syntax3.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: exp_none */
		{
#line 434 "syntax.act"

    (ZIe) = NULL_exp ;
#line 598 "syntax3.c"
		}
		/* END OF ACTION: exp_none */
	}
ZL0:;
	*ZOe = ZIe;
}

void
ZRmember_Hdeclarator_Hlist(TYPE ZIp, BASE_TYPE ZIq)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_member_Hdeclarator_Hlist:;
	{
		ZRmember_Hdeclarator (ZIp, ZIq);
		/* BEGINNING OF INLINE: 828 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: member-declarator-list */
					goto ZL2_member_Hdeclarator_Hlist;
					/* END OF INLINE: member-declarator-list */
				}
				UNREACHED;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 828 */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1081(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 96:
		{
			EXP ZIc;
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_case_begin */
			{
#line 647 "syntax.act"

    (ZIa) = begin_case_stmt ( (ZIc), 0 ) ;
#line 664 "syntax3.c"
			}
			/* END OF ACTION: stmt_case_begin */
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 765 "syntax.act"

    unreached_fall = 0 ;
#line 672 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_set */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_case_end */
			{
#line 651 "syntax.act"

    (ZIe) = end_case_stmt ( (ZIa), (ZIb) ) ;
#line 692 "syntax3.c"
			}
			/* END OF ACTION: stmt_case_end */
		}
		break;
	case 100:
		{
			EXP ZIa;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_default_begin */
			{
#line 685 "syntax.act"

    (ZIa) = begin_default_stmt ( 0 ) ;
#line 708 "syntax3.c"
			}
			/* END OF ACTION: stmt_default_begin */
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 765 "syntax.act"

    unreached_fall = 0 ;
#line 716 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_set */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_default_end */
			{
#line 689 "syntax.act"

    (ZIe) = end_default_stmt ( (ZIa), (ZIb) ) ;
#line 736 "syntax3.c"
			}
			/* END OF ACTION: stmt_default_end */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRtype_Hid(TYPE *ZOt, int *ZOn)
{
	TYPE ZIt;
	int ZIn;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		int ZIn1;
		BASE_TYPE ZIbt;
		TYPE ZIp;
		CV_SPEC ZIcv;
		TYPE ZIq;

		/* BEGINNING OF ACTION: no_type_defns */
		{
#line 1378 "syntax.act"

    (ZIn1) = no_type_defns ;
#line 775 "syntax3.c"
		}
		/* END OF ACTION: no_type_defns */
		ZRtype_Hspecifier_Hseq (&ZIbt, &ZIp, &ZIcv);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: type_complete */
		{
#line 988 "syntax.act"

    (ZIq) = complete_pre_type ( (ZIbt), (ZIp), (ZIcv), 1 ) ;
    have_type_specifier = 0 ;
#line 789 "syntax3.c"
		}
		/* END OF ACTION: type_complete */
		ZRabstract_Hdeclarator_Hopt (ZIq, &ZIt);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: diff_type_defns */
		{
#line 1386 "syntax.act"

    (ZIn) = no_type_defns - (ZIn1) ;
#line 802 "syntax3.c"
		}
		/* END OF ACTION: diff_type_defns */
		/* BEGINNING OF ACTION: type_check */
		{
#line 997 "syntax.act"

    object_type ( (ZIt), null_tag ) ;
#line 810 "syntax3.c"
		}
		/* END OF ACTION: type_check */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOt = ZIt;
	*ZOn = ZIn;
}

void
ZRflow_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 298:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_set */
			{
#line 609 "syntax.act"

    (ZIe) = make_set_exp ( (ZIa) ) ;
#line 851 "syntax3.c"
			}
			/* END OF ACTION: exp_set */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 324:
		{
			EXP ZIa;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unused */
			{
#line 621 "syntax.act"

    (ZIe) = make_unused_exp ( (ZIa) ) ;
#line 885 "syntax3.c"
			}
			/* END OF ACTION: exp_unused */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR701(BASE_TYPE *ZIb1, TYPE *ZIt1, CV_SPEC *ZIcv1, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZI1030;
		TYPE ZI1031;
		CV_SPEC ZI1032;
		BASE_TYPE ZIb2;
		TYPE ZIt2;
		CV_SPEC ZIcv2;

		/* BEGINNING OF ACTION: is_type_specifier */
		{
#line 1448 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 934 "syntax3.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL2;
		ZRtype_Hqualifier (&ZI1030, &ZI1031, &ZI1032);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: check_decl_specifier */
		{
#line 1474 "syntax.act"

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
#line 952 "syntax3.c"
		}
		/* END OF ACTION: check_decl_specifier */
		ZR701 (&ZI1030, &ZI1031, &ZI1032, &ZIb2, &ZIt2, &ZIcv2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: btype_join */
		{
#line 931 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 969 "syntax3.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 977 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 985 "syntax3.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 902 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 995 "syntax3.c"
		}
		/* END OF ACTION: cv_join */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			ZIbt = *ZIb1;
			ZIt = *ZIt1;
			ZIcv = *ZIcv1;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

void
ZRdeclaration_Hcond_Hbody(void)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		DECL_SPEC ZIds;
		TYPE ZIt;

		/* BEGINNING OF INLINE: open-brace */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 64:
					break;
				default:
					goto ZL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: open-brace */
		/* BEGINNING OF ACTION: dspec_none */
		{
#line 1116 "syntax.act"
 (ZIds) = dspec_none ; 
#line 1048 "syntax3.c"
		}
		/* END OF ACTION: dspec_none */
		/* BEGINNING OF ACTION: type_none */
		{
#line 952 "syntax.act"

    (ZIt) = NULL_type ;
#line 1056 "syntax3.c"
		}
		/* END OF ACTION: type_none */
		ZRdeclaration_Hseq_Hopt ();
		/* BEGINNING OF INLINE: close-brace */
		{
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case 38:
					break;
				default:
					goto ZL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: close-brace */
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZR1084(IDENTIFIER *ZIid, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 33: case 34: case 35: case 36:
	case 42: case 44: case 45: case 46:
	case 48: case 49: case 50: case 53:
	case 54: case 55: case 56: case 57:
	case 58: case 59: case 60: case 61:
	case 63: case 65: case 66: case 67:
	case 68: case 69: case 70: case 71:
	case 72: case 73: case 74: case 75:
	case 76: case 77: case 78: case 79:
	case 80: case 81: case 86: case 87:
		{
			EXP ZI1014;
			EXP ZI1015;
			EXP ZI1023;
			EXP ZIa;
			int ZIr;

			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 507 "syntax.act"

    (ZI1014) = make_id_exp ( (*ZIid) ) ;
#line 1112 "syntax3.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR924 (ZI1014, &ZI1015);
			ZR1013 (&ZI1015, &ZI1023);
			ZR1025 (&ZI1023, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1135 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 701 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1143 "syntax3.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 1151 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 41:
		{
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 773 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 1173 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 756 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZIid), lex_identifier ) ;
#line 1181 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 760 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 1195 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_end */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1085(IDENTIFIER *ZIid, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	default:
		{
			EXP ZIa;

			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 507 "syntax.act"

    (ZIa) = make_id_exp ( (*ZIid) ) ;
#line 1228 "syntax3.c"
			}
			/* END OF ACTION: exp_identifier */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 701 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 1236 "syntax3.c"
			}
			/* END OF ACTION: stmt_exp */
		}
		break;
	case 41:
		{
			EXP ZIa;
			EXP ZIb;

			/* BEGINNING OF ACTION: stmt_label_mod */
			{
#line 773 "syntax.act"

    if ( unreached_code ) unreached_fall = 0 ;
#line 1251 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_mod */
			/* BEGINNING OF ACTION: stmt_label_begin */
			{
#line 756 "syntax.act"

    (ZIa) = begin_label_stmt ( (*ZIid), lex_identifier ) ;
#line 1259 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_begin */
			ADVANCE_LEXER;
			ZRstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_end */
			{
#line 760 "syntax.act"

    (ZIe) = end_label_stmt ( (ZIa), (ZIb) ) ;
#line 1273 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_end */
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRexpression_Hlist(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;
		SID_LIST_EXP ZIq;

		ZRassignment_Hexpression (&ZIe);
		ZR626 (&ZIq);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: list_exp_cons */
		{
#line 419 "syntax.act"

    CONS_exp ( (ZIe), (ZIq), (ZIp) ) ;
#line 1312 "syntax3.c"
		}
		/* END OF ACTION: list_exp_cons */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOp = ZIp;
}

void
ZRassignment_Hexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 170:
		{
			int ZI1008;
			EXP ZI1009;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_alignof */
			{
#line 371 "syntax.act"
 (ZI1008) = lex_alignof ; 
#line 1340 "syntax3.c"
			}
			/* END OF ACTION: lex_alignof */
			ZRsizeof_Hexpression (ZI1008, &ZI1009);
			ZR1013 (&ZI1009, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 23:
		{
			EXP ZI1020;
			EXP ZI1021;

			/* BEGINNING OF EXTRACT: complex-exp */
			{
#line 334 "syntax.act"

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1020 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
#line 1364 "syntax3.c"
			}
			/* END OF EXTRACT: complex-exp */
			ADVANCE_LEXER;
			ZR924 (ZI1020, &ZI1021);
			ZR1013 (&ZI1021, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 206:
		{
			EXP ZIa;
			EXP ZI963;
			EXP ZI962;
			EXP ZI961;
			EXP ZI960;
			EXP ZI959;
			EXP ZI958;
			EXP ZI957;
			EXP ZI956;
			EXP ZI955;
			EXP ZI954;
			EXP ZI953;
			EXP ZI950;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ignore */
			{
#line 511 "syntax.act"

    (ZI963) = make_cast_exp ( type_void, (ZIa), 0 ) ;
#line 1403 "syntax3.c"
			}
			/* END OF ACTION: exp_ignore */
			ZR920 (ZI963, &ZI962);
			ZR916 (ZI962, &ZI961);
			ZR912 (ZI961, &ZI960);
			ZR908 (ZI960, &ZI959);
			ZR904 (ZI959, &ZI958);
			ZR900 (ZI958, &ZI957);
			ZR896 (ZI957, &ZI956);
			ZR892 (ZI956, &ZI955);
			ZR888 (ZI955, &ZI954);
			ZR884 (ZI954, &ZI953);
			ZR880 (ZI953, &ZI950);
			ZR952 (&ZI950, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 210:
		{
			EXP ZI1017;
			EXP ZI1018;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_ellipsis */
			{
#line 489 "syntax.act"

    (ZI1017) = make_ellipsis_exp () ;
#line 1435 "syntax3.c"
			}
			/* END OF ACTION: exp_ellipsis */
			ZR924 (ZI1017, &ZI1018);
			ZR1013 (&ZI1018, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1:
		{
			IDENTIFIER ZIid;
			EXP ZI1014;
			EXP ZI1015;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 198 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 1457 "syntax3.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp_identifier */
			{
#line 507 "syntax.act"

    (ZI1014) = make_id_exp ( (ZIid) ) ;
#line 1466 "syntax3.c"
			}
			/* END OF ACTION: exp_identifier */
			ZR924 (ZI1014, &ZI1015);
			ZR1013 (&ZI1015, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 255:
		{
			EXP ZIa;
			EXP ZI963;
			EXP ZI962;
			EXP ZI961;
			EXP ZI960;
			EXP ZI959;
			EXP ZI958;
			EXP ZI957;
			EXP ZI956;
			EXP ZI955;
			EXP ZI954;
			EXP ZI953;
			EXP ZI950;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_lit */
			{
#line 523 "syntax.act"

    (ZI963) = make_lit_exp ( (ZIa) ) ;
#line 1504 "syntax3.c"
			}
			/* END OF ACTION: exp_lit */
			ZR920 (ZI963, &ZI962);
			ZR916 (ZI962, &ZI961);
			ZR912 (ZI961, &ZI960);
			ZR908 (ZI960, &ZI959);
			ZR904 (ZI959, &ZI958);
			ZR900 (ZI958, &ZI957);
			ZR896 (ZI957, &ZI956);
			ZR892 (ZI956, &ZI955);
			ZR888 (ZI955, &ZI954);
			ZR884 (ZI954, &ZI953);
			ZR880 (ZI953, &ZI950);
			ZR952 (&ZI950, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 61:
		{
			EXP ZI989;
			EXP ZI990;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZI989);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_predec */
			{
#line 584 "syntax.act"

    (ZI990) = make_prefix_exp ( lex_minus_Hminus, (ZI989) ) ;
#line 1541 "syntax3.c"
			}
			/* END OF ACTION: exp_predec */
			ZR1013 (&ZI990, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 65:
		{
			ADVANCE_LEXER;
			ZR985 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 71:
		{
			EXP ZI986;
			EXP ZI987;

			ADVANCE_LEXER;
			ZRunary_Hexpression (&ZI986);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_preinc */
			{
#line 588 "syntax.act"

    (ZI987) = make_prefix_exp ( lex_plus_Hplus, (ZI986) ) ;
#line 1577 "syntax3.c"
			}
			/* END OF ACTION: exp_preinc */
			ZR1013 (&ZI987, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 116:
		{
			int ZI1005;
			EXP ZI1006;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_sizeof */
			{
#line 372 "syntax.act"
 (ZI1005) = lex_sizeof ; 
#line 1597 "syntax3.c"
			}
			/* END OF ACTION: lex_sizeof */
			ZRsizeof_Hexpression (ZI1005, &ZI1006);
			ZR1013 (&ZI1006, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			EXP ZI992;
			EXP ZI993;

			ADVANCE_LEXER;
			ZRcast_Hexpression (&ZI992);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_indir */
			{
#line 519 "syntax.act"

    (ZI993) = make_indir_exp ( (ZI992) ) ;
#line 1624 "syntax3.c"
			}
			/* END OF ACTION: exp_indir */
			ZR1013 (&ZI993, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 33:
		{
			EXP ZI995;
			EXP ZI996;

			/* BEGINNING OF INLINE: and */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 33:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: and */
			ZRcast_Hexpression (&ZI995);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_ref */
			{
#line 592 "syntax.act"

    (ZI996) = make_ref_exp ( (ZI995), 0 ) ;
#line 1662 "syntax3.c"
			}
			/* END OF ACTION: exp_ref */
			ZR1013 (&ZI996, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 17: case 18: case 19: case 20:
	case 21: case 22:
		{
			EXP ZI1011;
			EXP ZI1012;

			ZRliteral (&ZI1011);
			ZR924 (ZI1011, &ZI1012);
			ZR1013 (&ZI1012, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 62:
		{
			EXP ZI998;
			EXP ZI999;

			/* BEGINNING OF INLINE: not */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 62:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: not */
			ZRcast_Hexpression (&ZI998);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_not */
			{
#line 555 "syntax.act"

    (ZI999) = make_not_exp ( (ZI998) ) ;
#line 1715 "syntax3.c"
			}
			/* END OF ACTION: exp_not */
			ZR1013 (&ZI999, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 43: case 59: case 69: case 85:
		{
			int ZI1001;
			EXP ZI1002;
			EXP ZI1003;

			/* BEGINNING OF ACTION: lex_crt */
			{
#line 368 "syntax.act"
 (ZI1001) = crt_lex_token ; 
#line 1735 "syntax3.c"
			}
			/* END OF ACTION: lex_crt */
			ZRunary_Hoperator ();
			ZRcast_Hexpression (&ZI1002);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_unary */
			{
#line 617 "syntax.act"

    (ZI1003) = make_uminus_exp ( (ZI1001), (ZI1002) ) ;
#line 1749 "syntax3.c"
			}
			/* END OF ACTION: exp_unary */
			ZR1013 (&ZI1003, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRexpression_Hlist_Hopt(SID_LIST_EXP *ZOp)
{
	SID_LIST_EXP ZIp;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255:
		{
			ZRexpression_Hlist (&ZIp);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: list_exp_null */
			{
#line 415 "syntax.act"

    (ZIp) = NULL_list ( EXP ) ;
#line 1799 "syntax3.c"
			}
			/* END OF ACTION: list_exp_null */
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOp = ZIp;
}

void
ZRlogical_Hand_Hexpression(EXP *ZO883)
{
	EXP ZI883;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRinclusive_Hor_Hexpression (&ZIe);
		ZR884 (ZIe, &ZI883);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO883 = ZI883;
}

void
ZRjump_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 95:
		{
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1865 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_break */
			{
#line 643 "syntax.act"

    (ZIe) = make_break_stmt () ;
#line 1873 "syntax3.c"
			}
			/* END OF ACTION: stmt_break */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 1881 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 99:
		{
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1909 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_continue */
			{
#line 676 "syntax.act"

    (ZIe) = make_continue_stmt () ;
#line 1917 "syntax3.c"
			}
			/* END OF ACTION: stmt_continue */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 1925 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 108:
		{
			int ZIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1953 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			ZRjump_Hlabel (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 1966 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 113:
		{
			int ZIr;
			EXP ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 1995 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			ZR617 (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_return */
			{
#line 776 "syntax.act"

    (ZIe) = make_return_stmt ( (ZIa), lex_return ) ;
#line 2008 "syntax3.c"
			}
			/* END OF ACTION: stmt_return */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 2016 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRtarget_Hcondition_Hhead(EXP *ZO932, EXP *ZO933, int *ZO934)
{
	EXP ZI932;
	EXP ZI933;
	int ZI934;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIc;
		EXP ZIp;
		int ZIr;
		EXP ZIa;
		EXP ZIe;

		switch (CURRENT_TERMINAL) {
		case 26:
			/* BEGINNING OF EXTRACT: hash-if */
			{
#line 316 "syntax.act"

    ZIc = crt_token->pp_data.exp ;
#line 2063 "syntax3.c"
			}
			/* END OF EXTRACT: hash-if */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: cond_hash_if */
		{
#line 1310 "syntax.act"

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZIc), c ) ;
    (ZIp) = c ;
#line 2078 "syntax3.c"
		}
		/* END OF ACTION: cond_hash_if */
		/* BEGINNING OF ACTION: reach_check */
		{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2094 "syntax3.c"
		}
		/* END OF ACTION: reach_check */
		ZRcompound_Hstatement (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: reach_prev */
		{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 2106 "syntax3.c"
		}
		/* END OF ACTION: reach_prev */
		/* BEGINNING OF ACTION: stmt_hash_if */
		{
#line 800 "syntax.act"

    (ZIe) = begin_hash_if_stmt ( (ZIc), (ZIa) ) ;
#line 2114 "syntax3.c"
		}
		/* END OF ACTION: stmt_hash_if */
		ZR935 (ZIe, ZIp, ZIr, &ZI932, &ZI933, &ZI934);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO932 = ZI932;
	*ZO933 = ZI933;
	*ZO934 = ZI934;
}

void
ZRcv_Hqualifier_Hseq(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		CV_SPEC ZIa;

		ZRcv_Hqualifier (&ZIa);
		/* BEGINNING OF INLINE: 635 */
		{
			switch (CURRENT_TERMINAL) {
			case 98: case 124:
				{
					CV_SPEC ZIb;

					ZRcv_Hqualifier_Hseq (&ZIb);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: cv_join */
					{
#line 902 "syntax.act"

    CV_SPEC c = ( (ZIa) & (ZIb) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (ZIa) | (ZIb) ) ;
#line 2164 "syntax3.c"
					}
					/* END OF ACTION: cv_join */
				}
				break;
			default:
				{
					ZIcv = ZIa;
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 635 */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

void
ZRfunction_Hbody(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIc;
		int ZId;
		EXP ZIb;
		EXP ZIr;
		EXP ZIa;

		/* BEGINNING OF ACTION: stmt_compound_begin */
		{
#line 655 "syntax.act"

    (ZIc) = begin_compound_stmt ( 1 ) ;
#line 2209 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_begin */
		/* BEGINNING OF INLINE: open-brace */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 64:
					break;
				default:
					goto ZL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: open-brace */
		/* BEGINNING OF ACTION: stmt_compound_block */
		{
#line 663 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
    (ZId) = 1 ;
#line 2231 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_block */
		ZRstatement_Hseq_Hopt (ZIc, ZId, &ZIb);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_return_fall */
		{
#line 780 "syntax.act"

    (ZIr) = fall_return_stmt () ;
#line 2244 "syntax3.c"
		}
		/* END OF ACTION: stmt_return_fall */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 668 "syntax.act"

    (ZIa) = add_compound_stmt ( (ZIb), (ZIr) ) ;
#line 2252 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF INLINE: close-brace */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 38:
					break;
				default:
					goto ZL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: close-brace */
		/* BEGINNING OF ACTION: stmt_compound_end */
		{
#line 672 "syntax.act"

    (ZIe) = end_compound_stmt ( (ZIa) ) ;
#line 2273 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_end */
		/* BEGINNING OF ACTION: rescan_token */
		{
#line 1467 "syntax.act"

    RESCAN_LEXER ;
#line 2281 "syntax3.c"
		}
		/* END OF ACTION: rescan_token */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR965(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIt;
		int ZIn;
		EXP ZIa;

		/* BEGINNING OF ACTION: is_type_id_false */
		{
#line 1438 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 2312 "syntax3.c"
		}
		/* END OF ACTION: is_type_id_false */
		if (!ZI0)
			goto ZL2;
		ZRtype_Hid (&ZIt, &ZIn);
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		case 355:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcast_Hexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_cast */
		{
#line 465 "syntax.act"

    /* n is the number of type definitions in t */
    (ZIe) = make_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 2339 "syntax3.c"
		}
		/* END OF ACTION: exp_cast */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255: case 298:
	case 324: case 346:
		{
			EXP ZIa;
			EXP ZI964;

			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 564 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 2363 "syntax3.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 567 "syntax.act"

    (ZI964) = make_paren_exp ( (ZIa) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 2377 "syntax3.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR924 (ZI964, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRcv_Hqualifier_Hseq_Hopt(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 98: case 124:
		{
			ZRcv_Hqualifier_Hseq (&ZIcv);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cv_none */
			{
#line 897 "syntax.act"
 (ZIcv) = cv_none ; 
#line 2426 "syntax3.c"
			}
			/* END OF ACTION: cv_none */
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

void
ZR1095(EXP *ZI1094, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 347:
		{
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;
			EXP ZIa;
			int ZIr;

			ADVANCE_LEXER;
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 419 "syntax.act"

    CONS_exp ( (*ZI1094), (ZIq), (ZIp) ) ;
#line 2466 "syntax3.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 469 "syntax.act"

    (ZIa) = make_comma_exp ( (ZIp) ) ;
#line 2474 "syntax3.c"
			}
			/* END OF ACTION: exp_comma */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2490 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 701 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 2498 "syntax3.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 2506 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 77:
		{
			int ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 347:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 2543 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 701 "syntax.act"

    (ZIe) = make_exp_stmt ( (*ZI1094) ) ;
#line 2551 "syntax3.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 2559 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR1096(void)
{
	switch (CURRENT_TERMINAL) {
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 765 "syntax.act"

    unreached_fall = 0 ;
#line 2589 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_set */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: stmt_label_set */
			{
#line 765 "syntax.act"

    unreached_fall = 0 ;
#line 2601 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_set */
		}
		break;
	case 355:
		return;
	}
}

void
ZRfall_Hcheck(void)
{
	switch (CURRENT_TERMINAL) {
	case 223:
		{
			ADVANCE_LEXER;
			ZR1096 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRcv_Hqualifier(CV_SPEC *ZOcv)
{
	CV_SPEC ZIcv;

	switch (CURRENT_TERMINAL) {
	case 98:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cv_const */
			{
#line 898 "syntax.act"
 (ZIcv) = cv_const ; 
#line 2649 "syntax3.c"
			}
			/* END OF ACTION: cv_const */
		}
		break;
	case 124:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cv_volatile */
			{
#line 899 "syntax.act"
 (ZIcv) = cv_volatile ; 
#line 2661 "syntax3.c"
			}
			/* END OF ACTION: cv_volatile */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOcv = ZIcv;
}

void
ZRunary_Hoperator(void)
{
	switch (CURRENT_TERMINAL) {
	case 85:
		{
			ADVANCE_LEXER;
		}
		break;
	case 59:
		{
			ADVANCE_LEXER;
		}
		break;
	case 69:
		{
			ADVANCE_LEXER;
		}
		break;
	case 43:
		{
			/* BEGINNING OF INLINE: compl */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 43:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: compl */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRmember_Hdeclarator(TYPE ZIp, BASE_TYPE ZIq)
{
	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZI1036;
			IDENTIFIER ZI1037;
			TYPE ZI1033;
			IDENTIFIER ZIid;
			TYPE ZIt;

			ADVANCE_LEXER;
			ZRdeclarator_Haux (&ZI1036, &ZI1037);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1228 "syntax.act"

    if ( IS_NULL_type ( (ZI1036) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 2751 "syntax3.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR870 (ZI1036, ZI1037, &ZI1033, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1048 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1033) ) ? (ZIp) : inject_pre_type ( (ZI1033), (ZIp), 1 ) ) ;
#line 2771 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1198 "syntax.act"

    IDENTIFIER id = make_member_decl ( dspec_none, (ZIt), (ZIid), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2782 "syntax3.c"
			}
			/* END OF ACTION: declare_member */
		}
		break;
	case 1: case 2: case 4:
		{
			IDENTIFIER ZI1040;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 198 "syntax.act"

    ZI1040 = crt_token->pp_data.id.use ;
#line 2801 "syntax3.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 210 "syntax.act"

    ZI1040 = crt_token->pp_data.id.use ;
#line 2814 "syntax3.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 202 "syntax.act"

    ZI1040 = crt_token->pp_data.id.use ;
#line 2827 "syntax3.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: any-identifier */
			ZR1041 (&ZIp, &ZIq, &ZI1040);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 78:
		{
			TYPE ZI1034;
			TYPE ZI1035;
			IDENTIFIER ZIid;
			TYPE ZI1033;
			TYPE ZIt;

			ZRptr_Hoperator (&ZI1034);
			ZRdeclarator_Haux (&ZI1035, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1052 "syntax.act"

    (ZI1033) = ( IS_NULL_type ( (ZI1035) ) ? (ZI1034) : inject_pre_type ( (ZI1035), (ZI1034), 0 ) ) ;
#line 2864 "syntax3.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF ACTION: type_inject */
			{
#line 1048 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI1033) ) ? (ZIp) : inject_pre_type ( (ZI1033), (ZIp), 1 ) ) ;
#line 2872 "syntax3.c"
			}
			/* END OF ACTION: type_inject */
			/* BEGINNING OF ACTION: declare_member */
			{
#line 1198 "syntax.act"

    IDENTIFIER id = make_member_decl ( dspec_none, (ZIt), (ZIid), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2883 "syntax3.c"
			}
			/* END OF ACTION: declare_member */
		}
		break;
	case 41:
		{
			IDENTIFIER ZIid;
			EXP ZIc;
			TYPE ZIt;

			/* BEGINNING OF ACTION: id_anon */
			{
#line 390 "syntax.act"

    HASHID nm = lookup_anon () ;
    (ZIid) = DEREF_id ( hashid_id ( nm ) ) ;
#line 2900 "syntax3.c"
			}
			/* END OF ACTION: id_anon */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1223 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 2909 "syntax3.c"
			}
			/* END OF ACTION: declarator_begin */
			ADVANCE_LEXER;
			ZRconstant_Hexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_bitfield_mem */
			{
#line 1042 "syntax.act"

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (ZIid) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZIt) = make_bitfield_type ( (ZIp), (ZIq), (ZIc), z ) ;
#line 2926 "syntax3.c"
			}
			/* END OF ACTION: type_bitfield_mem */
			/* BEGINNING OF ACTION: declare_bitfield */
			{
#line 1212 "syntax.act"

    IDENTIFIER id = make_member_decl ( dspec_none, (ZIt), (ZIid), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 2937 "syntax3.c"
			}
			/* END OF ACTION: declare_bitfield */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRinitialiser_Hclause(IDENTIFIER ZId, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255:
		{
			ZRinitialiser_Hexpression (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 64:
		{
			SID_LIST_EXP ZIp;

			/* BEGINNING OF INLINE: open-brace */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 64:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: open-brace */
			ZR1074 (&ZId, &ZIp);
			/* BEGINNING OF INLINE: close-brace */
			{
				if ((CURRENT_TERMINAL) == 355) {
					RESTORE_LEXER;
					goto ZL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case 38:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: close-brace */
			/* BEGINNING OF ACTION: exp_aggregate */
			{
#line 439 "syntax.act"

    /* The expression type is a dummy */
    MAKE_exp_aggregate ( type_void, (ZIp), NULL_list ( OFFSET ), (ZIe) ) ;
#line 3014 "syntax3.c"
			}
			/* END OF ACTION: exp_aggregate */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRadditive_Hexpression(EXP *ZO915)
{
	EXP ZI915;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP ZIe;

		ZRmultiplicative_Hexpression (&ZIe);
		ZR916 (ZIe, &ZI915);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO915 = ZI915;
}

void
ZRdirect_Hdeclarator(TYPE *ZO868, IDENTIFIER *ZO869)
{
	TYPE ZI868;
	IDENTIFIER ZI869;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TYPE ZIt;
			IDENTIFIER ZIid;

			ADVANCE_LEXER;
			ZRdeclarator_Haux (&ZIt, &ZIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: declarator_bad */
			{
#line 1228 "syntax.act"

    if ( IS_NULL_type ( (ZIt) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
#line 3083 "syntax3.c"
			}
			/* END OF ACTION: declarator_bad */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR870 (ZIt, ZIid, &ZI868, &ZI869);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 2: case 4:
		{
			IDENTIFIER ZIid;
			TYPE ZIt;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 198 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3115 "syntax3.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 210 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3128 "syntax3.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 202 "syntax.act"

    ZIid = crt_token->pp_data.id.use ;
#line 3141 "syntax3.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: any-identifier */
			/* BEGINNING OF ACTION: type_none */
			{
#line 952 "syntax.act"

    (ZIt) = NULL_type ;
#line 3157 "syntax3.c"
			}
			/* END OF ACTION: type_none */
			/* BEGINNING OF ACTION: declarator_begin */
			{
#line 1223 "syntax.act"

    IDENTIFIER pid = underlying_id ( (ZIid) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
#line 3166 "syntax3.c"
			}
			/* END OF ACTION: declarator_begin */
			ZR870 (ZIt, ZIid, &ZI868, &ZI869);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO868 = ZI868;
	*ZO869 = ZI869;
}

void
ZRselection_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 109:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIc;
			EXP ZIa;
			EXP ZIbs;
			EXP ZIb;
			EXP ZId;
			EXP ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 846 "syntax.act"
 (ZIx) = crt_condition ; 
#line 3212 "syntax3.c"
			}
			/* END OF ACTION: condition_get */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3228 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			ZRopen_Hround_Hx ();
			ZRexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_if_begin */
			{
#line 735 "syntax.act"

    (ZIa) = begin_if_stmt ( (ZIc) ) ;
#line 3242 "syntax3.c"
			}
			/* END OF ACTION: stmt_if_begin */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 655 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 3257 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRscoped_Hstatement (ZIbs, &ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 3269 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_if_cont */
			{
#line 739 "syntax.act"

    (ZId) = cont_if_stmt ( (ZIa), (ZIb) ) ;
#line 3277 "syntax3.c"
			}
			/* END OF ACTION: stmt_if_cont */
			/* BEGINNING OF INLINE: 585 */
			{
				{
					EXP ZIfs;

					switch (CURRENT_TERMINAL) {
					case 103:
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: stmt_else */
					{
#line 748 "syntax.act"

    check_empty_stmt ( lex_else ) ;
#line 3297 "syntax3.c"
					}
					/* END OF ACTION: stmt_else */
					/* BEGINNING OF ACTION: stmt_compound_begin */
					{
#line 655 "syntax.act"

    (ZIfs) = begin_compound_stmt ( 1 ) ;
#line 3305 "syntax3.c"
					}
					/* END OF ACTION: stmt_compound_begin */
					ZRscoped_Hstatement (ZIfs, &ZIf);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto ZL3;
					}
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: stmt_no_else */
					{
#line 752 "syntax.act"

    report ( crt_loc, ERR_stmt_if_no_else () ) ;
    (ZIf) = NULL_exp ;
#line 3323 "syntax3.c"
					}
					/* END OF ACTION: stmt_no_else */
				}
			ZL2:;
			}
			/* END OF INLINE: 585 */
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 3334 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_if_end */
			{
#line 743 "syntax.act"

    (ZIe) = end_if_stmt ( (ZId), (ZIf) ) ;
#line 3342 "syntax3.c"
			}
			/* END OF ACTION: stmt_if_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 847 "syntax.act"
 crt_condition = (ZIx) ; 
#line 3349 "syntax3.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 3357 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 119:
		{
			int ZIr;
			EXP ZIc;
			EXP ZIa;
			int ZIex;
			EXP ZIbs;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 3385 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_switch_begin */
			{
#line 784 "syntax.act"

    (ZIa) = begin_switch_stmt ( (ZIc) ) ;
#line 3405 "syntax3.c"
			}
			/* END OF ACTION: stmt_switch_begin */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 588 */
			{
				switch (CURRENT_TERMINAL) {
				case 217:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: bool_true */
						{
#line 1406 "syntax.act"
 (ZIex) = 1 ; 
#line 3425 "syntax3.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 1405 "syntax.act"
 (ZIex) = 0 ; 
#line 3436 "syntax3.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 588 */
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 655 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 3449 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRscoped_Hstatement (ZIbs, &ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 3461 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_switch_end */
			{
#line 788 "syntax.act"

    (ZIe) = end_switch_stmt ( (ZIa), (ZIb), (ZIex) ) ;
#line 3469 "syntax3.c"
			}
			/* END OF ACTION: stmt_switch_end */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 3477 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 26:
		{
			ZRtarget_Hcondition (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 3494 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRexpression(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255:
		{
			EXP ZI1023;

			ZRassignment_Hexpression (&ZI1023);
			ZR1025 (&ZI1023, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 298: case 324:
		{
			EXP ZIa;
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRflow_Hexpression (&ZIa);
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 419 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 3552 "syntax3.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 469 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 3560 "syntax3.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	case 346:
		{
			EXP ZIa;
			SID_LIST_EXP ZIq;
			SID_LIST_EXP ZIp;

			ZRinset_Hflow_Hexpression (&ZIa);
			ZRcomma_Hexpression_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list_exp_cons */
			{
#line 419 "syntax.act"

    CONS_exp ( (ZIa), (ZIq), (ZIp) ) ;
#line 3582 "syntax3.c"
			}
			/* END OF ACTION: list_exp_cons */
			/* BEGINNING OF ACTION: exp_comma */
			{
#line 469 "syntax.act"

    (ZIe) = make_comma_exp ( (ZIp) ) ;
#line 3590 "syntax3.c"
			}
			/* END OF ACTION: exp_comma */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRstatement_Hseq_Hopt(EXP ZIc, int ZId, EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
ZL2_statement_Hseq_Hopt:;
	{
		EXP ZIa;
		EXP ZIb;

		/* BEGINNING OF ACTION: is_decl_statement */
		{
#line 1430 "syntax.act"

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) {
	if ( !(ZId) ) report ( crt_loc, ERR_stmt_dcl_start () ) ;
	in_declaration++ ;
    }
    (ZI0) = b ;
#line 3632 "syntax3.c"
		}
		/* END OF ACTION: is_decl_statement */
		if (!ZI0)
			goto ZL3;
		ZRdeclaration ();
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: stmt_decl */
		{
#line 681 "syntax.act"

    in_declaration-- ;
    (ZIa) = NULL_exp ;
#line 3648 "syntax3.c"
		}
		/* END OF ACTION: stmt_decl */
		/* BEGINNING OF ACTION: stmt_label_clear */
		{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 3656 "syntax3.c"
		}
		/* END OF ACTION: stmt_label_clear */
		/* BEGINNING OF ACTION: stmt_compound_add */
		{
#line 668 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3664 "syntax3.c"
		}
		/* END OF ACTION: stmt_compound_add */
		/* BEGINNING OF INLINE: statement-seq-opt */
		ZIc = ZIb;
		goto ZL2_statement_Hseq_Hopt;
		/* END OF INLINE: statement-seq-opt */
	}
	UNREACHED;
ZL3:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 4: case 17:
	case 18: case 19: case 20: case 21:
	case 22: case 23: case 24: case 26:
	case 33: case 43: case 59: case 61:
	case 62: case 64: case 65: case 69:
	case 71: case 77: case 78: case 85:
	case 95: case 96: case 99: case 100:
	case 101: case 107: case 108: case 109:
	case 113: case 116: case 119: case 125:
	case 126: case 170: case 206: case 210:
	case 223: case 255: case 289: case 298:
	case 323: case 324: case 346:
		{
			EXP ZIa;
			EXP ZIb;
			int ZIdb;

			ZRstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 668 "syntax.act"

    (ZIb) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3702 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_add */
			/* BEGINNING OF ACTION: bool_false */
			{
#line 1405 "syntax.act"
 (ZIdb) = 0 ; 
#line 3709 "syntax3.c"
			}
			/* END OF ACTION: bool_false */
			/* BEGINNING OF INLINE: statement-seq-opt */
			ZIc = ZIb;
			ZId = ZIdb;
			goto ZL2_statement_Hseq_Hopt;
			/* END OF INLINE: statement-seq-opt */
		}
		UNREACHED;
	default:
		{
			ZIe = ZIc;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRscoped_Hstmt_Hbody(EXP ZIc, EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 64:
		{
			int ZId;

			/* BEGINNING OF INLINE: open-brace */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 64:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: open-brace */
			/* BEGINNING OF ACTION: stmt_compound_block */
			{
#line 663 "syntax.act"

    COPY_int ( exp_sequence_block ( (ZIc) ), 2 ) ;
    (ZId) = 1 ;
#line 3762 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_block */
			ZRstatement_Hseq_Hopt (ZIc, ZId, &ZIe);
			/* BEGINNING OF INLINE: close-brace */
			{
				if ((CURRENT_TERMINAL) == 355) {
					RESTORE_LEXER;
					goto ZL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case 38:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: close-brace */
		}
		break;
	case 1: case 2: case 4: case 17:
	case 18: case 19: case 20: case 21:
	case 22: case 23: case 24: case 26:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 77: case 78: case 85: case 95:
	case 96: case 99: case 100: case 101:
	case 107: case 108: case 109: case 113:
	case 116: case 119: case 125: case 126:
	case 170: case 206: case 210: case 223:
	case 255: case 289: case 298: case 323:
	case 324: case 346:
		{
			EXP ZIa;

			ZRsimple_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_add */
			{
#line 668 "syntax.act"

    (ZIe) = add_compound_stmt ( (ZIc), (ZIa) ) ;
#line 3810 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_add */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR726(BASE_TYPE *ZIb1, TYPE *ZIt1, CV_SPEC *ZIcv1, DECL_SPEC *ZIds1, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv, DECL_SPEC *ZOds)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;
	DECL_SPEC ZIds;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		BASE_TYPE ZI1099;
		TYPE ZI1100;
		CV_SPEC ZI1101;
		DECL_SPEC ZI1102;
		BASE_TYPE ZIb2;
		TYPE ZIt2;
		CV_SPEC ZIcv2;
		DECL_SPEC ZIds2;

		/* BEGINNING OF ACTION: is_decl_specifier */
		{
#line 1423 "syntax.act"

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
#line 3855 "syntax3.c"
		}
		/* END OF ACTION: is_decl_specifier */
		if (!ZI0)
			goto ZL2;
		ZRdecl_Hspecifier (&ZI1099, &ZI1100, &ZI1101, &ZI1102);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: check_decl_specifier */
		{
#line 1474 "syntax.act"

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
#line 3873 "syntax3.c"
		}
		/* END OF ACTION: check_decl_specifier */
		ZR726 (&ZI1099, &ZI1100, &ZI1101, &ZI1102, &ZIb2, &ZIt2, &ZIcv2, &ZIds2);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: btype_join */
		{
#line 931 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 3890 "syntax3.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 977 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 3906 "syntax3.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 902 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 3916 "syntax3.c"
		}
		/* END OF ACTION: cv_join */
		/* BEGINNING OF ACTION: dspec_join */
		{
#line 1126 "syntax.act"

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (*ZIds1) & (ZIds2) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZIds) = ( (*ZIds1) | (ZIds2) ) ;
#line 3927 "syntax3.c"
		}
		/* END OF ACTION: dspec_join */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			ZIbt = *ZIb1;
			ZIt = *ZIt1;
			ZIcv = *ZIcv1;
			ZIds = *ZIds1;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
	*ZOds = ZIds;
}

void
ZRstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 64:
		{
			ZRcompound_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 1: case 2: case 4: case 17:
	case 18: case 19: case 20: case 21:
	case 22: case 23: case 24: case 26:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 77: case 78: case 85: case 95:
	case 96: case 99: case 100: case 101:
	case 107: case 108: case 109: case 113:
	case 116: case 119: case 125: case 126:
	case 170: case 206: case 210: case 223:
	case 255: case 289: case 298: case 323:
	case 324: case 346:
		{
			ZRsimple_Hstatement (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRdirect_Habstract_Hdeclarator(TYPE *ZO861)
{
	TYPE ZI861;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			ZR1058 (&ZI861);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 332:
		{
			IDENTIFIER ZIid;
			int ZIell;
			TYPE ZIt;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_none */
			{
#line 385 "syntax.act"

    (ZIid) = NULL_id ;
#line 4038 "syntax3.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: param_begin */
			{
#line 876 "syntax.act"

    func_type_defn ( 0 ) ;
    begin_param ( (ZIid) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
#line 4049 "syntax3.c"
			}
			/* END OF ACTION: param_begin */
			ZR760 (&ZIell);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_func_weak */
			{
#line 1020 "syntax.act"

    (ZIt) = make_func_type ( NULL_type, ( (ZIell) | FUNC_WEAK ), cv_c, empty_type_set ) ;
#line 4062 "syntax3.c"
			}
			/* END OF ACTION: type_func_weak */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: param_end */
			{
#line 885 "syntax.act"

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
#line 4079 "syntax3.c"
			}
			/* END OF ACTION: param_end */
			ZR862 (ZIt, &ZI861);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 66:
		{
			EXP ZIe;
			TYPE ZIt;

			/* BEGINNING OF INLINE: open-square */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 66:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: open-square */
			ZR759 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_array */
			{
#line 1032 "syntax.act"

    NAT n = make_array_dim ( (ZIe) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZIt) ) ;
#line 4118 "syntax3.c"
			}
			/* END OF ACTION: type_array */
			/* BEGINNING OF INLINE: close-square */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 40:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: close-square */
			ZR862 (ZIt, &ZI861);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO861 = ZI861;
}

void
ZR985(EXP *ZOe)
{
	EXP ZIe;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TYPE ZIt;
		int ZIn;
		EXP ZIa;
		EXP ZI963;
		EXP ZI962;
		EXP ZI961;
		EXP ZI960;
		EXP ZI959;
		EXP ZI958;
		EXP ZI957;
		EXP ZI956;
		EXP ZI955;
		EXP ZI954;
		EXP ZI953;
		EXP ZI950;

		/* BEGINNING OF ACTION: is_type_id_false */
		{
#line 1438 "syntax.act"

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
#line 4185 "syntax3.c"
		}
		/* END OF ACTION: is_type_id_false */
		if (!ZI0)
			goto ZL2;
		ZRtype_Hid (&ZIt, &ZIn);
		switch (CURRENT_TERMINAL) {
		case 39:
			break;
		case 355:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcast_Hexpression (&ZIa);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exp_cast */
		{
#line 465 "syntax.act"

    /* n is the number of type definitions in t */
    (ZI963) = make_cast_exp ( (ZIt), (ZIa), (ZIn) ) ;
#line 4212 "syntax3.c"
		}
		/* END OF ACTION: exp_cast */
		ZR920 (ZI963, &ZI962);
		ZR916 (ZI962, &ZI961);
		ZR912 (ZI961, &ZI960);
		ZR908 (ZI960, &ZI959);
		ZR904 (ZI959, &ZI958);
		ZR900 (ZI958, &ZI957);
		ZR896 (ZI957, &ZI956);
		ZR892 (ZI956, &ZI955);
		ZR888 (ZI955, &ZI954);
		ZR884 (ZI954, &ZI953);
		ZR880 (ZI953, &ZI950);
		ZR952 (&ZI950, &ZIe);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		}
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255: case 298:
	case 324: case 346:
		{
			EXP ZI1070;
			EXP ZI1071;
			EXP ZI1072;

			/* BEGINNING OF ACTION: exp_paren_begin */
			{
#line 564 "syntax.act"

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
#line 4253 "syntax3.c"
			}
			/* END OF ACTION: exp_paren_begin */
			ZRexpression (&ZI1070);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_paren_end */
			{
#line 567 "syntax.act"

    (ZI1071) = make_paren_exp ( (ZI1070) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
#line 4267 "syntax3.c"
			}
			/* END OF ACTION: exp_paren_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR924 (ZI1071, &ZI1072);
			ZR1013 (&ZI1072, &ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZR858(TYPE ZI854, IDENTIFIER ZI855, TYPE *ZO856, IDENTIFIER *ZO857)
{
	TYPE ZI856;
	IDENTIFIER ZI857;

ZL2_858:;
	switch (CURRENT_TERMINAL) {
	case 65: case 66: case 332:
		{
			IDENTIFIER ZIid;
			TYPE ZIq;
			TYPE ZIt;

			ZIid = ZI855;
			ZRabstract_Hdeclarator_Htail (&ZIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: type_build */
			{
#line 1052 "syntax.act"

    (ZIt) = ( IS_NULL_type ( (ZI854) ) ? (ZIq) : inject_pre_type ( (ZI854), (ZIq), 0 ) ) ;
#line 4321 "syntax3.c"
			}
			/* END OF ACTION: type_build */
			/* BEGINNING OF INLINE: 858 */
			ZI854 = ZIt;
			ZI855 = ZIid;
			goto ZL2_858;
			/* END OF INLINE: 858 */
		}
		UNREACHED;
	default:
		{
			ZI856 = ZI854;
			ZI857 = ZI855;
		}
		break;
	case 355:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZO856 = ZI856;
	*ZO857 = ZI857;
}

void
ZRiteration_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 101:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIa;
			EXP ZIbs;
			EXP ZIb;
			EXP ZIc0;
			EXP ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 846 "syntax.act"
 (ZIx) = crt_condition ; 
#line 4370 "syntax3.c"
			}
			/* END OF ACTION: condition_get */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4386 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_do_begin */
			{
#line 693 "syntax.act"

    (ZIa) = begin_do_stmt () ;
#line 4394 "syntax3.c"
			}
			/* END OF ACTION: stmt_do_begin */
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 655 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 4402 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRscoped_Hstatement (ZIbs, &ZIb);
			switch (CURRENT_TERMINAL) {
			case 125:
				break;
			case 355:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIc0);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 820 "syntax.act"

    (ZIc) = bind_temporary ( (ZIc0) ) ;
#line 4433 "syntax3.c"
			}
			/* END OF ACTION: bind_temporary */
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4440 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_do_end */
			{
#line 697 "syntax.act"

    (ZIe) = end_do_stmt ( (ZIa), (ZIb), (ZIc) ) ;
#line 4448 "syntax3.c"
			}
			/* END OF ACTION: stmt_do_end */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_set */
			{
#line 847 "syntax.act"
 crt_condition = (ZIx) ; 
#line 4462 "syntax3.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 4470 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			ZRsemicolon_Hx ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 107:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIf;
			EXP ZIa;
			EXP ZIg;
			EXP ZIc;
			EXP ZIds;
			EXP ZIb;
			EXP ZIh;
			EXP ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 846 "syntax.act"
 (ZIx) = crt_condition ; 
#line 4498 "syntax3.c"
			}
			/* END OF ACTION: condition_get */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4514 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_for_begin */
			{
#line 705 "syntax.act"

    (ZIf) = begin_for_stmt () ;
#line 4529 "syntax3.c"
			}
			/* END OF ACTION: stmt_for_begin */
			ZRfor_Hinit_Hstatement (&ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_for_init */
			{
#line 709 "syntax.act"

    (ZIg) = init_for_stmt ( (ZIf), &(ZIa) ) ;
#line 4542 "syntax3.c"
			}
			/* END OF ACTION: stmt_for_init */
			ZRfor_Hcond_Hstatement (&ZIc);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 655 "syntax.act"

    (ZIds) = begin_compound_stmt ( 1 ) ;
#line 4555 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRfor_Hend_Hstatement (&ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stmt_for_cond */
			{
#line 713 "syntax.act"

    (ZIh) = cond_for_stmt ( (ZIg), (ZIc), (ZIb) ) ;
#line 4568 "syntax3.c"
			}
			/* END OF ACTION: stmt_for_cond */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_mark */
			{
#line 659 "syntax.act"

    mark_compound_stmt ( (ZIds) ) ;
#line 4583 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_mark */
			ZRscoped_Hstatement (ZIds, &ZId);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4595 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_for_end */
			{
#line 717 "syntax.act"

    (ZIe) = end_for_stmt ( (ZIh), (ZId) ) ;
#line 4603 "syntax3.c"
			}
			/* END OF ACTION: stmt_for_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 847 "syntax.act"
 crt_condition = (ZIx) ; 
#line 4610 "syntax3.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 4618 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			/* BEGINNING OF ACTION: rescan_token */
			{
#line 1467 "syntax.act"

    RESCAN_LEXER ;
#line 4626 "syntax3.c"
			}
			/* END OF ACTION: rescan_token */
		}
		break;
	case 125:
		{
			unsigned ZIx;
			int ZIr;
			EXP ZIc0;
			EXP ZIc;
			EXP ZIa;
			EXP ZIbs;
			EXP ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: condition_get */
			{
#line 846 "syntax.act"
 (ZIx) = crt_condition ; 
#line 4646 "syntax3.c"
			}
			/* END OF ACTION: condition_get */
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4662 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			switch (CURRENT_TERMINAL) {
			case 65:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexpression (&ZIc0);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bind_temporary */
			{
#line 820 "syntax.act"

    (ZIc) = bind_temporary ( (ZIc0) ) ;
#line 4682 "syntax3.c"
			}
			/* END OF ACTION: bind_temporary */
			/* BEGINNING OF ACTION: stmt_while_begin */
			{
#line 792 "syntax.act"

    (ZIa) = begin_while_stmt ( (ZIc) ) ;
#line 4690 "syntax3.c"
			}
			/* END OF ACTION: stmt_while_begin */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_compound_begin */
			{
#line 655 "syntax.act"

    (ZIbs) = begin_compound_stmt ( 1 ) ;
#line 4705 "syntax3.c"
			}
			/* END OF ACTION: stmt_compound_begin */
			ZRscoped_Hstatement (ZIbs, &ZIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_prev */
			{
#line 842 "syntax.act"
 unreached_prev = (ZIr) ; 
#line 4717 "syntax3.c"
			}
			/* END OF ACTION: reach_prev */
			/* BEGINNING OF ACTION: stmt_while_end */
			{
#line 796 "syntax.act"

    (ZIe) = end_while_stmt ( (ZIa), (ZIb) ) ;
#line 4725 "syntax3.c"
			}
			/* END OF ACTION: stmt_while_end */
			/* BEGINNING OF ACTION: condition_set */
			{
#line 847 "syntax.act"
 crt_condition = (ZIx) ; 
#line 4732 "syntax3.c"
			}
			/* END OF ACTION: condition_set */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 4740 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
ZRassignment_Hoperator(void)
{
	switch (CURRENT_TERMINAL) {
	case 45:
		{
			ADVANCE_LEXER;
		}
		break;
	case 58:
		{
			ADVANCE_LEXER;
		}
		break;
	case 60:
		{
			ADVANCE_LEXER;
		}
		break;
	case 70:
		{
			ADVANCE_LEXER;
		}
		break;
	case 74:
		{
			ADVANCE_LEXER;
		}
		break;
	case 76:
		{
			ADVANCE_LEXER;
		}
		break;
	case 79:
		{
			ADVANCE_LEXER;
		}
		break;
	case 34:
		{
			/* BEGINNING OF INLINE: and-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 34:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: and-eq */
		}
		break;
	case 68:
		{
			/* BEGINNING OF INLINE: or-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 68:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or-eq */
		}
		break;
	case 81:
		{
			/* BEGINNING OF INLINE: xor-eq */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 81:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: xor-eq */
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (355);
	return;
}

void
ZRexpression_Hstatement(EXP *ZOe)
{
	EXP ZIe;

	switch (CURRENT_TERMINAL) {
	case 346:
		{
			ADVANCE_LEXER;
			ZR1080 (&ZIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: stmt_none */
			{
#line 639 "syntax.act"

    (ZIe) = NULL_exp ;
#line 4883 "syntax3.c"
			}
			/* END OF ACTION: stmt_none */
		}
		break;
	case 1: case 17: case 18: case 19:
	case 20: case 21: case 22: case 23:
	case 33: case 43: case 59: case 61:
	case 62: case 65: case 69: case 71:
	case 78: case 85: case 116: case 170:
	case 206: case 210: case 255:
		{
			EXP ZI1023;
			EXP ZIa;
			int ZIr;

			ZRassignment_Hexpression (&ZI1023);
			ZR1025 (&ZI1023, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4918 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 701 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4926 "syntax3.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 4934 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 298: case 324:
		{
			EXP ZI1075;
			EXP ZIa;
			int ZIr;

			ZRflow_Hexpression (&ZI1075);
			ZR1077 (&ZI1075, &ZIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: reach_check */
			{
#line 831 "syntax.act"

    (ZIr) = unreached_code ;
    if ( (ZIr) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
#line 4971 "syntax3.c"
			}
			/* END OF ACTION: reach_check */
			/* BEGINNING OF ACTION: stmt_exp */
			{
#line 701 "syntax.act"

    (ZIe) = make_exp_stmt ( (ZIa) ) ;
#line 4979 "syntax3.c"
			}
			/* END OF ACTION: stmt_exp */
			/* BEGINNING OF ACTION: stmt_label_clear */
			{
#line 769 "syntax.act"

    unreached_fall = 1 ;
#line 4987 "syntax3.c"
			}
			/* END OF ACTION: stmt_label_clear */
			switch (CURRENT_TERMINAL) {
			case 77:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 355:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (355);
	return;
ZL0:;
	*ZOe = ZIe;
}

/* END OF FILE */
