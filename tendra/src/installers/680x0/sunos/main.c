/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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
 *    		 Crown Copyright (c) 1996
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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/

#include "config.h"
#include "release.h"
#include "common_types.h"
#include "assembler.h"
#include "basicread.h"
#include "flpt.h"
#include "main_reads.h"
#include "weights.h"
#include "instrs.h"
#include "installglob.h"
#include "expmacs.h"
#include "exp.h"
#include "externs.h"
#include "flags.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "peephole.h"
#include "szs_als.h"
#include "tests.h"
#include "utility.h"
#include "version.h"
#include "reader_v.h"
#include "construct_v.h"
#include "where.h"
#if have_diagnostics
#include "xdb_basics.h"
#include "xdb_output.h"
#endif
extern int errors ;
extern int max_errors ;


/*
    PROGRAM NAME AND VERSION NUMBER
*/

char *progname = "hptrans" ;
static char *version_str = "Version: 0.6" ;
static char *revision = REVISION_STRING ;
static char *revdate = DATE_STRING ;
int normal_version = 1 ;


/*
    EXTRA COMPILATION FLAGS
*/

int do_peephole = 1 ;
int do_pic = 0 ;
static int do_quit = 0 ;
static int do_sep_units = 0 ;
static int ignore_errors = 0 ;
#ifdef EBUG
int optimize = 0 ;
#else
static int optimize = 1 ;
#endif
static int report_version = 0 ;
static int report_tdf_versions = 0 ;
static int show_options = 0 ;
static int dummy_option = 0 ;

#ifdef EBUG

int do_test = 0 ;
int seek_label = 0 ;
int seek_extern = 0 ;
int seek_label_no ;
char *seek_extern_id ;

int seek_line = 0 ;
int seek_line_no ;
static char *seek_line_id ;

#endif

int diag_override ;
static int diag_stab_override = 0 ;
static int diag_xdb_new_override = 0 ;
static int diag_xdb_old_override = 0 ;



/*
    VARIABLE SIZES AND ALIGNMENTS
*/

alignment MAX_BF_SIZE ;


/*
    MAXIMUM EXPONENT FOR FLOATING-POINT NUMBERS
*/

int target_dbl_maxexp = 1024 ;


/*
    OPTIONS

    There are two types of options.  Firstly, for certain key words,
    key, the option "-key" enables, and the option "-no_key" disables,
    the corresponding action.  Some of these options take an additional
    argument in their positive form, i.e. "-key arg".  Secondly, single
    letter options are used as shorthand for some of the options of the
    first type.

    Each entry in this table gives a key word, key, followed by the
    single letter option for "-key" (or 0 is there isn't one) and
    the single letter option for "-no_key".  There is also a pointer
    to the boolean changed by this option and, if the option takes a
    qualifying string, a pointer to the string thus set.
*/

struct {
    char *opt ;
    char on ;
    char off ;
    char sw ;
    int *flag ;
    char **value ;
} options [] = {
    { "alloca", 0, 0, 'A', &do_alloca, null },
    { "cc", 'c', 'g', 0, &cc_conventions, null },
    { "diag", 'H', 0, 0, &diagnose, null },
    { "extra_checks", 0, 'E', 0, &extra_checks, null },
    { "float_div", 0, 0, 'M', &strict_fl_div, null },
    { "float_inf", 0, 0, 'B', &flpt_const_overflow_fail, null },
    { "foralls", 0, 0, 'F', &do_foralls, null },
    { "ignore", 0, 0, 0, &ignore_errors, null },
    { "immediate", 'i', 0, 0, &output_immediately, null },
    { "inlining", 0, 0, 'I', &do_inlining, null },
    { "loopconsts", 0, 0, 'C', &do_loopconsts, null },
#if have_diagnostics
    { "stab", 0, 0, 0, &diag_stab_override, null },
    { "new_diag", 0, 0, 0, &diag_xdb_new_override, null },
    { "old_diag", 0, 0, 0, &diag_xdb_old_override, null },
#endif
    { "opt", 'O', 'X', 0, &optimize, null },
    { "options", 'o', 0, 0, &show_options, null },
    { "peephole", 0, 0, 0, &do_peephole, null },
    { "pic", 0, 0, 'D', &do_pic, null },
    { "profile", 'P', 0, 0, &do_profile, null },
    { "quit", 'Q', 0, 0, &do_quit, null },
    { "report_version", 'Z', 0, 0, &report_tdf_versions, null },
    { "round", 'r', 0, 'R', &round_after_flop, null },
    { "separate_units", 'U', 0, 0, &do_sep_units, null },
    { "special_fns", 0, 0, 0, &do_special_fns, null },
    { "sub_params", 0, 0, 0, &do_sub_params, null },
#ifdef EBUG
    { "label", 'L', 0, 0, &seek_extern, &seek_extern_id },
    { "line", 'l', 0, 0, &seek_line, &seek_line_id },
    { "test", 'l', 0, 0, &do_test, null },
#endif
    { "unroll", 0, 0, 'U', &do_unroll, null },
    { "version", 'V', 0, 0, &report_version, null },
    { "write_strings", 0, 0, 'W', &dummy_option, null }
} ;


/*
    MAIN ROUTINE

    This routine processes the command-line arguments, calls the
    initialization routines, and then calls the main processing
    routines.
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{
    int a ;
    char **p = null ;
    char *input = null ;
    char *output = null ;

    /* Set up program name */
    progname = basename ( argv [0] ) ;

    /* Set default options */
    diagnose = 0 ;
    do_alloca = 1 ;
    do_foralls = 1 ;
    do_inlining = 1 ;
    do_loopconsts = 1 ;
    do_profile = 0 ;
    do_special_fns = 1 ;
    do_unroll = 1 ;
    extra_checks = 1 ;
    redo_structfns = 0 ;

    /* Process arguments */
    for ( a = 1 ; a < argc ; a++ ) {
	if ( p ) {
	    /* Set extra part of two part options */
	    *p = argv [a] ;
	    p = null ;
	} else if ( argv [a][0] == '-' && argv [a][1] ) {
	    /* Search option table */
	    bool found = 0 ;
	    char *s = argv [a] + 1 ;
	    int i, n = array_size ( options ) ;
	    if ( ( s [1] == '0' || s [1] == '1' ) && s [2] == 0 ) {
		for ( i = 0 ; !found && i < n ; i++ ) {
		    if ( *s == options [i].sw ) {
			*( options [i].flag ) = ( s [1] - '0' ) ;
			p = options [i].value ;
			found = 1 ;
		    }
		}
	    } else if ( s [1] ) {
		bool b = 1 ;
		if ( strncmp ( s, "no_", 3 ) == 0 ) {
		    s += 3 ;
		    b = 0 ;
		}
		for ( i = 0 ; !found && i < n ; i++ ) {
		    if ( eq ( s, options [i].opt ) ) {
			*( options [i].flag ) = b ;
			if ( b ) p = options [i].value ;
			found = 1 ;
		    }
		}
	    } else {
		for ( i = 0 ; !found && i < n ; i++ ) {
		    if ( *s == options [i].on ) {
			*( options [i].flag ) = 1 ;
			p = options [i].value ;
			found = 1 ;
		    } else if ( *s == options [i].off ) {
			*( options [i].flag ) = 0 ;
			found = 1 ;
		    }
		}
	    }
	    if ( !found ) warning ( "Unknown option, %s", argv [a] ) ;
	} else {
	    /* Set up input and output files */
	    if ( input == null ) {
		input = argv [a] ;
	    } else if ( output == null ) {
		output = argv [a] ;
	    } else {
		error ( "Too many arguments" ) ;
		exit ( EXIT_FAILURE ) ;
	    }
	}
    }

#ifdef EBUG
    /* Deal with debugging options */
    if ( seek_extern ) {
	if ( is_local ( seek_extern_id ) ) {
	    seek_label = 1 ;
	    seek_label_no = atoi ( seek_extern_id + 1 ) ;
	}
    }
    if ( seek_line ) seek_line_no = atoi ( seek_line_id ) ;
#endif

    /* Report version if required */
    if ( report_version ) {
#ifdef NEXT
	char *machine = "NeXT" ;
#else
#ifdef SUN
	char *machine = "Sun/3" ;
#else
	char *machine = "HP" ;
#endif
#endif
	fprintf(stderr, "DRA TDF translator (TDF version %d.%d)\n",
		MAJOR_VERSION, MINOR_VERSION);
	fprintf(stderr, "reader %d.%d: ", reader_version,
		reader_revision);
	fprintf(stderr, "construct %d.%d: ", construct_version,
		construct_revision);
	fprintf(stderr, "target %d.%d.%d: \n", target_version,
		target_revision,target_patchlevel);
	fprintf(stderr, "system %s",machine);
#ifdef __DATE__
	fprintf(stderr," : installer compilation %s\n", __DATE__);
#endif
	fprintf(stderr,"release: %s\n",RELEASE);
	fprintf ( stderr, ".\n" ) ;
#ifdef EBUG
	fprintf ( stderr, "Last revised %s.\n", revdate ) ;
#endif
    }
    if ( report_tdf_versions ) report_versions = 1 ;

    /* Check on diagnostics */
    if ( !have_diagnostics && diagnose ) {
	error ( "Diagnostics not supported" ) ;
	diagnose = 0 ;
    }

#if have_diagnostics
    diag_override = DIAG_UNKNOWN ;
    if ( diag_stab_override ) diag_override = DIAG_STAB ;
    if ( diag_xdb_new_override ) diag_override = DIAG_XDB_NEW ;
    if ( diag_xdb_old_override ) diag_override = DIAG_XDB_OLD ;
#endif

    /* Switch off optimizations if required */
    if ( diagnose || !optimize ) {
	do_inlining = 0 ;
	do_loopconsts = 0 ;
	do_foralls = 0 ;
	do_peephole = 0 ;
	do_unroll = 0 ;
    }

    /* Show options if necessary */
    if ( show_options ) {
	int i, n = array_size ( options ) ;
	for ( i = 0 ; i < n ; i++ ) {
	    bool b = *( options [i].flag ) ;
	    char **pv = options [i].value ;
	    printf ( "%s = %s", options [i].opt, ( b ? "True" : "False" ) ) ;
	    if ( pv && b ) printf ( " (%s)", *pv ) ;
	    printf ( "\n" ) ;
	}
    }

    /* Check on separate units */
    if ( do_sep_units ) {
	separate_units = 1 ;
#if 0
	current_alloc_size = first_alloc_size ;
#endif
    }

    do_pic = 0 ; /* TODO */

    /* Other options */
    if ( do_pic ) PIC_code = 1 ;
    if ( !extra_checks ) target_dbl_maxexp = 16384 ;
    if ( do_quit ) exit ( EXIT_SUCCESS ) ;

    /* Open input file */
    if ( input == null ) {
	error ( "Not enough arguments" ) ;
	exit ( EXIT_FAILURE ) ;
    }
    if ( !initreader ( input ) ) {
	exit ( EXIT_FAILURE ) ;
    }
    /*open_input ( input ) ;*/

    /* Set up alignment rules */
    double_align = DBL_ALIGN ;
    param_align = PARAM_ALIGN ;
    stack_align = STACK_ALIGN ;

    MAX_BF_SIZE = ( cc_conventions ? MAX_BF_SIZE_CC : MAX_BF_SIZE_GCC ) ;

    /* Call initialization routines */
    top_def = null ;
    init_flpt () ;
    init_instructions () ;
#include "inits.h"
    init_weights () ;
    init_wheres () ;

    /* Decode, optimize and process the input TDF */
    open_output ( output ) ;
    asm_comment ;
    outs ( " TDF to 680x0, " ) ;
    outs ( version_str ) ;
    outs ( ", " ) ;
    outs ( revision ) ;
    outnl () ;
    init_output () ;
    area ( ptext ) ;
#if have_diagnostics
    if ( diagnose ) diag_prologue () ;
#endif
    d_capsule () ;
#if have_diagnostics
    if ( diagnose ) diag_epilogue () ;
#endif
#ifdef asm_version
    if ( normal_version ) {
	asm_version ;
    } else {
	asm_version_aux ;
    }
    outnl () ;
#endif
    if ( errors && !ignore_errors ) exit ( EXIT_FAILURE ) ;
    return ( 0 ) ;
}
