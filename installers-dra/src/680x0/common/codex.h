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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/codex.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: codex.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:10  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:49  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:11  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:25  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:53  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:10  john
 *
 * Revision 1.2  94/02/21  15:57:12  15:57:12  ra (Robert Andrews)
 * Declare functions with no arguments using ( void ).
 *
 * Revision 1.1  93/02/22  17:15:26  17:15:26  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef CODEX_INCLUDED
#define CODEX_INCLUDED

#include "config.h"

#include "installtypes.h"

extern int ins(long, int, int, int);
extern int insf(long, int, int, int);
extern void libcall(char *);
extern bool reserved(char *);

extern bitpattern regsinuse;
extern bitpattern regsinproc;
extern bitpattern reuseables;
extern bitpattern regsindec;
extern bitpattern bigregs;
extern long crt_ret_lab;

extern bool used_stack;
extern bool used_ldisp;
extern long max_stack;
extern long extra_stack;
extern long stack_dec;
extern long stack_size;
extern long ldisp;
extern int no_calls;

extern long stack_change;
extern int stack_direction;
extern void add_to_reg(int, long);
extern void dec_stack(long);
extern void update_stack(void);

extern void area(int);
#define  ptext		0
#define  pdata		1
#define  pbss		2
#define  plast		3

extern void profile_hack(void);
extern void cproc(exp, char *, long, int, int, diag_global *);

#endif
