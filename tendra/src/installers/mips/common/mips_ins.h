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
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:23  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* mips_instructionsdecs.h
    each mips instruction is a unique string starting i_ using MIPS names 
      with . replaced by _
     declarations in mips_instructions.c
*/


extern char *i_la /* "la" */ ;
extern char *i_lb /* "lb" */ ;
extern char *i_lbu /* "lbu" */ ;
extern char *i_lh /* "lh" */ ;
extern char *i_lhu /* "lhu" */ ;
extern char *i_lw /* "lw" */ ;
extern char *i_lwc1 /* "lwc1" */ ;
extern char *i_lwl /* "lwl" */ ;
extern char *i_sb /* "sb" */ ;
extern char *i_sh /* "sh" */ ;
extern char *i_sw /* "sw" */ ;
extern char *i_swc1 /* "swc1" */ ;
extern char *i_swl /* "swl" */ ;
extern char *i_swr /* "swr" */ ;
extern char *i_ulh /* "ulh" */ ;
extern char *i_ulhu /* "ulhu" */ ;
extern char *i_ulw /* "ulw" */ ;
extern char *i_ush /* "ush" */ ;
extern char *i_usw /* "usw" */ ;
extern char *i_rfe /* "rfe" */ ;
extern char *i_syscall /* "syscall" */ ;
extern char *i_break /* "break" */ ;
extern char *i_nop /* "nop" */ ;
extern char *i_li /* "li" */ ;
extern char *i_lui /* "lui" */ ;
extern char *i_abs /* "abs" */ ;
extern char *i_neg /* "neg" */ ;
extern char *i_negu /* "negu" */ ;
extern char *i_not /* "not" */ ;
extern char *i_add /* "add" */ ;
extern char *i_addu /* "addu" */ ;
extern char *i_and /* "and" */ ;
extern char *i_div /* "div" */ ;
extern char *i_divu /* "divu" */ ;
extern char *i_xor /* "xor" */ ;
extern char *i_mul /* "mul" */ ;
extern char *i_mulo /* "mulo" */ ;
extern char *i_mulou /* "mulou" */ ;
extern char *i_nor /* "nor" */ ;
extern char *i_or /* "or" */ ;
extern char *i_rem /* "rem" */ ;
extern char *i_remu /* "remu" */ ;
extern char *i_rol /* "rol" */ ;
extern char *i_ror /* "ror" */ ;
extern char *i_seq /* "seq" */ ;
extern char *i_slt /* "slt" */ ;
extern char *i_sltu /* "sltu" */ ;
extern char *i_sle /* "sle" */ ;
extern char *i_sleu /* "sleu" */ ;
extern char *i_sgt /* "sgt" */ ;
extern char *i_sgtu /* "sgtu" */ ;
extern char *i_sge /* "sge" */ ;
extern char *i_sgeu /* "sgeu" */ ;
extern char *i_sne /* "sne" */ ;
extern char *i_sll /* "sll" */ ;
extern char *i_sra /* "sra" */ ;
extern char *i_srl /* "srl" */ ;
extern char *i_sub /* "sub" */ ;
extern char *i_subu /* "subu" */ ;
extern char *i_mult /* "mult" */ ;
extern char *i_multu /* "multu" */ ;
extern char *i_b /* "b" */ ;
extern char *i_bc1t /* "bc1t" */ ;
extern char *i_bc1f /* "bc1f" */ ;
extern char *i_beq /* "beq" */ ;
extern char *i_bgt /* "bgt" */ ;
extern char *i_bge /* "bge" */ ;
extern char *i_bgeu /* "bgeu" */ ;
extern char *i_bgtu /* "bgtu" */ ;
extern char *i_blt /* "blt" */ ;
extern char *i_bltu;
extern char *i_ble /* "ble" */ ;
extern char *i_bleu /* "bleu" */ ;
extern char *i_bne /* "bne" */ ;
extern char *i_bal /* "bal" */ ;
extern char *i_beqz /* "beqz" */ ;
extern char *i_bgez /* "bgez" */ ;
extern char *i_bgezal /* "bgezal" */ ;
extern char *i_bgtz /* "bgtz" */ ;
extern char *i_blez /* "blez" */ ;
extern char *i_bltz /* "bltz" */ ;
extern char *i_bltzal /* "bltzal" */ ;
extern char *i_bnez /* "bnez" */ ;
extern char *i_j /* "j" */ ;
extern char *i_jal /* "jal" */ ;
extern char *i_move /* "move" */ ;
extern char *i_mfhi /* "mfhi" */ ;
extern char *i_mthi /* "mthi" */ ;
extern char *i_mflo /* "mflo" */ ;
extern char *i_mfc1 /* "mfc1" */ ;
extern char *i_mtc1 /* "mtc1" */ ;
extern char *i_cfc1 /* "cfc1" */ ;
extern char *i_ctc1 /* "ctc1" */ ;
extern char *i_l_d /* "l.d" */ ;
extern char *i_l_s /* "l.s" */ ;
extern char *i_s_d /* "s.d" */ ;
extern char *i_s_s;
extern char *i_mov_s /* "mov.s" */ ;
extern char *i_mov_d /* "mov.d" */ ;
extern char *i_abs_d /* "abs.d" */ ;
extern char *i_abs_s /* "abs.s" */ ;
extern char *i_add_d /* "add.d" */ ;
extern char *i_add_s /* "add.s" */ ;
extern char *i_div_s /* "div_s" */ ;
extern char *i_div_d /* "div.d" */ ;
extern char *i_mul_d /* "mul.d" */ ;
extern char *i_mul_s /* "mul.s" */ ;
extern char *i_sub_d /* "sub.d" */ ;
extern char *i_sub_s /* "sub.s" */ ;
extern char *i_cvt_s_d /* "cvt.s.d" */ ;
extern char *i_cvt_d_s;
extern char *i_cvt_s_w /* "cvt.s.w" */ ;
extern char *i_cvt_d_w /* "cvt.d.w" */ ;
extern char *i_cvt_w_d /* "cvt.w.d" */ ;
extern char *i_cvt_w_s /* "cvt.w.s" */ ;
extern char *i_neg_d /* "neg.d" */ ;
extern char *i_neg_s /* "neg.s" */ ;
extern char *i_c_eq_s /* "c.eq.s" */ ;
extern char *i_c_eq_d /* "c.eq.d" */ ;
extern char *i_c_lt_s /* "c.lt.s" */ ;
extern char *i_c_lt_d /* "c.lt.d" */ ;
extern char *i_c_le_s /* "c.le.s" */ ;
extern char *i_c_le_d /* "c.le.d" */ ;

extern char *i_trunc_w_s;
extern char *i_trunc_w_d;
extern char *i_round_w_s;
extern char *i_round_w_d;
