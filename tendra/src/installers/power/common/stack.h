/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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



/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/


#ifndef STACK_H
#define STACK_H  1

#define ALIGNNEXT(bitposn, bitalign)	(((bitposn)+(bitalign)-1) & ~((bitalign)-1))
#define ALLOCA_ALIGNMENT(n) ((n+7) & ~7)

/* Stack frame layout, from Assembler Reference manual page 4-19, in bytes */
#define STACK_LINK_AREA_SIZE		24
#define	STACK_BACK_CHAIN		0
#define	STACK_SAVED_CR			4
#define	STACK_SAVED_LR			8
#define	STACK_RESERVED1			12
#define	STACK_RESERVED2			16
#define	STACK_SAVED_TOC			20
#define	STACK_ARG_AREA			STACK_LINK_AREA_SIZE

#define	STACK_FIXED_REG_DUMP_AREA_SIZE	(19*4)		/* 19 fixed point */
#define	STACK_FLOAT_REG_DUMP_AREA_SIZE	((18*2)*4)	/* 18 doubles */
#define	STACK_REG_DUMP_AREA_SIZE	(ALIGNNEXT(STACK_FIXED_REG_DUMP_AREA_SIZE,8) \
						   +STACK_FLOAT_REG_DUMP_AREA_SIZE)
#define	STACK_MIN_MAXARGS		(8*4)		/* 8 words of params */

/* info on the stack frame of current proc being coded */
extern long p_no_of_returns;
extern long p_sreg_first_save;
extern long p_sfreg_first_save;
extern long p_frame_size;
extern long p_locals_offset;
extern long p_maxargbytes;

extern long p_args_and_link_size;/* maximum size of parameter list + LINK_AREA size in bytes */
extern bool p_has_fp;
extern bool p_has_saved_sp;
extern bool p_leaf;
extern bool p_has_back_chain;
extern bool p_has_alloca;
extern bool p_save_all_sregs;
extern bool p_has_vcallees;
extern bool p_has_no_vcallers;
extern long p_fixed_params;
extern long p_float_params;
extern long p_saved_sp_offset;
extern long p_callee_size;
extern bool p_has_tp;
extern int p_return_label;
extern ans p_result;/* what the result of the proc is */
extern exp p_current;
extern void generate_procedure_prologue(void);
extern void generate_procedure_epilogue(void);
extern void generate_untidy_procedure_epilogue(void);
extern void save_sp_on_stack(void);
extern void get_sp_from_stack(void);
extern void save_back_chain_using_frame_pointer(void);
extern void initialise_procedure(procrec *);
extern void restore_sregs(int,int);
extern void restore_link_register(void);
#define EXTRA_CALLEE_BYTES 8 /* the number of bytes added on to the callees i.e 4 to hold saved chain*/

#endif


