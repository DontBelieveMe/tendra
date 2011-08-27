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
    		 Crown Copyright (c) 1996

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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/xdb_output.c,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: xdb_output.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:23  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:35:40  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:25  ra
 * Added missing files.
 *
 * Revision 1.3  94/02/21  16:09:13  16:09:13  ra (Robert Andrews)
 * Put in a number of explicit casts.
 *
 * Revision 1.2  93/04/19  13:39:31  13:39:31  ra (Robert Andrews)
 * crt_fname and crt_line_num are no longer static.
 *
 * Revision 1.1  93/02/22  17:17:25  17:17:25  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "error.h"

#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "codex.h"
#include "exp.h"
#include "expmacs.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "tags.h"
#include "utility.h"
#include "xdb_types.h"
#include "xdb_output.h"
#include "stab_types.h"
extern int diag_override;


/*
    WORK OUT WHETHER TO DO A DYNAMIC TEST FOR DIAGNOSTIC FORMAT
*/

#if (default_diag == DIAG_UNKNOWN)
#define dynamic_test
extern double atof(const char *);
#include <sys/utsname.h>
#else
#undef dynamic_test
#endif


/*
    WHICH DIAGNOSTIC FORMAT SHOULD BE USED?
*/

bool diag_format = default_diag;


/*
    ARRAY OF DIAGNOSTIC DIRECTIVES

    This array gives information on all the available diagnostic directives,
    included those which are unused.
*/

diag_directive dd[] = {
    { m_dd_array, 2, 2 },
    { m_dd_begin, 1, 1 },
    { m_dd_const, 0, 0 },	/* unknown */
    { m_dd_dvar, 2, 2 },
    { m_dd_end, 1, 1 },
    { m_dd_entry, 0, 0 },	/* unknown */
    { m_dd_enum, 1, 1 },
    { m_dd_field, 2, 2 },
    { m_dd_file, 0, 0 },	/* unknown */
    { m_dd_fparam, 2, 2 },
    { m_dd_function, 3, 3 },
    { m_dd_functype, 2, 2 },
    { m_dd_import, 0, 0 },	/* unknown */
    { m_dd_label, 0, 0 },	/* unknown */
    { m_dd_memenum, 2, 2 },
    { m_dd_module, 1, 2 },
    { m_dd_pointer, 1, 1 },
    { m_dd_set, 0, 0 },		/* unknown */
    { m_dd_srcfile, 1, 1 },
    { m_dd_struct, 2, 2 },
    { m_dd_subrange, 2, 2 },
    { m_dd_svar, 2, 2 },
    { m_dd_tagdef, 1, 1 },
    { m_dd_typedef, 1, 1 },
    { m_dd_union, 1, 1 },
    { m_dd_variant, 0, 0 }	/* unknown */
};


/*
    DIAGNOSTICS FILES

    There are three sections of diagnostic information in the new
    diagnostics mode (the vt, lntt and gntt sections).  One temporary
    file is used for each.  In the old diagnosics mode there is
    only one section (the dntt section), and only one file, diagfp2,
    is used.
*/

static FILE *diagfp1;
static FILE *diagfp2;
static FILE *diagfp3;


/*
    INITIALIZE DIAGNOSTICS FILES

    The temporary files are opened, and the headings of the various
    sections are printed.
*/

void init_diag
(void)
{
    double vs = (diag_format == DIAG_XDB_NEW ? 7.40 : 7.05);

#ifdef dynamic_test
    struct utsname u;
    char *os = "HP-UX";
    uname(&u);
    os = u.sysname;
    vs = atof(u.release);
    if (strcmp(os, "HP-UX") == 0) {
	diag_format = (vs >= 7.40 ? DIAG_XDB_NEW : DIAG_XDB_OLD);
    } else {
	diag_format = DIAG_UNKNOWN;
   }
#endif

    if (diag_override != DIAG_UNKNOWN) {
	diag_format = diag_override;
	vs = (diag_format == DIAG_XDB_NEW ? 7.40 : 7.05);
    }
    switch (diag_format) {

	case DIAG_STAB: {
	    /* Temporary files not used */
	    break;
	}

	case DIAG_UNKNOWN: {
	    error(ERROR_WARNING, "Unknown diagnostics format");
	    diag_format = DIAG_XDB_NEW;
	    /* Fall through */
	}

	case DIAG_XDB_NEW: {
	    diagfp1 = tmpfile();
	    diagfp2 = tmpfile();
	    diagfp3 = tmpfile();
	    if (diagfp1 == null || diagfp2 == null || diagfp3 == null) {
		error(ERROR_FATAL, "Can't open temporary diagnostics file");
	    }
	    fprintf(diagfp1, "%s\n", instr_names[m_as_data]);
	    fprintf(diagfp1, "%s\n", instr_names[m_dd_vt]);
	    fprintf(diagfp2, "%s\n", instr_names[m_dd_lntt]);
	    fprintf(diagfp3, "%s\n", instr_names[m_dd_gntt]);
	    break;
	}

	case DIAG_XDB_OLD: {
	    diagfp2 = tmpfile();
	    if (diagfp2 == null) {
		error(ERROR_FATAL, "Can't open temporary diagnostics file");
	    }
	    fprintf(diagfp2, "%s\n", instr_names[m_as_data]);
	    fprintf(diagfp2, "%s\n", instr_names[m_dd_start]);
	    break;
	}
    }
    return;
}


/*
    COPY A FILE

    The the file is copied to the main output file, fpout.
*/

static void copy_diag_file
(FILE *file)
{
    int c;
    rewind(file);
    while (c = getc(file), c != EOF)putc(c, fpout);
    fclose(file);
    return;
}


/*
    VT AREA NEWLINE FLAG

    This flag is true if a newline has just been output in the vt area.
*/

static int vt_newline = 1;


/*
    COPY DIAGNOSTICS FILES

    All the diagnostic files are copied to the main output file.
*/

void copy_diag
(void)
{
    if (diag_format == DIAG_XDB_NEW) {
	if (vt_newline) {
	    fprintf(diagfp1, "%s0\n", instr_names[m_dd_vtbytes]);
	} else {
	    fprintf(diagfp1, ",0\n");
	}
	copy_diag_file(diagfp1);
	copy_diag_file(diagfp2);
	copy_diag_file(diagfp3);
    } else if (diag_format == DIAG_XDB_OLD) {
	copy_diag_file(diagfp2);
    }
    return;
}


/*
    OUTPUT A DIAGNOSTICS STRING

    Diagnostic strings (eg. procedure and variable names) are dealt with
    differently in the two formats.  In the old format they are output
    direct, in the new they are added to the vt table and the offset
    from the start of the table is used.
*/

void diag_string
(FILE *file, char *s)
{
    if (diag_format == DIAG_XDB_NEW) {
	static int vtposn = 0;
	static int vtwidth = 0;
	if (vt_newline) {
	    fprintf(diagfp1, "%s0", instr_names[m_dd_vtbytes]);
	    vt_newline = 0;
	} else {
	    fprintf(diagfp1, ",0");
	}
	vtposn++;
	vtwidth++;
	fprintf(file, "%d", vtposn);
	for (; *s; s++) {
	    if (vt_newline) {
		fprintf(diagfp1, "%s%d", instr_names[m_dd_vtbytes], *s);
		vt_newline = 0;
	    } else {
		fprintf(diagfp1, ",%d", *s);
	    }
	    vtposn++;
	    vtwidth++;
	    if (vtwidth > 12) {
		fprintf(diagfp1, "\n");
		vt_newline = 1;
		vtwidth = 0;
	    }
	}
    } else {
	fprintf(file, "\"%s\"", s);
    }
    return;
}


/*
    CURRENT FILE INDEX AND LINE NUMBER

    These variables record the current position in the source file.
*/

char *crt_fname = "";
long crt_line_num = -1;


/*
    NUMBER OF SLT INSTRUCTIONS

    A count of the number of slt instructions is maintained.
*/

static int slt_num = 0;


/*
    PRINT AN SLT SPECIAL INSTRUCTION

    An sltspecial instruction is output.  This goes straight into the
    main output file.
*/

static void slt_special
(int t, posn_t p)
{
    mach_op *op1, *op2, *op3;
    area(ptext);
    op1 = make_int_data(t);
    op2 = make_int_data(crt_line_num);
    op3 = make_hex_data(p);
    op1->of = op2;
    op2->of = op3;
    make_instr(m_dd_special, op1, null, 0);
    area(plast);
    slt_num++;
    return;
}


/*
    OUTPUT A SLT NORMAL INSTRUCTION

    An sltnormal instruction is output.  This goes straight into the
    main output file.
*/

static void slt_normal
(void)
{
    mach_op *op;
    area(ptext);
    op = make_int_data(crt_line_num);
    if (diag_format == DIAG_STAB) {
	mach_op *op1 = make_int_data(68);
	op1->of = make_int_data(0);
	op1->of->of = op;
	make_instr(m_stabd, op1, null, 0);
    } else {
	make_instr(m_dd_normal, op, null, 0);
    }
    area(plast);
    slt_num++;
    return;
}


/*
    OUTPUT A SLT EXIT INSTRUCTION

    An sltexit instruction is output (new format only).
*/

void slt_exit
(void)
{
    mach_op *op;
    area(ptext);
    op = make_int_data(crt_line_num);
    make_instr(m_dd_exit, op, null, 0);
    area(plast);
    slt_num++;
    return;
}


/*
    OUTPUT A DNT BEGIN INSTRUCTION
*/

void dnt_begin
(void)
{
    if (diag_format == DIAG_STAB) {
	long lab = next_lab();
	make_label(lab);
	push_dscope((posn_t)lab, 0);
    } else {
	posn_t p = out_dd(diagfp2, xdb_begin, 1);
	push_dscope(p, 4);
	if (diag_format == DIAG_XDB_NEW)fprintf(diagfp2, "0,");
	fprintf(diagfp2, "%d\n", slt_num);
	slt_special(5, p);
    }
    return;
}


/*
    OUTPUT A DNT END INSTRUCTION
*/

int dnt_end
(void)
{
    dscope *d = pop_dscope();
    if (d == null) return(0);
    if (diag_format == DIAG_STAB) {
	long lab1 = (long)d->posn;
	long lab2 = next_lab();
	make_label(lab2);
	make_stabn(192, lab1);
	make_stabn(224, lab2);
    } else {
	posn_t p = out_dd(diagfp2, xdb_end, 1);
	if (diag_format == DIAG_XDB_NEW) {
	    fprintf(diagfp2, "%d,0,", d->dscope_type);
	}
	fprintf(diagfp2, "%d,0x%x\n", slt_num,
		 (unsigned int)d->posn);
	slt_special(6, p);
    }
    return(1);
}


/*
    FLAG FOR MODULE NAME
*/

static bool have_module = 0;


/*
    DIAGNOSTICS FOR FILE NAME

    This routine output the necessary instructions to indicate a change
    of source file.
*/

void diag_source_file
(char *nm, long ln)
{
    if (diag_format == DIAG_STAB) {
	int n = strlen(nm) + 3;
	char *qnm = alloc_nof(char, n);
	mach_op *op = make_extern_data("Ltext", 0);
	sprintf(qnm, "\"%s\"", nm);
	make_stabs(qnm,(have_module ? 132 : 100), L0, op);
	if (!have_module) {
	    make_external_label("Ltext");
	    init_stab_types();
	    have_module = 1;
	}
	crt_fname = nm;
	crt_line_num = ln;
    } else {
	posn_t x = out_dd(diagfp2, xdb_srcfile, 1);
	fprintf(diagfp2, "1,");
	diag_string(diagfp2, nm);
	fprintf(diagfp2, ",%d\n", slt_num);
	crt_fname = nm;
	crt_line_num = ln;
	make_instr(m_dd_align, null, null, 0);
	slt_special(1, x);
	if (!have_module) {
	    x = out_dd(diagfp2, xdb_module, 1);
	    if (diag_format == DIAG_XDB_NEW) {
		fprintf(diagfp2, "0,0");
	    } else {
		diag_string(diagfp2, nm);
	    }
	    fprintf(diagfp2, ",%d\n", slt_num);
	    push_dscope(x, 1);
	    slt_special(2, x);
	    have_module = 1;
	}
    }
    return;
}


/*
    DIAGNOSTICS FOR LINE NUMBER

    This routine outputs an instruction indicating the position within
    the source file.
*/

void diag_source
(char *nm, long ln, int d)
{
    if (have_module && d == 0) return;
    if (!eq(nm, crt_fname))diag_source_file(nm, ln);
    crt_line_num = ln;
    if (d)slt_normal();
    return;
}


/*
    CURRENT DIAGNOSTICS PROCEDURE LABEL
*/

long crt_diag_proc_lab;


/*
    DIAGNOSTICS FOR A PROCEDURE
*/

void diag_proc_main
(diag_type dt, exp e, char *id, int is_glob, char *val)
{
    exp a;
    posn_t t;
    long fp;
    table_posn *p;
    diag_type dtl;

    /* Analyse result sort */
    if (dt->key != DIAG_TYPE_PROC) {
	error(ERROR_SERIOUS, "Illegal procedure type");
	return;
    }
    dtl = dt->data.proc.result_type;

    if (diag_format == DIAG_STAB) {
	mach_op *op = make_extern_data(val, 0);
	char *st = analyse_stab_type(dtl, id,(is_glob ? "F" : "f"));
	make_stabs(st, 36, crt_line_num, op);
	dnt_begin();
    } else {
	p = analyse_diag_type(diagfp2, dtl, 1);

	/* Create diagnostics procedure label */
	crt_diag_proc_lab = next_lab();

	/* Output function diagnostic directive */
	t = out_dd(diagfp2, xdb_function, 1);
	fprintf(diagfp2, "%d,1,", is_glob);
	if (diag_format == DIAG_XDB_NEW)fprintf(diagfp2, "0,0,0,0,0,");
	diag_string(diagfp2, id);
	if (strcmp(id, "main") == 0) {
	    fputc(',', diagfp2);
	    diag_string(diagfp2, "_MAIN_");
	    fputc(',', diagfp2);
	} else {
	    fprintf(diagfp2, ",0,");
	}
	fp = ftell(diagfp2);
	fprintf(diagfp2, "%s,%d,%s,", NULL_POSN_STR, slt_num, val);
	out_posn(diagfp2, p, 1);
	if (diag_format == DIAG_XDB_NEW)fprintf(diagfp2, "%s,", val);
	fprintf(diagfp2, "L%ld\n", crt_diag_proc_lab);

	/* Start new diagnostic scope */
	push_dscope(t, 2);
	slt_special(3, t);
    }

    /* Step over actual procedure arguments */
    a = son(e);
    while ( name ( a ) == ident_tag /* && isparam ( a ) */ ) {
	a = bro(son(a));
    }

    /* Read procedure argument definitions */
    while (name(a) == diagnose_tag) {
	diag_info *di = dno(a);
	if (di->key == DIAG_INFO_ID) {
	    exp ps = di->data.id_scope.access;
	    if (isparam(son(ps))) {
		diag_type pdt = di->data.id_scope.typ;
		char *pnm = di->data.id_scope.nme.ints.chars;
		long off = 8 + (no(ps) + no(son(ps))) / 8;
		if (diag_format == DIAG_STAB) {
		    mach_op *op = make_int_data(off);
		    char *st = analyse_stab_type(pdt, pnm, "p");
		    make_stabs(st, 160, L0, op);
		} else {
		    p = analyse_diag_type(diagfp2, pdt, 1);
		    t = out_dd(diagfp2, xdb_fparam, 1);
		    fill_gap(diagfp2, fp, t);
		    if (diag_format == DIAG_XDB_NEW) {
			fprintf(diagfp2, "0,0,0,0,0,");
		    } else {
			fprintf(diagfp2, "0,0,");
		    }
		    if (*pnm) {
			diag_string(diagfp2, pnm);
		    } else {
			diag_string(diagfp2, "__unknown");
		    }
		    fprintf(diagfp2, ",%ld,", off);
		    out_posn(diagfp2, p, 1);
		    fp = ftell(diagfp2);
		    if (diag_format == DIAG_XDB_NEW) {
			fprintf(diagfp2, "%s,0\n", NULL_POSN_STR);
		    } else {
			fprintf(diagfp2, "%s\n", NULL_POSN_STR);
		    }
		}
	    }
	}
	a = son(a);
    }
    return;
}


/*
    DIAGNOSTICS FOR A GLOBAL IDENTIFIER
*/

void diag_globl_variable
(diag_type dt, char *id, int is_glob, char *val, int has_def)
{
    if (diag_format == DIAG_STAB) {
	if (is_glob) {
	    char *st = analyse_stab_type(dt, id, "G");
	    make_stabs(st, 32, crt_line_num, null);
	} else {
	    mach_op *op = make_extern_data(val, 0);
	    char *st = analyse_stab_type(dt, id, "S");
	    make_stabs(st, 38, crt_line_num, op);
	}
    } else {
	int loc;
	FILE *file;
	table_posn *x;
	if (diag_format == DIAG_XDB_NEW) {
	    loc = (is_glob ? 0 : 1);
	    file = (is_glob ? diagfp3 : diagfp2);
	} else {
	    loc = 1;
	    file = diagfp2;
	}
	x = analyse_diag_type(file, dt, loc);
	(void)out_dd(file, xdb_svar, loc);
	if (diag_format == DIAG_XDB_NEW) {
	    fprintf(file, "%d,0,0,0,0,", is_glob);
	} else {
	    fprintf(file, "%d,0,", is_glob);
	}
	diag_string(file, id);
	if (has_def) {
	    fprintf(file, ",%s,", val);
	} else {
	    fprintf(file, ",-1,");
	}
	out_posn(file, x, 1);
	fprintf(file, "0,0\n");
    }
    return;
}


/*
    DIAGNOSTICS FOR A LOCAL IDENTIFIER
*/

void diag_local_variable
(diag_type dt, char *id, long fp)
{
    if (diag_format == DIAG_STAB) {
	mach_op *op = make_int_data(-fp);
	char *st = analyse_stab_type(dt, id, "l");
	make_stabs(st, 128, crt_line_num, op);
    } else {
	table_posn *x = analyse_diag_type(diagfp2, dt, 1);
	(void)out_dd(diagfp2, xdb_dvar, 1);
	if (diag_format == DIAG_XDB_NEW) {
	    fprintf(diagfp2, "0,0,0,0,");
	} else {
	    fprintf(diagfp2, "0,0,0,");
	}
	diag_string(diagfp2, id);
	fprintf(diagfp2, ",%ld,", -fp);
	if (diag_format == DIAG_XDB_NEW) {
	    out_posn(diagfp2, x, 1);
	    fprintf(diagfp2, "0\n");
	} else {
	    out_posn(diagfp2, x, 0);
	}
    }
    return;
}


/*
    DIAGNOSTICS FOR A TYPE DEFINITION
*/

void diag_type_defn
(char *nm, diag_type dt)
{
    switch (dt->key) {

	case DIAG_TYPE_UNINIT:
	case DIAG_TYPE_INITED: {
	    /* Ignore unused types */
	    break;
	}

	default : {
	    if (diag_format == DIAG_STAB) {
		char *st = analyse_stab_type(dt, nm, "t");
		make_stabs(st, 128, L1, null);
	    } else {
		int loc = (diag_format == DIAG_XDB_NEW ? 0 : 1);
		FILE *file = (loc ? diagfp2 : diagfp3);
		table_posn *p = analyse_diag_type(file, dt, loc);
		(void)out_dd(file, xdb_typedef, loc);
		fprintf(file, "0,");
		diag_string(file, nm);
		fprintf(file, ",");
		out_posn(file, p, 0);
	    }
	    break;
	}
    }
    return;
}
