/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
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
 */





#ifndef procreckey
#define procreckey 1

#include "exptypes.h"

#define wfixno		32
#define wfloatno	32

struct needst {
	int   fixneeds;		/* no of fixed t-regs required */
	int   floatneeds;		/* no of float t-regs required */
	prop propsneeds;		/* various binary properties of exp */
	int   maxargs;		/* size in bits for actual parameters in
						 *				   exp */
};
typedef struct needst needs;

struct weightst {
	float  fix[wfixno];
	float  floating[wfloatno];
};
typedef struct weightst weights;
/* used to allocate tags to registers */


struct spacereqt {
	long  fixdump;
	long	fltdump;
	long  stack;
	exp obtain;
};
typedef struct spacereqt  spacereq;
/* used characterise s-reg and stack requirements of proc */

struct procrect {
	needs      needsproc;
	spacereq   spacereqproc;
	bool leaf_proc;
	bool alloca_proc;
	bool has_fp;
	bool has_tp;
	bool has_saved_sp;
	bool save_all_sregs;
	bool has_vcallees;
	bool has_no_vcallers;
	long callee_size;
	long locals_space;
	long locals_offset;
	long frame_size;
	long params_offset;
	long maxargs;
	long max_callee_bytes;
	int sreg_first_save;
	int sfreg_first_save;
	long no_of_returns;
};
typedef struct procrect procrec;
/* various properties of a procedure */

struct wpt {
	weights wp_weights;
	long  fix_break;
	long  float_break;
};
typedef struct wpt  wp;
/* used to allocate tags to registers */

struct spacet {
	long  fixed;
	long  flt;
};
typedef struct spacet space;
/* used to indicate free t-regs in code production */

#endif
