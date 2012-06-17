/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include <reader/readglob.h>

/* VARIABLES */
/* All variables except good_trans are initialised. This assumes
that translation stops after the first error */

dec *capsule_tagtab;
/* the table of tags which are available at the capsule level */

tok_define *capsule_toktab;
/* the table of tokens which are available at the capsule level */

aldef *capsule_altab;
/* the table of alignment tags which are available at the capsule level */

diag_tagdef *capsule_diag_tagtab;	/* OLD DIAGS */
/* the table of diagnostic tags which are available at the capsule level */

dgtag_struct *capsule_dgtab;		/* NEW DIAGS */
/* the table of diagnostic tags which are available at the capsule level */

int capsule_no_of_tokens;
/* the number of tokens at the capsule level */

int capsule_no_of_tags;
/* the number of tags at the capsule level */

int capsule_no_of_als;
/* the number of alignment tags at the capsule level */

int capsule_no_of_diagtags;	/* OLD DIAGS */
/* the number of diagnostic tags at the capsule level */

int capsule_no_of_dgtags;	/* NEW DIAGS */
/* the number of diagnostic tags at the capsule level */


dec *unit_tagtab;
/* the table of tags for the current unit */

tok_define *unit_toktab;
/* the table of tokens for the current unit */

aldef *unit_altab;
/* the table of alignment tags for the current unit */

int unit_no_of_tokens;
/* the number of tokens in the current unit */

int unit_no_of_tags;
/* the number of tags in the current unit */

int unit_no_of_als;
/* the number of alignment tags in the current unit */

dec **unit_ind_tags;
/* table of pointers to the tags used in the current unit */

tok_define **unit_ind_tokens;
/* table of pointers to the tokens used in the current unit */

aldef **unit_ind_als;
/* table of pointers to the alignment tags used in the current unit */


exp *unit_labtab;
/* table of labels used in the current unit */

int unit_no_of_labels;
/* number of labels used in the current unit */

int crt_tagdef_unit_no;
/* number of current tagdef unit. -1 before tagdef units */

int unit_index;
/* number of current unit */

int rep_make_proc = 1;  /* identify any make_procs not in make_id_tagdef*/

int replace_arith_type = 0;	/* do not use C definitions of promote
				   etc. */

int good_trans = 0;		/* 0 if translation is good, 1 for error
				*/

char *crt_filename;

capsule_frees *capsule_freelist = (capsule_frees *)0;

int newcode = 1;

#ifdef NEWDIAGS
int within_diags = 0;	/* mark name_tag if it's not used for producing code */
#endif
