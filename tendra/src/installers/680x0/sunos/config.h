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


/*
 *    CONFIGURATION FILE
 *
 *    This file contains the basic information required by all files and
 *    the macros controlling the selection of target-dependent optimizations.
 */

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


/*
 *    DEFINE BASIC TYPES
 */

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN 0
#endif

typedef unsigned long bitpattern;

#define null NULL


/*
 *    SHOULD WE USE ALLOCA?
 */

#define NO_ALLOCA


/*
 *    DECLARE ERROR REPORTING FUNCTIONS
 *
 *    These functions are defined in utility.c.
 */

extern void error(char *, ...);
extern void warning(char *, ...);

#ifdef EBUG
#define  debug_warning(X) 	warning (X)
#else
#define  debug_warning(X)
#endif


/*
 *   DEFINE MACHINE TYPE
 *   
 *   It's a 68000, it isn't anything else.
 */

#define  SUN
#define  is68000		1
#define  is80x86		0
#define  ismips			0
#define  ispower		0
#define  issco			0
#define  issparc		0
#define  isvax			0
#define  isAlpha                0


/*
 *    DEFINE COMPILATION OPTIONS
 */

#define  check_shape		1	/* Check shape-correctness */
#define  convert_floats		1	/* Convert floating constants */
#define  dont_unpad_apply	1	/* Careful with procedure results */
#define  dynamic_diag_test	1	/* Test diagnostics format */
#define  has_byte_ops		1	/* Do have byte opertions */
#define  has_byte_regs		1	/* Do have byte registers */
#define  has_neg_shift		0	/* Don't have negative shifts */
#define  has_setcc		0	/* Don't use scc */
#define  has64bits		0	/* Doesn't have 64 bits */
#define  have_diagnostics	0	/* Have diagnostics */
#define  little_end		0	/* Big endian */
#define  load_ptr_pars		1	/* Inline ptr parameters */
#define  no_bitfield_ops	1	/* Do have bitfield operations */
#define  only_inline_static	1	/* Only inline static procedures */
#define  only_lengthen_ops	0	/* Don't avoid byte registers */
#ifdef SUN
#define  promote_pars           1       /* Parameters are 32 bit */
#endif
#define  no_trap_on_nil_contents 1      /* Let common code detect nil access */
#define  remove_zero_offsets	1	/* Do remove zero offsets */
#define  replace_compound	1	/* Replace compounds by externals */
#define  shift_is_byte		0	/* Shift count is not 8-bit */
#define  special_fns		1	/* Do look for special functions */
#define  substitute_params	1	/* Do substitute parameters */
#define  temp_mips		0	/* Don't need a mips hack */
#define  use_long_double	0	/* Not yet anyway */
#define  div0_implemented	1	/* div0 and rem0 implemented */
#define  remove_unused_counters	0	/* for foralls optimisation */
#define  remove_unused_index_counters\
				0	/* for foralls optimisation */
#define  good_index_factor(f)	0	/* for foralls optimisation */
#define  good_pointer_factor(f)\
				((f) != 1 && (f) != 2 &&\
				  (f) != 4 && (f) != 8)
#define  jump_table_density	10	/* for cases optimisation */
#define  non_default_entries	4	/* for cases optimisation */
#define  non_default_destinations\
				2	/* for cases optimisation */
#define  substitute_complex	1	/* don't have native complex numbers */


/*
 *    HACKS FOR CROSS-COMPILATION
 *
 *    Some routines are target-dependent and may not work properly when
 *    cross-compiling.  This section should take care of this.
 */

#ifdef CROSS_COMPILE
#undef   convert_floats
#define  convert_floats		0	/* Just to be on the safe side */
#endif

#ifdef SUN /* The SunOS 68k assembler whinges about align directives */
#define no_align_directives
#endif


/*
 *    EXTRA TAGS
 *
 *    These are target-specific tags.  Strictly speaking they belong in
 *    tags.h.
 */

#define  dummy_tag		100
#define  internal_tag		101
#define  regpair_tag		102


/*
 *    LONG INTEGER LITERALS
 *
 *    Some compilers don't understand 0L etc.
 */

#ifdef __STDC__
#define  L0			0L
#define  L1			1L
#define  L2			2L
#define  L3			3L
#define  L4			4L
#define  L5			5L
#define  L6			6L
#define  L7			7L
#define  L8			8L
#define  L9			9L
#define  L10			10L
#define  L16			16L
#define  L32			32L
#define  L64			64L
#define  L65536			65536L
#define  L21474836478		21474836478L
#define  L_1			-1L
#else
#define  L0			((long) 0)
#define  L1			((long) 1)
#define  L2			((long) 2)
#define  L3			((long) 3)
#define  L4			((long) 4)
#define  L5			((long) 5)
#define  L6			((long) 6)
#define  L7			((long) 7)
#define  L8			((long) 8)
#define  L9			((long) 9)
#define  L10			((long) 10)
#define  L16			((long) 16)
#define  L32			((long) 32)
#define  L64			((long) 64)
#define  L65536			((long) 65536)
#define  L21474836478		((long) 21474836478)
#define  L_1			((long) -1)
#endif

#define HAS_MAGIC		1
#define substitute_complex	1


#endif
