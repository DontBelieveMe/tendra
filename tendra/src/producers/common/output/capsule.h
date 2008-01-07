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


#ifndef CAPSULE_INCLUDED
#define CAPSULE_INCLUDED


/*
 *    TDF CAPSULE OUTPUT DECLARATIONS
 *
 *    The routines in this module describe the top level TDF output.
 */

extern void init_capsule(void) ;
extern void init_diag(void) ;
extern void write_capsule(void) ;
extern void output_option(string) ;
extern BITSTREAM *enc_version(BITSTREAM *) ;

extern int output_tdf;
extern int output_capsule;
extern int output_all;
extern int output_bugs;
extern int output_builtin;
extern int output_date;
extern int output_diag;
extern int output_except;
extern int output_init;
extern int output_inline;
extern int output_new_diag;
extern int output_order;
extern int output_partial;
extern int output_rtti;
extern int output_shared;
extern int output_std;
extern int output_term;
extern int output_tokdec;
extern int output_unused;
extern int output_virtual;

#if TDF_OUTPUT

extern int capsule_id(IDENTIFIER, int) ;
extern ulong capsule_no(string, int) ;
extern ulong capsule_name(ulong, string *, int) ;
extern ulong unit_no(BITSTREAM *, IDENTIFIER, int, int) ;
extern ulong link_no(BITSTREAM *, ulong, int) ;
extern void clear_no(IDENTIFIER) ;
extern ulong no_labels(BITSTREAM *) ;
extern void record_usage(ulong, int, unsigned) ;
extern void clear_usage(ulong, int) ;
extern unsigned find_usage(ulong, int) ;
extern void set_diag_tag(IDENTIFIER, int, ulong) ;
extern ulong get_diag_tag(IDENTIFIER, int) ;
extern void count_item(BITSTREAM *) ;
extern void clear_params(void) ;

extern BITSTREAM *tokdec_unit, *tokdef_unit;
extern BITSTREAM *tagdec_unit, *tagdef_unit;
extern BITSTREAM *aldef_unit, *linkinfo_unit;
extern BITSTREAM *diagtype_unit, *diagdef_unit, *diagcomp_unit;
extern BITSTREAM *init_func, *term_func, *term_static_func;
extern ulong init_no, term_no;
extern CLASS_TYPE last_class;
extern ulong last_params [];
extern int last_conts [];

#endif


/*
 *    CAPSULE VARIABLE TYPES
 *
 *    These values correspond to the various types of linkable entity and
 *    entity groups within a TDF capsule.  They are used as arguments to
 *    capsule_id, unit_no etc.  VAR_label is a dummy value used for labels.
 */

#define EQN_tld			0
#define EQN_versions		1
#define EQN_tokdec		2
#define EQN_tokdef		3
#define EQN_aldef		4
#define EQN_diagtype		5
#define EQN_tagdec		6
#define EQN_diagdef		7
#define EQN_dgcomp		8
#define EQN_tagdef		9
#define EQN_linkinfo		10
#define EQN_no			11

#define VAR_tag			0
#define VAR_token		1
#define VAR_alignment		2
#define VAR_diagtag		3
#define VAR_dgtag		4
#define VAR_no			5

#define VAR_label		5
#define VAR_total		6


/*
 *    USAGE INFORMATION
 *
 *    These values are used to record the usage information for external
 *    identifiers.
 */

#define USAGE_NONE		((unsigned) 0x00)
#define USAGE_USE		((unsigned) 0x01)
#define USAGE_DECL		((unsigned) 0x02)
#define USAGE_DEFN		((unsigned) 0x04)
#define USAGE_COMMON		((unsigned) 0x08)


/*
 *    DUMMY TAG NUMBERS
 *
 *    These values give the codes for the dummy tag numbers stored in
 *    last_params.  The values 0-9 give the function parameter numbers.
 */

#define DUMMY_this		0
#define DUMMY_first		0
#define DUMMY_second		1

#define DUMMY_return		10
#define DUMMY_copy		11
#define DUMMY_extra		12
#define DUMMY_ellipsis		13
#define DUMMY_count		14
#define DUMMY_catch		15
#define DUMMY_token		16

#define DUMMY_params		10
#define DUMMY_max		20


#endif
