/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.tendra.org/>
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


/* sco/cv_fns.c */


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "readglob.h"
#include "out.h"
#include "machine.h"
#include "cv_types.h"
#include "cv_outtype.h"
#include "expmacs.h"
#include "tags.h"
#include "diag_fns.h"
#include "diagglob.h"
#include "mark_scope.h"


/* VARIABLES */
/* All variables initialised */

static int crt_proc_start;
static int last_line_no;
static char * main_filename;	/* init by diagnose_prelude */
static int filename_space = 0;	/* init by diagnose_prelude */
static long filename_pos;
static int filename_gate = 0;	/* init by diagnose_prelude */

/* PROCEDURES */

static int
check_filename(sourcemark sm)
{
	if (main_filename)
    {
		if (!strcmp(main_filename, sm.file->file.ints.chars))
			return 1;
		return 0;
    }
	else
    {
		main_filename = sm.file->file.ints.chars;
		return 1;
    }
}

void
out_diagnose_prelude(void)
{
	main_filename = (char*)0;
	filename_space = 0;
	filename_gate = 0;
	return;
}

void
out_diagnose_postlude(void)
{
	return;
}


#ifdef NEWDIAGS

void
code_diag_info(diag_info * d, int proc_no,
			   void (*mcode)(void *), void * args)
{
	if (d == nildiag) {
		(*mcode)(args);
		return;
	}
	switch (d->key) {
    case DIAG_INFO_SCOPE: {
		fprintf(fpout, " .def .bb; .val .; .scl 100;  .line %d; .endef\n",
				last_line_no);
		code_diag_info (d->more, proc_no, mcode, args);
		fprintf(fpout, " .def .eb; .val .; .scl 100; .line %d; .endef\n",
				last_line_no);
		return;
    }
    case DIAG_INFO_SOURCE: {
		int l = (int)d -> data.source.beg.line_no.nat_val.small_nat -
			crt_proc_start + 1;
		if (check_filename(d -> data.source.beg) && l != last_line_no) {
			last_line_no = l;
			if (l > 0)
				fprintf(fpout, " .ln %d\n", l);
		}
		code_diag_info (d->more, proc_no, mcode, args);
		return;
    }
    case DIAG_INFO_ID: {
		exp acc = d -> data.id_scope.access;
		ot ty;
		int p, param_dec;
		if (name(acc) != hold_tag && name(acc) != hold2_tag)
			failer("not hold_tag");
		acc = son(acc);
		if (name(acc) == cont_tag && name(son(acc)) == name_tag && isvar(son(son(acc))))
			acc = son(acc);
		if (name(acc) == name_tag && !isdiscarded(acc) && !isglob(son(acc))) {
			p = (no(acc) + no(son(acc))) / 8;
			param_dec = isparam(son(acc));
			fprintf(fpout, " .def %s; .val ", d -> data.id_scope.nme.ints.chars);
			if (param_dec)
				fprintf(fpout, "%d", p+8);
			else
				fprintf(fpout, "%d-.Ldisp%d", p, proc_no);
			fprintf(fpout, "; .scl %d; ", (param_dec) ? 9 : 1);
			ty = out_type(d -> data.id_scope.typ, 0);
			fprintf(fpout, ".type 0%o; .endef\n", ty.type + (ty.modifier<<4));
		}
		code_diag_info (d->more, proc_no, mcode, args);
    }
	}
	return;
}

#else

void
output_diag(diag_info * d, int proc_no, exp e)
{
	if (d -> key == DIAG_INFO_SOURCE)
	{
		int l = (int)d -> data.source.beg.line_no.nat_val.small_nat -
			crt_proc_start + 1;
		if (!check_filename(d -> data.source.beg))
			return;

		if (l == last_line_no)
			return;
		last_line_no = l;
		if (l > 0)
			fprintf(fpout, " .ln %d\n", l);
		return;
	}
	if (d -> key == DIAG_INFO_ID)
	{
		ot ty;
		exp acc = d -> data.id_scope.access;
		int p = (no(acc) + no(son(acc))) / 8;
		int param_dec = isparam(son(acc));

		mark_scope(e);

		if (props(e) & 0x80)
		{
			fprintf(fpout, " .def .bb; .val .; .scl 100;  .line %d; .endef\n",
					last_line_no);
		}

		fprintf(fpout, " .def %s; .val ", d -> data.id_scope.nme.ints.chars);
		if (param_dec)
			fprintf(fpout, "%d", p+8);
		else
			fprintf(fpout, "%d-.Ldisp%d", p, proc_no);
		fprintf(fpout, "; .scl %d; ", (param_dec) ? 9 : 1);
		ty = out_type(d -> data.id_scope.typ, 0);
		fprintf(fpout, ".type 0%o; .endef\n", ty.type + (ty.modifier<<4));

		return;
	}

	return;
}
#endif

void
output_end_scope(diag_info * d, exp e)
{
	if (d -> key == DIAG_INFO_ID && props(e) & 0x80)
		fprintf(fpout, " .def .eb; .val .; .scl 100; .line %d; .endef\n",
				last_line_no);
	return;
}

void
diag_val_begin(diag_global * d, int global,
			   int cname, char * pname)
{
	ot typ;

	outs(" .def ");
	outs(d -> data.id.nme.ints.chars);
	outs("; .val ");
	if (cname == -1) {
		outs (pname);
	}
	else {
		outs(local_prefix);
		outn ((long)cname);
	}
	outs("; .scl ");
	outn((long)(global ? 2 : 3));
	outs("; ");
	typ = out_type(d -> data.id.new_type, 0);
	fprintf(fpout, ".type 0%o; .endef\n", typ.type + (typ.modifier << 4));
	return;
}

void
diag_val_end(diag_global * d)
{
	UNUSED(d);
	return;
}

void
diag_proc_begin(diag_global * d, int global,
				int cname, char * pname)
{
	ot typ;
	UNUSED(cname);

	if (!d)
		return;

	check_filename(d -> data.id.whence);

	outs(" .def ");
	outs(d -> data.id.nme.ints.chars);
	outs("; .val ");
	outs(pname);
	outs("; .scl ");
	outn((long)(global ? 2 : 3));
	outs("; ");
	typ = out_type(d -> data.id.new_type->data.proc.result_type, 0);
	fprintf(fpout, ".type 0%o; .endef\n",
			typ.type + (typ.modifier << 6) + 32);

	crt_proc_start = d -> data.id.whence.line_no.nat_val.small_nat;
	last_line_no = 1;
	fprintf(fpout, " .def .bf; .val .; .scl 101; .line %d; .endef\n",
            crt_proc_start);
	fprintf(fpout, " .ln 1\n");
	return;
}

void
diag_proc_end(diag_global * d)
{
	if (!d)
		return;
	fprintf(fpout, " .def .ef; .val .; .scl 101; .line %d; .endef\n",
            last_line_no + 1);
	fprintf(fpout, " .def %s; .val .; .scl -1; .endef\n",
            d -> data.id.nme.ints.chars);
	return;
}


void
OUTPUT_GLOBALS_TAB(void)
{
	diag_descriptor *di = unit_diagvar_tab.array;
	int n = unit_diagvar_tab.lastused;
	int i;
	ot typ;

	for (i=0; i<n; i++)
	{
		if (di[i].key == DIAG_TYPEDEF_KEY)
		{
			fprintf (fpout, " .def %s; .scl 13; ", di[i].data.typ.nme.ints.chars);
			typ = out_type (di[i].data.typ.new_type, 0);
			fprintf(fpout, ".type 0%o; .endef\n", typ.type + (typ.modifier << 4));
		}
	}
	return;
}

void
OUTPUT_DIAG_TAGS(void)
{
	diag_tagdef ** di = cunit->u_ind_diagtags;
	int n = cunit->u_ndiagtags;
	int i;

	if (!filename_space)
	{
		filename_pos = ftell(fpout);
		outs ("                                                                                                                      ");
		outnl ();
		filename_space = 1;
	}

	for (i=0; i<n; ++i)
	{
		diag_type d = di[i]->d_type;
		switch (d -> key)
		{
        case DIAG_TYPE_STRUCT:
        case DIAG_TYPE_UNION:
        case DIAG_TYPE_ENUM:
            out_tagged(d);
            break;
        default: break;
		}
	}
	return;
}

void
INSPECT_FILENAME(filename fn)
{
	long here;
	char * nm = fn -> file.ints.chars;
	char * f;
	int len = (int)strlen(fn -> file.ints.chars);

	if (filename_gate || len < 4 || len > 120 || nm[len-1] == 'h' ||
		nm[len-2] != '.')
		return;

	f = &nm[len-2];

	while (f != nm && f[-1] != '/')
		--f;

	filename_gate = 1;

	if (!filename_space)
		fprintf(fpout, " .file \"%s\"\n", f);
	else
	{
		here = ftell(fpout);
		fseek (fpout, filename_pos, 0);
		fprintf(fpout, " .file \"%s\"\n", f);
		fseek(fpout, here, 0);
	}
	return;
}
