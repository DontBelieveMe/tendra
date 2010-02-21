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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/utility.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: utility.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:00  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:19  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:47  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.1  93/02/22  17:16:58  17:16:58  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include "xalloc.h"

extern char *basename(char *);

extern int bits_in(bitpattern);
extern int bit_one(bitpattern);

extern bitpattern lo_bits[];
extern bitpattern hi_bits[];

#define  alloc_nof(TYPE, N)\
	((TYPE *)xmalloc((N)* sizeof(TYPE)))

#define  realloc_nof(PTR, TYPE, N)\
	((TYPE *)xrealloc((PTR), (N)* sizeof(TYPE)))

#define  eq(X, Y)		(!strcmp((X), (Y)))
#define  maximum(X, Y)	(((X) > (Y))?(X):(Y))
#define  minimum(X, Y)	(((X) > (Y))?(Y):(X))
#define  array_size(X)	(sizeof(X) / sizeof(X[0]))
#define  round(X, Y)		((Y)*(((X) + (Y) - 1) / (Y)))
#define  log2(X)		bit_one(X)
#define  pow2(X)		(1 << (X))
#define  is_pow2(X)		(((X) & ((X) - 1)) == 0)

#endif
