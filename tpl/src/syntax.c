/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 170 "syntax.act"



#include "config.h"
#include "util.h"
#include "defs.h"
#include "encodings.h"
#include "enc_nos.h"
#include "consfile.h"
#include "lex.h"
#include "analyse_sort.h"
#include "find_id.h"
#include "readstreams.h"
#include "standardsh.h"
#include "syntax.h"
#include "units.h"

#include <shared/xalloc.h>

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA unreachable code allow
#pragma TenDRA variable analysis off
#endif

static int saved = 0;
#define CURRENT_TERMINAL	(unsigned)lex_v.t
#define ADVANCE_LEXER		lex_v = reader()
#define SAVE_LEXER(e)		((saved = lex_v.t), (lex_v.t = (e)))
#define RESTORE_LEXER		(lex_v.t = saved)

typedef Al_tagdec *PTR_Al_tagdec;
typedef Labdec *PTR_Labdec;
typedef char *PTR_char;
typedef Tagdec *PTR_Tagdec;
typedef TDF *PTR_TDF;
typedef Tokdec *PTR_Tokdec;
typedef Tokpar *PTR_Tokpar;
typedef unsigned long unsigned_long;


static Tokpar *g_tokpars;
static Sort g_sname;
static TDF g_tok_defn;
static TokSort g_toksort;
int search_for_toks = 1;
static Tokdec *g_tokformals;
static int g_lastfield;
static TDF g_shape;
static TDF g_lastshape;

static Name *g_shtokname;
static int g_has_vis = 0;
static Bool issigned;
static Labdec *g_labdec;
static unsigned long intvalue;
static TDF optlab;
static TDF g_lower;
static TDF g_upper;
static Bool g_has_upper;
static TDF intro_acc;
static TDF intro_init;

static int query_t;
static int g_cr_v;
static int g_ce_v;
static int g_unt;
static Tagdec *g_app_tags;

static void
do_procprops(int i)
{
    switch (i) {
       case 0: return;
       case 1: OPTION(o_var_callers); return;
       case 2: OPTION(o_var_callees); return;
       case 3: OPTION(o_add_procprops(o_var_callers, o_var_callees)); return;
       case 4: OPTION(o_untidy); return;
       case 5: OPTION(o_add_procprops(o_var_callers, o_untidy)); return;
       case 6: OPTION(o_add_procprops(o_var_callees, o_untidy)); return;
       case 7: OPTION(o_add_procprops(o_var_callers,
		      o_add_procprops(o_var_callees, o_untidy))); return;
       case 8: OPTION(o_check_stack); return;
       case 9: OPTION(o_add_procprops(o_var_callers,o_check_stack)); return;
       case 10: OPTION(o_add_procprops(o_var_callees,o_check_stack)); return;
       case 11: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callers, o_var_callees))); return;
       case 12: OPTION(o_add_procprops(o_untidy,o_check_stack)); return;
       case 13: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callers, o_untidy))); return;
       case 14: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callees, o_untidy))); return;
       case 15: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callers,
		       o_add_procprops(o_var_callees, o_untidy)))); return;
    }
}

static int defaultlab = -1;
static TDF g_lablist;
int do_pp = 0;

static void
success(void)
{
    IGNORE printf("Reached end\n");
    print_res();
}

static int HAS_MAGIC = 1;
unsigned long MAJOR_NO = major_version;
unsigned long MINOR_NO = minor_version;


#line 128 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_label(void);
static void ZR641(PTR_Tokdec *);
static void ZRfull__sortname(void);
static void ZR643(int *);
static void ZR645(void);
extern void read_variety(void);
static void ZR646(void);
static void ZRtok__formal__list__opt(void);
static void ZR647(void);
static void ZR648(void);
static void ZR650(void);
static void ZRsortname__list(void);
static void ZRsignature__opt(void);
static void ZRexp__sequence(void);
static void ZRrange(void);
static void ZR654(void);
static void ZR655(TDF *, PTR_TDF *);
static void ZRrange__label__list(void);
static void ZR656(void);
extern void read_shape(void);
static void ZR657(void);
static void ZRaccess__list(void);
static void ZR660(TDF *, TDF *, TDF *, TDF *);
static void ZRtagshacc__list__opt(void);
static void ZR661(TDF *, PTR_TDF *);
static void ZRlabdest__opt(void);
static void ZR662(PTR_TDF *);
static void ZRalignment__list__opt(void);
static void ZR663(void);
extern void read_string(void);
static void ZR664(void);
static void ZRotagexp__list(void);
static void ZRvariety__sign(void);
static void ZR668(void);
static void ZR669(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
static void ZR670(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
extern void read_signed_nat(void);
static void ZR672(TDF *, TDF *, PTR_TDF *, PTR_char *);
extern void read_token(void);
static void ZR673(void);
static void ZRnat__not__int(void);
static void ZRshape__body(void);
static void ZRrepeat__starter__opt(void);
static void ZR674(void);
static void ZRfield__list(void);
static void ZR675(void);
static void ZR676(void);
static void ZR677(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *);
static void ZRrounding__mode__opt(void);
static void ZR678(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *);
static void ZRnonst__shape(void);
static void ZR679(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *);
static void ZRaccess__opt(void);
extern void read_error_code(void);
static void ZRpostlude__opt(void);
static void ZR680(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
static void ZRexponent__opt(void);
static void ZR681(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
static void ZRclosed__exp(void);
extern void read_bool(void);
static void ZRvarintro__opt(void);
extern void read_ntest(void);
extern void read_bitfield_variety(void);
static void ZRsigned__nat__body(void);
static void ZRlabset__opt(void);
static void ZRkeep__item(void);
static void ZRstruct__def(void);
static void ZRnonst__shape__body(void);
extern void read_tag(void);
static void ZRvariety__opt(void);
extern void read_nat_option(void);
static void ZRsortname__list__opt(void);
extern void read_floating_variety(void);
static void ZRtagshacc(void);
static void ZRelement__list__opt(void);
extern void read_nat(void);
extern void read_alignment(void);
static void ZRvarpar__opt(void);
static void ZRkeep__list(void);
static void ZRproc__def(void);
extern void read_error_code_list(void);
static void ZRcallee__var__opt(void);
static void ZRtag__dec(void);
static void ZRtag__intro(void);
extern void read_exp(void);
static void ZRtag__def(void);
static void ZRotagexp__list__opt(void);
static void ZRtok__formal__list(void);
static void ZRuntidy__opt(void);
static void ZRcaller__var__opt(void);
static void ZRproc__def__body(void);
static void ZRlabelled__list(void);
static void ZRoffset__exp__list(void);
static void ZRbitfield__sign(void);
static void ZRtok__dec(void);
static void ZRexp__comma__list(void);
static void ZRexp__body(void);
static void ZRtok__def(void);
static void ZRunary__exp(void);
static void ZRtagshacc__list(void);
static void ZRshapetok(void);
static void ZRalignment__list(void);
extern void read_error_treatment(void);
static void ZRcallee(void);
extern void read_al_tag(void);
extern void read_exp_list(void);
static void ZRelement(void);
static void ZR622(void);
static void ZRtok__def__body(void);
static void ZRinteger(void);
extern void read_transfer_mode(void);
extern void read_rounding_mode(void);
static void ZR625(void);
static void ZR626(void);
extern void read_access(void);
static void ZR627(void);
static void ZR628(void);
static void ZR629(void);
static void ZR630(void);
static void ZR632(void);
static void ZRkeep__list__opt(void);
static void ZR633(void);
static void ZRal__tag__def(void);
static void ZRotagexp(void);
extern void read_program(void);
static void ZR634(void);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

void
read_label(void)
{
ZL2_label:;
	switch (CURRENT_TERMINAL) {
	case 59:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: label */
			goto ZL2_label;
			/* END OF INLINE: label */
		}
		/*UNREACHED*/
	case 60:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 294 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 303 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 54:
		{
			/* BEGINNING OF ACTION: label1 */
			{
#line 1402 "syntax.act"

    char * n =lex_v.val.name;
    Labdec * x = find_lab(n);
    if (x== (Labdec*)0) {
	x = xmalloc(sizeof *x);
	x->idname.id = n; x->idname.name.unit_name = next_label();
	x->declared = 0;
	x->next = labdecs; labdecs = x;
    }
    g_labdec = x;
    o_make_label(out_tdfint32(LOCNAME(x->idname)));
#line 324 "syntax.c"
			}
			/* END OF ACTION: label1 */
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 343 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR641(PTR_Tokdec *ZI640)
{
	switch (CURRENT_TERMINAL) {
	case 43:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((*ZI640), &(*ZI640)->sort);
#line 361 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 100:
		{
			TDF ZIa;
			TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((*ZI640), &(*ZI640)->sort);
#line 377 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 387 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 409 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRfull__sortname(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		/* BEGINNING OF ACTION: sortname1 */
		{
#line 1806 "syntax.act"

    g_sname.sort = lex_v.t;
#line 444 "syntax.c"
		}
		/* END OF ACTION: sortname1 */
		/* BEGINNING OF INLINE: sortname */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					ADVANCE_LEXER;
				}
				break;
			case 8:
				{
					ADVANCE_LEXER;
				}
				break;
			case 14:
				{
					ADVANCE_LEXER;
				}
				break;
			case 17:
				{
					ADVANCE_LEXER;
				}
				break;
			case 39:
				{
					ADVANCE_LEXER;
				}
				break;
			case 42:
				{
					ADVANCE_LEXER;
				}
				break;
			case 48:
				{
					ADVANCE_LEXER;
				}
				break;
			case 59:
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
			case 90:
				{
					ADVANCE_LEXER;
				}
				break;
			case 95:
				{
					ADVANCE_LEXER;
				}
				break;
			case 99:
				{
					ADVANCE_LEXER;
				}
				break;
			case 105:
				{
					ADVANCE_LEXER;
				}
				break;
			case 110:
				{
					ADVANCE_LEXER;
				}
				break;
			case 116:
				{
					ADVANCE_LEXER;
				}
				break;
			case 119:
				{
					ADVANCE_LEXER;
				}
				break;
			case 127:
				{
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: sortname */
		ZR674 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR643(int *ZI642)
{
	switch (CURRENT_TERMINAL) {
	case 41:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(*ZI642)].f)();
#line 574 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 98:
		{
			TDF ZIa;
			TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(*ZI642)].f)();
#line 590 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 600 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 622 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR645(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expneg1_dec */
			{
#line 741 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 660 "syntax.c"
			}
			/* END OF ACTION: expneg1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expnegate2 */
			{
#line 745 "syntax.act"

    RESET_TDF((ZIb));
    o_negate(o_wrap, append_TDF(&(ZIa),1));
#line 674 "syntax.c"
			}
			/* END OF ACTION: expnegate2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 22: case 55: case 69: case 70:
	case 71:
		{
			TDF ZIa;
			TDF ZIb;

			ZR634 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 704 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 726 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 44:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			int ZIf;
			unsigned_long ZIg;

			/* BEGINNING OF ACTION: fden2_dec */
			{
#line 922 "syntax.act"

    /* (ZIc), (ZId) uninitialised */
    (ZIf) = 1;
    (ZIg) = UL(radix);
    SET_TDF((ZIe), &(ZIa));
    out_tdfstring_bytes(fformat(lex_v.val.name,lnum), 8, UI(lnum));
    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 759 "syntax.c"
			}
			/* END OF ACTION: fden2_dec */
			ADVANCE_LEXER;
			ZRexponent__opt ();
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: fden3 */
			{
#line 932 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
#line 780 "syntax.c"
			}
			/* END OF ACTION: fden3 */
			read_floating_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden4 */
			{
#line 937 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
#line 794 "syntax.c"
			}
			/* END OF ACTION: fden4 */
			ZRrounding__mode__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden5 */
			{
#line 942 "syntax.act"

    RESET_TDF((ZIe));
    o_make_floating(append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1),
		    if ((ZIf)) { o_true; } else { o_false; },
		    o_make_string(append_TDF(&(ZIa), 1)),
		    o_make_nat(out_tdfint32((ZIg))),
		    append_TDF(&(ZIb), 1));
#line 813 "syntax.c"
			}
			/* END OF ACTION: fden5 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_variety(void)
{
ZL2_variety:;
	switch (CURRENT_TERMINAL) {
	case 127:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 649 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: variety */
						goto ZL2_variety;
						/* END OF INLINE: variety */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 869 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 890 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_variety ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 911 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_variety ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: variety1 */
						{
#line 2324 "syntax.act"

    RESET_TDF((ZId));
    o_var_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
#line 933 "syntax.c"
						}
						/* END OF ACTION: variety1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 649 */
		}
		break;
	case 21: case 56: case 64: case 97:
	case 101: case 121:
		{
			ZRvariety__sign ();
			ZR650 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 126:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 972 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 981 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 128:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 996 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 1005 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 10: case 22: case 55: case 62:
	case 68: case 98: case 99: case 100:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: variety2_dec */
			{
#line 2330 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 1023 "syntax.c"
			}
			/* END OF ACTION: variety2_dec */
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: variety3 */
			{
#line 2335 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 1037 "syntax.c"
			}
			/* END OF ACTION: variety3 */
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: variety4 */
			{
#line 2340 "syntax.act"

    RESET_TDF((ZIc));
    o_var_limits(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 1058 "syntax.c"
			}
			/* END OF ACTION: variety4 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 1076 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR646(void)
{
	switch (CURRENT_TERMINAL) {
	case 79:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;

			/* BEGINNING OF ACTION: call1_dec */
			{
#line 323 "syntax.act"

    /* (ZIb), (ZIc), (ZId) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 1100 "syntax.c"
			}
			/* END OF ACTION: call1_dec */
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: call2 */
			{
#line 329 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
#line 1115 "syntax.c"
			}
			/* END OF ACTION: call2 */
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR660 (&ZIa, &ZIb, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 112:
		{
			TDF ZIa;

			/* BEGINNING OF ACTION: tcall1_dec */
			{
#line 2124 "syntax.act"

    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 1142 "syntax.c"
			}
			/* END OF ACTION: tcall1_dec */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 79:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcallee ();
			ZRcallee__var__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tcall2 */
			{
#line 2133 "syntax.act"

    TDF cees;
    cees = *current_TDF;
    INIT_TDF(current_TDF);
    o_tail_call(do_procprops(g_ce_v*2),
		append_TDF(&(ZIa),1), append_TDF(&cees,1));
#line 1168 "syntax.c"
			}
			/* END OF ACTION: tcall2 */
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtok__formal__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 54:
		{
			ZRtok__formal__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: tok_fml_opt1 */
			{
#line 2305 "syntax.act"

    g_tokpars = (Tokpar*)0;
#line 1211 "syntax.c"
			}
			/* END OF ACTION: tok_fml_opt1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR647(void)
{
	switch (CURRENT_TERMINAL) {
	case 54:
		{
			/* BEGINNING OF ACTION: expstar1 */
			{
#line 826 "syntax.act"

    char * n = lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x == (Tagdec*)0) { fail("%s is not a tag", n); }
    else
    if (!x->isvar || x->hassh == 0) {
	fail("Don't know shape of %s", n);
    }
    o_contents(
	if (x->hassh == 1) {
	    o_shape_apply_token(make_tok(&x->sh.shtok), {});
	} else { append_TDF(&x->sh.tdfsh, 0); },
	o_obtain_tag(make_tag(&x->idname.name)));
#line 1247 "syntax.c"
			}
			/* END OF ACTION: expstar1 */
			ADVANCE_LEXER;
		}
		break;
	case 78:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: expstar2_dec */
			{
#line 829 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 1265 "syntax.c"
			}
			/* END OF ACTION: expstar2_dec */
			ADVANCE_LEXER;
			read_shape ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expstar3 */
			{
#line 834 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 1286 "syntax.c"
			}
			/* END OF ACTION: expstar3 */
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expstar4 */
			{
#line 839 "syntax.act"

    RESET_TDF((ZIc));
    o_contents(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 1300 "syntax.c"
			}
			/* END OF ACTION: expstar4 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR648(void)
{
	switch (CURRENT_TERMINAL) {
	case 76:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;
			PTR_Labdec ZIf;

			/* BEGINNING OF ACTION: expcond1_dec */
			{
#line 627 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = defaultlab;
    (ZIf) = labdecs;
    defaultlab = -1;
    SET_TDF((ZId), &(ZIa));
#line 1338 "syntax.c"
			}
			/* END OF ACTION: expcond1_dec */
			ADVANCE_LEXER;
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond2 */
			{
#line 635 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 1353 "syntax.c"
			}
			/* END OF ACTION: expcond2 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRlabset__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond3 */
			{
#line 640 "syntax.act"

    (ZIc) = optlab;
    defaultlab = (ZIe);
    tidy_labels((ZIf));
#line 1375 "syntax.c"
			}
			/* END OF ACTION: expcond3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond4 */
			{
#line 646 "syntax.act"

    INIT_TDF((ZId));
    RESET_TDF((ZId));
    o_conditional(append_TDF(&(ZIc),1),
		  append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 1391 "syntax.c"
			}
			/* END OF ACTION: expcond4 */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 78:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;

			/* BEGINNING OF ACTION: query_type1 */
			{
#line 1596 "syntax.act"

    query_t = lex_query;
#line 1416 "syntax.c"
			}
			/* END OF ACTION: query_type1 */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 866 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 1427 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 872 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 1441 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 877 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 1455 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 882 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
#line 1495 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR650(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietychar */
			{
#line 2350 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSC:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSC:MAXUSC))));
#line 1534 "syntax.c"
			}
			/* END OF ACTION: varietychar */
		}
		break;
	case 56:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietyint */
			{
#line 2358 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSI:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSI:MAXUSI))));
#line 1551 "syntax.c"
			}
			/* END OF ACTION: varietyint */
		}
		break;
	case 64:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietylong */
			{
#line 2366 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSL:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSL:MAXUSL))));
#line 1568 "syntax.c"
			}
			/* END OF ACTION: varietylong */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietyshort */
			{
#line 2381 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSS:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSS:MAXUSS))));
#line 1585 "syntax.c"
			}
			/* END OF ACTION: varietyshort */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRsortname__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		ZRfull__sortname ();
		ZR673 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRsignature__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 85: case 104: case 105: case 107:
		{
			read_string ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: newstr_opt1 */
			{
#line 1490 "syntax.act"

    current_TDF->no=1;
#line 1637 "syntax.c"
			}
			/* END OF ACTION: newstr_opt1 */
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRexp__sequence(void)
{
	switch (CURRENT_TERMINAL) {
	case 10: case 19: case 22: case 28:
	case 41: case 42: case 43: case 44:
	case 45: case 52: case 54: case 55:
	case 58: case 61: case 62: case 68:
	case 76: case 77: case 78: case 79:
	case 81: case 82: case 84: case 85:
	case 86: case 88: case 98: case 99:
	case 100: case 102: case 103: case 104:
	case 105: case 107: case 109: case 110:
	case 111: case 124:
		{
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_sls2 */
			{
#line 600 "syntax.act"

    current_TDF->no =1;
#line 1678 "syntax.c"
			}
			/* END OF ACTION: exp_sls2 */
			ZR628 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_sls1 */
			{
#line 596 "syntax.act"

    current_TDF->no =1;
    o_make_top;
#line 1696 "syntax.c"
			}
			/* END OF ACTION: exp_sls1 */
			ZR628 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRrange(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_TDF ZIa;

		/* BEGINNING OF ACTION: range1_dec */
		{
#line 1615 "syntax.act"

    SET_TDF((ZIa), &g_lower);
#line 1729 "syntax.c"
		}
		/* END OF ACTION: range1_dec */
		ZRsigned__nat__body ();
		ZR662 (&ZIa);
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR654(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapechar */
			{
#line 1676 "syntax.act"

    Name * shtok = tokforcharsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1758 "syntax.c"
			}
			/* END OF ACTION: shapechar */
		}
		break;
	case 56:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapeint */
			{
#line 1691 "syntax.act"

    Name * shtok = tokforintsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1772 "syntax.c"
			}
			/* END OF ACTION: shapeint */
		}
		break;
	case 64:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapelong */
			{
#line 1696 "syntax.act"

    Name * shtok = tokforlongsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1786 "syntax.c"
			}
			/* END OF ACTION: shapelong */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapeshort */
			{
#line 1706 "syntax.act"

    Name * shtok = tokforshortsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1800 "syntax.c"
			}
			/* END OF ACTION: shapeshort */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR655(TDF *ZIa, PTR_TDF *ZIb)
{
	switch (CURRENT_TERMINAL) {
	case 24:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: otagexp3 */
			{
#line 1563 "syntax.act"

    char* n = lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    x = xmalloc(sizeof *x); x->isdeffed = 1; x->hassh=0; x->iskept=0;
    NEW_IDNAME(x->idname, n, tag_ent);
    x->isvar = 1;
    x->next = g_app_tags; g_app_tags = x;
    RESET_TDF((*ZIb));
    o_make_otagexp(OPTION(make_tag(&x->idname.name)),append_TDF(&(*ZIa),1));
#line 1836 "syntax.c"
			}
			/* END OF ACTION: otagexp3 */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: otagexp2 */
			{
#line 1551 "syntax.act"

    RESET_TDF((*ZIb));
    o_make_otagexp({}, append_TDF(&(*ZIa),1));
#line 1856 "syntax.c"
			}
			/* END OF ACTION: otagexp2 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRrange__label__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;

		/* BEGINNING OF ACTION: rllist1_dec */
		{
#line 1635 "syntax.act"

    SET_TDF((ZIb),&(ZIa));
#line 1885 "syntax.c"
		}
		/* END OF ACTION: rllist1_dec */
		ZRrange ();
		switch (CURRENT_TERMINAL) {
		case 51:
			break;
		case 130:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		read_label ();
		ZR661 (&ZIa, &ZIb);
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR656(void)
{
	switch (CURRENT_TERMINAL) {
	case 10: case 19: case 22: case 28:
	case 41: case 42: case 43: case 44:
	case 45: case 52: case 54: case 55:
	case 58: case 61: case 62: case 68:
	case 76: case 77: case 78: case 79:
	case 81: case 82: case 84: case 85:
	case 86: case 88: case 98: case 99:
	case 100: case 102: case 103: case 104:
	case 105: case 107: case 109: case 110:
	case 111: case 124:
		{
			ZRexp__comma__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_shape(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		int ZIc;

		/* BEGINNING OF ACTION: genhold1_dec */
		{
#line 1086 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
#line 1964 "syntax.c"
		}
		/* END OF ACTION: genhold1_dec */
		ZRshape__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: genhold2 */
		{
#line 1093 "syntax.act"

    if (!(ZIc)) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
#line 1981 "syntax.c"
		}
		/* END OF ACTION: genhold2 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 1993 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR657(void)
{
	switch (CURRENT_TERMINAL) {
	case 23:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: untidy3 */
			{
#line 2317 "syntax.act"

    g_unt = 3;
#line 2011 "syntax.c"
			}
			/* END OF ACTION: untidy3 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: untidy2 */
			{
#line 2313 "syntax.act"

    g_unt = 1;
#line 2023 "syntax.c"
			}
			/* END OF ACTION: untidy2 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZRaccess__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		read_access ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: acc_l1 */
		{
#line 189 "syntax.act"

    current_TDF->no=1;
#line 2050 "syntax.c"
		}
		/* END OF ACTION: acc_l1 */
		ZR627 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR660(TDF *ZIa, TDF *ZIb, TDF *ZIc, TDF *ZId)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			ADVANCE_LEXER;
			read_exp_list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: call3 */
			{
#line 334 "syntax.act"

    (*ZIc) = *current_TDF;
    INIT_TDF(current_TDF);
#line 2083 "syntax.c"
			}
			/* END OF ACTION: call3 */
			ZRvarpar__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: call4 */
			{
#line 339 "syntax.act"

    (*ZId) = *current_TDF;
    INIT_TDF(current_TDF);
    o_apply_proc(append_TDF(&(*ZIb),1), append_TDF(&(*ZIa),1),
	    { append_TDF(&(*ZIc), 1); current_TDF->no = (*ZIc).no; },
	      if ((*ZId).no !=0) { OPTION(append_TDF(&(*ZId),1)); }
	   );
#line 2101 "syntax.c"
			}
			/* END OF ACTION: call4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 79:
		{
			TDF ZIe;
			TDF ZIf;
			TDF ZIg;
			int ZIh;
			int ZIi;
			PTR_Tagdec ZIj;
			PTR_Tagdec ZIk;
			PTR_Tagdec ZIl;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gcall1_dec */
			{
#line 1023 "syntax.act"

    /* (ZIe), (ZIf), (ZIg) uninitialised */
    /* (ZIh), (ZIi), (ZIk) uninitialised */
    (ZIj) = g_app_tags;
    (ZIl) = tagdecs;
    g_app_tags = (Tagdec*)0;
#line 2134 "syntax.c"
			}
			/* END OF ACTION: gcall1_dec */
			ZRotagexp__list__opt ();
			ZRcaller__var__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gcall2 */
			{
#line 1031 "syntax.act"

    (ZIe) = *current_TDF;
    INIT_TDF(current_TDF);
    (ZIh) = g_cr_v;
    (ZIk) = g_app_tags;
    g_app_tags = (ZIj);
#line 2152 "syntax.c"
			}
			/* END OF ACTION: gcall2 */
			switch (CURRENT_TERMINAL) {
			case 93:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcallee ();
			ZRcallee__var__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gcall3 */
			{
#line 1039 "syntax.act"

    (ZIf) = *current_TDF;
    (ZIi) = g_ce_v;
    INIT_TDF(current_TDF);
    while ((ZIk) != (Tagdec*)0) {
	Tagdec * x = (ZIk);
	(ZIk) = x->next;
	x->next = tagdecs;
	tagdecs = x;
    }
#line 2181 "syntax.c"
			}
			/* END OF ACTION: gcall3 */
			ZRpostlude__opt ();
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRuntidy__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gcall4 */
			{
#line 1051 "syntax.act"

    (ZIg) = *current_TDF;
    INIT_TDF(current_TDF);
    tagdecs = (ZIl);
    o_apply_general_proc(
	append_TDF(&(*ZIb),1), do_procprops((ZIh)+2*(ZIi)+4*g_unt),
	append_TDF(&(*ZIa),1),
	{ append_TDF(&(ZIe),1); current_TDF->no = (ZIe).no; },
	append_TDF(&(ZIf),1),
	append_TDF(&(ZIg), 1))
#line 2213 "syntax.c"
			}
			/* END OF ACTION: gcall4 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtagshacc__list__opt(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		/* BEGINNING OF ACTION: tagshacc_l1 */
		{
#line 2117 "syntax.act"

    current_TDF->no =0;
#line 2241 "syntax.c"
		}
		/* END OF ACTION: tagshacc_l1 */
		ZR664 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR661(TDF *ZIa, PTR_TDF *ZIb)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: rllist2 */
			{
#line 1639 "syntax.act"

    RESET_TDF((*ZIb));
    o_make_caselim(append_TDF(&(*ZIa),1),
		   append_TDF(&g_lower, g_has_upper),
		   append_TDF(&g_upper,1));
    current_TDF->no = 1;
#line 2271 "syntax.c"
			}
			/* END OF ACTION: rllist2 */
		}
		break;
	case 25:
		{
			/* BEGINNING OF ACTION: rllist3 */
			{
#line 1647 "syntax.act"

    RESET_TDF((*ZIb));
    o_make_caselim(append_TDF(&(*ZIa),1),
		   append_TDF(&g_lower, g_has_upper),
		   append_TDF(&g_upper,1));
#line 2286 "syntax.c"
			}
			/* END OF ACTION: rllist3 */
			ADVANCE_LEXER;
			ZRrange__label__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: rllist4 */
			{
#line 1655 "syntax.act"

    current_TDF->no++;
#line 2300 "syntax.c"
			}
			/* END OF ACTION: rllist4 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRlabdest__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 11:
		{
			PTR_TDF ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dest_o1_dec */
			{
#line 452 "syntax.act"

    SET_TDF((ZIa), &optlab);
#line 2328 "syntax.c"
			}
			/* END OF ACTION: dest_o1_dec */
			read_label ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: dest_opt2 */
			{
#line 456 "syntax.act"

    RESET_TDF((ZIa));
#line 2341 "syntax.c"
			}
			/* END OF ACTION: dest_opt2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lset_o1 */
			{
#line 1439 "syntax.act"

    TDF * hold;
    SET_TDF(hold, &optlab);
    if (defaultlab==-1)defaultlab = next_label();
    o_make_label(out_tdfint32(UL(defaultlab)));
    RESET_TDF(hold);
#line 2357 "syntax.c"
			}
			/* END OF ACTION: lset_o1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR662(PTR_TDF *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 24:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: range3 */
			{
#line 1625 "syntax.act"

    RESET_TDF((*ZIa));
    SET_TDF((*ZIa), &g_upper);
#line 2384 "syntax.c"
			}
			/* END OF ACTION: range3 */
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: range4 */
			{
#line 1630 "syntax.act"

    RESET_TDF((*ZIa));
    g_has_upper=1;
#line 2398 "syntax.c"
			}
			/* END OF ACTION: range4 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: range2 */
			{
#line 1619 "syntax.act"

    RESET_TDF((*ZIa));
    g_upper = g_lower;
    g_has_upper=0;
#line 2412 "syntax.c"
			}
			/* END OF ACTION: range2 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRalignment__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: al_list_opt1 */
			{
#line 231 "syntax.act"

    o_alignment(o_top);
#line 2437 "syntax.c"
			}
			/* END OF ACTION: al_list_opt1 */
		}
		break;
	case 4: case 5: case 7: case 8:
	case 9: case 54: case 78:
		{
			TDF ZIa;
			PTR_TDF ZIb;
			int ZIc;

			/* BEGINNING OF ACTION: genhold1_dec */
			{
#line 1086 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
#line 2457 "syntax.c"
			}
			/* END OF ACTION: genhold1_dec */
			ZRalignment__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: genhold2 */
			{
#line 1093 "syntax.act"

    if (!(ZIc)) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
#line 2474 "syntax.c"
			}
			/* END OF ACTION: genhold2 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR663(void)
{
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			ADVANCE_LEXER;
			ZRoffset__exp__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: offexpl2 */
			{
#line 1532 "syntax.act"

    current_TDF->no+=2;
#line 2505 "syntax.c"
			}
			/* END OF ACTION: offexpl2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: offexpl1 */
			{
#line 1528 "syntax.act"

    current_TDF->no = 2;
#line 2517 "syntax.c"
			}
			/* END OF ACTION: offexpl1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_string(void)
{
ZL2_string:;
	switch (CURRENT_TERMINAL) {
	case 105:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 631 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: string */
						goto ZL2_string;
						/* END OF INLINE: string */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 2564 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 2585 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_string ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 2612 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_string ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: newstring2 */
						{
#line 1498 "syntax.act"

    RESET_TDF((ZId));
    o_string_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		  append_TDF(&(ZIc),1));
#line 2627 "syntax.c"
						}
						/* END OF ACTION: newstring2 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 631 */
		}
		break;
	case 104:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 2655 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 2664 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 107:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 2679 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 2688 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 85:
		{
			/* BEGINNING OF ACTION: newstring1 */
			{
#line 1495 "syntax.act"

    char * s = lex_v.val.name;
    o_make_string(out_tdfstring_bytes(s, 8, UI(strlen(s))));
#line 2701 "syntax.c"
			}
			/* END OF ACTION: newstring1 */
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 2720 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR664(void)
{
	switch (CURRENT_TERMINAL) {
	case 54:
		{
			ZRtagshacc__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRotagexp__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		ZRotagexp ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: otagel1 */
		{
#line 1536 "syntax.act"

    current_TDF->no = 1;
#line 2767 "syntax.c"
		}
		/* END OF ACTION: otagel1 */
		ZR626 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRvariety__sign(void)
{
	switch (CURRENT_TERMINAL) {
	case 101:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: signedornot1 */
			{
#line 1792 "syntax.act"

    issigned = 1;
#line 2794 "syntax.c"
			}
			/* END OF ACTION: signedornot1 */
		}
		break;
	case 121:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: signedornot2 */
			{
#line 1796 "syntax.act"

    issigned = 0;
#line 2807 "syntax.c"
			}
			/* END OF ACTION: signedornot2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: signedornot1 */
			{
#line 1792 "syntax.act"

    issigned = 1;
#line 2819 "syntax.c"
			}
			/* END OF ACTION: signedornot1 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZR668(void)
{
	switch (CURRENT_TERMINAL) {
	case 11:
		{
			ADVANCE_LEXER;
			ZRlabelled__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: llist4 */
			{
#line 1426 "syntax.act"

    g_lablist.no++;
#line 2846 "syntax.c"
			}
			/* END OF ACTION: llist4 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: llist3 */
			{
#line 1422 "syntax.act"

    g_lablist.no = 1;
#line 2858 "syntax.c"
			}
			/* END OF ACTION: llist3 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR669(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIe)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			/* BEGINNING OF ACTION: intro2 */
			{
#line 1187 "syntax.act"

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZIb));
    (*ZIe) = g_has_vis;
#line 2885 "syntax.c"
			}
			/* END OF ACTION: intro2 */
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro4 */
			{
#line 1199 "syntax.act"

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
#line 2910 "syntax.c"
			}
			/* END OF ACTION: intro4 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: intro3 */
			{
#line 1193 "syntax.act"

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZId)->sh.tdfsh);
    (*ZId)->hassh=2;
#line 2924 "syntax.c"
			}
			/* END OF ACTION: intro3 */
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro2 */
			{
#line 1187 "syntax.act"

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZIb));
    (*ZIe) = g_has_vis;
#line 2940 "syntax.c"
			}
			/* END OF ACTION: intro2 */
			ZR670 (ZIa, ZIb, ZIc, ZId, ZIe);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR670(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIe)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro4 */
			{
#line 1199 "syntax.act"

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
#line 2989 "syntax.c"
			}
			/* END OF ACTION: intro4 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: intro6 */
			{
#line 1229 "syntax.act"

    o_make_value(append_TDF(&(*ZId)->sh.tdfsh, 0));
#line 3001 "syntax.c"
			}
			/* END OF ACTION: intro6 */
			/* BEGINNING OF ACTION: intro4 */
			{
#line 1199 "syntax.act"

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
#line 3020 "syntax.c"
			}
			/* END OF ACTION: intro4 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_signed_nat(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		ZRsigned__nat__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 3055 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR672(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_char *ZId)
{
	switch (CURRENT_TERMINAL) {
	case 3:
		{
			ADVANCE_LEXER;
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp2 */
			{
#line 508 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId), "*+.") ==0) {
	o_add_to_ptr(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "*-*") ==0) {
	o_subtract_ptrs(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".*") ==0) {
	o_offset_mult(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".+.") ==0) {
	o_offset_add(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".-.") ==0) {
	o_offset_subtract(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "./") ==0) {
	o_offset_div_by_int(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "./.") ==0) {
	o_offset_div(
	    o_var_limits(
		o_make_signed_nat(out_tdfbool(1), out_tdfint32(UL(MINSI))),
		o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(MAXSI)))),
	    append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".max.") ==0) {
	o_offset_max(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else { fail("%s not an addrop", (*ZId)); }
#line 3100 "syntax.c"
			}
			/* END OF ACTION: exp2 */
		}
		break;
	case 36:
		{
			ADVANCE_LEXER;
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp6 */
			{
#line 588 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    o_assign(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
#line 3120 "syntax.c"
			}
			/* END OF ACTION: exp6 */
		}
		break;
	case 63:
		{
			ADVANCE_LEXER;
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp3 */
			{
#line 534 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId), "And") ==0) {
	o_and(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "Or") ==0) {
	o_or(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "Xor") ==0) {
	o_xor(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else { fail("%s not a logop", (*ZId)); }
#line 3146 "syntax.c"
			}
			/* END OF ACTION: exp3 */
		}
		break;
	case 10: case 68: case 103:
		{
			/* BEGINNING OF INLINE: binop */
			{
				switch (CURRENT_TERMINAL) {
				case 10:
					{
						ADVANCE_LEXER;
					}
					break;
				case 68:
					{
						ADVANCE_LEXER;
					}
					break;
				case 103:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: binop */
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp5 */
			{
#line 546 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId),"%") ==0) {
	o_rem2(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"%1") ==0) {
	o_rem1(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"*") ==0) {
	o_mult(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"+") ==0) {
	o_plus(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"-") ==0) {
	o_minus(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"/") ==0) {
	o_div2(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"/1") ==0) {
	o_div1(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"<<") ==0) {
	o_shift_left(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F*") ==0) {
	o_floating_mult(o_continue,
	    { LIST_ELEM(append_TDF(&(*ZIa),1));
	    LIST_ELEM(append_TDF(&(*ZIb),1))});
    } else if (strcmp((*ZId),">>") ==0) {
	o_shift_right(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F+") ==0) {
	o_floating_plus(o_continue,
	    { LIST_ELEM(append_TDF(&(*ZIa),1));
	    LIST_ELEM(append_TDF(&(*ZIb),1))});
    } else if (strcmp((*ZId),"F-") ==0) {
	o_floating_minus(o_continue, append_TDF(&(*ZIa),1),
			 append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F/") ==0) {
	o_floating_div(o_continue, append_TDF(&(*ZIa),1),
		       append_TDF(&(*ZIb),1));
    } else { fail("%s not an arithop", (*ZId)); }
#line 3224 "syntax.c"
			}
			/* END OF ACTION: exp5 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_token(void)
{
ZL2_token:;
	switch (CURRENT_TERMINAL) {
	case 116:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: token */
			goto ZL2_token;
			/* END OF INLINE: token */
		}
		/*UNREACHED*/
	case 123:
		{
			TDF ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tok2_dec */
			{
#line 2167 "syntax.act"

    (ZIa) = g_tok_defn;
#line 3270 "syntax.c"
			}
			/* END OF ACTION: tok2_dec */
			ZRtok__def__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tok3 */
			{
#line 2172 "syntax.act"

    o_use_tokdef(append_TDF(&g_tok_defn,1));
    g_tok_defn = (ZIa);
#line 3284 "syntax.c"
			}
			/* END OF ACTION: tok3 */
		}
		break;
	case 2: case 5: case 9: case 15:
	case 18: case 40: case 43: case 49:
	case 60: case 71: case 75: case 91:
	case 96: case 100: case 111: case 120:
	case 128:
		{
			/* BEGINNING OF ACTION: tok1 */
			{
#line 2164 "syntax.act"

    Tokdec * td = lex_v.val.tokname;
    if (td->isparam) {
	o_token_apply_token(make_tok(&td->idname.name), {});
    } else {
	make_tok(&td->idname.name);
    }
    /* token should only be expanded as parameter of a token */
#line 3306 "syntax.c"
			}
			/* END OF ACTION: tok1 */
			/* BEGINNING OF INLINE: tok_item */
			{
				switch (CURRENT_TERMINAL) {
				case 2:
					{
						ADVANCE_LEXER;
					}
					break;
				case 5:
					{
						ADVANCE_LEXER;
					}
					break;
				case 9:
					{
						ADVANCE_LEXER;
					}
					break;
				case 15:
					{
						ADVANCE_LEXER;
					}
					break;
				case 18:
					{
						ADVANCE_LEXER;
					}
					break;
				case 40:
					{
						ADVANCE_LEXER;
					}
					break;
				case 43:
					{
						ADVANCE_LEXER;
					}
					break;
				case 49:
					{
						ADVANCE_LEXER;
					}
					break;
				case 60:
					{
						ADVANCE_LEXER;
					}
					break;
				case 71:
					{
						ADVANCE_LEXER;
					}
					break;
				case 75:
					{
						ADVANCE_LEXER;
					}
					break;
				case 91:
					{
						ADVANCE_LEXER;
					}
					break;
				case 96:
					{
						ADVANCE_LEXER;
					}
					break;
				case 100:
					{
						ADVANCE_LEXER;
					}
					break;
				case 111:
					{
						ADVANCE_LEXER;
					}
					break;
				case 120:
					{
						ADVANCE_LEXER;
					}
					break;
				case 128:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: tok_item */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 3417 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR673(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: snl1 */
			{
#line 1841 "syntax.act"

    g_tokpars = xmalloc(sizeof *g_tokpars);
    g_tokpars->par = g_sname;
    g_tokpars->next = (Tokpar*)0;
#line 3436 "syntax.c"
			}
			/* END OF ACTION: snl1 */
		}
		break;
	case 25:
		{
			Sort ZIa;

			/* BEGINNING OF ACTION: snl2_dec */
			{
#line 1844 "syntax.act"

    (ZIa) = g_sname;
#line 3450 "syntax.c"
			}
			/* END OF ACTION: snl2_dec */
			ADVANCE_LEXER;
			ZRsortname__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: snl3 */
			{
#line 1849 "syntax.act"

    Tokpar * x = xmalloc(sizeof *x);
    x->par = (ZIa);
    x->next = g_tokpars;
    g_tokpars = x;
#line 3467 "syntax.c"
			}
			/* END OF ACTION: snl3 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRnat__not__int(void)
{
ZL2_nat__not__int:;
	switch (CURRENT_TERMINAL) {
	case 70:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 651 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						read_nat ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 3516 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 3537 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_nat ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 3558 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_nat ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: nat1 */
						{
#line 1470 "syntax.act"

    RESET_TDF((ZId));
    o_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
#line 3580 "syntax.c"
						}
						/* END OF ACTION: nat1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 651 */
		}
		break;
	case 69:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 3608 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 3617 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 71:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 3632 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 3641 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRshape__body(void)
{
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapedouble */
			{
#line 1681 "syntax.act"

    Name * shtok = tokfordoublesh();
    o_shape_apply_token(make_tok(shtok), {});
#line 3670 "syntax.c"
			}
			/* END OF ACTION: shapedouble */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapefloat */
			{
#line 1686 "syntax.act"

    Name * shtok = tokforfloatsh();
    o_shape_apply_token(make_tok(shtok), {});
#line 3684 "syntax.c"
			}
			/* END OF ACTION: shapefloat */
		}
		break;
	case 83:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shptr1_dec */
			{
#line 1730 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 3700 "syntax.c"
			}
			/* END OF ACTION: shptr1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shapeptr2 */
			{
#line 1699 "syntax.act"

    RESET_TDF((ZIb));
    o_pointer(o_alignment(append_TDF(&(ZIa),1)));
#line 3714 "syntax.c"
			}
			/* END OF ACTION: shapeptr2 */
		}
		break;
	case 95:
		{
			ADVANCE_LEXER;
			ZR676 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 21: case 56: case 64: case 97:
	case 101: case 121:
		{
			ZRvariety__sign ();
			ZR654 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 94:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 3749 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 3758 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 96:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 3773 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 3782 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRrepeat__starter__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			ADVANCE_LEXER;
			ZRexp__sequence ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: strtr1 */
			{
#line 1856 "syntax.act"

    o_make_top;
#line 3825 "syntax.c"
			}
			/* END OF ACTION: strtr1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR674(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: sortname2 */
			{
#line 1813 "syntax.act"

    if (g_sname.sort == token_sort) {
	fail("Token pars require result and parameter sorts");
    }
    g_sname.toksort= (TokSort*)0;
#line 3853 "syntax.c"
			}
			/* END OF ACTION: sortname2 */
		}
		break;
	case 79:
		{
			Sort ZIa;
			PTR_Tokpar ZIb;
			PTR_Tokpar ZIc;

			/* BEGINNING OF ACTION: sortname3_dec */
			{
#line 1816 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIc) = g_tokpars;
    (ZIa) = g_sname;
    if (g_sname.sort != token_sort) {
	fail("Only token pars require result and parameter sorts");
    }
#line 3874 "syntax.c"
			}
			/* END OF ACTION: sortname3_dec */
			ADVANCE_LEXER;
			ZRsortname__list__opt ();
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: sortname4 */
			{
#line 1825 "syntax.act"

    (ZIb) = g_tokpars;
#line 3894 "syntax.c"
			}
			/* END OF ACTION: sortname4 */
			ZRfull__sortname ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: sortname5 */
			{
#line 1831 "syntax.act"

    TokSort * ts = xmalloc(sizeof *ts);
    ts->ressort = g_sname;
    ts->pars = (ZIb);
    g_tokpars = (ZIc);
    (ZIa).toksort = ts;
    g_sname = (ZIa);
#line 3912 "syntax.c"
			}
			/* END OF ACTION: sortname5 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRfield__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
ZL2_field__list:;
	{
		PTR_TDF ZIa;
		PTR_Tokdec ZIb;
		PTR_Tokdec ZIc;

		/* BEGINNING OF ACTION: field1_dec */
		{
#line 954 "syntax.act"

    char * dotn = append_string(".",lex_v.val.name);
    char * n = lex_v.val.name;
    (ZIb) = find_tok(dotn);
    (ZIc) = find_tok(n);
    if ((ZIb)!= (Tokdec*)0 || (ZIc)!= (Tokdec*)0)
	    fail("Field name %s must be unique", dotn);
    (ZIb) = xmalloc(sizeof *(ZIb)); NEW_IDNAME((ZIb)->idname, dotn, tok_ent);
    (ZIb)->isdeffed = 1; (ZIb)->isused=0; (ZIb)->iskept = 0;
    (ZIb)->sort.ressort.sort = exp_sort;
    (ZIb)->sort.pars = (Tokpar *)0;

    (ZIc) = xmalloc(sizeof *(ZIc)); NEW_IDNAME((ZIc)->idname, n, tok_ent);
    (ZIc)->isdeffed = 1; (ZIc)->isused=0; (ZIc)->iskept = 0;
    (ZIc)->sort.ressort.sort = exp_sort;
    (ZIc)->sort.pars = xmalloc(sizeof *(ZIc)->sort.pars);
    (ZIc)->sort.pars->par.sort = exp_sort;
    (ZIc)->sort.pars->next = (Tokpar*)0;
    (ZIb)->next = (ZIc);
    SET_TDF((ZIa), &g_shape);
#line 3961 "syntax.c"
		}
		/* END OF ACTION: field1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		read_shape ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: field2 */
		{
#line 975 "syntax.act"

    int tn;
    RESET_TDF((ZIa));
    o_make_tokdef(out_tdfint32(LOCNAME((ZIb)->idname)), {},
	o_token_def(o_exp, {},
	    if (g_lastfield==-1) { /* first field */
		o_offset_zero(o_alignment(append_TDF(&g_shape, 0)));
	    } else {
		o_offset_pad(o_alignment(append_TDF(&g_shape,0)),
		    o_offset_add(o_exp_apply_token(
			o_make_tok(out_tdfint32(UL(g_lastfield))),{}),
		    o_shape_offset(append_TDF(&g_lastshape, 1))))
	    }));
    g_lastfield = (int)(LOCNAME((ZIb)->idname));
    g_lastshape = g_shape;
    INC_LIST;
    o_make_tokdef(out_tdfint32(LOCNAME((ZIc)->idname)), {},
	o_token_def(o_exp,
	    LIST_ELEM(o_make_tokformals(o_exp,
		out_tdfint32(UL(tn=next_unit_name(tok_ent))))),
	    o_component(append_TDF(&g_lastshape,0),
		o_exp_apply_token(o_make_tok(out_tdfint32(UL(tn))),{}),
		o_exp_apply_token(
		    o_make_tok(out_tdfint32(UL(g_lastfield))),{}))));
    INC_LIST;
    (ZIc)->next = tokdecs;
    tokdecs = (ZIb);
#line 4013 "syntax.c"
		}
		/* END OF ACTION: field2 */
		/* BEGINNING OF INLINE: 682 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: field_list */
					goto ZL2_field__list;
					/* END OF INLINE: field_list */
				}
				/*UNREACHED*/
			default:
				break;
			}
		}
		/* END OF INLINE: 682 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR675(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapetokchar */
			{
#line 1719 "syntax.act"

    * g_shtokname = *(tokforcharsh(issigned));
#line 4051 "syntax.c"
			}
			/* END OF ACTION: shapetokchar */
		}
		break;
	case 56:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapetokint */
			{
#line 1723 "syntax.act"

    * g_shtokname = *(tokforintsh(issigned));
#line 4064 "syntax.c"
			}
			/* END OF ACTION: shapetokint */
		}
		break;
	case 64:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapetoklong */
			{
#line 1727 "syntax.act"

    * g_shtokname = *(tokforlongsh(issigned));
#line 4077 "syntax.c"
			}
			/* END OF ACTION: shapetoklong */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shtokshrt */
			{
#line 1751 "syntax.act"

    * g_shtokname = *(tokforshortsh(issigned));
#line 4090 "syntax.c"
			}
			/* END OF ACTION: shtokshrt */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR676(void)
{
	switch (CURRENT_TERMINAL) {
	case 24:
		{
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 86:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencond1_dec */
			{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 4134 "syntax.c"
			}
			/* END OF ACTION: gencond1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gencond2 */
			{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 4155 "syntax.c"
			}
			/* END OF ACTION: gencond2 */
			switch (CURRENT_TERMINAL) {
			case 25:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gencond3 */
			{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 4176 "syntax.c"
			}
			/* END OF ACTION: gencond3 */
			switch (CURRENT_TERMINAL) {
			case 25:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shape1 */
			{
#line 1668 "syntax.act"

    RESET_TDF((ZId));
    o_shape_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 4198 "syntax.c"
			}
			/* END OF ACTION: shape1 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR677(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, PTR_char *ZIe, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			/* BEGINNING OF ACTION: tag_def2 */
			{
#line 1992 "syntax.act"

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh)fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
#line 4234 "syntax.c"
			}
			/* END OF ACTION: tag_def2 */
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def3 */
			{
#line 1998 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
#line 4254 "syntax.c"
			}
			/* END OF ACTION: tag_def3 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: tag_def4 */
			{
#line 2008 "syntax.act"

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh)fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
#line 4268 "syntax.c"
			}
			/* END OF ACTION: tag_def4 */
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def5 */
			{
#line 2014 "syntax.act"

    SET_TDF((*ZIc), &(*ZIa));
#line 4282 "syntax.c"
			}
			/* END OF ACTION: tag_def5 */
			ZR680 (ZIa, ZIb, ZIc, ZId, ZIf);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRrounding__mode__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 89: case 90: case 91:
		{
			read_rounding_mode ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: rmodeopt1 */
			{
#line 1665 "syntax.act"

    o_to_nearest;
#line 4323 "syntax.c"
			}
			/* END OF ACTION: rmodeopt1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR678(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, PTR_char *ZIe, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			/* BEGINNING OF ACTION: tag_def2 */
			{
#line 1992 "syntax.act"

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh)fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
#line 4350 "syntax.c"
			}
			/* END OF ACTION: tag_def2 */
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ctag_def3 */
			{
#line 423 "syntax.act"

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
#line 4370 "syntax.c"
			}
			/* END OF ACTION: ctag_def3 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: tag_def4 */
			{
#line 2008 "syntax.act"

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh)fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
#line 4384 "syntax.c"
			}
			/* END OF ACTION: tag_def4 */
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def5 */
			{
#line 2014 "syntax.act"

    SET_TDF((*ZIc), &(*ZIa));
#line 4398 "syntax.c"
			}
			/* END OF ACTION: tag_def5 */
			ZR681 (ZIa, ZIb, ZIc, ZId, ZIf);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRnonst__shape(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		int ZIc;

		/* BEGINNING OF ACTION: genhold1_dec */
		{
#line 1086 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
#line 4438 "syntax.c"
		}
		/* END OF ACTION: genhold1_dec */
		ZRnonst__shape__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: genhold2 */
		{
#line 1093 "syntax.act"

    if (!(ZIc)) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
#line 4455 "syntax.c"
		}
		/* END OF ACTION: genhold2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR679(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, PTR_char *ZIe, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def2 */
			{
#line 1992 "syntax.act"

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh)fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
#line 4479 "syntax.c"
			}
			/* END OF ACTION: tag_def2 */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def8 */
			{
#line 2056 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_id_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))),
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
#line 4497 "syntax.c"
			}
			/* END OF ACTION: tag_def8 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: tag_def4 */
			{
#line 2008 "syntax.act"

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh)fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
#line 4511 "syntax.c"
			}
			/* END OF ACTION: tag_def4 */
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def5 */
			{
#line 2014 "syntax.act"

    SET_TDF((*ZIc), &(*ZIa));
#line 4525 "syntax.c"
			}
			/* END OF ACTION: tag_def5 */
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def9 */
			{
#line 2065 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_id_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_id_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4559 "syntax.c"
			}
			/* END OF ACTION: tag_def9 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRaccess__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 79:
		{
			ADVANCE_LEXER;
			ZRaccess__list ();
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_error_code(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		int ZIa;

		/* BEGINNING OF ACTION: gencons1_dec */
		{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 4620 "syntax.c"
		}
		/* END OF ACTION: gencons1_dec */
		switch (CURRENT_TERMINAL) {
		case 37:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: gencons2 */
		{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 4635 "syntax.c"
		}
		/* END OF ACTION: gencons2 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 4647 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRpostlude__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 93:
		{
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: plude1 */
			{
#line 1569 "syntax.act"

    o_make_top;
#line 4674 "syntax.c"
			}
			/* END OF ACTION: plude1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR680(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def6 */
			{
#line 2018 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4720 "syntax.c"
			}
			/* END OF ACTION: tag_def6 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: tag_def10 */
			{
#line 1952 "syntax.act"

    o_make_value(o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
#line 4732 "syntax.c"
			}
			/* END OF ACTION: tag_def10 */
			/* BEGINNING OF ACTION: tag_def6 */
			{
#line 2018 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4755 "syntax.c"
			}
			/* END OF ACTION: tag_def6 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRexponent__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 34:
		{
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: eopt1 */
			{
#line 465 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(0)));
#line 4790 "syntax.c"
			}
			/* END OF ACTION: eopt1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR681(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ctag_def6 */
			{
#line 433 "syntax.act"

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_common_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4836 "syntax.c"
			}
			/* END OF ACTION: ctag_def6 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: tag_def10 */
			{
#line 1952 "syntax.act"

    o_make_value(o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
#line 4848 "syntax.c"
			}
			/* END OF ACTION: tag_def10 */
			/* BEGINNING OF ACTION: ctag_def6 */
			{
#line 433 "syntax.act"

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_common_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4871 "syntax.c"
			}
			/* END OF ACTION: ctag_def6 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRclosed__exp(void)
{
	switch (CURRENT_TERMINAL) {
	case 58:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			PTR_Labdec ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: explab1_dec */
			{
#line 717 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIe) = labdecs;
    (ZIc) = g_lablist;
    INIT_TDF(&g_lablist);
    SET_TDF((ZId), &(ZIa));
#line 4907 "syntax.c"
			}
			/* END OF ACTION: explab1_dec */
			switch (CURRENT_TERMINAL) {
			case 76:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: explab2 */
			{
#line 725 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 4928 "syntax.c"
			}
			/* END OF ACTION: explab2 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRlabelled__list ();
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: explab3 */
			{
#line 730 "syntax.act"

    RESET_TDF((ZId));
    o_labelled({ append_TDF(&g_lablist,1);
		  current_TDF->no = g_lablist.no;},
		  append_TDF(&(ZIa), 1),
		  { append_TDF(&(ZIb),1);
		    current_TDF->no = g_lablist.no;});
    tidy_labels((ZIe));
    g_lablist = (ZIc);
#line 4961 "syntax.c"
			}
			/* END OF ACTION: explab3 */
		}
		break;
	case 76:
		{
			ADVANCE_LEXER;
			ZRexp__sequence ();
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 86:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;
			PTR_Labdec ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expcond1_dec */
			{
#line 627 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = defaultlab;
    (ZIf) = labdecs;
    defaultlab = -1;
    SET_TDF((ZId), &(ZIa));
#line 5001 "syntax.c"
			}
			/* END OF ACTION: expcond1_dec */
			switch (CURRENT_TERMINAL) {
			case 76:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond2 */
			{
#line 635 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5022 "syntax.c"
			}
			/* END OF ACTION: expcond2 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRlabset__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond3 */
			{
#line 640 "syntax.act"

    (ZIc) = optlab;
    defaultlab = (ZIe);
    tidy_labels((ZIf));
#line 5044 "syntax.c"
			}
			/* END OF ACTION: expcond3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond4 */
			{
#line 646 "syntax.act"

    INIT_TDF((ZId));
    RESET_TDF((ZId));
    o_conditional(append_TDF(&(ZIc),1),
		  append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 5060 "syntax.c"
			}
			/* END OF ACTION: expcond4 */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 88:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			PTR_Labdec ZIe;
			int ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exprep1_dec */
			{
#line 790 "syntax.act"

    /* (ZIb), (ZIc), (ZIf) uninitialised */
    (ZIe) = labdecs;
    SET_TDF((ZId), &(ZIa));
#line 5089 "syntax.c"
			}
			/* END OF ACTION: exprep1_dec */
			ZRrepeat__starter__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep2 */
			{
#line 796 "syntax.act"

    (ZIf) = defaultlab;
    defaultlab = -1;
#line 5103 "syntax.c"
			}
			/* END OF ACTION: exprep2 */
			switch (CURRENT_TERMINAL) {
			case 76:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRlabset__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep3 */
			{
#line 801 "syntax.act"

    (ZIc) = optlab;
    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5125 "syntax.c"
			}
			/* END OF ACTION: exprep3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep4 */
			{
#line 807 "syntax.act"

    RESET_TDF((ZId));
    o_repeat(append_TDF(&(ZIc),1), append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
    tidy_labels((ZIe));
    defaultlab = (ZIf);
#line 5141 "syntax.c"
			}
			/* END OF ACTION: exprep4 */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 61: case 124:
		{
			PTR_Tagdec ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			Name ZIf;
			int ZIg;

			/* BEGINNING OF ACTION: expdec1_dec */
			{
#line 669 "syntax.act"

    (ZIa) = localdecs;
#line 5168 "syntax.c"
			}
			/* END OF ACTION: expdec1_dec */
			ZRtag__intro ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ibody1_dec */
			{
#line 1160 "syntax.act"

    (ZIg) = localdecs->isvar;
    (ZIb) = intro_acc;
    (ZIc) = intro_init;
    (ZIf) = localdecs->idname.name;
    SET_TDF((ZIe), &(ZId));
#line 5185 "syntax.c"
			}
			/* END OF ACTION: ibody1_dec */
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: introbody2 */
			{
#line 1233 "syntax.act"

    RESET_TDF((ZIe));
    if ((ZIg)) {
	o_variable(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    } else {
	o_identify(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    }
#line 5207 "syntax.c"
			}
			/* END OF ACTION: introbody2 */
			/* BEGINNING OF ACTION: expdec2 */
			{
#line 673 "syntax.act"

    localdecs = (ZIa);
#line 5215 "syntax.c"
			}
			/* END OF ACTION: expdec2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_bool(void)
{
ZL2_bool:;
	switch (CURRENT_TERMINAL) {
	case 17:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: after_bool_sort */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: bool */
						goto ZL2_bool;
						/* END OF INLINE: bool */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5263 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						ADVANCE_LEXER;
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5291 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						read_bool ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5311 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_bool ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: bool1 */
						{
#line 291 "syntax.act"

    RESET_TDF((ZId));
    o_bool_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		append_TDF(&(ZIc),1));
#line 5326 "syntax.c"
						}
						/* END OF ACTION: bool1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: after_bool_sort */
		}
		break;
	case 16:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 5354 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 5363 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 18:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 5378 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 5387 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 5405 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRvarintro__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 129:
		{
			ADVANCE_LEXER;
			read_tag ();
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_alignment ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_ntest(void)
{
ZL2_ntest:;
	switch (CURRENT_TERMINAL) {
	case 74:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 671 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: ntest */
						goto ZL2_ntest;
						/* END OF INLINE: ntest */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5480 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5501 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_ntest ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5522 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_ntest ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: ntest1 */
						{
#line 1504 "syntax.act"

    RESET_TDF((ZId));
    o_ntest_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 5544 "syntax.c"
						}
						/* END OF ACTION: ntest1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 671 */
		}
		break;
	case 75:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 5573 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 5582 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 87:
		{
			/* BEGINNING OF ACTION: ntest2 */
			{
#line 1524 "syntax.act"

    char * n = lex_v.val.name;
    if (strcmp(n,"!<") ==0) { o_not_less_than; }
    else if (strcmp(n,"!<=") ==0) { o_not_less_than_or_equal; }
    else if (strcmp(n,"!=") ==0) { o_not_equal; }
    else if (strcmp(n,"!>") ==0) { o_not_greater_than; }
    else if (strcmp(n,"!>=") ==0) { o_not_greater_than_or_equal; }
    else if (strcmp(n,"!Comparable") ==0) { o_not_comparable; }
    else if (strcmp(n,"<") ==0) { o_less_than; }
    else if (strcmp(n,"<=") ==0) { o_less_than_or_equal; }
    else if (strcmp(n,"==") ==0) { o_equal; }
    else if (strcmp(n,">") ==0) { o_greater_than; }
    else if (strcmp(n,">=") ==0) { o_greater_than_or_equal; }
    else if (strcmp(n,"Comparable") ==0) { o_comparable; }
    else { fail("%s is not a comparison", n); }
#line 5607 "syntax.c"
			}
			/* END OF ACTION: ntest2 */
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 5626 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_bitfield_variety(void)
{
ZL2_bitfield__variety:;
	switch (CURRENT_TERMINAL) {
	case 14:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: after_bv_sort */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: bitfield_variety */
						goto ZL2_bitfield__variety;
						/* END OF INLINE: bitfield_variety */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5664 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						ADVANCE_LEXER;
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5692 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						read_bitfield_variety ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5712 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_bitfield_variety ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: bvariety1 */
						{
#line 302 "syntax.act"

    RESET_TDF((ZId));
    o_bfvar_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 5727 "syntax.c"
						}
						/* END OF ACTION: bvariety1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: after_bv_sort */
		}
		break;
	case 16: case 17: case 18: case 22:
	case 55: case 69: case 70: case 71:
	case 101: case 121:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: bvar3_dec */
			{
#line 297 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 5760 "syntax.c"
			}
			/* END OF ACTION: bvar3_dec */
			ZRbitfield__sign ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bvariety4 */
			{
#line 313 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 5774 "syntax.c"
			}
			/* END OF ACTION: bvariety4 */
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bvariety5 */
			{
#line 318 "syntax.act"

    RESET_TDF((ZIc));
    o_bfvar_bits(append_TDF(&(ZIa),1), append_TDF(&(ZIb), 1));
#line 5788 "syntax.c"
			}
			/* END OF ACTION: bvariety5 */
		}
		break;
	case 13:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 5802 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 5811 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 15:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 5826 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 5835 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 5853 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRsigned__nat__body(void)
{
ZL2_signed__nat__body:;
	switch (CURRENT_TERMINAL) {
	case 68:
		{
			ADVANCE_LEXER;
			ZR634 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 99:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 633 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: signed_nat_body */
						goto ZL2_signed__nat__body;
						/* END OF INLINE: signed_nat_body */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5902 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5923 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						ZRsigned__nat__body ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5944 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						ZRsigned__nat__body ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: signed_nat1 */
						{
#line 1754 "syntax.act"

    RESET_TDF((ZId));
    o_signed_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		      append_TDF(&(ZIc),1));
#line 5966 "syntax.c"
						}
						/* END OF ACTION: signed_nat1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 633 */
		}
		break;
	case 22: case 55:
		{
			ZRinteger ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat2 */
			{
#line 1761 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(intvalue));
#line 5997 "syntax.c"
			}
			/* END OF ACTION: signed_nat2 */
		}
		break;
	case 98:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6011 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6020 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 100:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6035 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6044 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 62:
		{
			/* BEGINNING OF ACTION: signed_nat4 */
			{
#line 1769 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(cLINE));
#line 6056 "syntax.c"
			}
			/* END OF ACTION: signed_nat4 */
			ADVANCE_LEXER;
		}
		break;
	case 10:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: signed_nat7_dec */
			{
#line 1781 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
    if (strcmp(lex_v.val.name, "+"))fail("Only + or - on NATs");
#line 6073 "syntax.c"
			}
			/* END OF ACTION: signed_nat7_dec */
			ADVANCE_LEXER;
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat8 */
			{
#line 1786 "syntax.act"

    RESET_TDF((ZIb));
    o_snat_from_nat(o_false, append_TDF(&(ZIa),1));
#line 6088 "syntax.c"
			}
			/* END OF ACTION: signed_nat8 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRlabset__opt(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: lset_o1 */
			{
#line 1439 "syntax.act"

    TDF * hold;
    SET_TDF(hold, &optlab);
    if (defaultlab==-1)defaultlab = next_label();
    o_make_label(out_tdfint32(UL(defaultlab)));
    RESET_TDF(hold);
#line 6119 "syntax.c"
			}
			/* END OF ACTION: lset_o1 */
		}
		break;
	case 24:
		{
			PTR_TDF ZIa;

			/* BEGINNING OF ACTION: lset_o2_dec */
			{
#line 1442 "syntax.act"

    SET_TDF((ZIa), &optlab);
    g_labdec = (Labdec*)0;
    if (defaultlab != -1) { fail("This conditional uses a default jump"); }
#line 6135 "syntax.c"
			}
			/* END OF ACTION: lset_o2_dec */
			ADVANCE_LEXER;
			read_label ();
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lset_o3 */
			{
#line 1454 "syntax.act"

    if (g_labdec != (Labdec*)0) {
	if (g_labdec->declared) {
	    fail("Label %s set twice", g_labdec->idname.id);
	}
	g_labdec->declared = 1;
    }
    RESET_TDF((ZIa));
#line 6161 "syntax.c"
			}
			/* END OF ACTION: lset_o3 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRkeep__item(void)
{
	switch (CURRENT_TERMINAL) {
	case 2: case 5: case 9: case 15:
	case 18: case 40: case 43: case 49:
	case 60: case 71: case 75: case 91:
	case 96: case 100: case 111: case 120:
	case 128:
		{
			/* BEGINNING OF ACTION: keep1 */
			{
#line 1248 "syntax.act"

    Tokdec * k = lex_v.val.tokname;
    k->iskept = 1;
#line 6191 "syntax.c"
			}
			/* END OF ACTION: keep1 */
			/* BEGINNING OF INLINE: tok_item */
			{
				switch (CURRENT_TERMINAL) {
				case 2:
					{
						ADVANCE_LEXER;
					}
					break;
				case 5:
					{
						ADVANCE_LEXER;
					}
					break;
				case 9:
					{
						ADVANCE_LEXER;
					}
					break;
				case 15:
					{
						ADVANCE_LEXER;
					}
					break;
				case 18:
					{
						ADVANCE_LEXER;
					}
					break;
				case 40:
					{
						ADVANCE_LEXER;
					}
					break;
				case 43:
					{
						ADVANCE_LEXER;
					}
					break;
				case 49:
					{
						ADVANCE_LEXER;
					}
					break;
				case 60:
					{
						ADVANCE_LEXER;
					}
					break;
				case 71:
					{
						ADVANCE_LEXER;
					}
					break;
				case 75:
					{
						ADVANCE_LEXER;
					}
					break;
				case 91:
					{
						ADVANCE_LEXER;
					}
					break;
				case 96:
					{
						ADVANCE_LEXER;
					}
					break;
				case 100:
					{
						ADVANCE_LEXER;
					}
					break;
				case 111:
					{
						ADVANCE_LEXER;
					}
					break;
				case 120:
					{
						ADVANCE_LEXER;
					}
					break;
				case 128:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: tok_item */
		}
		break;
	case 54:
		{
			/* BEGINNING OF ACTION: keep2 */
			{
#line 1262 "syntax.act"

    char * n = lex_v.val.name;
    Tagdec * t = find_tag(n);
    if (t != (Tagdec*)0) {
	t->iskept = 1;
     } else {
	Al_tagdec * a = find_al_tag(n);
	if (a == (Al_tagdec*)0) {
	    fail("Ident %s not declared",n);
	}
	a->iskept = 1;
    }
#line 6306 "syntax.c"
			}
			/* END OF ACTION: keep2 */
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRstruct__def(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_Tokdec ZIa;

		switch (CURRENT_TERMINAL) {
		case 108:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: struct1_dec */
		{
#line 1860 "syntax.act"

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    SELECT_UNIT(tokdef_unit);
    if ((ZIa)!= (Tokdec*)0)fail("Struct name %s must be unique", n);
    (ZIa) = xmalloc(sizeof *(ZIa)); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->sort.ressort.sort = shape_sort; (ZIa)->sort.pars = (Tokpar*)0;
    (ZIa)->isdeffed = 1; (ZIa)->isused=0; (ZIa)->iskept=0;
    g_lastfield = -1;
#line 6351 "syntax.c"
		}
		/* END OF ACTION: struct1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 78:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRfield__list ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: struct2 */
		{
#line 1870 "syntax.act"

    o_make_tokdef(out_tdfint32(LOCNAME((ZIa)->idname)), {},
	o_token_def(o_shape, {},
	    o_compound(o_offset_add(
		o_exp_apply_token(
		    o_make_tok(out_tdfint32(UL(g_lastfield))),{}),
		o_shape_offset(append_TDF(&g_lastshape, 1))))))
    INC_LIST;
    (ZIa)->next = tokdecs;
    tokdecs = (ZIa);
#line 6386 "syntax.c"
		}
		/* END OF ACTION: struct2 */
		switch (CURRENT_TERMINAL) {
		case 29:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRnonst__shape__body(void)
{
	switch (CURRENT_TERMINAL) {
	case 83:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shptr1_dec */
			{
#line 1730 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 6418 "syntax.c"
			}
			/* END OF ACTION: shptr1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shapeptr2 */
			{
#line 1699 "syntax.act"

    RESET_TDF((ZIb));
    o_pointer(o_alignment(append_TDF(&(ZIa),1)));
#line 6432 "syntax.c"
			}
			/* END OF ACTION: shapeptr2 */
		}
		break;
	case 95:
		{
			ADVANCE_LEXER;
			ZR676 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 94:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6456 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6465 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 96:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6480 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6489 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_tag(void)
{
ZL2_tag:;
	switch (CURRENT_TERMINAL) {
	case 110:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: tag */
			goto ZL2_tag;
			/* END OF INLINE: tag */
		}
		/*UNREACHED*/
	case 109:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6534 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6543 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 111:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6558 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6567 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 54:
		{
			/* BEGINNING OF ACTION: tag1 */
			{
#line 1891 "syntax.act"

    char * n =lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x == (Tagdec*)0) { fail("Ident %s not declared", n); }
    x->isused = 1;
    make_tag(&x->idname.name);
#line 6583 "syntax.c"
			}
			/* END OF ACTION: tag1 */
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 6602 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRvariety__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			ADVANCE_LEXER;
			read_variety ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: varietyopt1 */
			{
#line 2373 "syntax.act"

    /* unsigned char */
    o_var_limits(
	o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(0))),
	o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(255))));
#line 6638 "syntax.c"
			}
			/* END OF ACTION: varietyopt1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_nat_option(void)
{
	switch (CURRENT_TERMINAL) {
	case 22: case 55: case 69: case 70:
	case 71:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: natopt_dec */
			{
#line 1485 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 6667 "syntax.c"
			}
			/* END OF ACTION: natopt_dec */
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: natopt1 */
			{
#line 1480 "syntax.act"

    RESET_TDF((ZIb));
    OPTION(append_TDF(&(ZIa),1));
#line 6681 "syntax.c"
			}
			/* END OF ACTION: natopt1 */
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 6699 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRsortname__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 1: case 4: case 8: case 14:
	case 17: case 39: case 42: case 48:
	case 59: case 70: case 74: case 90:
	case 95: case 99: case 105: case 110:
	case 116: case 119: case 127:
		{
			ZRsortname__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty_snl */
			{
#line 461 "syntax.act"

    g_tokpars = (Tokpar*)0;
#line 6729 "syntax.c"
			}
			/* END OF ACTION: empty_snl */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_floating_variety(void)
{
ZL2_floating__variety:;
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: fvardouble */
			{
#line 1013 "syntax.act"

    o_flvar_parms(o_make_nat(out_tdfint32(UL(2))),
		  o_make_nat(out_tdfint32(UL(MANT_DOUBLE))),
		  o_make_nat(out_tdfint32(UL(MINEXP_DOUBLE))),
		  o_make_nat(out_tdfint32(UL(MAXEXP_DOUBLE))));
#line 6759 "syntax.c"
			}
			/* END OF ACTION: fvardouble */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: fvarfloat */
			{
#line 1020 "syntax.act"

    o_flvar_parms(o_make_nat(out_tdfint32(UL(2))),
		  o_make_nat(out_tdfint32(UL(MANT_FLOAT))),
		  o_make_nat(out_tdfint32(UL(MINEXP_FLOAT))),
		  o_make_nat(out_tdfint32(UL(MAXEXP_FLOAT))));
#line 6775 "syntax.c"
			}
			/* END OF ACTION: fvarfloat */
		}
		break;
	case 48:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 658 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: floating_variety */
						goto ZL2_floating__variety;
						/* END OF INLINE: floating_variety */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 6807 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						ADVANCE_LEXER;
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 6835 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						read_floating_variety ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 6855 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_floating_variety ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: fvar1 */
						{
#line 1003 "syntax.act"

    RESET_TDF((ZId));
    o_flvar_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 6870 "syntax.c"
						}
						/* END OF ACTION: fvar1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 658 */
		}
		break;
	case 47:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6898 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6907 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 49:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6922 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6931 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 6949 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRtagshacc(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		PTR_Tagdec ZIc;
		int ZId;

		/* BEGINNING OF ACTION: tagsa1_dec */
		{
#line 2083 "syntax.act"

    /* (ZId) uninitialised */
    char * n =lex_v.val.name;
    (ZIc) = find_tag(n);
    if ((ZIc) != (Tagdec*)0)fail("Ident %s already declared", n);
    (ZIc) = xmalloc(sizeof *(ZIc));
    (ZIc)->hassh = 2; (ZIc)->isvar =1; (ZIc)->isdeffed = 1; (ZIc)->iskept=0;
    NEW_IDNAME((ZIc)->idname, n, tag_ent);
    g_has_vis =0;
    SET_TDF((ZIb), &(ZIa));
#line 6980 "syntax.c"
		}
		/* END OF ACTION: tagsa1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRaccess__opt ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tagshacc2 */
		{
#line 2095 "syntax.act"

    RESET_TDF((ZIb));
    SET_TDF((ZIb), &(ZIc)->sh.tdfsh);
    (ZId) = g_has_vis;
#line 7002 "syntax.c"
		}
		/* END OF ACTION: tagshacc2 */
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		read_shape ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tagshacc3 */
		{
#line 2101 "syntax.act"

    RESET_TDF((ZIb));
    o_make_tagshacc(append_TDF(&(ZIc)->sh.tdfsh, 0),
	if ((ZIa).no != 0) {OPTION(append_TDF(&(ZIa),1));},
	make_tag(&(ZIc)->idname.name));
    if ((ZId)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(ZIc);
	y->next = tagdecs;
	tagdecs = y;
    }
    (ZIc)->next = localdecs;
    localdecs = (ZIc);
#line 7033 "syntax.c"
		}
		/* END OF ACTION: tagshacc3 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRelement__list__opt(void)
{
ZL2_element__list__opt:;
	switch (CURRENT_TERMINAL) {
	case 6: case 26: case 27: case 53:
	case 61: case 81: case 106: case 108:
	case 113: case 114: case 124: case 125:
		{
			ZRelement ();
			switch (CURRENT_TERMINAL) {
			case 93:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: element_list_opt */
			goto ZL2_element__list__opt;
			/* END OF INLINE: element_list_opt */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_nat(void)
{
ZL2_nat:;
	switch (CURRENT_TERMINAL) {
	case 22: case 55:
		{
			ZRinteger ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: nat2 */
			{
#line 1477 "syntax.act"

    o_make_nat(out_tdfint32(intvalue));
#line 7096 "syntax.c"
			}
			/* END OF ACTION: nat2 */
		}
		break;
	case 69: case 70: case 71:
		{
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 7123 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_alignment(void)
{
ZL2_alignment:;
	switch (CURRENT_TERMINAL) {
	case 8:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 666 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: alignment */
						goto ZL2_alignment;
						/* END OF INLINE: alignment */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 7162 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 7189 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						read_alignment ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 7209 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_alignment ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: alignment1 */
						{
#line 276 "syntax.act"

    RESET_TDF((ZId));
    o_alignment_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		     append_TDF(&(ZIc),1));
#line 7224 "syntax.c"
						}
						/* END OF ACTION: alignment1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 666 */
		}
		break;
	case 78:
		{
			ADVANCE_LEXER;
			ZRalignment__list__opt ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 4: case 5: case 54:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: alment2_dec */
			{
#line 287 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 7269 "syntax.c"
			}
			/* END OF ACTION: alment2_dec */
			read_al_tag ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: alignment3 */
			{
#line 282 "syntax.act"

    RESET_TDF((ZIb));
    o_obtain_al_tag(append_TDF(&(ZIa), 1));
#line 7283 "syntax.c"
			}
			/* END OF ACTION: alignment3 */
		}
		break;
	case 7:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 7297 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 7306 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 9:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 7321 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 7330 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 7348 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRvarpar__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 129:
		{
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: vpar1 */
			{
#line 2385 "syntax.act"

    current_TDF->no=1;
#line 7371 "syntax.c"
			}
			/* END OF ACTION: vpar1 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: vpar2 */
			{
#line 2389 "syntax.act"

    current_TDF->no=0;
#line 7383 "syntax.c"
			}
			/* END OF ACTION: vpar2 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRkeep__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
ZL2_keep__list:;
	{
		ZRkeep__item ();
		/* BEGINNING OF INLINE: 683 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: keep_list */
					goto ZL2_keep__list;
					/* END OF INLINE: keep_list */
				}
				/*UNREACHED*/
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 683 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRproc__def(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		TDF ZIb;
		PTR_TDF ZIc;
		PTR_Tagdec ZId;
		PTR_char ZIe;
		int ZIf;

		switch (CURRENT_TERMINAL) {
		case 81:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: tag_def7_dec */
		{
#line 2037 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if ((ZId)->isvar)fail("Tag %s declared as variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=0; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused = 0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 7473 "syntax.c"
		}
		/* END OF ACTION: tag_def7_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: proc_def1 */
		{
#line 1572 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIa));
#line 7496 "syntax.c"
		}
		/* END OF ACTION: proc_def1 */
		ZRproc__def__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: proc_def2 */
		{
#line 1577 "syntax.act"

    RESET_TDF((ZIc));
    o_make_id_tagdef(out_tdfint32(UL(local_name(&(ZId)->idname.name, tag_ent))),
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), (ZIf))); },
      append_TDF(&(ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(ZIf)) {
	o_make_id_tagdec(out_tdfint32(UL(non_local(&(ZId)->idname.name,tag_ent))),
	    {},
	    if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	    o_proc);
	INC_LIST;
    }
    (ZId)->isdeffed=1;
    if (!(ZIf)) {(ZId)->next = tagdecs; tagdecs = (ZId);}
#line 7523 "syntax.c"
		}
		/* END OF ACTION: proc_def2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_error_code_list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		read_error_code ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: errc1 */
		{
#line 469 "syntax.act"

    current_TDF->no = 1;
#line 7550 "syntax.c"
		}
		/* END OF ACTION: errc1 */
		ZR625 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 7567 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRcallee__var__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 31:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cevaropt2 */
			{
#line 381 "syntax.act"

    g_ce_v = 1;
#line 7585 "syntax.c"
			}
			/* END OF ACTION: cevaropt2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cevaropt1 */
			{
#line 377 "syntax.act"

    g_ce_v = 0;
#line 7597 "syntax.c"
			}
			/* END OF ACTION: cevaropt1 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZRtag__dec(void)
{
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_dec1_dec */
			{
#line 1894 "syntax.act"

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0)fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = xmalloc(sizeof *(ZId)); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7632 "syntax.c"
			}
			/* END OF ACTION: tag_dec1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRaccess__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec6 */
			{
#line 1947 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 7653 "syntax.c"
			}
			/* END OF ACTION: tag_dec6 */
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec2 */
			{
#line 1906 "syntax.act"

    g_shtokname = &(ZId)->sh.shtok;
#line 7666 "syntax.c"
			}
			/* END OF ACTION: tag_dec2 */
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec5 */
			{
#line 1934 "syntax.act"

    RESET_TDF((ZIc));
    (ZId)->iscommon = 1;
    o_common_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 1;
    tagdecs = (ZId);
#line 7695 "syntax.c"
			}
			/* END OF ACTION: tag_dec5 */
		}
		break;
	case 53:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_dec1_dec */
			{
#line 1894 "syntax.act"

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0)fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = xmalloc(sizeof *(ZId)); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7721 "syntax.c"
			}
			/* END OF ACTION: tag_dec1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRaccess__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec6 */
			{
#line 1947 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 7742 "syntax.c"
			}
			/* END OF ACTION: tag_dec6 */
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec2 */
			{
#line 1906 "syntax.act"

    g_shtokname = &(ZId)->sh.shtok;
#line 7755 "syntax.c"
			}
			/* END OF ACTION: tag_dec2 */
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec4 */
			{
#line 1922 "syntax.act"

    RESET_TDF((ZIc));
    o_make_id_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 0;
    tagdecs = (ZId);
#line 7783 "syntax.c"
			}
			/* END OF ACTION: tag_dec4 */
		}
		break;
	case 125:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_dec1_dec */
			{
#line 1894 "syntax.act"

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0)fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = xmalloc(sizeof *(ZId)); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7809 "syntax.c"
			}
			/* END OF ACTION: tag_dec1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRaccess__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec6 */
			{
#line 1947 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 7830 "syntax.c"
			}
			/* END OF ACTION: tag_dec6 */
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec2 */
			{
#line 1906 "syntax.act"

    g_shtokname = &(ZId)->sh.shtok;
#line 7843 "syntax.c"
			}
			/* END OF ACTION: tag_dec2 */
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec3 */
			{
#line 1910 "syntax.act"

    RESET_TDF((ZIc));
    o_make_var_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 1;
    tagdecs = (ZId);
#line 7871 "syntax.c"
			}
			/* END OF ACTION: tag_dec3 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtag__intro(void)
{
	switch (CURRENT_TERMINAL) {
	case 61:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;
			int ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: intro1_dec */
			{
#line 1176 "syntax.act"

    /* (ZIb), (ZIe) uninitialised */
    char* n = lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    (ZId) = xmalloc(sizeof *(ZId)); (ZId)->isdeffed = 1; (ZId)->hassh=0; (ZId)->iskept=0;
    NEW_IDNAME((ZId)->idname, n, tag_ent);
    g_has_vis = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7912 "syntax.c"
			}
			/* END OF ACTION: intro1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRaccess__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro2 */
			{
#line 1187 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
    (ZIe) = g_has_vis;
#line 7934 "syntax.c"
			}
			/* END OF ACTION: intro2 */
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro5 */
			{
#line 1214 "syntax.act"

    RESET_TDF((ZIc));
    intro_acc = (ZIa);
    intro_init = (ZIb);
    (ZId)->isvar=0;
    if ((ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (ZId)->next = localdecs;
    localdecs = (ZId);
#line 7965 "syntax.c"
			}
			/* END OF ACTION: intro5 */
		}
		break;
	case 124:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;
			int ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: intro1_dec */
			{
#line 1176 "syntax.act"

    /* (ZIb), (ZIe) uninitialised */
    char* n = lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    (ZId) = xmalloc(sizeof *(ZId)); (ZId)->isdeffed = 1; (ZId)->hassh=0; (ZId)->iskept=0;
    NEW_IDNAME((ZId)->idname, n, tag_ent);
    g_has_vis = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7991 "syntax.c"
			}
			/* END OF ACTION: intro1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRaccess__opt ();
			ZR669 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_exp(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		int ZIc;
		unsigned_long ZId;
		int ZIe;

		/* BEGINNING OF ACTION: exphold1_dec */
		{
#line 681 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    (ZId) = cLINE;
    (ZIe) = bind;
    if (!(ZIc) || line_no_tok != -1) { SET_TDF((ZIb), &(ZIa)); }
#line 8043 "syntax.c"
		}
		/* END OF ACTION: exphold1_dec */
		ZRexp__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exphold2 */
		{
#line 690 "syntax.act"

    if (!(ZIc) || line_no_tok != -1) {
	SET((ZIb));
	RESET_TDF((ZIb));
	if (line_no_tok != -1) {
	    o_exp_apply_token(
		o_make_tok(out_tdfint32(UL(cname_to_lname(line_no_tok,tok_ent)))),
		{ append_TDF(&(ZIa),1);
		  o_make_sourcemark(FILENAME(),
			o_make_nat(out_tdfint32((ZId))),
			o_make_nat(out_tdfint32(UL((ZIe)))));
			o_make_sourcemark(FILENAME(),
			    o_make_nat(out_tdfint32(cLINE)),
			    o_make_nat(out_tdfint32(UL(bind))));
		});
	 } else append_TDF(&(ZIa),1);
    }
#line 8071 "syntax.c"
		}
		/* END OF ACTION: exphold2 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 8083 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRtag__def(void)
{
	switch (CURRENT_TERMINAL) {
	case 26:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;
			PTR_char ZIe;
			int ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def1_dec */
			{
#line 1973 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar)fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8123 "syntax.c"
			}
			/* END OF ACTION: tag_def1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsignature__opt ();
			ZR678 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe, &ZIf);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 61:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;
			PTR_char ZIe;
			int ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def7_dec */
			{
#line 2037 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if ((ZId)->isvar)fail("Tag %s declared as variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=0; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused = 0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8171 "syntax.c"
			}
			/* END OF ACTION: tag_def7_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsignature__opt ();
			ZR679 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe, &ZIf);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 106:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;
			PTR_char ZIe;
			int ZIf;
			TDF ZIg;
			PTR_char ZIh;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def1_dec */
			{
#line 1973 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar)fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8221 "syntax.c"
			}
			/* END OF ACTION: tag_def1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tgdef10_dec */
			{
#line 2137 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIg));
#line 8242 "syntax.c"
			}
			/* END OF ACTION: tgdef10_dec */
			ZRvariety__opt ();
			switch (CURRENT_TERMINAL) {
			case 36:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tgdef11_dec */
			{
#line 2142 "syntax.act"

    (ZIh) = lex_v.val.name;
    if ((ZId)->hassh)fail("Two declaration shapes for %s", (ZIe));
    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIa));
    o_make_nof_int(append_TDF(&(ZIg), 0),
	o_make_string(out_tdfstring_bytes((ZIh), 8, UI(strlen((ZIh)) +1))));
#line 8266 "syntax.c"
			}
			/* END OF ACTION: tgdef11_dec */
			switch (CURRENT_TERMINAL) {
			case 85:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def12 */
			{
#line 1956 "syntax.act"

    RESET_TDF((ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(ZId)->idname.name, tag_ent))),
	{}, {}, append_TDF(&(ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(ZId)->idname.name,tag_ent))),
	    {}, {},
	    o_nof(o_make_nat(out_tdfint32(UL(strlen((ZIh)) +1))),
		o_integer(append_TDF(&(ZIg), 0))));
       INC_LIST;
    }
    (ZId)->isdeffed=1;
    if (!(ZIf)) { (ZId)->next = tagdecs; tagdecs = (ZId); }
#line 8294 "syntax.c"
			}
			/* END OF ACTION: tag_def12 */
		}
		break;
	case 124:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;
			PTR_char ZIe;
			int ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def1_dec */
			{
#line 1973 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar)fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8329 "syntax.c"
			}
			/* END OF ACTION: tag_def1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsignature__opt ();
			ZR677 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe, &ZIf);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRotagexp__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 10: case 19: case 22: case 28:
	case 41: case 42: case 43: case 44:
	case 45: case 52: case 54: case 55:
	case 58: case 61: case 62: case 68:
	case 76: case 77: case 78: case 79:
	case 81: case 82: case 84: case 85:
	case 86: case 88: case 98: case 99:
	case 100: case 102: case 103: case 104:
	case 105: case 107: case 109: case 110:
	case 111: case 124:
		{
			ZRotagexp__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: otagel_opt1 */
			{
#line 1544 "syntax.act"

    current_TDF->no = 0;
#line 8387 "syntax.c"
			}
			/* END OF ACTION: otagel_opt1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtok__formal__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_Tokdec ZIa;

		/* BEGINNING OF ACTION: tok_fml1_dec */
		{
#line 2283 "syntax.act"

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    if ((ZIa)!= (Tokdec*)0)fail("Token parameter name %s must be unique", n);
    (ZIa) = xmalloc(sizeof *(ZIa)); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->isdeffed = 1; (ZIa)->isused = 0; (ZIa)->iskept=0;
    (ZIa)->next = (Tokdec*)0;
#line 8420 "syntax.c"
		}
		/* END OF ACTION: tok_fml1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRfull__sortname ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tok_fml2 */
		{
#line 2291 "syntax.act"

    (ZIa)->sort.ressort = g_sname;
    (ZIa)->sort.pars = (Tokpar*)0;  /* no pars in formal pars */
    g_tokformals = (ZIa);
#line 8449 "syntax.c"
		}
		/* END OF ACTION: tok_fml2 */
		ZR629 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRuntidy__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 23:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: untidy4 */
			{
#line 2321 "syntax.act"

    g_unt = 2;
#line 8476 "syntax.c"
			}
			/* END OF ACTION: untidy4 */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			ZR657 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: untidy1 */
			{
#line 2309 "syntax.act"

    g_unt = 0;
#line 8498 "syntax.c"
			}
			/* END OF ACTION: untidy1 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRcaller__var__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 31:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: crvaropt2 */
			{
#line 404 "syntax.act"

    g_cr_v = 1;
#line 8524 "syntax.c"
			}
			/* END OF ACTION: crvaropt2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: crvaropt1 */
			{
#line 400 "syntax.act"

    g_cr_v = 0;
#line 8536 "syntax.c"
			}
			/* END OF ACTION: crvaropt1 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZRproc__def__body(void)
{
	switch (CURRENT_TERMINAL) {
	case 50:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			int ZIf;
			int ZIg;
			int ZIh;
			PTR_Tagdec ZIi;
			PTR_Labdec ZIj;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gproc1_dec */
			{
#line 1110 "syntax.act"

    /* (ZIb), (ZIc), (ZId) uninitialised */
    /* (ZIf), (ZIg) (ZIh) uninitialised */
    (ZIi) = localdecs;
    (ZIj) = labdecs;
    localdecs = (Tagdec*)0;
    labdecs = (Labdec *)0;
    SET_TDF((ZIe), &(ZIa));
#line 8575 "syntax.c"
			}
			/* END OF ACTION: gproc1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc2 */
			{
#line 1120 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 8589 "syntax.c"
			}
			/* END OF ACTION: gproc2 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRtagshacc__list__opt ();
			ZRcaller__var__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc3 */
			{
#line 1125 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
    (ZIf) = g_cr_v;
#line 8612 "syntax.c"
			}
			/* END OF ACTION: gproc3 */
			switch (CURRENT_TERMINAL) {
			case 93:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRtagshacc__list__opt ();
			ZRcallee__var__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc4 */
			{
#line 1131 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
    (ZIg) = g_ce_v;
#line 8635 "syntax.c"
			}
			/* END OF ACTION: gproc4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRuntidy__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc5 */
			{
#line 1137 "syntax.act"

    (ZIh) = g_unt;
#line 8655 "syntax.c"
			}
			/* END OF ACTION: gproc5 */
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc6 */
			{
#line 1141 "syntax.act"

    RESET_TDF((ZIe));
    o_make_general_proc(append_TDF(&(ZIa),1),
			do_procprops((ZIf)+2*(ZIg)+4*(ZIh)),
			{ append_TDF(&(ZIb),1);
			  current_TDF->no = (ZIb).no;},
			{ append_TDF(&(ZIc),1);
			  current_TDF->no = (ZIc).no;},
			append_TDF(&(ZId),1))
    while (labdecs != (Labdec *)0) {
	if (!labdecs->declared) {
	    fail("Label %s not declared", labdecs->idname.id);
	}
	labdecs = labdecs->next;
    }
    localdecs = (ZIi);
    labdecs = (ZIj);
#line 8683 "syntax.c"
			}
			/* END OF ACTION: gproc6 */
		}
		break;
	case 21: case 32: case 46: case 56:
	case 64: case 83: case 94: case 95:
	case 96: case 97: case 101: case 121:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			PTR_Tagdec ZIf;
			PTR_Labdec ZIg;

			/* BEGINNING OF ACTION: expproc1_dec */
			{
#line 750 "syntax.act"

    /* (ZIa), (ZIb), (ZIc) uninitialised */
    (ZIf) = localdecs;
    (ZIg) = labdecs;
    localdecs = (Tagdec*)0;
    labdecs = (Labdec *)0;
    SET_TDF((ZIe), &(ZId));
#line 8710 "syntax.c"
			}
			/* END OF ACTION: expproc1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expproc2 */
			{
#line 759 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIa))
#line 8724 "syntax.c"
			}
			/* END OF ACTION: expproc2 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRtagshacc__list__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expproc3 */
			{
#line 764 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 8745 "syntax.c"
			}
			/* END OF ACTION: expproc3 */
			ZRvarintro__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expproc4 */
			{
#line 769 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
#line 8759 "syntax.c"
			}
			/* END OF ACTION: expproc4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expproc5 */
			{
#line 774 "syntax.act"

    RESET_TDF((ZIe));
    o_make_proc(append_TDF(&(ZId),1),
		{ append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no;},
		if ((ZIb).no !=0) {OPTION(append_TDF(&(ZIb),1)); },
		append_TDF(&(ZIc),1);)
    while (labdecs != (Labdec *)0) {
	if (!labdecs->declared) {
	    fail("Label %s not declared", labdecs->idname.id);
	}
	labdecs = labdecs->next;
    }
    localdecs = (ZIf);
    labdecs = (ZIg);
#line 8791 "syntax.c"
			}
			/* END OF ACTION: expproc5 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRlabelled__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;

		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: llist1_dec */
		{
#line 1405 "syntax.act"

    (ZIb) = current_TDF;
    INIT_TDF(&(ZIa));
    current_TDF = &g_lablist;
#line 8831 "syntax.c"
		}
		/* END OF ACTION: llist1_dec */
		read_label ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: llist2 */
		{
#line 1417 "syntax.act"

    if (g_labdec != (Labdec*)0) {
	if (g_labdec->declared) {
	    fail("Label %s set twice", g_labdec->idname.id);
	}
	g_labdec->declared = 1;
    }
    current_TDF = &(ZIa);
#line 8850 "syntax.c"
		}
		/* END OF ACTION: llist2 */
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRexp__sequence ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: llist5 */
		{
#line 1429 "syntax.act"

    RESET_TDF((ZIb));
    append_TDF(&(ZIa), 1);
#line 8871 "syntax.c"
		}
		/* END OF ACTION: llist5 */
		ZR668 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRoffset__exp__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		read_exp ();
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		case 130:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		read_exp ();
		ZR663 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRbitfield__sign(void)
{
	switch (CURRENT_TERMINAL) {
	case 16: case 17: case 18:
		{
			read_bool ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			ZRvariety__sign ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bvariety2 */
			{
#line 310 "syntax.act"

    if (issigned) { o_true; }
    else { o_false; }
#line 8943 "syntax.c"
			}
			/* END OF ACTION: bvariety2 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtok__dec(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		PTR_Tokdec ZIc;

		switch (CURRENT_TERMINAL) {
		case 113:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: tok_dec1_dec */
		{
#line 2177 "syntax.act"

    char *n = lex_v.val.name;
    (ZIc) = find_tok(n);
    if ((ZIc) != (Tokdec *)0)fail("Token %s declared twice", n);
    SELECT_UNIT(tokdec_unit);
    (ZIc) = xmalloc(sizeof *(ZIc));
    NEW_IDNAME((ZIc)->idname, n, tok_ent);
    SET_TDF((ZIb), &(ZIa));
#line 8986 "syntax.c"
		}
		/* END OF ACTION: tok_dec1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRsignature__opt ();
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		case 130:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 79:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRsortname__list__opt ();
		switch (CURRENT_TERMINAL) {
		case 30:
			break;
		case 130:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRfull__sortname ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tok_dec2 */
		{
#line 2186 "syntax.act"

    RESET_TDF((ZIb));
    (ZIc)->sort.ressort = g_sname;
    (ZIc)->sort.pars = g_tokpars;
    (ZIc)->next = tokdecs;
    (ZIc)->isdeffed = 0; (ZIc)->isused = 0; (ZIc)->iskept=0; (ZIc)->isparam=0;
    tokdecs = (ZIc);
    o_make_tokdec(out_tdfint32(LOCNAME((ZIc)->idname)),
	if ((ZIa).no != 0) { OPTION(append_TDF(&(ZIa), 1)); },
	out_toksort(&(ZIc)->sort));
    INC_LIST;
#line 9044 "syntax.c"
		}
		/* END OF ACTION: tok_dec2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRexp__comma__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
ZL2_exp__comma__list:;
	{
		read_exp ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: expl2 */
		{
#line 714 "syntax.act"

    current_TDF->no++;
#line 9072 "syntax.c"
		}
		/* END OF ACTION: expl2 */
		/* BEGINNING OF INLINE: 624 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: exp_comma_list */
					goto ZL2_exp__comma__list;
					/* END OF INLINE: exp_comma_list */
				}
				/*UNREACHED*/
			default:
				break;
			}
		}
		/* END OF INLINE: 624 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRexp__body(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		ZRunary__exp ();
		ZR632 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtok__def(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		TDF ZIb;
		PTR_TDF ZIc;
		PTR_Tokdec ZId;
		int ZIe;

		/* BEGINNING OF ACTION: tok_def0 */
		{
#line 2200 "syntax.act"

    search_for_toks = 0;
#line 9136 "syntax.c"
		}
		/* END OF ACTION: tok_def0 */
		switch (CURRENT_TERMINAL) {
		case 114:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: tok_def1_dec */
		{
#line 2204 "syntax.act"

    char *n = lex_v.val.name;
    (ZId) = find_tok(n);
    (ZIa) = g_tok_defn;
    SELECT_UNIT(tokdef_unit);
    search_for_toks = 1;
    if ((ZId) != (Tokdec *)0) {
	if ((ZId)->isdeffed)fail("Token %s defined twice", n);
	(ZIe) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	NEW_IDNAME((ZId)->idname, n, tok_ent);
	(ZIe) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 9164 "syntax.c"
		}
		/* END OF ACTION: tok_def1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRtok__def__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tok_def2 */
		{
#line 2220 "syntax.act"

    RESET_TDF((ZIc));
    (ZId)->sort = g_toksort;
    (ZId)->isdeffed =1; (ZId)->iskept=0; (ZId)->isparam = 0;
    o_make_tokdef(out_tdfint32(UL(local_name(&(ZId)->idname.name,tok_ent))),
	if ((ZIb).no != 0) { OPTION(append_TDF(&(ZIb), 1)); },
	append_TDF(&g_tok_defn, 1));
    INC_LIST;
    if (!(ZIe)) { (ZId)->next = tokdecs; tokdecs = (ZId); (ZId)->isused=0; }
    g_tok_defn = (ZIa);
#line 9199 "syntax.c"
		}
		/* END OF ACTION: tok_def2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRunary__exp(void)
{
ZL2_unary__exp:;
	switch (CURRENT_TERMINAL) {
	case 19:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cseexp1_dec */
			{
#line 407 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 9227 "syntax.c"
			}
			/* END OF ACTION: cseexp1_dec */
			read_exp ();
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cseexp2 */
			{
#line 412 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 9247 "syntax.c"
			}
			/* END OF ACTION: cseexp2 */
			ZRrange__label__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cseexp3 */
			{
#line 417 "syntax.act"

    RESET_TDF((ZIc));
    o_case(o_false, append_TDF(&(ZIa),1),
	   { append_TDF(&(ZIb),1); current_TDF->no = (ZIb).no; });
#line 9262 "syntax.c"
			}
			/* END OF ACTION: cseexp3 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 28:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 79:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expcons1_dec */
			{
#line 653 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 9294 "syntax.c"
			}
			/* END OF ACTION: expcons1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcons2 */
			{
#line 658 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 9308 "syntax.c"
			}
			/* END OF ACTION: expcons2 */
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRoffset__exp__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcons3 */
			{
#line 663 "syntax.act"

    RESET_TDF((ZIc));
    o_make_compound(append_TDF(&(ZIa),1),
		    { append_TDF(&(ZIb),1); current_TDF->no = (ZIb).no; });
#line 9337 "syntax.c"
			}
			/* END OF ACTION: expcons3 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 42:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 639 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: unary_exp */
						goto ZL2_unary__exp;
						/* END OF INLINE: unary_exp */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 9377 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 9398 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 9419 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: exp1 */
						{
#line 496 "syntax.act"

    RESET_TDF((ZId));
    o_exp_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
#line 9441 "syntax.c"
						}
						/* END OF ACTION: exp1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 639 */
		}
		break;
	case 45:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: query_type2 */
			{
#line 1600 "syntax.act"

    query_t = lex_float__query;
#line 9474 "syntax.c"
			}
			/* END OF ACTION: query_type2 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 866 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 9491 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 872 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 9505 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 877 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 9519 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 882 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
#line 9559 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 52:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expfail1 */
			{
#line 678 "syntax.act"

    o_fail_installer(read_string());
#line 9579 "syntax.c"
			}
			/* END OF ACTION: expfail1 */
		}
		break;
	case 58:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			PTR_Labdec ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: explab1_dec */
			{
#line 717 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIe) = labdecs;
    (ZIc) = g_lablist;
    INIT_TDF(&g_lablist);
    SET_TDF((ZId), &(ZIa));
#line 9602 "syntax.c"
			}
			/* END OF ACTION: explab1_dec */
			switch (CURRENT_TERMINAL) {
			case 76:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: explab2 */
			{
#line 725 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 9623 "syntax.c"
			}
			/* END OF ACTION: explab2 */
			switch (CURRENT_TERMINAL) {
			case 11:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRlabelled__list ();
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: explab3 */
			{
#line 730 "syntax.act"

    RESET_TDF((ZId));
    o_labelled({ append_TDF(&g_lablist,1);
		  current_TDF->no = g_lablist.no;},
		  append_TDF(&(ZIa), 1),
		  { append_TDF(&(ZIb),1);
		    current_TDF->no = g_lablist.no;});
    tidy_labels((ZIe));
    g_lablist = (ZIc);
#line 9656 "syntax.c"
			}
			/* END OF ACTION: explab3 */
		}
		break;
	case 68:
		{
			ADVANCE_LEXER;
			ZR645 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 76:
		{
			ADVANCE_LEXER;
			ZRexp__sequence ();
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 77:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: query_type5 */
			{
#line 1612 "syntax.act"

    query_t = lex_offset__query;
#line 9701 "syntax.c"
			}
			/* END OF ACTION: query_type5 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 866 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 9718 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 872 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 9732 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 877 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 9746 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 882 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
#line 9786 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 78:
		{
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR646 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 79:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: chvar1_dec */
			{
#line 384 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 9832 "syntax.c"
			}
			/* END OF ACTION: chvar1_dec */
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: chvar2 */
			{
#line 389 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 9846 "syntax.c"
			}
			/* END OF ACTION: chvar2 */
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: chvar3 */
			{
#line 394 "syntax.act"

    RESET_TDF((ZIc));
    o_change_variety(o_wrap, append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 9867 "syntax.c"
			}
			/* END OF ACTION: chvar3 */
		}
		break;
	case 81:
		{
			ADVANCE_LEXER;
			ZRproc__def__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 82:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: query_type4 */
			{
#line 1608 "syntax.act"

    query_t = lex_proc__query;
#line 9896 "syntax.c"
			}
			/* END OF ACTION: query_type4 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 866 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 9913 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 872 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 9927 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 877 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 9941 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 882 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
#line 9981 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 84:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			int ZIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: query_type3 */
			{
#line 1604 "syntax.act"

    query_t = lex_ptr__query;
#line 10007 "syntax.c"
			}
			/* END OF ACTION: query_type3 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 866 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 10024 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 872 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 10038 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 877 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 10052 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 882 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
#line 10092 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 86:
		{
			ADVANCE_LEXER;
			ZR648 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 88:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;
			PTR_Labdec ZIe;
			int ZIf;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exprep1_dec */
			{
#line 790 "syntax.act"

    /* (ZIb), (ZIc), (ZIf) uninitialised */
    (ZIe) = labdecs;
    SET_TDF((ZId), &(ZIa));
#line 10131 "syntax.c"
			}
			/* END OF ACTION: exprep1_dec */
			ZRrepeat__starter__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep2 */
			{
#line 796 "syntax.act"

    (ZIf) = defaultlab;
    defaultlab = -1;
#line 10145 "syntax.c"
			}
			/* END OF ACTION: exprep2 */
			switch (CURRENT_TERMINAL) {
			case 76:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRlabset__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep3 */
			{
#line 801 "syntax.act"

    (ZIc) = optlab;
    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 10167 "syntax.c"
			}
			/* END OF ACTION: exprep3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep4 */
			{
#line 807 "syntax.act"

    RESET_TDF((ZId));
    o_repeat(append_TDF(&(ZIc),1), append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
    tidy_labels((ZIe));
    defaultlab = (ZIf);
#line 10183 "syntax.c"
			}
			/* END OF ACTION: exprep4 */
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 99:
		{
			TDF ZIa;
			TDF ZIb;

			ADVANCE_LEXER;
			ZR633 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10213 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10235 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 102:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: szexp1_dec */
			{
#line 1882 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 10265 "syntax.c"
			}
			/* END OF ACTION: szexp1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: sizeexp2 */
			{
#line 1799 "syntax.act"

    RESET_TDF((ZIb));
    o_offset_pad(o_alignment(append_TDF(&(ZIa), 0)),
		 o_shape_offset(append_TDF(&(ZIa), 1)));
#line 10280 "syntax.c"
			}
			/* END OF ACTION: sizeexp2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 103:
		{
			ADVANCE_LEXER;
			ZR647 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 22: case 55:
		{
			TDF ZIa;
			TDF ZIb;

			ZRinteger ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat2 */
			{
#line 1761 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(intvalue));
#line 10317 "syntax.c"
			}
			/* END OF ACTION: signed_nat2 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10327 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10349 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 54: case 109: case 110: case 111:
		{
			read_tag ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptag1 */
			{
#line 863 "syntax.act"

    TDF tg;
    tg = *current_TDF;
    INIT_TDF(current_TDF);
    o_obtain_tag(append_TDF(&tg,1));
#line 10376 "syntax.c"
			}
			/* END OF ACTION: exptag1 */
			ZR646 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 61: case 124:
		{
			PTR_Tagdec ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			Name ZIf;
			int ZIg;

			/* BEGINNING OF ACTION: expdec1_dec */
			{
#line 669 "syntax.act"

    (ZIa) = localdecs;
#line 10401 "syntax.c"
			}
			/* END OF ACTION: expdec1_dec */
			ZRtag__intro ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ibody1_dec */
			{
#line 1160 "syntax.act"

    (ZIg) = localdecs->isvar;
    (ZIb) = intro_acc;
    (ZIc) = intro_init;
    (ZIf) = localdecs->idname.name;
    SET_TDF((ZIe), &(ZId));
#line 10418 "syntax.c"
			}
			/* END OF ACTION: ibody1_dec */
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: introbody2 */
			{
#line 1233 "syntax.act"

    RESET_TDF((ZIe));
    if ((ZIg)) {
	o_variable(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    } else {
	o_identify(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    }
#line 10440 "syntax.c"
			}
			/* END OF ACTION: introbody2 */
			/* BEGINNING OF ACTION: expdec2 */
			{
#line 673 "syntax.act"

    localdecs = (ZIa);
#line 10448 "syntax.c"
			}
			/* END OF ACTION: expdec2 */
		}
		break;
	case 85: case 104: case 105: case 107:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: expstr1_dec */
			{
#line 844 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 10465 "syntax.c"
			}
			/* END OF ACTION: expstr1_dec */
			read_string ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expstr2 */
			{
#line 849 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 10479 "syntax.c"
			}
			/* END OF ACTION: expstr2 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expstring2 */
			{
#line 854 "syntax.act"

    RESET_TDF((ZIc));
    o_make_nof_int(append_TDF(&(ZIb), 1), append_TDF(&(ZIa), 1););
#line 10506 "syntax.c"
			}
			/* END OF ACTION: expstring2 */
		}
		break;
	case 44:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			int ZIf;
			unsigned_long ZIg;

			/* BEGINNING OF ACTION: fden1_dec */
			{
#line 912 "syntax.act"

    /* (ZIc), (ZId) uninitialised */
    (ZIf) = 0;
    (ZIg) = UL(radix);
    SET_TDF((ZIe), &(ZIa));
    out_tdfstring_bytes(fformat(lex_v.val.name,lnum), 8, UI(lnum));
    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 10532 "syntax.c"
			}
			/* END OF ACTION: fden1_dec */
			ADVANCE_LEXER;
			ZRexponent__opt ();
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: fden3 */
			{
#line 932 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
#line 10553 "syntax.c"
			}
			/* END OF ACTION: fden3 */
			read_floating_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden4 */
			{
#line 937 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
#line 10567 "syntax.c"
			}
			/* END OF ACTION: fden4 */
			ZRrounding__mode__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden5 */
			{
#line 942 "syntax.act"

    RESET_TDF((ZIe));
    o_make_floating(append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1),
		    if ((ZIf)) { o_true; } else { o_false; },
		    o_make_string(append_TDF(&(ZIa), 1)),
		    o_make_nat(out_tdfint32((ZIg))),
		    append_TDF(&(ZIb), 1));
#line 10586 "syntax.c"
			}
			/* END OF ACTION: fden5 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 41: case 98:
		{
			int ZI642;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZI642) = lex_v.val.v;
#line 10607 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ZR643 (&ZI642);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 43: case 100:
		{
			PTR_Tokdec ZI640;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZI640) = lex_v.val.tokname;
    (ZI640)->isused = 1;
#line 10627 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ZR641 (&ZI640);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 62:
		{
			TDF ZIa;
			TDF ZIb;

			/* BEGINNING OF ACTION: signed_nat4 */
			{
#line 1769 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(cLINE));
#line 10647 "syntax.c"
			}
			/* END OF ACTION: signed_nat4 */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10658 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10680 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 10:
		{
			TDF ZI637;
			PTR_TDF ZI638;
			TDF ZIa;
			TDF ZIb;

			/* BEGINNING OF ACTION: signed_nat7_dec */
			{
#line 1781 "syntax.act"

    SET_TDF((ZI638), &(ZI637));
    if (strcmp(lex_v.val.name, "+"))fail("Only + or - on NATs");
#line 10705 "syntax.c"
			}
			/* END OF ACTION: signed_nat7_dec */
			ADVANCE_LEXER;
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat8 */
			{
#line 1786 "syntax.act"

    RESET_TDF((ZI638));
    o_snat_from_nat(o_false, append_TDF(&(ZI637),1));
#line 10720 "syntax.c"
			}
			/* END OF ACTION: signed_nat8 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1458 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10730 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1464 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10752 "syntax.c"
			}
			/* END OF ACTION: mint2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtagshacc__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
ZL2_tagshacc__list:;
	{
		ZRtagshacc ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tagshacc_l2 */
		{
#line 2121 "syntax.act"

    current_TDF->no++;
#line 10793 "syntax.c"
		}
		/* END OF ACTION: tagshacc_l2 */
		/* BEGINNING OF INLINE: 623 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: tagshacc_list */
					goto ZL2_tagshacc__list;
					/* END OF INLINE: tagshacc_list */
				}
				/*UNREACHED*/
			default:
				break;
			}
		}
		/* END OF INLINE: 623 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRshapetok(void)
{
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shtokdb */
			{
#line 1743 "syntax.act"

    * g_shtokname = *(tokfordoublesh());
#line 10831 "syntax.c"
			}
			/* END OF ACTION: shtokdb */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shtokflt */
			{
#line 1747 "syntax.act"

    * g_shtokname = *(tokforfloatsh());
#line 10844 "syntax.c"
			}
			/* END OF ACTION: shtokflt */
		}
		break;
	case 21: case 56: case 64: case 97:
	case 101: case 121:
		{
			ZRvariety__sign ();
			ZR675 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 83: case 94: case 95: case 96:
		{
			PTR_TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			int ZId;

			/* BEGINNING OF ACTION: shtok1_dec */
			{
#line 1734 "syntax.act"

    (ZIa) = current_TDF;
    (ZId) = current_Unit;
    select_tokdef_unit();
    * g_shtokname = next_name(tok_ent);
    SET_TDF((ZIc), &(ZIb));
#line 10876 "syntax.c"
			}
			/* END OF ACTION: shtok1_dec */
			ZRnonst__shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shapetok2 */
			{
#line 1709 "syntax.act"

    RESET_TDF((ZIc));
    o_make_tokdef(out_tdfint32(UL(g_shtokname->unit_name)), {},
		  o_token_def(o_shape, {}, append_TDF(&(ZIb), 1)));
    INC_LIST;
    current_Unit = (ZId);
    RESET_TDF((ZIa));
#line 10894 "syntax.c"
			}
			/* END OF ACTION: shapetok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRalignment__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		read_alignment ();
		ZR622 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_error_treatment(void)
{
ZL2_error__treatment:;
	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 684 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: error_treatment */
						goto ZL2_error__treatment;
						/* END OF INLINE: error_treatment */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 10962 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						ADVANCE_LEXER;
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 10990 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						read_error_treatment ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 11010 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_error_treatment ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: errt1 */
						{
#line 476 "syntax.act"

    RESET_TDF((ZId));
    o_errt_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		append_TDF(&(ZIc),1));
#line 11025 "syntax.c"
						}
						/* END OF ACTION: errt1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 684 */
		}
		break;
	case 79:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: errt2_dec */
			{
#line 482 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 11055 "syntax.c"
			}
			/* END OF ACTION: errt2_dec */
			read_error_code_list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: errt5 */
			{
#line 491 "syntax.act"

    RESET_TDF((ZIb));
    o_trap({append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no; });
#line 11069 "syntax.c"
			}
			/* END OF ACTION: errt5 */
			switch (CURRENT_TERMINAL) {
			case 30:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 54: case 59: case 60:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: errt2_dec */
			{
#line 482 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 11091 "syntax.c"
			}
			/* END OF ACTION: errt2_dec */
			read_label ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: errt3 */
			{
#line 486 "syntax.act"

    RESET_TDF((ZIb));
    o_error_jump(append_TDF(&(ZIa),1));
#line 11105 "syntax.c"
			}
			/* END OF ACTION: errt3 */
		}
		break;
	case 38:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 11119 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 11128 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 40:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 11143 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 11152 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 11170 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRcallee(void)
{
	switch (CURRENT_TERMINAL) {
	case 33:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: callee3_dec */
			{
#line 357 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 11193 "syntax.c"
			}
			/* END OF ACTION: callee3_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: callee4 */
			{
#line 362 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 11214 "syntax.c"
			}
			/* END OF ACTION: callee4 */
			switch (CURRENT_TERMINAL) {
			case 25:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: callee5 */
			{
#line 367 "syntax.act"

    RESET_TDF((ZIc));
    o_make_dynamic_callees(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 11235 "syntax.c"
			}
			/* END OF ACTION: callee5 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 92:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: callee6 */
			{
#line 373 "syntax.act"

    o_same_callees;
#line 11255 "syntax.c"
			}
			/* END OF ACTION: callee6 */
		}
		break;
	default:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: callee1_dec */
			{
#line 348 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 11270 "syntax.c"
			}
			/* END OF ACTION: callee1_dec */
			read_exp_list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: callee2 */
			{
#line 352 "syntax.act"

    RESET_TDF((ZIb));
    o_make_callee_list({ append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no;});
#line 11284 "syntax.c"
			}
			/* END OF ACTION: callee2 */
		}
		break;
	case 130:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_al_tag(void)
{
ZL2_al__tag:;
	switch (CURRENT_TERMINAL) {
	case 4:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: al_tag */
			goto ZL2_al__tag;
			/* END OF INLINE: al_tag */
		}
		/*UNREACHED*/
	case 54:
		{
			/* BEGINNING OF ACTION: al_tag1 */
			{
#line 245 "syntax.act"

    char * n =lex_v.val.name;
    Al_tagdec * x = find_al_tag(n);
    if (x== (Al_tagdec*)0) {
	x= xmalloc(sizeof *x);
	x->isdeffed =0; x->iskept=0;
	NEW_IDNAME(x->idname, n, al_tag_ent);
	x->next = al_tagdecs;
	al_tagdecs = x;
    }
    x->isused =1;
    make_al_tag(&x->idname.name);
#line 11335 "syntax.c"
			}
			/* END OF ACTION: al_tag1 */
			ADVANCE_LEXER;
		}
		break;
	case 5:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 11351 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 11360 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 11378 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_exp_list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		/* BEGINNING OF ACTION: expl1 */
		{
#line 710 "syntax.act"

    current_TDF->no=0;
#line 11396 "syntax.c"
		}
		/* END OF ACTION: expl1 */
		ZR656 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 11413 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRelement(void)
{
	switch (CURRENT_TERMINAL) {
	case 6:
		{
			ZRal__tag__def ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 81:
		{
			ZRproc__def ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 108:
		{
			ZRstruct__def ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 27: case 53: case 125:
		{
			ZRtag__dec ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 26: case 61: case 106: case 124:
		{
			ZRtag__def ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 113:
		{
			ZRtok__dec ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 114:
		{
			ZRtok__def ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR622(void)
{
ZL2_622:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: al_list1_dec */
			{
#line 216 "syntax.act"

    (ZIb) = current_TDF;
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 11514 "syntax.c"
			}
			/* END OF ACTION: al_list1_dec */
			ADVANCE_LEXER;
			read_alignment ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: al_list2 */
			{
#line 224 "syntax.act"

    TDF second;
    second = *current_TDF;
    INIT_TDF((ZIb));
    RESET_TDF((ZIb));
    o_unite_alignments(append_TDF(&(ZIa),1), append_TDF(&second,1));
#line 11532 "syntax.c"
			}
			/* END OF ACTION: al_list2 */
			/* BEGINNING OF INLINE: 622 */
			goto ZL2_622;
			/* END OF INLINE: 622 */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRtok__def__body(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_Tokdec ZIa;

		/* BEGINNING OF ACTION: tok_dn1_dec */
		{
#line 2232 "syntax.act"

    (ZIa) = g_tokformals;
#line 11565 "syntax.c"
		}
		/* END OF ACTION: tok_dn1_dec */
		switch (CURRENT_TERMINAL) {
		case 79:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRtok__formal__list__opt ();
		switch (CURRENT_TERMINAL) {
		case 30:
			break;
		case 130:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRfull__sortname ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: tok_dn2 */
		{
#line 2278 "syntax.act"

    Tokdec * old_tokdecs = tokdecs;
    Tokdec * tokformals = g_tokformals;
    TDF * hold = current_TDF;
    Tokpar * tp = (Tokpar*)0;
    Sort sn;
    Tokdec * tfrev = (Tokdec*)0;
    while (g_tokformals != (Tokdec*)0) { /* the wrong way round!! */
	Tokdec * x = xmalloc(sizeof *x);
	*x = *g_tokformals;
	x->next = tfrev;
	tfrev = x;
	g_tokformals = g_tokformals->next;
    }
    sn = g_sname;
    current_TDF = &g_tok_defn;
    INIT_TDF(current_TDF);
    o_token_def(out_sort(&sn),
	{
	    while (tfrev != (Tokdec*)0) {
		Tokdec * x = tfrev->next;
		LIST_ELEM(
		    o_make_tokformals(
			out_sort(&tfrev->sort.ressort),
			out_tdfint32(LOCNAME(tfrev->idname))));
		tfrev->isparam = 1;
		tfrev->next = tokdecs;
		tokdecs = tfrev;
		tfrev = x;
	    }
	},
	analyse_sort(sn.sort));
    g_toksort.ressort = sn;
    while (tokformals != (Tokdec*)0) {
	Tokpar * p = xmalloc(sizeof *p);
	p->par = tokformals->sort.ressort;
	p->next = tp;
	tokformals = tokformals->next;
	tp = p;
    }
    g_toksort.pars = tp;
    RESET_TDF(hold);
    tokdecs = old_tokdecs;
    g_tokformals = (ZIa);
#line 11638 "syntax.c"
		}
		/* END OF ACTION: tok_dn2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRinteger(void)
{
	switch (CURRENT_TERMINAL) {
	case 55:
		{
			/* BEGINNING OF ACTION: integer1 */
			{
#line 1169 "syntax.act"

    intvalue = UL(stoi(lex_v.val.name, lnum));
#line 11659 "syntax.c"
			}
			/* END OF ACTION: integer1 */
			ADVANCE_LEXER;
		}
		break;
	case 22:
		{
			/* BEGINNING OF ACTION: integer2 */
			{
#line 1173 "syntax.act"

    intvalue = UL(lex_v.val.v);
#line 11672 "syntax.c"
			}
			/* END OF ACTION: integer2 */
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_transfer_mode(void)
{
ZL2_transfer__mode:;
	switch (CURRENT_TERMINAL) {
	case 119:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 685 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: transfer_mode */
						goto ZL2_transfer__mode;
						/* END OF INLINE: transfer_mode */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 11722 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 11743 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_transfer_mode ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 11764 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_transfer_mode ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: tmode1 */
						{
#line 2151 "syntax.act"

    RESET_TDF((ZId));
    o_transfer_mode_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
			 append_TDF(&(ZIc),1));
#line 11786 "syntax.c"
						}
						/* END OF ACTION: tmode1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 685 */
		}
		break;
	case 118:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 11814 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 11823 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 120:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 11838 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 11847 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 11865 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_rounding_mode(void)
{
ZL2_rounding__mode:;
	switch (CURRENT_TERMINAL) {
	case 90:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 659 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: rounding_mode */
						goto ZL2_rounding__mode;
						/* END OF INLINE: rounding_mode */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 11904 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 11931 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						read_rounding_mode ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 11951 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_rounding_mode ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: rmode1 */
						{
#line 1658 "syntax.act"

    RESET_TDF((ZId));
    o_rounding_mode_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
			 append_TDF(&(ZIc),1));
#line 11966 "syntax.c"
						}
						/* END OF ACTION: rmode1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 659 */
		}
		break;
	case 89:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 11994 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 12003 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 91:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 12018 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 12027 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 12045 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR625(void)
{
ZL2_625:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			ADVANCE_LEXER;
			read_error_code ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: errc2 */
			{
#line 473 "syntax.act"

    current_TDF->no++;
#line 12069 "syntax.c"
			}
			/* END OF ACTION: errc2 */
			/* BEGINNING OF INLINE: 625 */
			goto ZL2_625;
			/* END OF INLINE: 625 */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR626(void)
{
ZL2_626:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			/* BEGINNING OF ACTION: otagel2 */
			{
#line 1540 "syntax.act"

    current_TDF->no++;
#line 12100 "syntax.c"
			}
			/* END OF ACTION: otagel2 */
			ADVANCE_LEXER;
			ZRotagexp ();
			/* BEGINNING OF INLINE: 626 */
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_626;
			}
			/* END OF INLINE: 626 */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_access(void)
{
ZL2_access:;
	switch (CURRENT_TERMINAL) {
	case 1:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 665 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: access */
						goto ZL2_access;
						/* END OF INLINE: access */
					}
					/*UNREACHED*/
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 12159 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
						switch (CURRENT_TERMINAL) {
						case 78:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 12180 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						read_access ();
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 130:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 12207 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_access ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: access1 */
						{
#line 206 "syntax.act"

    RESET_TDF((ZId));
    o_access_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		  append_TDF(&(ZIc),1));
#line 12222 "syntax.c"
						}
						/* END OF ACTION: access1 */
						switch (CURRENT_TERMINAL) {
						case 29:
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
			}
			/* END OF INLINE: 665 */
		}
		break;
	case 0:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1078 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 12250 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access2 */
			{
#line 212 "syntax.act"

    if (strcmp(constructs[(ZIa)].name, "visible") ==0) { g_has_vis = 1; }
#line 12259 "syntax.c"
			}
			/* END OF ACTION: access2 */
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1082 "syntax.act"

   (constructs[(ZIa)].f)();
#line 12267 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 2:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1101 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 12282 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1106 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 12291 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 12309 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR627(void)
{
ZL2_627:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: acc_l2_dec */
			{
#line 192 "syntax.act"

    (ZIc) = current_TDF;
    (ZIa) = *current_TDF;
    INIT_TDF(&(ZIb));
    RESET_TDF(&(ZIb));
#line 12334 "syntax.c"
			}
			/* END OF ACTION: acc_l2_dec */
			ADVANCE_LEXER;
			read_access ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: acc_l3 */
			{
#line 199 "syntax.act"

    INIT_TDF((ZIc));
    RESET_TDF((ZIc));
    o_add_accesses(append_TDF(&(ZIa),1), append_TDF(&(ZIb), 1));
    current_TDF->no = 1;
#line 12351 "syntax.c"
			}
			/* END OF ACTION: acc_l3 */
			/* BEGINNING OF INLINE: 627 */
			goto ZL2_627;
			/* END OF INLINE: 627 */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR628(void)
{
ZL2_628:;
	switch (CURRENT_TERMINAL) {
	case 93:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: exp_sls3_dec */
			{
#line 603 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 12385 "syntax.c"
			}
			/* END OF ACTION: exp_sls3_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 667 */
			{
				switch (CURRENT_TERMINAL) {
				case 10: case 19: case 22: case 28:
				case 41: case 42: case 43: case 44:
				case 45: case 52: case 54: case 55:
				case 58: case 61: case 62: case 68:
				case 76: case 77: case 78: case 79:
				case 81: case 82: case 84: case 85:
				case 86: case 88: case 98: case 99:
				case 100: case 102: case 103: case 104:
				case 105: case 107: case 109: case 110:
				case 111: case 124:
					{
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: exp_sls4 */
						{
#line 607 "syntax.act"

    RESET_TDF((ZIb));
    if (lex_v.t == lex_semi) {
	current_TDF->no +=1;
	append_TDF(&(ZIa),1);
    } else {
	TDF stats;
	stats = *current_TDF;
	INIT_TDF(current_TDF);
	o_sequence(
	    { append_TDF(&stats,1); current_TDF->no = stats.no; },
	    append_TDF(&(ZIa),1));
	/* cheats LIST in o_sequence */
    }
#line 12425 "syntax.c"
						}
						/* END OF ACTION: exp_sls4 */
						/* BEGINNING OF INLINE: 628 */
						goto ZL2_628;
						/* END OF INLINE: 628 */
					}
					/*UNREACHED*/
				default:
					{
						/* BEGINNING OF ACTION: exp_sls5 */
						{
#line 624 "syntax.act"

    o_make_top;
#line 12440 "syntax.c"
						}
						/* END OF ACTION: exp_sls5 */
						/* BEGINNING OF ACTION: exp_sls4 */
						{
#line 607 "syntax.act"

    RESET_TDF((ZIb));
    if (lex_v.t == lex_semi) {
	current_TDF->no +=1;
	append_TDF(&(ZIa),1);
    } else {
	TDF stats;
	stats = *current_TDF;
	INIT_TDF(current_TDF);
	o_sequence(
	    { append_TDF(&stats,1); current_TDF->no = stats.no; },
	    append_TDF(&(ZIa),1));
	/* cheats LIST in o_sequence */
    }
#line 12460 "syntax.c"
						}
						/* END OF ACTION: exp_sls4 */
						/* BEGINNING OF INLINE: 628 */
						goto ZL2_628;
						/* END OF INLINE: 628 */
					}
					/*UNREACHED*/
				}
			}
			/* END OF INLINE: 667 */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR629(void)
{
ZL2_629:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			PTR_Tokdec ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tok_fml1_dec */
			{
#line 2283 "syntax.act"

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    if ((ZIa)!= (Tokdec*)0)fail("Token parameter name %s must be unique", n);
    (ZIa) = xmalloc(sizeof *(ZIa)); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->isdeffed = 1; (ZIa)->isused = 0; (ZIa)->iskept=0;
    (ZIa)->next = (Tokdec*)0;
#line 12504 "syntax.c"
			}
			/* END OF ACTION: tok_fml1_dec */
			switch (CURRENT_TERMINAL) {
			case 54:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 24:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRfull__sortname ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tok_fml3 */
			{
#line 2297 "syntax.act"

    (ZIa)->sort.ressort = g_sname;
    (ZIa)->sort.pars = (Tokpar*)0; /* no pars in formal pars */
    (ZIa)->next = g_tokformals;
    g_tokformals = (ZIa);
#line 12534 "syntax.c"
			}
			/* END OF ACTION: tok_fml3 */
			/* BEGINNING OF INLINE: 629 */
			goto ZL2_629;
			/* END OF INLINE: 629 */
		}
		/*UNREACHED*/
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR630(void)
{
	switch (CURRENT_TERMINAL) {
	case 35:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: keeps1 */
			{
#line 1269 "syntax.act"

    int i;
    for (i=0; i<NO_OF_ENTITIES; i++) {
	INIT_TDF(lk_externs+i);
    }
#line 12568 "syntax.c"
			}
			/* END OF ACTION: keeps1 */
			/* BEGINNING OF ACTION: keeps2 */
			{
#line 1389 "syntax.act"

    CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(1)));
    if (line_no_tok != -1) {
	current_TDF = lk_externs+tok_ent;
	o_make_linkextern(
	    out_tdfint32(UL(line_no_tok)),
		o_string_extern(
		    { out_tdfident_bytes("~exp_to_source"); }));
	current_TDF->no++;
	CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(3)));
    }
    {
	Tokdec * k = tokdecs;
	while (k != (Tokdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tok_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tok_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Tagdec * k = tagdecs;
	while (k != (Tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + ((k->iscommon)?8:(4*k->isdeffed));
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Al_tagdec * k = al_tagdecs;
	while (k != (Al_tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, al_tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+al_tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	int i;
	TDF caps;
	add_extra_toks();
	INIT_TDF(&caps);
	RESET_TDF(&caps);
	if (do_pp)success();
	if (HAS_MAGIC) {
	    out_basic_int(UL('T'), UI(8));
	    out_basic_int(UL('D'), UI(8));
	    out_basic_int(UL('F'), UI(8));
	    out_basic_int(UL('C'), UI(8));
	    out_tdfint32(MAJOR_NO);
	    out_tdfint32(MINOR_NO);
	    byte_align();
	}
	o_make_capsule(
	    {
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			char* n;
			n = unit_names[i];
			LIST_ELEM({ out_tdfident_bytes(n); });
		    }
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    char* n;
		    n = ent_names[i];
		    LIST_ELEM(
			o_make_capsule_link(
			    { out_tdfident_bytes(n);},
			    out_tdfint32(UL(capsule_names[i]))))
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    TDF * lks = lk_externs+i;
		    LIST_ELEM(
			o_make_extern_link(
			    { append_TDF(lks,1); current_TDF->no = lks->no; });
		   )
		}
	    },
	    {
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			LIST_ELEM(
			    o_make_group(LIST_ELEM(make_unit(i))););
		    }
		}
	    }
	);
	make_tdf_file(&caps, out_file);
    }
#line 12692 "syntax.c"
			}
			/* END OF ACTION: keeps2 */
		}
		break;
	case 57:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: keeps1 */
			{
#line 1269 "syntax.act"

    int i;
    for (i=0; i<NO_OF_ENTITIES; i++) {
	INIT_TDF(lk_externs+i);
    }
#line 12715 "syntax.c"
			}
			/* END OF ACTION: keeps1 */
			ZRkeep__list__opt ();
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 35:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: keeps2 */
			{
#line 1389 "syntax.act"

    CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(1)));
    if (line_no_tok != -1) {
	current_TDF = lk_externs+tok_ent;
	o_make_linkextern(
	    out_tdfint32(UL(line_no_tok)),
		o_string_extern(
		    { out_tdfident_bytes("~exp_to_source"); }));
	current_TDF->no++;
	CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(3)));
    }
    {
	Tokdec * k = tokdecs;
	while (k != (Tokdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tok_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tok_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Tagdec * k = tagdecs;
	while (k != (Tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + ((k->iscommon)?8:(4*k->isdeffed));
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Al_tagdec * k = al_tagdecs;
	while (k != (Al_tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, al_tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+al_tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	int i;
	TDF caps;
	add_extra_toks();
	INIT_TDF(&caps);
	RESET_TDF(&caps);
	if (do_pp)success();
	if (HAS_MAGIC) {
	    out_basic_int(UL('T'), UI(8));
	    out_basic_int(UL('D'), UI(8));
	    out_basic_int(UL('F'), UI(8));
	    out_basic_int(UL('C'), UI(8));
	    out_tdfint32(MAJOR_NO);
	    out_tdfint32(MINOR_NO);
	    byte_align();
	}
	o_make_capsule(
	    {
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			char* n;
			n = unit_names[i];
			LIST_ELEM({ out_tdfident_bytes(n); });
		    }
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    char* n;
		    n = ent_names[i];
		    LIST_ELEM(
			o_make_capsule_link(
			    { out_tdfident_bytes(n);},
			    out_tdfint32(UL(capsule_names[i]))))
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    TDF * lks = lk_externs+i;
		    LIST_ELEM(
			o_make_extern_link(
			    { append_TDF(lks,1); current_TDF->no = lks->no; });
		   )
		}
	    },
	    {
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			LIST_ELEM(
			    o_make_group(LIST_ELEM(make_unit(i))););
		    }
		}
	    }
	);
	make_tdf_file(&caps, out_file);
    }
#line 12857 "syntax.c"
			}
			/* END OF ACTION: keeps2 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR632(void)
{
	switch (CURRENT_TERMINAL) {
	case 3: case 10: case 36: case 63:
	case 68: case 103:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_char ZId;

			/* BEGINNING OF ACTION: exp1_dec */
			{
#line 502 "syntax.act"

    (ZId) = lex_v.val.name;
    (ZIa) = *current_TDF;
    SET_TDF((ZIc), &(ZIb));
#line 12892 "syntax.c"
			}
			/* END OF ACTION: exp1_dec */
			ZR672 (&ZIa, &ZIb, &ZIc, &ZId);
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRkeep__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 2: case 5: case 9: case 15:
	case 18: case 40: case 43: case 49:
	case 54: case 60: case 71: case 75:
	case 91: case 96: case 100: case 111:
	case 120: case 128:
		{
			ZRkeep__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 130:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR633(void)
{
ZL2_633:;
	switch (CURRENT_TERMINAL) {
	case 24:
		{
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 86:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencond1_dec */
			{
#line 1063 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 12970 "syntax.c"
			}
			/* END OF ACTION: gencond1_dec */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gencond2 */
			{
#line 1068 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 12991 "syntax.c"
			}
			/* END OF ACTION: gencond2 */
			switch (CURRENT_TERMINAL) {
			case 25:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gencond3 */
			{
#line 1073 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 13012 "syntax.c"
			}
			/* END OF ACTION: gencond3 */
			switch (CURRENT_TERMINAL) {
			case 25:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat1 */
			{
#line 1754 "syntax.act"

    RESET_TDF((ZId));
    o_signed_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		      append_TDF(&(ZIc),1));
#line 13034 "syntax.c"
			}
			/* END OF ACTION: signed_nat1 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRal__tag__def(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_Al_tagdec ZIa;
		TDF ZIb;
		PTR_TDF ZIc;
		int ZId;

		switch (CURRENT_TERMINAL) {
		case 6:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: al_tgdf1_dec */
		{
#line 261 "syntax.act"

    char * n =lex_v.val.name;
    (ZIa) = find_al_tag(n);
    SELECT_UNIT(al_tagdef_unit);
    if ((ZIa)== (Al_tagdec*)0) {
	(ZIa)= xmalloc(sizeof *(ZIa)); (ZIa)->isdeffed =0; (ZIa)->iskept=0; (ZIa)->isused=0;
	NEW_IDNAME((ZIa)->idname, n, al_tag_ent);
	(ZIa)->next = al_tagdecs; al_tagdecs = (ZIa);
	(ZId) = 0;
    }
    else (ZId) = 1;
    if ((ZIa)->isdeffed) { fail("Al_tag %s defined twice", n); }
    (ZIa)->isdeffed = 1;
    SET_TDF((ZIc), &(ZIb));
#line 13093 "syntax.c"
		}
		/* END OF ACTION: al_tgdf1_dec */
		switch (CURRENT_TERMINAL) {
		case 54:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 36:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		read_alignment ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: al_tagdef2 */
		{
#line 248 "syntax.act"

    RESET_TDF((ZIc));
    o_make_al_tagdef(if ((ZId)) {
			  out_tdfint32(UL(non_local(&(ZIa)->idname.name,al_tag_ent)));
			  } else {
			      out_tdfint32(LOCNAME((ZIa)->idname));
			  },
			  append_TDF(&(ZIb), 1)
			);
    INC_LIST;
#line 13128 "syntax.c"
		}
		/* END OF ACTION: al_tagdef2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRotagexp(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;

		/* BEGINNING OF ACTION: otagexp1_dec */
		{
#line 1547 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 13153 "syntax.c"
		}
		/* END OF ACTION: otagexp1_dec */
		read_exp ();
		ZR655 (&ZIa, &ZIb);
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_program(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		ZRelement__list__opt ();
		ZR630 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2393 "syntax.act"

    fail("Syntax error");
#line 13191 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR634(void)
{
	switch (CURRENT_TERMINAL) {
	case 22: case 55:
		{
			ZRinteger ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat3 */
			{
#line 1765 "syntax.act"

    o_make_signed_nat(out_tdfbool(1), out_tdfint32(intvalue));
#line 13213 "syntax.c"
			}
			/* END OF ACTION: signed_nat3 */
		}
		break;
	case 69: case 70: case 71:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: signed_nat5_dec */
			{
#line 1772 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 13228 "syntax.c"
			}
			/* END OF ACTION: signed_nat5_dec */
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat6 */
			{
#line 1776 "syntax.act"

    RESET_TDF((ZIb));
    o_snat_from_nat(o_true, append_TDF(&(ZIa),1));
#line 13242 "syntax.c"
			}
			/* END OF ACTION: signed_nat6 */
		}
		break;
	case 130:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

/* BEGINNING OF TRAILER */

#line 2396 "syntax.act"

#line 13262 "syntax.c"

/* END OF FILE */
