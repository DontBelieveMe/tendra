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


#ifndef TOK_INCLUDED
#define TOK_INCLUDED


/*
 *    TDF TOKEN ENCODING ROUTINES
 *
 *    The routines in this module are concerned with the encoding of the
 *    tokens used in the TDF output.
 */

extern TOKEN make_sort(CONST char *, int) ;
extern IDENTIFIER resolve_token(IDENTIFIER, CONST char *, int) ;
extern IDENTIFIER get_special(int, int) ;
extern string special_name(int) ;
extern void set_special(int, IDENTIFIER) ;
extern int token_code(TOKEN) ;
extern int builtin_token(IDENTIFIER) ;
extern void define_special(int) ;
extern void init_tok(int) ;

#if TDF_OUTPUT
extern ulong special_no(int) ;
extern BITSTREAM *enc_special(BITSTREAM *, int) ;
extern BITSTREAM *enc_diag_special(BITSTREAM *, int, int) ;
extern BITSTREAM *enc_sort(BITSTREAM *, int) ;
extern BITSTREAM *enc_token(BITSTREAM *, IDENTIFIER, LIST (TOKEN)) ;
extern BITSTREAM *enc_tokdef_body(BITSTREAM *, IDENTIFIER, TOKEN) ;
extern BITSTREAM *enc_asm(BITSTREAM *, EXP) ;
#endif


/*
 *    BASIC TYPE TOKEN INFORMATION
 *
 *    The table base_token contains the token numbers associated with the
 *    basic types.
 */

typedef struct {
    int tok;
    unsigned no;
    unsigned alt;
} BASE_TOKEN;

extern BASE_TOKEN base_token [];


/*
 *    SPECIAL TOKEN NUMBERS
 *
 *    These values correspond to the special tokens.
 */

#define TOK_char				0
#define TOK_signed_char				1
#define TOK_unsigned_char			2
#define TOK_signed_short			3
#define TOK_unsigned_short			4
#define TOK_signed_int				5
#define TOK_unsigned_int			6
#define TOK_signed_long				7
#define TOK_unsigned_long			8
#define TOK_signed_llong			9
#define TOK_unsigned_llong			10

#define TOK_float				11
#define TOK_double				12
#define TOK_long_double				13

#define TOK_bool				14
#define TOK_ptrdiff_t				15
#define TOK_size_t				16
#define TOK_size_t_2				17
#define TOK_wchar_t				18

#define TOK_convert				19
#define TOK_arith_type				20
#define TOK_promote				21
#define TOK_sign_promote			22

#define TOK_lit_int				23
#define TOK_lit_hex				24
#define TOK_lit_unsigned			25
#define TOK_lit_long				26
#define TOK_lit_ulong				27
#define TOK_lit_llong				28
#define TOK_lit_ullong				29

#define TOK_bitf_sign				30

#define TOK_ptr_void				31
#define TOK_null_pv				32
#define TOK_to_ptr_void				33
#define TOK_from_ptr_void			34
#define TOK_pv_test				35
#define TOK_pv_compare				36

#define TOK_ptr_to_ptr				37
#define TOK_f_to_pv				38
#define TOK_pv_to_f				39
#define TOK_i_to_p				40
#define TOK_p_to_i				41
#define TOK_i_to_pv				42
#define TOK_pv_to_i				43
#define TOK_ptr_rep				44

#define TOK_div					45
#define TOK_rem					46

#define TOK_va_t				47

#define TOK_pm_type				48
#define TOK_pm_make				49
#define TOK_pm_null				50
#define TOK_pm_offset				51
#define TOK_pm_cast				52
#define TOK_pm_uncast				53
#define TOK_pm_test				54
#define TOK_pm_compare				55

#define TOK_pmf_type				56
#define TOK_pmf_make				57
#define TOK_pmf_vmake				58
#define TOK_pmf_null				59
#define TOK_pmf_null2				60
#define TOK_pmf_delta				61
#define TOK_pmf_func				62
#define TOK_pmf_virt				63
#define TOK_pmf_cast				64
#define TOK_pmf_uncast				65
#define TOK_pmf_test				66
#define TOK_pmf_compare				67

#define TOK_comp_off				68
#define TOK_pad					69
#define TOK_empty_align				70
#define TOK_empty_shape				71
#define TOK_empty_offset			72

#define TOK_vtab_type				73
#define TOK_vtab_diag				74
#define TOK_vtab_make				75
#define TOK_vtab_pure				76
#define TOK_vtab_func				77
#define TOK_vtab_off				78

#define TOK_typeid_type				79
#define TOK_typeid_make				80
#define TOK_typeid_basic			81
#define TOK_typeid_ref				82
#define TOK_baseid_type				83
#define TOK_baseid_make				84
#define TOK_dynam_cast				85

#define TOK_destr_type				86
#define TOK_destr_global			87
#define TOK_destr_local				88
#define TOK_destr_end				89
#define TOK_destr_init				90
#define TOK_destr_null				91
#define TOK_destr_ptr				92
#define TOK_start				93

#define TOK_try_type				94
#define TOK_try_begin				95
#define TOK_try_end				96
#define TOK_except_alloc			97
#define TOK_except_throw			98
#define TOK_except_rethrow			99
#define TOK_except_catch			100
#define TOK_except_value			101
#define TOK_except_caught			102
#define TOK_except_end				103
#define TOK_except_bad				104
#define TOK_except_jump				105
#define TOK_ptr_code				106
#define TOK_ptr_frame				107

#define TOK_asm_sequence			108
#define TOK_asm					109
#define TOK_asm_input				110
#define TOK_asm_output				111
#define TOK_asm_address				112

#define TOK_char_offset				113
#define TOK_shape_offset			114
#define TOK_extra_offset			115
#define TOK_down_cast				116
#define TOK_destr_cast				117
#define TOK_destr_test				118

#define TOK_no					119


#endif
