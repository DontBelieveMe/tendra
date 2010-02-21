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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: installtypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1996/11/12  10:42:24  currie
 * unsigned cases
 *
 * Revision 1.6  1996/01/08  11:49:26  currie
 * ishppa
 *
 * Revision 1.5  1995/10/06  14:42:00  currie
 * Env-offset alignments + new div with ET
 *
 * Revision 1.4  1995/09/19  16:06:52  currie
 * isAlpha!!
 *
 * Revision 1.3  1995/09/11  15:35:37  currie
 * caller params -ve
 *
 * Revision 1.2  1995/05/05  08:10:54  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef installtypes_key
#define installtypes_key 1

typedef exp otagexp;

typedef struct otagexp_list_t {
	exp start;
	exp end;
	exp id;
	int number;
} otagexp_list;

typedef int procprops;

typedef int procprops_option;
typedef exp callees;
typedef int error_code;
typedef int error_code_list;

typedef tdfstring string;

union signed_nat_u {
	int small_s_nat;
	flpt big_s_nat;
};

struct signed_nat_t {
	union signed_nat_u signed_nat_val;
	char issmall;		/* 1 if small_s_nat 0 big */
	char negative;};	/* 1 for neg, 0 for pos */
typedef struct signed_nat_t signed_nat;

typedef struct nat_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	nat val;
} nat_option;

typedef struct exp_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	exp val;
} exp_option;


/* dummy definitions */
typedef int access;
typedef int access_option;

typedef int transfer_mode;


typedef struct alignment_t {
	int al_n;	/* code describing the state
			   1 - defined in al_val.al
			   2 - the join of al_val.al_join.a and b
			   3 - in al_val.al_join.a
			 */
	int sh_hd;
	struct alignment_u {
		int al;
		int al_frame;
		struct join_t {
			struct aldef_t *a;
			struct aldef_t *b;
		} al_join;
	} al_val;
} alignment_cell;

typedef struct aldef_t {
	struct aldef_t *next_aldef;	/* keeps a list of all aldefs */
	alignment_cell al;
} aldef;

typedef aldef *alignment;


struct bfvar_t {
	int bits;	/* number of bits in bitfield */
	int has_sign;	/* 1 if signed */
};
typedef struct bfvar_t bitfield_variety;

typedef char bool;

typedef exp shape;

typedef exp *label;

struct caselim_t {
	label lab;	/* label to jump if control between low and high */
	signed_nat low;
	signed_nat high;
};	/* caselim during reading */

typedef struct caselim_t caselim;

typedef struct error_treatment_t {
	int err_code;	/* code for treatment */
	label jmp_dest;
} error_treatment;	/* error treatment during reading */

 /* structure which describes a declaration */
struct dec_t {
	struct dec_t *def_next;
	/* if this is a global declaration this field holds next global
	   declaration which needs processing. If there is none, it is nilexp */
	union ut {
		struct dec_v {
			char *dec_id;
			/* identifier to be used */
			shape dec_shape;
			/* shape of the value */
			exp dec_exp;
			/* definition or nilexp */
			int unit_number;
			diag_global *diag_info;
			access acc;
			int index;
			/* used in inl_norm to hold procedure index number */

#if ismips || issparc || ispower || isAlpha || ishppa
			int sym_number;
#endif

			/* bitfields only after this */
			unsigned int extnamed :1;
			/* external */
			unsigned int dec_var :1;
			/* this is a variable */
			unsigned int dec_outermost :1;
			/* this is global */
			unsigned int have_def :1;
			/* we have a definition */
			unsigned int processed :1;
			/* this exp has been output */
			unsigned int isweak :1;
			/* definition is weak */
			unsigned int is_common :1;
			/* declaration is common */
			unsigned int has_signature : 1;
			/* declaration has signature */
		} dec_val;
	} dec_u;
};

typedef struct dec_t dec;

typedef dec *tag;
typedef aldef *al_tag;

typedef int floating_variety;
typedef unsigned char ntest;
typedef unsigned char rounding_mode;

typedef struct shape_list_t {
	shape *elems;
	int number;
} shape_list;	/* number shapes */

typedef shape variety;

typedef struct tag_option_t {
	bool present;
	/* 1 if val is present, 0 otherwise */
	tag val;
} tag_option;

typedef struct string_option_t {
	bool present;
	string val;
} string_option;

typedef struct tagsh_t {
	shape sha;
	access visible;
	tag tg;
} tagshacc;

typedef struct tagsh_list_t {
	exp id;
	exp last_def;
	exp last_id;
	exp proc_def;
	int size;
	int number;
} tagshacc_list;

typedef struct tagacc_t {
	tag tg;
	access visible;
} tagacc;

typedef struct tagacc_option_t {
	bool present;	/* 1 if val is present, 0 otherwise */
	tagacc val;
} tagacc_option;

typedef  struct labtag_t {
	label place_label;
} labtag;


typedef struct exp_list_t {
	exp start;	/* the first element of a list chained through bro */
	exp end;	/* the last element of a list chained through bro */
	int number;	/* the number of elements in the list */
} exp_list;

typedef exp caselim_list;


struct labtag_list_t {
	label *elems;
	int number;	/* number labels */
};
typedef struct labtag_list_t label_list;

typedef struct tagshacc_option_t {
	int present;	/* 1 if val is present, 0 otherwise */
	tagshacc val;
} tagshacc_option;

typedef struct proc_props_t {
	struct proc_props_t *pushed;
	exp proc_struct_result;
	int proc_label_count;
	float default_freq;
	alignment frame_alignment;
	int has_alloca;
	int proc_is_recursive;
	int uses_crt_env;
	int has_setjmp;
	int uses_loc_address;
	int proc_struct_res;
	int proc_externs;
	int in_proc_def;
	int rep_make_proc;
	int in_initial_value;
} proc_props;
/* holds properties of a procedure while an internally defined procedure is
 * being read */

typedef struct version_t {
	int major_version;
	int minor_version;
} version;

typedef int version_props;
typedef int version_list;

#endif /* installtypes_key */
