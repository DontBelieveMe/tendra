/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CPROC_H
#define CPROC_H

int cproc (exp p, char *pname, int cname, int global
#ifdef TDF_DIAG3
	, diag_descriptor *diag_props
#endif
#ifdef TDF_DIAG4
	, struct dg_name_t *diag_props
#endif
);
void restore_callregs(int untidy);

extern  unsigned normal_fpucon;
extern  int stack_aligned_8byte;
extern  int permit_8byte_align;
extern  int useful_double;
extern  int keep_short;
extern  int always_use_frame;   /* always use %ebp as a frame pointer */
extern  outofline *odd_bits;

#endif /* CPROC_H */
