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


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "diag_fns.h"
#include "flags.h"
#include "check.h"
#include "me_fns.h"
#include "externs.h"
#include "installglob.h"
#include "messages_r.h"
#include "main_reads.h"
#include "install_fns.h"
#include "c_arith_type.h"
#include "natmacs.h"

#include "spec_tok.h"
#include "shapemacs.h"
#include "szs_als.h"
#include "new_tags.h"
/* intercepts specially defined tokens */

#define MAX_INT 2147483647
#define MIN_INT (-MAX_INT-1)
#define UMAX_INT 4294967295U
extern shape f_off64_64;
extern shape f_off32_32;

/*
   This function returns a component at offset 'align' from the
   compound given in e.
*/
exp
get_component(exp e, alignment shc, alignment align, int size, int nm, shape offshape, int offset)
{

  exp offsetexp /* offset in compound for required component */
    = getexp(offshape,nilexp,0,nilexp,nilexp,0,offset,val_tag);
  
  shape resshape	/* shape of component */
    = getshape(1,shc,shc,align,size,nm);
    
  return hold_check(f_component(resshape,hold_check(me_u3(sh(son(son(e))),e,cont_tag)),offsetexp));
}


tokval
special_token(token t, bitstream pars, int sortcode, int *done)
{
  tokval tkv;
  UNUSED(sortcode);
  if (t -> tok_name == (char*)0) {
    SET(tkv); /* call looks at done to see if result is meaningful */
    return tkv;
  }

  if (!strcmp(t -> tok_name, "~alloca"))  {
    exp arg1;

    arg1 = hold_check(d_exp());
    tkv.tk_exp = hold_check(me_u3(f_pointer(long_to_al(8)),
				  arg1, alloca_tag));
    *done = 1;
    has_alloca = 1;
    return tkv;
  }
  if(!strcmp(t->tok_name,"__builtin_isfloat")){
    /* builtin function taking a TYPE argument and returning 
       TRUE if the argument is float,double or long double and FALSE
       otherwise */
    shape arg;
    signed_nat lower,upper,resval;

    arg = d_shape();
    resval.issmall=lower.issmall=upper.issmall=1;
    resval.negative=lower.negative=upper.negative=0;
    lower.signed_nat_val.small_s_nat=MIN_INT;
    upper.signed_nat_val.small_s_nat=MAX_INT;
    if(is_floating(name(arg))){
      resval.signed_nat_val.small_s_nat=1;
    }
    else{
      resval.signed_nat_val.small_s_nat=0;
    }
    tkv.tk_exp = f_make_int(slongsh,resval);
    *done=1;
    return tkv;
  }
  if(!strcmp(t->tok_name, "__builtin_va_token")){
    tkv.tk_exp = getexp(f_off32_32,nilexp,0,nilexp,nilexp,0,0,val_tag);
    set_vararg(tkv.tk_exp);
    *done = 1;
    return tkv;
  }

  if(!strcmp(t->tok_name, "~Sync_handler")){
    tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,special_tag);
    *done = 1;
    return tkv;
  }
  
  if(!strcmp(t->tok_name, "__alpha_special")){
    /* This is a means of invoking alpha assembler instructions from a
       TDF file */
    exp arg;

    arg = d_exp();
    Assert(name(arg) == val_tag);
    if(no(arg) == 0){
      /* trapb : used to ensure that all pending exceptions have been raised
	 before continuing */
      tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,special_tag);
      *done = 1;
    }
    else{
      failer("Unsupported argument to token __alpha_special");
      tkv.tk_exp = getexp(f_top,nilexp,0,nilexp,nilexp,0,0,null_tag);
      *done = 1;
    }
    return tkv;
  }
    
  if(!strcmp(t->tok_name, "__builtin_va_start")){
    /* builtin function taking 3 arguments: a va_list, a va_alist,
       and an integer i.e a compound(ptrhd,slonghd),
       an integer(s64shd) and an integer(slonghd).
       The pointer field of the compound is set equal to the 64
       bit integer, and the integer field is set to 8.
       */
    exp arg1,arg2,arg3;		/* parameters of the token */
    exp_list list;		/* list of exps used to construct the 
			       result sequence */
    exp res = f_make_top();	/* the result part of the sequence */
    exp assignment1,assignment2; /* the two assignment operations */
    exp component1;	
    exp component2;		/* the components of the exp */
    exp copy_of_compound;
    arg1 = d_exp();
    arg2 = d_exp();
    arg3 = d_exp(); /* don't care */
    /* here we start to perform the transformation.  We must obtain 
       the compound variable of arg1 and apply the component 
       operation to separate out the pointer and integer for use 
       in subsequent assignments.
       */
    set_vararg(arg1);
    copy_of_compound = copyexp(arg1);
    component1 = get_component(arg1,const_al64,PTR_ALIGN,PTR_SZ,
			       ptrhd,f_off64_64,0);
    component2 = get_component(copy_of_compound,const_al32,SLONG_ALIGN,
			       SLONG_SZ,slonghd,f_off32_32,64);
    assignment1 = f_assign(component1,arg2);
    assignment2 = f_assign(component2,getexp(f_off32_32,nilexp,0,nilexp,nilexp,
					     0,0,val_tag));
    bro(assignment1)=assignment2;
    list.start = assignment1;
    list.end = assignment2;
    list.number = 2;
    tkv.tk_exp = f_sequence(list,res);
    kill_exp(arg3,arg3);
    *done=1;
    return tkv;
  }
  
  if (!strcmp(t -> tok_name, "~exp_to_source") ||
      !strcmp(t -> tok_name, "~diag_id_scope") ||
      !strcmp(t -> tok_name, "~diag_type_scope") ||
      !strcmp(t -> tok_name, "~diag_tag_scope"))  {

    tkv.tk_exp = hold_check(d_exp());
    *done = 1;
    
    if (!diagnose)
      return tkv;

    if (!strcmp(t -> tok_name, "~exp_to_source")){
      exp r;
      diag_info * di = read_exp_to_source();
      crt_lno = natint(di -> data.source.end.line_no);
      crt_charno = natint(di -> data.source.end.char_off);
      crt_flnm = di -> data.source.beg.file->file.ints.chars;
      r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
		 1, 0, diagnose_tag);
      setfather(r, tkv.tk_exp);
      dno(r) = di;
      tkv.tk_exp = r;
      return tkv;
    }
    if (!strcmp(t -> tok_name, "~diag_id_scope")){
      exp r;
      diag_info * di = read_diag_id_scope();
      r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
		 2, 0, diagnose_tag);
      setfather(r, tkv.tk_exp);
      dno(r) = di;
      tkv.tk_exp = r;
      return tkv;
    }
    if (!strcmp(t -> tok_name, "~diag_type_scope")){
      exp r;
      diag_info * di = read_diag_type_scope();
      r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
		 3, 0, diagnose_tag);
      setfather(r, tkv.tk_exp);
      dno(r) = di;
      tkv.tk_exp = r;
      return tkv;
    }
    if (!strcmp(t -> tok_name, "~diag_tag_scope")){
      exp r;
      diag_info * di = read_diag_tag_scope();
      r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
		 4, 0, diagnose_tag);
      setfather(r, tkv.tk_exp);
      dno(r) = di;
      tkv.tk_exp = r;
      return tkv;
    }
  }
  SET(tkv); /* call looks at done to see if result is meaningful */
  return tkv;
}











