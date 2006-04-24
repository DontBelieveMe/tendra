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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/proc.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: proc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/03/26  13:04:49  pwe
 * general proc compatibility
 *
 * Revision 1.4  1995/11/07  09:51:32  john
 * New extern
 *
 * Revision 1.3  1995/07/14  16:33:37  john
 * New macro
 *
 * Revision 1.2  1995/05/26  13:00:34  john
 * Changes for new spec (3.1)
 *
 * Revision 1.1.1.1  1995/03/13  10:18:51  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:31  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:03  14:59:03  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef PROCDECS_INCLUDED
#define PROCDECS_INCLUDED

#include "addrtypes.h"
#include "proctypes.h"
#include "exptypes.h"

struct proc_state {
  ans procans;
  bool leaf_proc;
  baseoff mem_temp0;
  int rscope_level;
  int rscope_label;
  int result_label;
  long params_offset;
  long frame_size;
  long locals_offset;
  long locals_space;
  long maxargs;
  long callee_size;
};

extern bool Has_vcallees;
extern bool Has_no_vcallers;
extern bool in_general_proc;
extern int callee_size;
#ifdef GENCOMPAT
extern bool May_have_callees;
#endif

extern struct proc_state proc_state;

extern baseoff mem_temp(int);
extern makeans make_proc_tag_code(exp, space, where, int);
extern makeans make_rscope_tag_code(exp, space, where, int);
extern makeans make_res_tag_code(exp, space, where, int);
extern makeans make_apply_tag_code(exp, space, where, int);
extern makeans make_apply_general_tag_code(exp,space,where,int);
extern makeans make_make_callee_list_tag(exp,space,where,int);
extern makeans make_make_dynamic_callee_tag(exp,space,where,int);
extern makeans make_same_callees_tag(exp,space,where,int);
extern makeans make_tail_call_tag(exp,space,where,int);

#define PARAMS_OFFSET(16+1)*32

#endif /* PROCDECS_INCLUDED */
