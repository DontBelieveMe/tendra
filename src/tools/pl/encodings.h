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


#ifndef ENCODING_INCLUDED
#define ENCODING_INCLUDED


/* CONSTRUCTS FOR ACCESS */

#define o_access_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_access_apply_token, ( unsigned ) 4 ),\
	s_access, p0, p1 )

#define o_access_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_access_cond, ( unsigned ) 4 ),\
	s_access, p0, p1, p2 )

#define o_add_accesses( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_add_accesses, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_access ) ;\
	p1 ; ASSERT_SORT ( s_access ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_constant\
    {\
	out_basic_int ( ( unsigned long ) e_constant, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_long_jump_access\
    {\
	out_basic_int ( ( unsigned long ) e_long_jump_access, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_no_other_read\
    {\
	out_basic_int ( ( unsigned long ) e_no_other_read, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_no_other_write\
    {\
	out_basic_int ( ( unsigned long ) e_no_other_write, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_out_par\
    {\
	out_basic_int ( ( unsigned long ) e_out_par, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_preserve\
    {\
	out_basic_int ( ( unsigned long ) e_preserve, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_register\
    {\
	out_basic_int ( ( unsigned long ) e_register, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_standard_access\
    {\
	out_basic_int ( ( unsigned long ) e_standard_access, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_used_as_volatile\
    {\
	out_basic_int ( ( unsigned long ) e_used_as_volatile, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }

#define o_visible\
    {\
	out_basic_int ( ( unsigned long ) e_visible, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_access ) ;\
    }


/* CONSTRUCTS FOR AL_TAG */

#define o_al_tag_apply_token( p0, p1 )\
    TOK_APP (\
	out_extendable_int ( ( unsigned long ) e_al_tag_apply_token, ( unsigned ) 1 ),\
	s_al_tag, p0, p1 )

#define o_make_al_tag( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_al_tag, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_al_tag ) ;\
    }


/* CONSTRUCTS FOR AL_TAGDEF */

#define o_make_al_tagdef( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_al_tagdef, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	p1 ; ASSERT_SORT ( s_alignment ) ;\
	SET_RSORT ( s_al_tagdef ) ;\
    }


/* CONSTRUCTS FOR AL_TAGDEF_PROPS */

#define o_make_al_tagdefs( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_al_tagdef_list ( p1 ) ;\
	SET_RSORT ( s_al_tagdef_props ) ;\
    }


/* CONSTRUCTS FOR ALIGNMENT */

#define o_alignment_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_alignment_apply_token, ( unsigned ) 4 ),\
	s_alignment, p0, p1 )

#define o_alignment_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_alignment_cond, ( unsigned ) 4 ),\
	s_alignment, p0, p1, p2 )

#define o_alignment( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_alignment, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_alloca_alignment\
    {\
	out_basic_int ( ( unsigned long ) e_alloca_alignment, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_callees_alignment( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_callees_alignment, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_bool ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_callers_alignment( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_callers_alignment, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_bool ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_code_alignment\
    {\
	out_basic_int ( ( unsigned long ) e_code_alignment, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_locals_alignment\
    {\
	out_basic_int ( ( unsigned long ) e_locals_alignment, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_obtain_al_tag( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_obtain_al_tag, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_al_tag ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_parameter_alignment( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_parameter_alignment, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_unite_alignments( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_unite_alignments, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	p1 ; ASSERT_SORT ( s_alignment ) ;\
	SET_RSORT ( s_alignment ) ;\
    }

#define o_var_param_alignment\
    {\
	out_basic_int ( ( unsigned long ) e_var_param_alignment, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_alignment ) ;\
    }


/* CONSTRUCTS FOR BITFIELD_VARIETY */

#define o_bfvar_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_bfvar_apply_token, ( unsigned ) 2 ),\
	s_bitfield_variety, p0, p1 )

#define o_bfvar_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_bfvar_cond, ( unsigned ) 2 ),\
	s_bitfield_variety, p0, p1, p2 )

#define o_bfvar_bits( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_bfvar_bits, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_bool ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_bitfield_variety ) ;\
    }


/* CONSTRUCTS FOR BOOL */

#define o_bool_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_bool_apply_token, ( unsigned ) 3 ),\
	s_bool, p0, p1 )

#define o_bool_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_bool_cond, ( unsigned ) 3 ),\
	s_bool, p0, p1, p2 )

#define o_false\
    {\
	out_basic_int ( ( unsigned long ) e_false, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_bool ) ;\
    }

#define o_true\
    {\
	out_basic_int ( ( unsigned long ) e_true, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_bool ) ;\
    }


/* CONSTRUCTS FOR CALLEES */

#define o_make_callee_list( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_callee_list, ( unsigned ) 2 ) ;\
	o_exp_list ( p0 ) ;\
	SET_RSORT ( s_callees ) ;\
    }

#define o_make_dynamic_callees( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_dynamic_callees, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_callees ) ;\
    }

#define o_same_callees\
    {\
	out_basic_int ( ( unsigned long ) e_same_callees, ( unsigned ) 2 ) ;\
	SET_RSORT ( s_callees ) ;\
    }


/* CONSTRUCTS FOR CAPSULE */

#define o_make_capsule( p0, p1, p2, p3 )\
    {\
	o_tdfident_list ( p0 ) ;\
	o_capsule_link_list ( p1 ) ;\
	o_extern_link_list ( p2 ) ;\
	o_group_list ( p3 ) ;\
	SET_RSORT ( s_capsule ) ;\
    }


/* CONSTRUCTS FOR CAPSULE_LINK */

#define o_make_capsule_link( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfident ) ;\
	p1 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_capsule_link ) ;\
    }


/* CONSTRUCTS FOR CASELIM */

#define o_make_caselim( p0, p1, p2 )\
    {\
	p0 ; ASSERT_SORT ( s_label ) ;\
	p1 ; ASSERT_SORT ( s_signed_nat ) ;\
	p2 ; ASSERT_SORT ( s_signed_nat ) ;\
	SET_RSORT ( s_caselim ) ;\
    }


/* CONSTRUCTS FOR DIAG_DESCRIPTOR */

#define o_diag_desc_id( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_desc_id, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	p1 ; ASSERT_SORT ( s_sourcemark ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_descriptor ) ;\
    }

#define o_diag_desc_struct( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_desc_struct, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	p1 ; ASSERT_SORT ( s_sourcemark ) ;\
	p2 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_descriptor ) ;\
    }

#define o_diag_desc_typedef( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_desc_typedef, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	p1 ; ASSERT_SORT ( s_sourcemark ) ;\
	p2 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_descriptor ) ;\
    }


/* CONSTRUCTS FOR DIAG_FIELD */

#define o_make_diag_field( p0, p1, p2 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_field ) ;\
    }


/* CONSTRUCTS FOR DIAG_TAG */

#define o_make_diag_tag( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_diag_tag, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_diag_tag ) ;\
    }


/* CONSTRUCTS FOR DIAG_TAGDEF */

#define o_make_diag_tagdef( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_diag_tagdef, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	p1 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_tagdef ) ;\
    }


/* CONSTRUCTS FOR DIAG_TQ */

#define o_add_diag_const( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_add_diag_const, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_diag_tq ) ;\
	SET_RSORT ( s_diag_tq ) ;\
    }

#define o_add_diag_volatile( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_add_diag_volatile, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_diag_tq ) ;\
	SET_RSORT ( s_diag_tq ) ;\
    }

#define o_diag_tq_null\
    {\
	out_basic_int ( ( unsigned long ) e_diag_tq_null, ( unsigned ) 2 ) ;\
	SET_RSORT ( s_diag_tq ) ;\
    }


/* CONSTRUCTS FOR DIAG_TYPE */

#define o_diag_type_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_diag_type_apply_token, ( unsigned ) 4 ),\
	s_diag_type, p0, p1 )

#define o_diag_array( p0, p1, p2, p3, p4 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_array, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_diag_type ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	p4 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_bitfield( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_bitfield, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_diag_type ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_enum( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_enum, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_diag_type ) ;\
	p1 ; ASSERT_SORT ( s_tdfstring ) ;\
	o_enum_values_list ( p2 ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_floating_variety( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_floating_variety, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_floating_variety ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_loc( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_loc, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_diag_type ) ;\
	p1 ; ASSERT_SORT ( s_diag_tq ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_proc( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_proc, ( unsigned ) 4 ) ;\
	o_diag_type_list ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_bool ) ;\
	p2 ; ASSERT_SORT ( s_diag_type ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_ptr( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_ptr, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_diag_type ) ;\
	p1 ; ASSERT_SORT ( s_diag_tq ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_struct( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_struct, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	p1 ; ASSERT_SORT ( s_tdfstring ) ;\
	o_diag_field_list ( p2 ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_type_null\
    {\
	out_basic_int ( ( unsigned long ) e_diag_type_null, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_union( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_union, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	p1 ; ASSERT_SORT ( s_tdfstring ) ;\
	o_diag_field_list ( p2 ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_diag_variety( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_diag_variety, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_variety ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }

#define o_use_diag_tag( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_use_diag_tag, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_diag_tag ) ;\
	SET_RSORT ( s_diag_type ) ;\
    }


/* CONSTRUCTS FOR DIAG_TYPE_UNIT */

#define o_build_diagtype_unit( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_diag_tagdef_list ( p1 ) ;\
	SET_RSORT ( s_diag_type_unit ) ;\
    }


/* CONSTRUCTS FOR DIAG_UNIT */

#define o_build_diag_unit( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_diag_descriptor_list ( p1 ) ;\
	SET_RSORT ( s_diag_unit ) ;\
    }


/* CONSTRUCTS FOR ENUM_VALUES */

#define o_make_enum_values( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_tdfstring ) ;\
	SET_RSORT ( s_enum_values ) ;\
    }


/* CONSTRUCTS FOR ERROR_CODE */

#define o_nil_access\
    {\
	out_basic_int ( ( unsigned long ) e_nil_access, ( unsigned ) 2 ) ;\
	SET_RSORT ( s_error_code ) ;\
    }

#define o_overflow\
    {\
	out_basic_int ( ( unsigned long ) e_overflow, ( unsigned ) 2 ) ;\
	SET_RSORT ( s_error_code ) ;\
    }

#define o_stack_overflow\
    {\
	out_basic_int ( ( unsigned long ) e_stack_overflow, ( unsigned ) 2 ) ;\
	SET_RSORT ( s_error_code ) ;\
    }


/* CONSTRUCTS FOR ERROR_TREATMENT */

#define o_errt_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_errt_apply_token, ( unsigned ) 3 ),\
	s_error_treatment, p0, p1 )

#define o_errt_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_errt_cond, ( unsigned ) 3 ),\
	s_error_treatment, p0, p1, p2 )

#define o_continue\
    {\
	out_basic_int ( ( unsigned long ) e_continue, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_error_treatment ) ;\
    }

#define o_error_jump( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_error_jump, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_label ) ;\
	SET_RSORT ( s_error_treatment ) ;\
    }

#define o_trap( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_trap, ( unsigned ) 3 ) ;\
	o_error_code_list ( p0 ) ;\
	SET_RSORT ( s_error_treatment ) ;\
    }

#define o_wrap\
    {\
	out_basic_int ( ( unsigned long ) e_wrap, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_error_treatment ) ;\
    }

#define o_impossible\
    {\
	out_basic_int ( ( unsigned long ) e_impossible, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_error_treatment ) ;\
    }


/* CONSTRUCTS FOR EXP */

#define o_exp_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_exp_apply_token, ( unsigned ) 7 ),\
	s_exp, p0, p1 )

#define o_exp_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_exp_cond, ( unsigned ) 7 ),\
	s_exp, p0, p1, p2 )

#define o_abs( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_abs, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_add_to_ptr( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_add_to_ptr, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_and( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_and, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_apply_proc( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_apply_proc, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	o_exp_list ( p2 ) ;\
	o_exp_option ( p3 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_apply_general_proc( p0, p1, p2, p3, p4, p5 )\
    {\
	out_basic_int ( ( unsigned long ) e_apply_general_proc, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	o_procprops_option ( p1 ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	o_otagexp_list ( p3 ) ;\
	p4 ; ASSERT_SORT ( s_callees ) ;\
	p5 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_assign( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_assign, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_assign_with_mode( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_assign_with_mode, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_transfer_mode ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_bitfield_assign( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_bitfield_assign, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_bitfield_assign_with_mode( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_bitfield_assign_with_mode, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_transfer_mode ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_bitfield_contents( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_bitfield_contents, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_bitfield_variety ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_bitfield_contents_with_mode( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_bitfield_contents_with_mode, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_transfer_mode ) ;\
	p1 ; ASSERT_SORT ( s_bitfield_variety ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_case( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_case, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_bool ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	o_caselim_list ( p2 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_change_bitfield_to_int( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_change_bitfield_to_int, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_variety ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_change_floating_variety( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_change_floating_variety, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_floating_variety ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_change_variety( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_change_variety, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_variety ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_change_int_to_bitfield( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_change_int_to_bitfield, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_bitfield_variety ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_complex_conjugate( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_complex_conjugate, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_component( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_component, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_concat_nof( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_concat_nof, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_conditional( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_conditional, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_label ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_contents( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_contents, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_contents_with_mode( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_contents_with_mode, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_transfer_mode ) ;\
	p1 ; ASSERT_SORT ( s_shape ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_current_env\
    {\
	out_basic_int ( ( unsigned long ) e_current_env, ( unsigned ) 7 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_div0( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_div0, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_div1( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_div1, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_div2( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_div2, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_env_offset( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_env_offset, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	p1 ; ASSERT_SORT ( s_alignment ) ;\
	p2 ; ASSERT_SORT ( s_tag ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_env_size( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_env_size, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_tag ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_fail_installer( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_fail_installer, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_string ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_float_int( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_float_int, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_floating_variety ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_abs( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_abs, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_div( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_div, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_minus( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_minus, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_maximum( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_maximum, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_minimum( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_minimum, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_mult( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_mult, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	o_exp_list ( p1 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_negate( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_negate, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_plus( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_plus, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	o_exp_list ( p1 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_power( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_power, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_floating_test( p0, p1, p2, p3, p4, p5 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating_test, ( unsigned ) 7 ) ;\
	o_nat_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_ntest ) ;\
	p3 ; ASSERT_SORT ( s_label ) ;\
	p4 ; ASSERT_SORT ( s_exp ) ;\
	p5 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_goto( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_goto, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_label ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_goto_local_lv( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_goto_local_lv, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_identify( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_identify, ( unsigned ) 7 ) ;\
	o_access_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_tag ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_ignorable( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_ignorable, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_imaginary_part( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_imaginary_part, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_initial_value( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_initial_value, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_integer_test( p0, p1, p2, p3, p4 )\
    {\
	out_basic_int ( ( unsigned long ) e_integer_test, ( unsigned ) 7 ) ;\
	o_nat_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_ntest ) ;\
	p2 ; ASSERT_SORT ( s_label ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	p4 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_labelled( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_labelled, ( unsigned ) 7 ) ;\
	o_label_list ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	o_exp_list ( p2 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_last_local( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_last_local, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_local_alloc( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_local_alloc, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_local_alloc_check( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_local_alloc_check, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_local_free( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_local_free, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_local_free_all\
    {\
	out_basic_int ( ( unsigned long ) e_local_free_all, ( unsigned ) 7 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_long_jump( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_long_jump, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_complex( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_complex, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_floating_variety ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_compound( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_compound, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	o_exp_list ( p1 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_floating( p0, p1, p2, p3, p4, p5 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_floating, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_floating_variety ) ;\
	p1 ; ASSERT_SORT ( s_rounding_mode ) ;\
	p2 ; ASSERT_SORT ( s_bool ) ;\
	p3 ; ASSERT_SORT ( s_string ) ;\
	p4 ; ASSERT_SORT ( s_nat ) ;\
	p5 ; ASSERT_SORT ( s_signed_nat ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_general_proc( p0, p1, p2, p3, p4 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_general_proc, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	o_procprops_option ( p1 ) ;\
	o_tagshacc_list ( p2 ) ;\
	o_tagshacc_list ( p3 ) ;\
	p4 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_int( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_int, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_variety ) ;\
	p1 ; ASSERT_SORT ( s_signed_nat ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_local_lv( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_local_lv, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_label ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_nof( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_nof, ( unsigned ) 7 ) ;\
	o_exp_list ( p0 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_nof_int( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_nof_int, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_variety ) ;\
	p1 ; ASSERT_SORT ( s_string ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_null_local_lv\
    {\
	out_basic_int ( ( unsigned long ) e_make_null_local_lv, ( unsigned ) 7 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_null_proc\
    {\
	out_basic_int ( ( unsigned long ) e_make_null_proc, ( unsigned ) 7 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_null_ptr( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_null_ptr, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_proc( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_proc, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	o_tagshacc_list ( p1 ) ;\
	o_tagacc_option ( p2 ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_stack_limit( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_stack_limit, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_top\
    {\
	out_basic_int ( ( unsigned long ) e_make_top, ( unsigned ) 7 ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_make_value( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_value, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_maximum( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_maximum, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_minimum( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_minimum, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_minus( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_minus, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_move_some( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_move_some, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_transfer_mode ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_mult( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_mult, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_n_copies( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_n_copies, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_nat ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_negate( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_negate, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_not( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_not, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_obtain_tag( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_obtain_tag, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_tag ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_add( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_add, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_div( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_div, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_variety ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_div_by_int( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_div_by_int, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_max( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_max, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_mult( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_mult, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_negate( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_negate, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_pad( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_pad, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_subtract( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_subtract, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_test( p0, p1, p2, p3, p4 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_test, ( unsigned ) 7 ) ;\
	o_nat_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_ntest ) ;\
	p2 ; ASSERT_SORT ( s_label ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	p4 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_offset_zero( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset_zero, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_or( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_or, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_plus( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_plus, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_pointer_test( p0, p1, p2, p3, p4 )\
    {\
	out_basic_int ( ( unsigned long ) e_pointer_test, ( unsigned ) 7 ) ;\
	o_nat_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_ntest ) ;\
	p2 ; ASSERT_SORT ( s_label ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	p4 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_power( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_power, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_proc_test( p0, p1, p2, p3, p4 )\
    {\
	out_basic_int ( ( unsigned long ) e_proc_test, ( unsigned ) 7 ) ;\
	o_nat_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_ntest ) ;\
	p2 ; ASSERT_SORT ( s_label ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	p4 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_profile( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_profile, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_real_part( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_real_part, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_rem0( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_rem0, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_rem1( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_rem1, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_rem2( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_rem2, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_error_treatment ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_repeat( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_repeat, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_label ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_return( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_return, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_return_to_label( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_return_to_label, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_round_with_mode( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_round_with_mode, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_rounding_mode ) ;\
	p2 ; ASSERT_SORT ( s_variety ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_rotate_left( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_rotate_left, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_rotate_right( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_rotate_right, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_sequence( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_sequence, ( unsigned ) 7 ) ;\
	o_exp_list ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_set_stack_limit( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_set_stack_limit, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_shape_offset( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_shape_offset, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_shift_left( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_shift_left, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_error_treatment ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_shift_right( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_shift_right, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_subtract_ptrs( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_subtract_ptrs, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_tail_call( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_tail_call, ( unsigned ) 7 ) ;\
	o_procprops_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	p2 ; ASSERT_SORT ( s_callees ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_untidy_return( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_untidy_return, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_variable( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_variable, ( unsigned ) 7 ) ;\
	o_access_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_tag ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }

#define o_xor( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_xor, ( unsigned ) 7 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_exp ) ;\
    }


/* CONSTRUCTS FOR EXTERN_LINK */

#define o_make_extern_link( p0 )\
    {\
	o_linkextern_list ( p0 ) ;\
	SET_RSORT ( s_extern_link ) ;\
    }


/* CONSTRUCTS FOR EXTERNAL */

#define o_string_extern( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_string_extern, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfident ) ;\
	SET_RSORT ( s_external ) ;\
    }

#define o_unique_extern( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_unique_extern, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_unique ) ;\
	SET_RSORT ( s_external ) ;\
    }

#define o_chain_extern( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_chain_extern, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfident ) ;\
	p1 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_external ) ;\
    }


/* CONSTRUCTS FOR FILENAME */

#define o_filename_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_filename_apply_token, ( unsigned ) 2 ),\
	s_filename, p0, p1 )

#define o_make_filename( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_filename, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_nat ) ;\
	p1 ; ASSERT_SORT ( s_tdfstring ) ;\
	p2 ; ASSERT_SORT ( s_tdfstring ) ;\
	SET_RSORT ( s_filename ) ;\
    }


/* CONSTRUCTS FOR FLOATING_VARIETY */

#define o_flvar_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_flvar_apply_token, ( unsigned ) 3 ),\
	s_floating_variety, p0, p1 )

#define o_flvar_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_flvar_cond, ( unsigned ) 3 ),\
	s_floating_variety, p0, p1, p2 )

#define o_flvar_parms( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_flvar_parms, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_nat ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	p2 ; ASSERT_SORT ( s_nat ) ;\
	p3 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_floating_variety ) ;\
    }

#define o_complex_parms( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_complex_parms, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_nat ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	p2 ; ASSERT_SORT ( s_nat ) ;\
	p3 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_floating_variety ) ;\
    }

#define o_float_of_complex( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_float_of_complex, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_floating_variety ) ;\
    }

#define o_complex_of_float( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_complex_of_float, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_floating_variety ) ;\
    }


/* CONSTRUCTS FOR GROUP */

#define o_make_group( p0 )\
    {\
	o_unit_list ( p0 ) ;\
	SET_RSORT ( s_group ) ;\
    }


/* CONSTRUCTS FOR LABEL */

#define o_label_apply_token( p0, p1 )\
    TOK_APP (\
	out_extendable_int ( ( unsigned long ) e_label_apply_token, ( unsigned ) 1 ),\
	s_label, p0, p1 )

#define o_make_label( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_label, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_label ) ;\
    }


/* CONSTRUCTS FOR LINK */

#define o_make_link( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	p1 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_link ) ;\
    }


/* CONSTRUCTS FOR LINKEXTERN */

#define o_make_linkextern( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	p1 ; ASSERT_SORT ( s_external ) ;\
	SET_RSORT ( s_linkextern ) ;\
    }


/* CONSTRUCTS FOR LINKINFO */

#define o_static_name_def( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_static_name_def, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_tdfstring ) ;\
	SET_RSORT ( s_linkinfo ) ;\
    }

#define o_make_comment( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_comment, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	SET_RSORT ( s_linkinfo ) ;\
    }

#define o_make_weak_defn( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_weak_defn, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_linkinfo ) ;\
    }

#define o_make_weak_symbol( p0, p1 )\
    {\
	out_extendable_int ( ( unsigned long ) e_make_weak_symbol, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_linkinfo ) ;\
    }


/* CONSTRUCTS FOR LINKINFO_PROPS */

#define o_make_linkinfos( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_linkinfo_list ( p1 ) ;\
	SET_RSORT ( s_linkinfo_props ) ;\
    }


/* CONSTRUCTS FOR LINKS */

#define o_make_links( p0 )\
    {\
	o_link_list ( p0 ) ;\
	SET_RSORT ( s_links ) ;\
    }


/* CONSTRUCTS FOR NAT */

#define o_nat_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_nat_apply_token, ( unsigned ) 3 ),\
	s_nat, p0, p1 )

#define o_nat_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_nat_cond, ( unsigned ) 3 ),\
	s_nat, p0, p1, p2 )

#define o_computed_nat( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_computed_nat, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_nat ) ;\
    }

#define o_error_val( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_error_val, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_error_code ) ;\
	SET_RSORT ( s_nat ) ;\
    }

#define o_make_nat( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_nat, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_nat ) ;\
    }


/* CONSTRUCTS FOR NTEST */

#define o_ntest_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_ntest_apply_token, ( unsigned ) 4 ),\
	s_ntest, p0, p1 )

#define o_ntest_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_ntest_cond, ( unsigned ) 4 ),\
	s_ntest, p0, p1, p2 )

#define o_equal\
    {\
	out_basic_int ( ( unsigned long ) e_equal, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_greater_than\
    {\
	out_basic_int ( ( unsigned long ) e_greater_than, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_greater_than_or_equal\
    {\
	out_basic_int ( ( unsigned long ) e_greater_than_or_equal, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_less_than\
    {\
	out_basic_int ( ( unsigned long ) e_less_than, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_less_than_or_equal\
    {\
	out_basic_int ( ( unsigned long ) e_less_than_or_equal, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_equal\
    {\
	out_basic_int ( ( unsigned long ) e_not_equal, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_greater_than\
    {\
	out_basic_int ( ( unsigned long ) e_not_greater_than, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_greater_than_or_equal\
    {\
	out_basic_int ( ( unsigned long ) e_not_greater_than_or_equal, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_less_than\
    {\
	out_basic_int ( ( unsigned long ) e_not_less_than, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_less_than_or_equal\
    {\
	out_basic_int ( ( unsigned long ) e_not_less_than_or_equal, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_less_than_or_greater_than\
    {\
	out_basic_int ( ( unsigned long ) e_less_than_or_greater_than, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_less_than_and_not_greater_than\
    {\
	out_basic_int ( ( unsigned long ) e_not_less_than_and_not_greater_than, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_comparable\
    {\
	out_basic_int ( ( unsigned long ) e_comparable, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }

#define o_not_comparable\
    {\
	out_extendable_int ( ( unsigned long ) e_not_comparable, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_ntest ) ;\
    }


/* CONSTRUCTS FOR OTAGEXP */

#define o_make_otagexp( p0, p1 )\
    {\
	o_tag_option ( p0 ) ;\
	p1 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_otagexp ) ;\
    }


/* CONSTRUCTS FOR PROCPROPS */

#define o_procprops_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_procprops_apply_token, ( unsigned ) 4 ),\
	s_procprops, p0, p1 )

#define o_procprops_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_procprops_cond, ( unsigned ) 4 ),\
	s_procprops, p0, p1, p2 )

#define o_add_procprops( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_add_procprops, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_procprops ) ;\
	p1 ; ASSERT_SORT ( s_procprops ) ;\
	SET_RSORT ( s_procprops ) ;\
    }

#define o_check_stack\
    {\
	out_basic_int ( ( unsigned long ) e_check_stack, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_procprops ) ;\
    }

#define o_inline\
    {\
	out_basic_int ( ( unsigned long ) e_inline, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_procprops ) ;\
    }

#define o_no_long_jump_dest\
    {\
	out_basic_int ( ( unsigned long ) e_no_long_jump_dest, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_procprops ) ;\
    }

#define o_untidy\
    {\
	out_basic_int ( ( unsigned long ) e_untidy, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_procprops ) ;\
    }

#define o_var_callees\
    {\
	out_basic_int ( ( unsigned long ) e_var_callees, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_procprops ) ;\
    }

#define o_var_callers\
    {\
	out_basic_int ( ( unsigned long ) e_var_callers, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_procprops ) ;\
    }


/* CONSTRUCTS FOR ROUNDING_MODE */

#define o_rounding_mode_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_rounding_mode_apply_token, ( unsigned ) 3 ),\
	s_rounding_mode, p0, p1 )

#define o_rounding_mode_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_rounding_mode_cond, ( unsigned ) 3 ),\
	s_rounding_mode, p0, p1, p2 )

#define o_round_as_state\
    {\
	out_basic_int ( ( unsigned long ) e_round_as_state, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_rounding_mode ) ;\
    }

#define o_to_nearest\
    {\
	out_basic_int ( ( unsigned long ) e_to_nearest, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_rounding_mode ) ;\
    }

#define o_toward_larger\
    {\
	out_basic_int ( ( unsigned long ) e_toward_larger, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_rounding_mode ) ;\
    }

#define o_toward_smaller\
    {\
	out_basic_int ( ( unsigned long ) e_toward_smaller, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_rounding_mode ) ;\
    }

#define o_toward_zero\
    {\
	out_basic_int ( ( unsigned long ) e_toward_zero, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_rounding_mode ) ;\
    }


/* CONSTRUCTS FOR SHAPE */

#define o_shape_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_shape_apply_token, ( unsigned ) 4 ),\
	s_shape, p0, p1 )

#define o_shape_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_shape_cond, ( unsigned ) 4 ),\
	s_shape, p0, p1, p2 )

#define o_bitfield( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_bitfield, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_bitfield_variety ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_bottom\
    {\
	out_basic_int ( ( unsigned long ) e_bottom, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_compound( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_compound, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_floating( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_floating, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_floating_variety ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_integer( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_integer, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_variety ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_nof( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_nof, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_nat ) ;\
	p1 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_offset( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_offset, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	p1 ; ASSERT_SORT ( s_alignment ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_pointer( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_pointer, ( unsigned ) 4 ) ;\
	p0 ; ASSERT_SORT ( s_alignment ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_proc\
    {\
	out_basic_int ( ( unsigned long ) e_proc, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_shape ) ;\
    }

#define o_top\
    {\
	out_basic_int ( ( unsigned long ) e_top, ( unsigned ) 4 ) ;\
	SET_RSORT ( s_shape ) ;\
    }


/* CONSTRUCTS FOR SIGNED_NAT */

#define o_signed_nat_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_signed_nat_apply_token, ( unsigned ) 3 ),\
	s_signed_nat, p0, p1 )

#define o_signed_nat_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_signed_nat_cond, ( unsigned ) 3 ),\
	s_signed_nat, p0, p1, p2 )

#define o_computed_signed_nat( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_computed_signed_nat, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_signed_nat ) ;\
    }

#define o_make_signed_nat( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_signed_nat, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_tdfbool ) ;\
	p1 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_signed_nat ) ;\
    }

#define o_snat_from_nat( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_snat_from_nat, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_bool ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_signed_nat ) ;\
    }


/* CONSTRUCTS FOR SORTNAME */

#define o_access\
    {\
	out_basic_int ( ( unsigned long ) e_access, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_al_tag\
    {\
	out_basic_int ( ( unsigned long ) e_al_tag, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_alignment_sort\
    {\
	out_basic_int ( ( unsigned long ) e_alignment_sort, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_bitfield_variety\
    {\
	out_basic_int ( ( unsigned long ) e_bitfield_variety, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_bool\
    {\
	out_basic_int ( ( unsigned long ) e_bool, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_error_treatment\
    {\
	out_basic_int ( ( unsigned long ) e_error_treatment, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_exp\
    {\
	out_basic_int ( ( unsigned long ) e_exp, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_floating_variety\
    {\
	out_basic_int ( ( unsigned long ) e_floating_variety, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_foreign_sort( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_foreign_sort, ( unsigned ) 5 ) ;\
	p0 ; ASSERT_SORT ( s_string ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_label\
    {\
	out_basic_int ( ( unsigned long ) e_label, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_nat\
    {\
	out_basic_int ( ( unsigned long ) e_nat, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_ntest\
    {\
	out_basic_int ( ( unsigned long ) e_ntest, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_procprops\
    {\
	out_basic_int ( ( unsigned long ) e_procprops, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_rounding_mode\
    {\
	out_basic_int ( ( unsigned long ) e_rounding_mode, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_shape\
    {\
	out_basic_int ( ( unsigned long ) e_shape, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_signed_nat\
    {\
	out_basic_int ( ( unsigned long ) e_signed_nat, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_string\
    {\
	out_basic_int ( ( unsigned long ) e_string, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_tag\
    {\
	out_basic_int ( ( unsigned long ) e_tag, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_transfer_mode\
    {\
	out_basic_int ( ( unsigned long ) e_transfer_mode, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_token( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_token, ( unsigned ) 5 ) ;\
	p0 ; ASSERT_SORT ( s_sortname ) ;\
	o_sortname_list ( p1 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }

#define o_variety\
    {\
	out_basic_int ( ( unsigned long ) e_variety, ( unsigned ) 5 ) ;\
	SET_RSORT ( s_sortname ) ;\
    }


/* CONSTRUCTS FOR SOURCEMARK */

#define o_make_sourcemark( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_sourcemark, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_filename ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	p2 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_sourcemark ) ;\
    }


/* CONSTRUCTS FOR STRING */

#define o_string_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_string_apply_token, ( unsigned ) 3 ),\
	s_string, p0, p1 )

#define o_string_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_string_cond, ( unsigned ) 3 ),\
	s_string, p0, p1, p2 )

#define o_concat_string( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_concat_string, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_string ) ;\
	p1 ; ASSERT_SORT ( s_string ) ;\
	SET_RSORT ( s_string ) ;\
    }

#define o_make_string( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_string, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_tdfstring ) ;\
	SET_RSORT ( s_string ) ;\
    }


/* CONSTRUCTS FOR TAG */

#define o_tag_apply_token( p0, p1 )\
    TOK_APP (\
	out_extendable_int ( ( unsigned long ) e_tag_apply_token, ( unsigned ) 1 ),\
	s_tag, p0, p1 )

#define o_make_tag( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_tag, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_tag ) ;\
    }


/* CONSTRUCTS FOR TAGACC */

#define o_make_tagacc( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tag ) ;\
	o_access_option ( p1 ) ;\
	SET_RSORT ( s_tagacc ) ;\
    }


/* CONSTRUCTS FOR TAGDEC */

#define o_make_id_tagdec( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_id_tagdec, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_access_option ( p1 ) ;\
	o_string_option ( p2 ) ;\
	p3 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_tagdec ) ;\
    }

#define o_make_var_tagdec( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_var_tagdec, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_access_option ( p1 ) ;\
	o_string_option ( p2 ) ;\
	p3 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_tagdec ) ;\
    }

#define o_common_tagdec( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_common_tagdec, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_access_option ( p1 ) ;\
	o_string_option ( p2 ) ;\
	p3 ; ASSERT_SORT ( s_shape ) ;\
	SET_RSORT ( s_tagdec ) ;\
    }


/* CONSTRUCTS FOR TAGDEC_PROPS */

#define o_make_tagdecs( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_tagdec_list ( p1 ) ;\
	SET_RSORT ( s_tagdec_props ) ;\
    }


/* CONSTRUCTS FOR TAGDEF */

#define o_make_id_tagdef( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_id_tagdef, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_string_option ( p1 ) ;\
	p2 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_tagdef ) ;\
    }

#define o_make_var_tagdef( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_var_tagdef, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_access_option ( p1 ) ;\
	o_string_option ( p2 ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_tagdef ) ;\
    }

#define o_common_tagdef( p0, p1, p2, p3 )\
    {\
	out_basic_int ( ( unsigned long ) e_common_tagdef, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_access_option ( p1 ) ;\
	o_string_option ( p2 ) ;\
	p3 ; ASSERT_SORT ( s_exp ) ;\
	SET_RSORT ( s_tagdef ) ;\
    }


/* CONSTRUCTS FOR TAGDEF_PROPS */

#define o_make_tagdefs( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_tagdef_list ( p1 ) ;\
	SET_RSORT ( s_tagdef_props ) ;\
    }


/* CONSTRUCTS FOR TAGSHACC */

#define o_make_tagshacc( p0, p1, p2 )\
    {\
	p0 ; ASSERT_SORT ( s_shape ) ;\
	o_access_option ( p1 ) ;\
	p2 ; ASSERT_SORT ( s_tag ) ;\
	SET_RSORT ( s_tagshacc ) ;\
    }


/* CONSTRUCTS FOR TOKDEC */

#define o_make_tokdec( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_tokdec, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_string_option ( p1 ) ;\
	p2 ; ASSERT_SORT ( s_sortname ) ;\
	SET_RSORT ( s_tokdec ) ;\
    }


/* CONSTRUCTS FOR TOKDEC_PROPS */

#define o_make_tokdecs( p0 )\
    {\
	o_tokdec_list ( p0 ) ;\
	SET_RSORT ( s_tokdec_props ) ;\
    }


/* CONSTRUCTS FOR TOKDEF */

#define o_make_tokdef( p0, p1, p2 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_tokdef, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_string_option ( p1 ) ;\
	p2 ; ASSERT_SORT ( s_bitstream ) ;\
	SET_RSORT ( s_tokdef ) ;\
    }


/* CONSTRUCTS FOR TOKDEF_PROPS */

#define o_make_tokdefs( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	o_tokdef_list ( p1 ) ;\
	SET_RSORT ( s_tokdef_props ) ;\
    }


/* CONSTRUCTS FOR TOKEN */

#define o_token_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_token_apply_token, ( unsigned ) 2 ),\
	s_token, p0, p1 )

#define o_make_tok( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_tok, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_token ) ;\
    }

#define o_use_tokdef( p0 )\
    {\
	out_basic_int ( ( unsigned long ) e_use_tokdef, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_bitstream ) ;\
	SET_RSORT ( s_token ) ;\
    }


/* CONSTRUCTS FOR TOKEN_DEFN */

#define o_token_definition( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_token_definition, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_sortname ) ;\
	o_tokformals_list ( p1 ) ;\
	SET_RSORT ( s_token_defn ) ;\
    }


/* CONSTRUCTS FOR TOKFORMALS */

#define o_make_tokformals( p0, p1 )\
    {\
	p0 ; ASSERT_SORT ( s_sortname ) ;\
	p1 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_tokformals ) ;\
    }


/* CONSTRUCTS FOR TRANSFER_MODE */

#define o_transfer_mode_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_transfer_mode_apply_token, ( unsigned ) 3 ),\
	s_transfer_mode, p0, p1 )

#define o_transfer_mode_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_transfer_mode_cond, ( unsigned ) 3 ),\
	s_transfer_mode, p0, p1, p2 )

#define o_add_modes( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_add_modes, ( unsigned ) 3 ) ;\
	p0 ; ASSERT_SORT ( s_transfer_mode ) ;\
	p1 ; ASSERT_SORT ( s_transfer_mode ) ;\
	SET_RSORT ( s_transfer_mode ) ;\
    }

#define o_overlap\
    {\
	out_basic_int ( ( unsigned long ) e_overlap, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_transfer_mode ) ;\
    }

#define o_standard_transfer_mode\
    {\
	out_basic_int ( ( unsigned long ) e_standard_transfer_mode, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_transfer_mode ) ;\
    }

#define o_trap_on_nil\
    {\
	out_basic_int ( ( unsigned long ) e_trap_on_nil, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_transfer_mode ) ;\
    }

#define o_volatile\
    {\
	out_basic_int ( ( unsigned long ) e_volatile, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_transfer_mode ) ;\
    }

#define o_complete\
    {\
	out_extendable_int ( ( unsigned long ) e_complete, ( unsigned ) 3 ) ;\
	SET_RSORT ( s_transfer_mode ) ;\
    }


/* CONSTRUCTS FOR UNIQUE */

#define o_make_unique( p0 )\
    {\
	o_tdfident_list ( p0 ) ;\
	SET_RSORT ( s_unique ) ;\
    }


/* CONSTRUCTS FOR UNIT */

#define o_make_unit( p0, p1, p2 )\
    {\
	o_tdfint_list ( p0 ) ;\
	o_links_list ( p1 ) ;\
	p2 ; ASSERT_SORT ( s_bytestream ) ;\
	SET_RSORT ( s_unit ) ;\
    }


/* CONSTRUCTS FOR VARIETY */

#define o_var_apply_token( p0, p1 )\
    TOK_APP (\
	out_basic_int ( ( unsigned long ) e_var_apply_token, ( unsigned ) 2 ),\
	s_variety, p0, p1 )

#define o_var_cond( p0, p1, p2 )\
    TDF_COND (\
	out_basic_int ( ( unsigned long ) e_var_cond, ( unsigned ) 2 ),\
	s_variety, p0, p1, p2 )

#define o_var_limits( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_var_limits, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_signed_nat ) ;\
	p1 ; ASSERT_SORT ( s_signed_nat ) ;\
	SET_RSORT ( s_variety ) ;\
    }

#define o_var_width( p0, p1 )\
    {\
	out_extendable_int ( ( unsigned long ) e_var_width, ( unsigned ) 2 ) ;\
	p0 ; ASSERT_SORT ( s_bool ) ;\
	p1 ; ASSERT_SORT ( s_nat ) ;\
	SET_RSORT ( s_variety ) ;\
    }


/* CONSTRUCTS FOR VERSION */

#define o_make_version( p0, p1 )\
    {\
	out_basic_int ( ( unsigned long ) e_make_version, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_tdfint ) ;\
	p1 ; ASSERT_SORT ( s_tdfint ) ;\
	SET_RSORT ( s_version ) ;\
    }

#define o_user_info( p0 )\
    {\
	out_extendable_int ( ( unsigned long ) e_user_info, ( unsigned ) 1 ) ;\
	p0 ; ASSERT_SORT ( s_string ) ;\
	SET_RSORT ( s_version ) ;\
    }


/* CONSTRUCTS FOR VERSION_PROPS */

#define o_make_versions( p0 )\
    {\
	o_version_list ( p0 ) ;\
	SET_RSORT ( s_version_props ) ;\
    }


/* CONSTRUCTS FOR COMPOUND SORTS */

#define o_access_option( p )		TDF_OPTION ( p, s_access )
#define o_al_tagdef_list( p )		TDF_SLIST ( p, s_al_tagdef )
#define o_capsule_link_list( p )	TDF_SLIST ( p, s_capsule_link )
#define o_caselim_list( p )		TDF_LIST ( p, s_caselim )
#define o_diag_descriptor_list( p )	TDF_SLIST ( p, s_diag_descriptor )
#define o_diag_field_list( p )		TDF_LIST ( p, s_diag_field )
#define o_diag_tagdef_list( p )		TDF_SLIST ( p, s_diag_tagdef )
#define o_diag_type_list( p )		TDF_LIST ( p, s_diag_type )
#define o_enum_values_list( p )		TDF_LIST ( p, s_enum_values )
#define o_error_code_list( p )		TDF_LIST ( p, s_error_code )
#define o_exp_list( p )			TDF_LIST ( p, s_exp )
#define o_exp_option( p )		TDF_OPTION ( p, s_exp )
#define o_extern_link_list( p )		TDF_SLIST ( p, s_extern_link )
#define o_group_list( p )		TDF_SLIST ( p, s_group )
#define o_label_list( p )		TDF_LIST ( p, s_label )
#define o_link_list( p )		TDF_SLIST ( p, s_link )
#define o_linkextern_list( p )		TDF_SLIST ( p, s_linkextern )
#define o_linkinfo_list( p )		TDF_SLIST ( p, s_linkinfo )
#define o_links_list( p )		TDF_SLIST ( p, s_links )
#define o_nat_option( p )		TDF_OPTION ( p, s_nat )
#define o_otagexp_list( p )		TDF_LIST ( p, s_otagexp )
#define o_procprops_option( p )		TDF_OPTION ( p, s_procprops )
#define o_sortname_list( p )		TDF_LIST ( p, s_sortname )
#define o_string_option( p )		TDF_OPTION ( p, s_string )
#define o_tag_option( p )		TDF_OPTION ( p, s_tag )
#define o_tagacc_option( p )		TDF_OPTION ( p, s_tagacc )
#define o_tagdec_list( p )		TDF_SLIST ( p, s_tagdec )
#define o_tagdef_list( p )		TDF_SLIST ( p, s_tagdef )
#define o_tagshacc_list( p )		TDF_LIST ( p, s_tagshacc )
#define o_tdfident_list( p )		TDF_SLIST ( p, s_tdfident )
#define o_tdfint_list( p )		TDF_SLIST ( p, s_tdfint )
#define o_tokdec_list( p )		TDF_SLIST ( p, s_tokdec )
#define o_tokdef_list( p )		TDF_SLIST ( p, s_tokdef )
#define o_tokformals_list( p )		TDF_LIST ( p, s_tokformals )
#define o_unit_list( p )		TDF_SLIST ( p, s_unit )
#define o_version_list( p )		TDF_SLIST ( p, s_version )


#endif