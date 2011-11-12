/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: bstack.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/*  Definition of stack for maintaining isymMac and isymstart.

This is required because entries in the symbol table such as blocks,
procedures and files have two entries in the symbol table corresponding
to their beginning and end. The "start" entry has an associated index which
is the index of the "end" plus 1. The "end" entry has an associated index
which is the index of the "start". Consequently a stack of these indices
can be built up and an index is pushed when the start of a block, proc or
file is reached and popped when an end is reached. The routines for this are
given in bstack.c */

#define STACKSIZE 100


typedef struct stackdef {
		long symind[STACKSIZE];
		long strind [STACKSIZE];	/* space for stack elements */
		long pos;		/* current position of top of stack */
		struct stackdef * nextspace;	/* if more space required */
			} BSTACK;

/* An elemnt of the stack has the following type (result of popping a stack) */
typedef struct symstrdef	{long sym;
				long str;
				} SYMSTR;


extern void push(long, long, BSTACK *);
extern SYMSTR pop(BSTACK *);
