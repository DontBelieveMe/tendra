/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/* automatically generated - edit with care */
typedef enum {
	ident_tag = 1,
	seq_tag = 3,
	cond_tag = 4,
	labst_tag = 5,
	rep_tag = 6,
	goto_tag = 7,
	test_tag = 8,
	ass_tag = 9,
	apply_tag = 11,
	res_tag = 12,
	goto_lv_tag = 13,
	solve_tag = 15,
	assvol_tag = 16,
	compound_tag = 17,
	nof_tag = 18,
	local_free_all_tag = 19,
	local_free_tag = 20,
	last_local_tag = 21,
	long_jump_tag = 22,
	concatnof_tag = 23,
	ncopies_tag = 24,
	case_tag = 25,
	movecont_tag = 26,
	testbit_tag = 27,
	alloca_tag = 28,
	diagnose_tag = 29,
	prof_tag = 30,
	ignorable_tag = 31,
	bfass_tag = 32,
	bfassvol_tag = 33,
	plus_tag = 39,
	neg_tag = 40,
	shl_tag = 41,
	mod_tag = 43,
	rem2_tag = 44,
	abs_tag = 45,
	round_tag = 46,
	offset_pad_tag = 47,
	offset_div_tag = 48,
	offset_max_tag = 49,
	minptr_tag = 50,
	fpower_tag = 51,
	fplus_tag = 52,
	fminus_tag = 53,
	fmult_tag = 54,
	fdiv_tag = 55,
	fabs_tag = 56,
	fneg_tag = 57,
	float_tag = 58,
	chfl_tag = 59,
	and_tag = 60,
	or_tag = 61,
	xor_tag = 62,
	not_tag = 63,
	component_tag = 64,
	max_tag = 65,
	min_tag = 66,
	bitf_to_int_tag = 67,
	bfcont_tag = 68,
	fmax_tag = 69,
	shr_tag = 70,
	fmin_tag = 71,
	div0_tag = 72,
	bfcontvol_tag = 73,
	absbool_tag = 74,
	addptr_tag = 75,
	chvar_tag = 76,
	minus_tag = 77,
	mult_tag = 78,
	subptr_tag = 79,
	realpart_tag = 80,
	div1_tag = 81,
	div2_tag = 82,
	offset_add_tag = 83,
	offset_div_by_int_tag = 84,
	offset_mult_tag = 85,
	offset_negate_tag = 86,
	offset_subtract_tag = 87,
	rem0_tag = 88,
	rotl_tag = 89,
	rotr_tag = 90,
	power_tag = 91,
	imag_tag = 92,
	make_complex_tag = 93,
	int_to_bitf_tag = 94,
	hold_tag = 101,
	cont_tag = 113,
	field_tag = 114,
	val_tag = 115,
	reff_tag = 116,
	name_tag = 117,
	proc_tag = 118,
	top_tag = 119,
	contvol_tag = 120,
	current_env_tag = 121,
	env_offset_tag = 122,
	make_lv_tag = 123,
	clear_tag = 124,
	null_tag = 125,
	real_tag = 126,
	string_tag = 127
} 
enum_tag_name;
typedef enum {
	bothd = 1,
	tophd = 2,
	scharhd = 3,
	ucharhd = 4,
	swordhd = 5,
	uwordhd = 6,
	slonghd = 7,
	ulonghd = 8,
	s64hd = 9,
	u64hd = 10,
	shcomplexhd = 17,
	complexhd = 18,
	complexdoublehd = 19,
	shrealhd = 20,
	realhd = 21,
	doublehd = 22,
	bitfhd = 23,
	prokhd = 24,
	ptrhd = 25,
	offsethd = 26,
	sizehd = 27,
	cpdhd = 28,
	nofhd = 29,
	tokhd = 30
} 
enum_shape_name;
