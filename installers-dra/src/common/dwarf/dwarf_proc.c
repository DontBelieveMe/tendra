/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/02/04 10:43:38 $
$Revision: 1.2 $
$Log: dwarf_proc.c,v $
 * Revision 1.2  1998/02/04  10:43:38  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/04/01  17:20:32  pwe
 * diagnose pl_tests
 *
 * Revision 1.2  1995/09/28  12:39:56  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:24  pwe
 * transferred from DJCH
 *
**********************************************************************/

/* LOG 7/9/93 changes for SPARC SVR4.2 djch
   */
/* LOG 25/11/93 removed redundant args with UNUSED djch */

#include "config.h"
#include "installtypes.h"

/* machine dependant */
#include "machine.h"
#include "codermacs.h"
#include "tags.h"
#include "out.h"

#include "shapemacs.h"

/* machine dependant */
#include "expmacs.h"

#include "basicread.h"
#include "diag_config.h"
#include "dwarf_types.h"
#include "dwarf_type.h"
#include "dwarf_out.h"
#include "dwarf_mc.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

extern int continue_decs;

void
out_dwarf_proc_args(diag_type t)
{
	if (t->key != DIAG_TYPE_PROC) {
		failer("Can't output args of non proc type");
	}

	if (t->data.proc.opt_args) {
		cont_sib_chain(TAG_unspecified_parameters);
		leave_dwarf_blk();
	}
}


void
diag_proc_begin(diag_global *d_props, int global, int cname, char *pname)
{
	UNUSED(cname);
	UNUSED(pname);

	if (!d_props) {
		return;
	}

	outs(COMMENT_2("\t", "\tHere beginneth a proc"));
	outnl();
	if (d_props->desc->key != DIAG_ID_KEY) {
		failer("proc beg without id");
	}

	next_dwarf_lab(&(d_props->lab));
	OUT_DWARF_BEG(&(d_props->lab));

	if (global) {
		cont_sib_chain(TAG_global_subroutine);
	} else {
		cont_sib_chain(TAG_subroutine);
	}

	out_dwarf_name_attr(TDFSTRING2CHAR(d_props->desc->data.id.nme));
	out_dwarf_type_attr(d_props->desc->data.id.new_type->data.proc.result_type);
	OUT_DWARF_ATTR(AT_low_pc);
	dwarf4(LAB2CHAR(d_props->lab.beg));
	OUT_DWARF_ATTR(AT_high_pc);
	dwarf4(LAB2CHAR(d_props->lab.end));
	leave_dwarf_blk();
	make_next_new_chain();

	/* must be OUTSIDE blk */
	out_dwarf_sourcemark(&d_props->desc->data.id.whence);

	out_dwarf_proc_args(d_props->desc->data.id.new_type);
	continue_decs = 1;
}


void
diag_proc_end(diag_global *d_props)
{
	if (!d_props) {
		return;
	}

	outs(COMMENT_2("\t", "\tHere endeth a proc"));
	outnl();
	OUT_DWARF_END(& (d_props->lab));
	end_sib_chain();
}


void
diag_val_begin(diag_global *d_props, int global, int cname, char *pname)
{
	UNUSED(d_props);
	UNUSED(global);
	UNUSED(cname);
	UNUSED(pname);

	outs(COMMENT_2("\t", "\tHere beginneth a val"));
	outnl();
}


void
diag_val_end(diag_global *d_props)
{
	UNUSED(d_props);

	outs(COMMENT_2("\t", "\tHere endeth a val"));
	outnl();
}
