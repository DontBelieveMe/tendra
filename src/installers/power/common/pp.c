/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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


#include "config.h"
#ifdef DEBUG_POWERTRANS
#include "common_types.h"
#include "exptypes.h"
#include "expmacs.h"
#include "exp.h"
#include "tags.h"
#include "shapemacs.h"
#include "ash.h"
#include "addresstypes.h"
#include "locate.h"
#include "translat.h"

#include "pp.h"
/*
 * This file contains debugging tools used in debugging a translator
 */

void properties PROTO_S ((int));
exp show_bro PROTO_S ((int));
exp show_son PROTO_S ((int));
exp show_current PROTO_S ((int));
exp show_father PROTO_S ((int));
exp show_pt PROTO_S ((int));
exp recurse PROTO_S ((int));
exp infotag PROTO_S ((exp,int));
void showme PROTO_S ((exp,int,int));
static exp last_exp_seen=NULL;
static exp last_exp_seen1=NULL;
static exp last_exp_seen2=NULL;
static exp last_exp_seen3=NULL;
static exp last_exp_seen4=NULL;
static exp last_exp_seen5=NULL;

static void exp_show PROTO_S ((exp,int,int,int));
char *find_test_name PROTO_S ((exp));
static void myprint PROTO_S ((char *));
char *shape_name PROTO_S ((int ));
char *getname PROTO_S ((int));
void ident_props PROTO_S ((exp));
void proc_tag_props PROTO_S ((exp));
void general_proc_tag_props PROTO_S ((exp));
void solve_props PROTO_S ((exp));
void movecont_props PROTO_S ((exp));
void cont_props PROTO_S ((exp));
void labst_props PROTO_S ((exp));
void name_props PROTO_S ((exp));
void string_props PROTO_S ((exp));
void val_props PROTO_S ((exp));
void rep_props PROTO_S ((exp));
void apply_props PROTO_S ((exp));

static exp stored_idents[1000];
static exp stored_labsts[1000];
static int store_ident PROTO_S ((exp));
static int store_labst PROTO_S ((exp));
static int no_of_idents_stored=0;
static int no_of_labsts_stored=0;
static int ident_no PROTO_S ((exp));
static int labst_no PROTO_S ((exp));

static int store_ident PROTO_N ((e)) PROTO_T (exp e)
{
  no_of_idents_stored++;
  stored_idents[no_of_idents_stored]=e;
  return no_of_idents_stored;
}
static int store_labst PROTO_N ((e)) PROTO_T (exp e)
{
  no_of_labsts_stored++;
  stored_labsts[no_of_labsts_stored]=e;
  return no_of_labsts_stored;
}
static int ident_no PROTO_N ((e)) PROTO_T (exp e)
{
  int i;
  for (i=no_of_idents_stored;i>0;i--)
    if(stored_idents[i]==e) return i;
  return 0;
}
static int labst_no PROTO_N ((e)) PROTO_T (exp e)
{
  int i;
  for (i=no_of_labsts_stored;i>0;i--)
    if(stored_labsts[i]==e) return i;
  return 0;
}
void scan_for_labsts PROTO_N ((e)) PROTO_T (exp e)
{
  if (e==nilexp)
    return;
  switch(name(e))
  {
   case labst_tag:
    store_labst(e);
    break;
   case ident_tag:
    store_ident(e);
    break;
    /* don't scan sons of these tags */
   case name_tag:
   case env_offset_tag:
    if(!last(e)) scan_for_labsts(bro(e));
    return;
    /* don't scan bros of these tags */
   case case_tag:
    scan_for_labsts(son(e));
    return;
  }
  scan_for_labsts(son(e));
  if(!last(e)) scan_for_labsts(bro(e));
  return;
}

  

void showme PROTO_N ((e,depth_of_recursion,flag)) PROTO_T (exp e X int depth_of_recursion X int flag)
{
  no_of_labsts_stored=0;
  no_of_idents_stored=0;
  if (name(e)==labst_tag)
    store_labst(e);
  if (name(e)==ident_tag)
    store_ident(e);
  scan_for_labsts(son(e));
  exp_show(e,0,depth_of_recursion,flag);
  return;
}

exp show_current PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  
  if (l==NULL)
  {
    printf("No current exp for stored exp no %d\n",i);
  }
  else
  {
    infotag(l,i);
  }
  return l;
}

exp show_bro PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  
  if (l==NULL)
  {
    printf("No current exp\n");
    return NULL;
  }
  
  if(bro(l)!=NULL)
  {
    infotag(bro(l),i);
  }
  else
  {
    printf("No brother field to stored exp no %d\n",i);
  }
  return l;
  
  
}
exp show_son PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  
  if(l==NULL)
  {
    printf("No current exp\n");
    return 0;
    
  }
      
  if(son(l)!=NULL)
  {
    infotag(son(l),i);
  }
  else
  {
    printf("No son field to stored exp no %d\n",i);
  }
  return l;
  
}
exp show_father PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  
  if(l==NULL)
  {
    printf("No current stored exp no %d\n",i);
    return NULL;
  }
  if (father(l)!=NULL)
  {
    infotag(father(l),i);
  }
  else
  {
    printf("Cannot find father of stored exp no %d\n",i);
  }
  return l;
}
exp show_pt PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  
  if(l==NULL)
  {
    printf("No current exp\n");
    return 0;
    
  }
      
  if(pt(l)!=NULL)
  {
    infotag(pt(l),i);
  }
  else
  {
    printf("No pt field to stored exp no %d\n",i);
  }
  return l;
  
}

exp recurse PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  
  if(l==NULL)
  {
    printf("No current exp for no %d (Use infotag)\n",i);
  }
  else
  {
    showme(l,-1,1);
  }
  return l;
}


char * getname PROTO_N ((n)) PROTO_T (int n)
{
  char * tagname;
  switch (n){
   case 0                     :tagname= "zero";break;
   case ident_tag             :tagname= "ident";break;
   case seq_tag               :tagname= "seq";break;
   case cond_tag              :tagname= "cond";break;
   case labst_tag             :tagname= "labst";break;
   case rep_tag               :tagname= "rep";break;
   case goto_tag              :tagname= "goto";break;
   case test_tag              :tagname= "test";break;
   case ass_tag               :tagname= "ass";break;
   case apply_tag             :tagname= "apply";break;
   case res_tag               :tagname= "res";break;
   case goto_lv_tag           :tagname= "goto_lv";break;
   case solve_tag             :tagname= "solve";break;
   case assvol_tag            :tagname= "assvol";break;
   case compound_tag          :tagname= "compound";break;
   case nof_tag               :tagname= "nof";break;
   case local_free_all_tag    :tagname= "local_free_all";break;
   case local_free_tag        :tagname= "local_free";break;
   case last_local_tag        :tagname= "last_local";break;
   case long_jump_tag         :tagname= "long_jump";break;
   case concatnof_tag         :tagname= "concatnof";break;
   case ncopies_tag           :tagname= "ncopies";break;
   case case_tag              :tagname= "case";break;
   case movecont_tag          :tagname= "movecont";break;
   case testbit_tag           :tagname= "testbit";break;
   case alloca_tag            :tagname= "alloca";break;
   case diagnose_tag          :tagname= "diagnose";break;
   case prof_tag              :tagname= "prof";break;
   case ignorable_tag         :tagname= "ignorable";break;
   case bfass_tag             :tagname= "bfass";break;
   case bfassvol_tag          :tagname= "bfassvol";break;
   case condassign_tag        :tagname= "condassign";break;
   case apply_general_tag     :tagname= "apply_general";break;
   case tail_call_tag         :tagname= "tail_call";break;
   case untidy_return_tag     :tagname= "untidy_return";break;
   case same_callees_tag      :tagname= "same_callees";break;
   case plus_tag              :tagname= "plus";break;
   case neg_tag               :tagname= "neg";break;
   case shl_tag               :tagname= "shl";break;
   case mod_tag               :tagname= "mod";break;
   case rem2_tag              :tagname= "rem2";break;
   case abs_tag               :tagname= "abs";break;
   case round_tag             :tagname= "round";break;
   case offset_pad_tag        :tagname= "offset_pad";break;
   case offset_div_tag        :tagname= "offset_div";break;
   case offset_max_tag        :tagname= "offset_max";break;
   case minptr_tag            :tagname= "minptr";break;
   case fpower_tag            :tagname= "fpower";break;
   case fplus_tag             :tagname= "fplus";break;
   case fminus_tag            :tagname= "fminus";break;
   case fmult_tag             :tagname= "fmult";break;
   case fdiv_tag              :tagname= "fdiv";break;
   case fabs_tag              :tagname= "fabs";break;
   case fneg_tag              :tagname= "fneg";break;
   case float_tag             :tagname= "float";break;
   case chfl_tag              :tagname= "chfl";break;
   case and_tag               :tagname= "and";break;
   case or_tag                :tagname= "or";break;
   case xor_tag               :tagname= "xor";break;
   case not_tag               :tagname= "not";break;
   case component_tag         :tagname= "component";break;
   case max_tag               :tagname= "max";break;
   case min_tag               :tagname= "min";break;
   case bitf_to_int_tag       :tagname= "bitf_to_int";break;
   case bfcont_tag            :tagname= "bfcont";break;
   case fmax_tag              :tagname= "fmax";break;
   case shr_tag               :tagname= "shr";break;
   case fmin_tag              :tagname= "fmin";break;
   case div0_tag              :tagname= "div0";break;
   case bfcontvol_tag         :tagname= "bfcontvol";break;
   case absbool_tag           :tagname= "absbool";break;
   case addptr_tag            :tagname= "addptr";break;
   case chvar_tag             :tagname= "chvar";break;
   case minus_tag             :tagname= "minus";break;
   case mult_tag              :tagname= "mult";break;
   case subptr_tag            :tagname= "subptr";break;
   case realpart_tag          :tagname= "realpart";break;
   case div1_tag              :tagname= "div1";break;
   case div2_tag              :tagname= "div2";break;
   case offset_add_tag        :tagname= "offset_add";break;
   case offset_div_by_int_tag :tagname= "offset_div_by_int";break;
   case offset_mult_tag       :tagname= "offset_mult";break;
   case offset_negate_tag     :tagname= "offset_negate";break;
   case offset_subtract_tag   :tagname= "offset_subtract";break;
   case rem0_tag              :tagname= "rem0";break;
   case rotl_tag              :tagname= "rotl";break;
   case rotr_tag              :tagname= "rotr";break;
   case power_tag             :tagname= "power";break;
   case imag_tag              :tagname= "imag";break;
   case make_complex_tag      :tagname= "make_complex";break;
   case int_to_bitf_tag       :tagname= "int_to_bitf";break;
   case hold_tag              :tagname= "hold";break;
   case hold2_tag             :tagname= "hold2";break;
   case cont_tag              :tagname= "cont";break;
   case field_tag             :tagname= "field";break;
   case val_tag               :tagname= "val";break;
   case reff_tag              :tagname= "reff";break;
   case name_tag              :tagname= "name";break;
   case proc_tag              :tagname= "proc";break;
   case top_tag               :tagname= "top";break;
   case contvol_tag           :tagname= "contvol";break;
   case current_env_tag       :tagname= "current_env";break;
   case env_offset_tag        :tagname= "env_offset";break;
   case make_lv_tag           :tagname= "make_lv";break;
   case clear_tag             :tagname= "clear";break;
   case null_tag              :tagname= "null";break;
   case real_tag              :tagname= "real";break;
   case string_tag            :tagname= "string";break;
   case general_proc_tag      :tagname= "general_proc";break;     
   case env_size_tag          :tagname= "env_size";break;
   case give_stack_limit_tag  :tagname= "give_stack_limit";break;
   case general_env_offset_tag:tagname= "general_env_offset";break;
   case caller_tag            :tagname= "caller";break;
   case caller_name_tag       :tagname= "caller_name";break;
   case make_dynamic_callee_tag:tagname="make_dynamic_callee";break;
   case make_callee_list_tag  :tagname= "make_callee_list";break;
   case set_stack_limit_tag   :tagname= "set_stack_limit";break;
   case formal_callee_tag     :tagname= "formal_callee";break;
   case trap_tag              :tagname= "trap_tag";break;
    
    /* Powertrans specific */
   case locptr_tag           :tagname= "locptr_tag";break;
        
   default                    :tagname= "undefined";
    
  }
  return tagname;
}

exp infotag PROTO_N ((e,i)) PROTO_T (exp e X int i)
{
  switch(i)
  {
   case 0:last_exp_seen=e;break;
   case 1:last_exp_seen1=e;break;
   case 2:last_exp_seen2=e;break;
   case 3:last_exp_seen3=e;break;
   case 4:last_exp_seen4=e;break;
   case 5:last_exp_seen5=e;break;
  }
  
  if (e==nilexp){
    printf("Error 'nilexp'\n");
    return e;
  }
  printf("-------------------------------------------------------------------------------\n");
  printf("| %-17s 0x%-8x         | SHAPE information                    |\n",getname(name(e)),(unsigned int)e);
  printf("-------------------------------------------------------------------------------\n");
  printf("| no(e)        = %-15d       ",no(e));
  if(sh(e)!=NULL)
  {
    printf("| name(sh(e))        = %-15s |\n",shape_name(name(sh(e))));
  }
  else
  {
    printf("| No shape                             |\n");
  }
  printf("| props(e)     = ");
  {
    int i;
    unsigned short mask;
    for (i=15;i>=0;i--)
    {
      mask=1<<i;
      if (mask & props(e))
      {
	printf("1");
      }
      else 
      {
	printf("0");
      }
    
      if (i%4 == 0)
      {
	printf(" ");
      }
    }
  }

  if(sh(e)!=NULL)
  {
    printf("  | shape_size(sh(e))  = %-8d        |\n",shape_size(sh(e)));
  }
  else
  {
    printf("  |                                      |\n");
  }
  
  printf("| bro(e)       = 0x%-8x            ",(unsigned int)bro(e));  
  
  if(sh(e)!=NULL)
  {

    printf("| shape_align(sh(e)) = %-8d        |",(int)shape_align(sh(e)));
    
  }
  else
  {
    printf("|                                      |");
  }
  if(bro(e)!=NULL)
  {
    if(last(e))
    {
      printf("-->father:%s\n",getname(name(bro(e))));
    }
    else
    {
      printf("-->brother:%s\n",getname(name(bro(e))));
    }
  }
  else
  {
    printf("-->NULL\n");
  }
  

  printf("| sh(e)        = 0x%-8x            ",(unsigned int)sh(e));

  if(sh(e)!=NULL)
  {
    printf("| is_signed(sh(e))   = %-2d              |\n",is_signed(sh(e)));
  }
  else
  {
    printf("|                                      |\n");
  }
  printf("| pt(e)        = 0x%-8x            ",(unsigned int)pt(e));  

  if(sh(e)!=NULL)
  {
    printf("| al1(sh(e))         = %-2d              |\n",(int)al1(sh(e)));
  }
  else
  {
    printf("|                                      |\n");
  }
  
  printf("| last(e)      = %d                     ",last(e));
  
  if(sh(e)!=NULL)
  {
    printf("| al2(sh(e))         = %-2d              |\n",(int)al2(sh(e)));
  }
  else
  {
    printf("|                                      |\n");
  }
  
  printf("-------------------------------------------------------------------------------\n");
  if(son(e)!=nilexp)
  {
    int finished=0;
    exp point=son(e);    
    if (name(e)==name_tag)
    {
      printf("son is ident 0x%-8x\n",(unsigned int)son(e));
      return e;
    }
    
    printf("                |\n");

    /* first line */
    while(!finished)
    {
      finished=last(point);
      printf("------------------------------   ");
      point=bro(point);
    }
    printf("\n");
    /* second line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      printf("| %-17s0x%-8x|   ",getname(name(point)),(unsigned int)point);
      point=bro(point);
    }
    printf("\n");
    /**/
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      printf("------------------------------   ");
      point=bro(point);
    }
    printf("\n");
    /* new line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      printf("| no          = %-10d   |   ",no(point));      
      point=bro(point);
    }
    printf("\n");
    /* new line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      printf("| pt          = 0x%-8x   |   ",(unsigned int)pt(point));      
      point=bro(point);
    }
    printf("\n");
    /* third line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      if(sh(point)!=NULL)
      {
	printf("| name(sh) = %-15s |",shape_name(name(sh(point))));      
      }
      else
      {
	printf("|                            |");
      }
      if(finished==0)
      {
	printf("-->");
      }
      point=bro(point);
    }
    printf("\n");

    /* fourth line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      if(sh(point)!=NULL)
      {
	printf("| shape_size  = %-4d         |   ",shape_size(sh(point)));
      }
      else
      {
	printf("|                            |   ");
      }
      point=bro(point);
    }
    printf("\n");
    /**/
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      if(sh(point)!=NULL)
      {
	printf("| shape_align = %-4d         |   ",(int)shape_align(sh(point)));
      }
      else
      {
	printf("|                            |   ");
      }
      point=bro(point);
    }
    printf("\n");
    /* fifth_line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      if(sh(point)!=NULL)
      {
	printf("| is_signed   = %-4d         |   ",is_signed(sh(e)));
      }
      else
      {
	printf("|                            |   ");
      }
      
      point=bro(point);
    }
    printf("\n");
    /**/
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      printf("------------------------------   ");
      point=bro(point);
    }
    printf("\n");
    /* last line */
    point=son(e);
    finished=0;
    while(!finished)
    {
      finished=last(point);
      if(son(point)==NULL)
      {
	
	printf("                                 ");
      }
      else 
      {
	printf("                |                ");
      }
      
      
      point=bro(point);
    }
    printf("\n");
  }
  
    

    
    
  return e;
}
static void print_spaces PROTO_N ((n)) PROTO_T (int n)
{
  int i;
  int j=0;
  for (i=0;i<n;i++)
  {
    switch(j)
    {
     case 0:printf(" ");break;
     case 1:printf(" ");break;
     case 2:printf("|");break;
     } 
     j++;
    if (j==3)
      j=0;
  }
  
}

      
static void exp_show PROTO_N ((e,depth,depth_of_recursion,flag)) PROTO_T (exp e X int depth X int depth_of_recursion X int flag)
{
  char *tagname;

  if( e == nilexp || depth == depth_of_recursion )
    return;
  printf("(0x%x)",(int)e);
  tagname = getname(name(e));
  
  print_spaces(depth);
    
  switch(name(e))
  {
    /* Don't want to look down son's of name_tag's or env_offset_tag because this will take you to
ident_tag's and thus into an infinite loop */

   case proc_tag:
   case general_proc_tag:
    {
      if (done_scan==1)
      {
	baseoff b = boff(father(e));
	char *ext;
	ext = main_globals[(-b.base) - 1]->dec_u.dec_val.dec_id;
	printf("%s:\"%s\"\n",tagname,ext);
      }
      else
      {
	printf("%s:\n",tagname);
      }
      
      exp_show(son(e),depth+1,depth_of_recursion,0);
      break;
    }
    
   case name_tag:
    {
      int l = ident_no(son(e));
      if(l)
	printf("%s:<%s> no=%d obtain {tag~%04d}\n",tagname,shape_name(name(sh(e))),no(e),l);
#if 1
      else if(name(sh(e))==prokhd &&(name(son(son(e)))==proc_tag||son(son(e))==nilexp||name(son(son(e)))==general_proc_tag) && done_scan==1)
      {
	baseoff b = boff(son(e));
	char *ext;
	ext = main_globals[(-b.base) - 1]->dec_u.dec_val.dec_id;
	printf("%s:<%s> function \"%s\"(0x%x)\n",tagname,shape_name(name(sh(e))),ext,(int)(son(e)));
      }
#endif
      else
	printf("%s:<%s> no=%d obtain (0x%x)\n",tagname,shape_name(name(sh(e))),no(e),(int)son(e));
      break;
    }
   case trap_tag:
    {
      printf("%s:no=%d\n",tagname,no(e));
      exp_show(son(e),depth+1,depth_of_recursion,0);
      break;
    }
    
   case general_env_offset_tag:
   case env_offset_tag:
    {
      int l = ident_no(son(e));
      if(l)
	printf("%s:<%s> for ident {tag~%04d}\n",tagname,shape_name(name(sh(e))),l);
      else
	printf("%s:<%s> for ident (0x%x)\n",tagname,shape_name(name(sh(e))),(int)son(e));
      break;
    }
   case caller_name_tag:
    {
      printf("%s:<%s> for caller NO_%d\n",tagname,shape_name(name(sh(e))),no(e));
      break;
    } 
   case case_tag:
    printf("%s:<%s>\n",tagname,shape_name(name(sh(e))));
    exp_show(son(e),depth+1,depth_of_recursion,1);
    {
      exp s=son(e);
      do
      {
	int label;
	s=bro(s);
	printf("(0x%x)",(int)s);
	print_spaces(depth+1);
	printf("(%d",no(s));
	if(son(s)!=nilexp)
	  printf("-%d)",no(son(s)));
	else 
	  printf(")");
	label = labst_no(pt(s));
	if (label)
	  printf(" ----> {label~%04d}\n",label);
	else
	  printf(" ----> (0x%x)\n",(int)pt(s));
      }
      while ( !last(s));
    }
    break;
   case goto_tag:
    {
      int label= labst_no(pt(e));
      if (label)
	printf("%s:<%s> ---->{label~%04d}\n",tagname,shape_name(name(sh(e))),label);
      else
	printf("%s:<%s> ---->(0x%x)\n",tagname,shape_name(name(sh(e))),(int)pt(e));
      exp_show(son(e),depth+1,depth_of_recursion,0);
      break;
    }
   case fdiv_tag:
   case fplus_tag:
   case fminus_tag:
   case fneg_tag:
   case fpower_tag:
   case mult_tag:
   case neg_tag:
   case plus_tag:
   case power_tag:
   case rem0_tag:
   case rem2_tag:
   case mod_tag:
   case round_tag:
   case shl_tag:
   case shr_tag:
    
    if (optop(e))
    {
      printf("%s:<%s>\n",tagname,shape_name(name(sh(e))));
    }
    else
    {
      int label = labst_no(pt(e));
      if (label)
	printf("%s:<%s> error_jump=>{label~%04d}\n",tagname,shape_name(name(sh(e))),label);
      else
	printf("%s:<%s> error_jump=>0x%x\n",tagname,shape_name(name(sh(e))),(unsigned int)pt(e));
    }
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;



   case last_local_tag:
    printf("%s: pt=0x%x\n",tagname,(unsigned int)pt(e));
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case make_lv_tag:
    {
      int label = labst_no(pt(e));
      if(label)
	printf("%s: {label~%04d}\n",tagname,label);
      else
	printf("%s: Label=0x%x\n",tagname,(unsigned int)pt(e));
      exp_show(son(e),depth+1,depth_of_recursion,0);
      break;
    }
    
   case seq_tag:
   case rotl_tag:
   case rotr_tag:
   case realpart_tag:
   case nof_tag:
   case not_tag:
   case null_tag:
   case offset_add_tag:
   case offset_div_tag:
   case offset_max_tag:
   case offset_mult_tag:
   case offset_negate_tag:
   case offset_pad_tag:
   case offset_subtract_tag:
   case or_tag:
   case minptr_tag:
   case ignorable_tag:
   case imag_tag:
   case float_tag:
   case fmax_tag:
   case fmin_tag:
   case fabs_tag:
   case div2_tag:
   case div1_tag:   
   case div0_tag:
   case current_env_tag:
   case concatnof_tag:
   case abs_tag:
   case addptr_tag:
   case alloca_tag:
   case and_tag:
   case apply_tag:
   case int_to_bitf_tag:
   case bitf_to_int_tag:
   case cont_tag:
   case cond_tag:
   case chfl_tag:
   case caller_tag:
    printf("%s:<%s>\n",tagname,shape_name(name(sh(e))));
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case bfass_tag:
   case bfcont_tag:
    if (name(sh(e))==bitfhd)
    {
      printf("%s:<%s> %s %d bit bitfield , bit_offset=%d\n",tagname,shape_name(name(sh(e))),is_signed(sh(e))?"Signed":"Unsigned",shape_size(sh(e)),no(e));
    }
    else
    {
      printf("%s:<%s> bit_offset=%d\n",tagname,shape_name(name(sh(e))),no(e));
    }
    
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case chvar_tag:
    if (name(sh(e))==bitfhd)
    {
      printf("%s:<%s> %s %d bit bitfield\n",tagname,shape_name(name(sh(e))),is_signed(sh(e))==0?"Unsigned":"Signed",shape_size(sh(e)));
    }
    else
    {
      printf("%s:<%s>\n",tagname,shape_name(name(sh(e))));
    }
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case make_callee_list_tag:
    if(call_has_vcallees(e))
    {
      printf("%s:has_vcallees no=%d\n",tagname,no(e));
    }
    else
    {
      printf("%s: no=%d\n",tagname,no(e));
    }
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case clear_tag:
    printf("%s:<%s> no=%d\n",tagname,shape_name(name(sh(e))),no(e));
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case labst_tag:
    printf("%s:<%s> {label~%04d}\n",tagname,shape_name(name(sh(e))),labst_no(e));
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case diagnose_tag:
    printf("%s:<%s> dno=0x%x\n",tagname,shape_name(name(sh(e))),(unsigned int)dno(e));
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case val_tag:
    if (is_signed(sh(e)))
    {
      printf("%s:<%s> no=%d (0x%08x)\n",tagname,shape_name(name(sh(e))),no(e),no(e));
    }
    else
    {
      printf("%s:<%s> no=%u (0x%08x)\n",tagname,shape_name(name(sh(e))),no(e),no(e));
    }
    
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;
   case reff_tag:
   case field_tag:
   case real_tag:
   case ncopies_tag:
    printf("%s:<%s> no=%d\n",tagname,shape_name(name(sh(e))),no(e));
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;

  case test_tag:
    {
      int label= labst_no(pt(e));
      if (label)
	printf("%s: (f_%s) fails---->{label~%04d}\n",tagname,find_test_name(e),label);
      else
	printf("%s: (f_%s) fails---->(0x%x)\n",tagname,find_test_name(e),(int)pt(e));
      exp_show(son(e),depth+1,depth_of_recursion,0);
      break;
    }
    
   case ident_tag:
    printf("%s:<%s> {tag~%04d}",tagname,shape_name(name(sh(e))),ident_no(e));
    if (isvar(e))
    {
      printf(" VAR");
    }
    if(isvis(e))
    {
      printf(" VIS");
    }
    if(isenvoff(e))
    {
      printf(" ENVOFF");
    }
    if(iscaonly(e))
    {
      printf(" CAONLY");
    }
    if (isparam(e))
    {
      printf(" PARAM");
    }
    if (isglob(e))
    {
      printf(" GLOB");
    }
    printf("\n");
    
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;

    
  case string_tag:
    printf("%s: \"",tagname);
    myprint(nostr(e));
    printf("\"\n");
    exp_show(son(e),depth+1,depth_of_recursion,0);
    break;

    
  default:
/* default action will be */
    printf("%s:\n",tagname);
    exp_show(son(e),depth+1,depth_of_recursion,0);
  }



  
  /* always look at brother unless told not to or it is last */
  if (last(e) || flag)
    return;
  else 
  {
    exp_show(bro(e),depth,depth_of_recursion,0);
    return;
  }
}
char *find_test_name PROTO_N ((e)) PROTO_T (exp e)
{
  char *word;
  switch (test_number(e))
  {
   case 1:
    word="greater_than";
    break;
   case 2:
    word="greater_than_or_equal";
    break;
   case 3:
    word="less_than";
    break;
   case 4:
    word="less_than_or_equal";
    break;
   case 5:
    word="equal";
    break;
   case 6:
    word="not_equal";
    break;
   case 7:
    word="not_less_than_or_equal";
    break;
   case 8:
    word="not_less_than";
    break;
   case 9:
    word="not_greater_than_or_equal";
    break;
   case 10:
    word="not_greater_than";
    break;
   case 11:
    word="less_than_or_greater_than";
    break;
   case 12:
    word="not_less_than_and_not_greater_than";
    break;
   case 13:
    word="comparable";
    break;
   case 14:
    word="not_comparable";
    break;
  }
  return word;
}
static void myprint PROTO_N ((word)) PROTO_T (char *word)
{
  char *k;
  k=word;
  while(*k!=0){
    switch(*k){
    case '\n':
      printf("\\n");
      break;
    case '\t':
      printf("\\t");
      break;
    default:
      printf("%c",*k);
    }
    k++;
  }
  return;
}
char *shape_name PROTO_N ((n)) PROTO_T (int n)
{
  char *k;
  switch(n)
  {
   case 1:
    k="bothd";
    break;
   case 2:
    k="tophd";
    break;
   case 3:
    k="scharhd";
    break;
   case 4:
    k="ucharhd";
    break;
   case 5:
    k="swordhd";
    break;
   case 6:
    k="uwordhd";
    break;
   case 7:
    k="slonghd";
    break;
   case 8:
    k="ulonghd";
    break;
   case 9:
    k="s64hd";
    break;
   case 10:
    k="u64hd";
    break;
   case 17:
    k="shcomplexhd";
    break;
   case 18:
    k="complexhd";
    break;
   case 19:
    k="complexdoublehd";
    break;
   case 20:
    k="shrealhd";
    break;
   case 21:
    k="realhd";
    break;
   case 22:
    k="doublehd";
    break;
   case 23:
    k="bitfhd";
    break;
   case 24:
    k="prokhd";
    break;
   case 25:
    k="ptrhd";
    break;
   case 26:
    k="offsethd";
    break;
   case 27:
    k="sizehd";
    break;
   case 28:
    k="cpdhd";
    break;
   case 29:
    k="nofhd";
    break;
   case 30:
    k="tokhd";
    break;
    
   default:
    k="unknown";
    break;
  }
  return k;
}
void properties PROTO_N ((i)) PROTO_T (int i)
{
  exp l;
  
  switch(i)
  {
   case 0:l=last_exp_seen;break;
   case 1:l=last_exp_seen1;break;
   case 2:l=last_exp_seen2;break;
   case 3:l=last_exp_seen3;break;
   case 4:l=last_exp_seen4;break;
   case 5:l=last_exp_seen5;break;
  }
  if(l==NULL)
  {
    printf("No current exp\n");
    return;
  }
  switch(name(l))
  {
    case ident_tag:ident_props(l);break;
    case proc_tag:proc_tag_props(l);break;
    case general_proc_tag:general_proc_tag_props(l);break;
    case solve_tag:solve_props(l);break;
   case movecont_tag:movecont_props(l);break;
   case cont_tag:cont_props(l);break;
   case labst_tag:labst_props(l);break;
   case name_tag:name_props(l);break;
   case string_tag:string_props(l);break;
   case val_tag:val_props(l);break;
   case rep_tag:rep_props(l);break;
   case apply_tag:apply_props(l);break;
   default:printf("Don't know about the properties of a %s\n",getname(name(l)));break;
  }
  return;
}
void ident_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("isvar       = %d\n",isvar(e));
  printf("isvis       = %d\n",isvis(e));
  printf("isenvoff    = %d\n",isenvoff(e));
  printf("iscaonly    = %d\n",iscaonly(e));
  printf("isusereg    = %d\n",isusereg(e));
  printf("isparam     = %d\n",isparam(e));
  printf("isglob      = %d\n",isglob(e));
  printf("copying     = %d\n",copying(e));
  printf("isinlined   = %d\n",isinlined(e));
#ifdef POWER
#define subvar 0x0100
  printf("subvar      = %d\n",!(!(props(e) & subvar)));
  printf("inreg_bits  = %d\n",!(!(props(e) & inreg_bits)));
  printf("infreg_bits = %d\n",!(!(props(e) & infreg_bits)));
  printf("inanyreg    = %d\n",!(!(props(e) & inanyreg)));
  printf("defer_bit   = %d\n",!(!(props(e) & defer_bit)));
  printf("notparreg   = %d\n",!(!(props(e) & notparreg)));
  printf("notresreg   = %d\n",!(!(props(e) & notresreg)));
#endif
}
void proc_tag_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("has_struct_res     = %d\n",has_struct_res(e));
  printf("loc_address        = %d\n",loc_address(e));
  printf("proc_has_setjmp    = %d\n",proc_has_setjmp(e));
  printf("proc_has_lv        = %d\n",proc_has_lv(e));
  printf("isrecursive        = %d\n",isrecursive(e));
  printf("proc_uses_crt_env  = %d\n",proc_uses_crt_env(e));
  printf("proc_uses_external = %d\n",proc_uses_external(e));
}
void general_proc_tag_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("has_struct_res     = %d\n",has_struct_res(e));
  printf("loc_address        = %d\n",loc_address(e));
  printf("proc_has_setjmp    = %d\n",proc_has_setjmp(e));
  printf("proc_has_lv        = %d\n",proc_has_lv(e));
  printf("isrecursive        = %d\n",isrecursive(e));
  printf("proc_uses_crt_env  = %d\n",proc_uses_crt_env(e));
  printf("proc_uses_external = %d\n",proc_uses_external(e));
  printf("PROCPROPS\n");
  printf("proc_has_vcallees  = %d\n",proc_has_vcallees(e));
  printf("proc_has_vcallers  = %d\n",proc_has_vcallers(e));
  printf("proc_has_checkstack= %d\n",proc_has_checkstack(e));
  printf("proc_has_nolongj   = %d\n",proc_has_nolongj(e));
}

void solve_props PROTO_N ((e)) PROTO_T (exp e)
{
#ifdef POWER
  printf("is_copying_solve = %d\n",is_copying_solve(e));
#endif
}
void movecont_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("isnooverlap = %d\n",isnooverlap(e));
}
void cont_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("to_propagate = %d\n",to_propagate(e));
}
void labst_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("is_loaded_lv = %d\n",is_loaded_lv(e));
  printf("isunroll     = %d\n",isunroll(e));
}
void name_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("islastuse   = %d\n",islastuse(e));
  printf("isloadparam = %d\n",isloadparam(e));
  printf("isreallyass = %d\n",isreallyass(e));
}
void string_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("string_char_size = %d\n",string_char_size(e));
}
void val_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("isbigval = %d\n",isbigval(e));
}
void rep_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("isunrolled = %d\n",isunrolled(e));
}
void apply_props PROTO_N ((e)) PROTO_T (exp e)
{
  printf("istoinline = %d\n",istoinline(e));
}
#endif