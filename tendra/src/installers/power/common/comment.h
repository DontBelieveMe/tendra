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
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
    		 Crown Copyright (c) 1997

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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:42 $
$Revision: 1.2 $
$Log: comment.h,v $
 * Revision 1.2  1998/02/04  15:48:42  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:56  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef COMMENT_H
#define COMMENT_H


#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"			/* for bool */


extern bool do_comment;

extern void fail(char *);


#ifdef DO_COMMENT

/* implemented as functions in comment.c */
extern void COMMENT(char *);
extern void COMMENT1(char *, long);
extern void COMMENT2(char *, long, long);
extern void COMMENT3(char *, long, long, long);
extern void COMMENT4(char *, long, long, long, long);

#else

#define COMMENT(s)			((void)0)
#define COMMENT1(s,p1)			((void)0)
#define COMMENT2(s,p1,p2)		((void)0)
#define COMMENT3(s,p1,p2,p3)		((void)0)
#define COMMENT4(s,p1,p2,p3,p4)		((void)0)

#endif


#ifdef DO_FULLCOMMENT

#define FULLCOMMENT(s)			COMMENT(s)
#define FULLCOMMENT1(s,p1)		COMMENT1(s,p1)
#define FULLCOMMENT2(s,p1,p2)		COMMENT2(s,p1,p2)
#define FULLCOMMENT3(s,p1,p2,p3)	COMMENT3(s,p1,p2,p3)
#define FULLCOMMENT4(s,p1,p2,p3,p4)	COMMENT4(s,p1,p2,p3,p4)

#else

#define FULLCOMMENT(s)			((void)0)
#define FULLCOMMENT1(s,p1)		((void)0)
#define FULLCOMMENT2(s,p1,p2)		((void)0)
#define FULLCOMMENT3(s,p1,p2,p3)	((void)0)
#define FULLCOMMENT4(s,p1,p2,p3,p4)	((void)0)

#endif

#endif				/* COMMENT_H */








