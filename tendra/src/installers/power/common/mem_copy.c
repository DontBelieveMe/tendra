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



/**********************************************************************
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:26  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.2  1998/02/04  15:48:58  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:34  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "comment.h"
#include "myassert.h"
#include "mem_copy.h"


#define MAX_BYTE_COPY 80

void static_memory_copy PROTO_N ((reg_from,reg_to,number_of_bytes)) PROTO_T ( int reg_from X int reg_to X int number_of_bytes)
{
  baseoff from;
  baseoff to;
  int bytes;
  int words;
  int i;
  COMMENT3("memory copy of %d bytes from R_%d to R_%d",number_of_bytes,reg_from,reg_to);
  ASSERT(number_of_bytes >=0);
  if(reg_from == reg_to || number_of_bytes==0 )
  {
    /* Nothing to do */
    return;
  }
  words = number_of_bytes/4;
  bytes = number_of_bytes - (words *4);
  
  from.base = reg_from;
  from.offset = 0;
  to.base = reg_to;
  to.offset = 0;  
  
  if(number_of_bytes <= MAX_BYTE_COPY)
  {
    /* copy the words */
    for(i=0;i<words;i++)
    {
      ld_ro_ins(i_l,from,R_TMP0);comment(NIL);
      st_ro_ins(i_st,R_TMP0,to);comment(NIL);
      from.offset += 4;
      to.offset += 4;
    }
    /* copy the bytes */
    for(i=0;i<bytes;i++)
    {
      ld_ro_ins(i_lbz,from,R_TMP0);comment(NIL);
      st_ro_ins(i_stb,R_TMP0,to);comment(NIL);
      from.offset +=1;
      to.offset +=1;
    }
  }
  else
  {
    if(words >0)
    {
      /* dynamically copy */
      int loop = new_label();
      from.base = reg_from;
      from.offset = 4;
      to.base = reg_to;
      to.offset = 4;
      rir_ins(i_a,reg_from,-4,reg_from);
      rir_ins(i_a,reg_to,-4,reg_to);
      ld_const_ins(words,R_TMP0);
      mt_ins(i_mtctr,R_TMP0);
      set_label(loop);
      ld_ro_ins(i_lu,from,R_TMP0);comment(NIL);
      st_ro_ins(i_stu,R_TMP0,to);comment(NIL);
      uncond_ins(i_bdn,loop);
      rir_ins(i_a,reg_from,4,reg_from);
      rir_ins(i_a,reg_to,4,reg_to);
    }
    from.base = reg_from;
    from.offset = 0;
    to.base = reg_to;
    to.offset =0;
    for(i=0;i<bytes;i++)
    {
      ld_ro_ins(i_lbz,from,R_TMP0);comment(NIL);
      st_ro_ins(i_stb,R_TMP0,to);comment(NIL);
      from.offset +=1;
      to.offset +=1;
    }
    
    /* restore the pointers to their initial values */
    if(words>0)
    {
      rir_ins(i_a,reg_from,-4 * words,reg_from);
      rir_ins(i_a,reg_to,-4 * words,reg_to);
    }
  }
  return;
}
void reverse_static_memory_copy PROTO_N ((reg_from,reg_to,number_of_bytes)) PROTO_T (int reg_from X int reg_to X int number_of_bytes)
{
  int bytes;
  int words;
  int r;
  baseoff from;
  baseoff to;
  int offset;
  
  from.base = reg_from;
  to.base = reg_to;
  
  COMMENT("reverse static memory copy");
  
  words = number_of_bytes/4;
  bytes = number_of_bytes - (4*words);

  offset = number_of_bytes;
  for(r = 0;r<bytes;r++)
  {
    offset -=1;
    from.offset =offset;
    to.offset = offset;
    ld_ro_ins(i_lbz,from,R_TMP0);comment(NIL);
    st_ro_ins(i_stb,R_TMP0,to);comment(NIL);
  }
  for(r = 0;r<words;r++)
  {
    offset -=4;
    from.offset =offset;
    to.offset = offset;
    ld_ro_ins(i_l,from,R_TMP0);comment(NIL);
    st_ro_ins(i_st,R_TMP0,to);comment(NIL);
  }
  ASSERT(offset ==0);
  return;
}

void dynamic_byte_memory_copy PROTO_N ((reg_from,reg_to,reg_size)) PROTO_T (int reg_from X int reg_to X int reg_size)
{
  /* reg_size contains the number of bytes to copy */
  int zero = new_label();
  int loop = new_label();
  int creg = next_creg();
  baseoff from;
  baseoff to;
  COMMENT3("dynamic copy (byte at a time) from R_%d ro R_%d using no of bytes in R_%d",reg_from,reg_to,reg_size);
  
  cmp_ri_ins(i_cmp,reg_size,0,creg);
  bc_ins(i_beq,creg,zero,UNLIKELY_TO_JUMP);
  from.base = reg_from;
  from.offset =1;
  to.base = reg_to;
  to.offset =1;
  
  rir_ins(i_a,reg_from,-1,reg_from);
  rir_ins(i_a,reg_to,-1,reg_to);
  
  mt_ins(i_mtctr,reg_size);
  
  set_label(loop);
  ld_ro_ins(i_lbzu,from,R_TMP0);comment(NIL);
  st_ro_ins(i_stbu,R_TMP0,to);comment(NIL);
  uncond_ins(i_bdn,loop);
  
  rir_ins(i_a,reg_from,1,reg_from);
  rir_ins(i_a,reg_to,1,reg_to);
  set_label(zero);

  /* reg_from goes to reg_from + reg_size */
  /* reg_to goes to reg_to + reg_size */
  return;
}
void reverse_dynamic_byte_memory_copy PROTO_N ((reg_from,reg_to,reg_size)) PROTO_T (int reg_from X int reg_to X int reg_size )
{
  /* reg_size contains the number of bytes to copy */
  int zero = new_label();
  int loop = new_label();
  int creg = next_creg();
  baseoff from;
  baseoff to;
  COMMENT3("reverse dynamic copy (byte at a time) from R_%d ro R_%d using no of bytes in R_%d",reg_from,reg_to,reg_size);
  cmp_ri_ins(i_cmp,reg_size,0,creg);
  bc_ins(i_beq,creg,zero,UNLIKELY_TO_JUMP);
  from.base = reg_from;
  from.offset = -1;
  to.base = reg_to;
  to.offset = -1;
  rrr_ins(i_a,reg_from,reg_size,reg_from);
  rrr_ins(i_a,reg_to,reg_size,reg_to);
  mt_ins(i_mtctr,reg_size);
  set_label(loop);
  ld_ro_ins(i_lbzu,from,R_TMP0);comment(NIL);
  st_ro_ins(i_stbu,R_TMP0,to);comment(NIL);
  uncond_ins(i_bdn,loop);
  
  set_label(zero);

  return;
}

void dynamic_word_memory_copy PROTO_N ((reg_from,reg_to,reg_size)) PROTO_T (int reg_from X int reg_to X int reg_size)
{
  /* reg_size contains the number of bytes to copy */
  /* however in this case we do it word at a time */
  int zero = new_label();
  int loop = new_label();
  int creg = next_creg();
  baseoff from;
  baseoff to;
  COMMENT3("dynamic copy (word at a time) from R_%d ro R_%d using no of bytes in R_%d",reg_from,reg_to,reg_size);
  cmp_ri_ins(i_cmp,reg_size,0,creg);
  bc_ins(i_beq,creg,zero,UNLIKELY_TO_JUMP);
  from.base = reg_from;
  from.offset =4;
  to.base = reg_to;
  to.offset =4;
  
  rir_ins(i_a,reg_from,-4,reg_from);
  rir_ins(i_a,reg_to,-4,reg_to);
  
  rir_ins(i_sr,reg_size,2,R_TMP0);
  mt_ins(i_mtctr,R_TMP0);
  
  set_label(loop);
  ld_ro_ins(i_lu,from,R_TMP0);comment(NIL);
  st_ro_ins(i_stu,R_TMP0,to);comment(NIL);
  uncond_ins(i_bdn,loop);
  
  rir_ins(i_a,reg_from,4,reg_from);
  rir_ins(i_a,reg_to,4,reg_to);
  set_label(zero);

  /* reg_from goes to reg_from + reg_size */
  /* reg_to goes to reg_to + reg_size */
  return;
}
void reverse_dynamic_word_memory_copy PROTO_N ((reg_from,reg_to,reg_size)) PROTO_T (int reg_from X int reg_to X int reg_size )
{
  int zero = new_label();
  int loop = new_label();
  int creg = next_creg();
  baseoff from;
  baseoff to;
  COMMENT3("reverse dynamic copy (word at a time) from R_%d ro R_%d using no of bytes in R_%d",reg_from,reg_to,reg_size);
  cmp_ri_ins(i_cmp,reg_size,0,creg);
  bc_ins(i_beq,creg,zero,UNLIKELY_TO_JUMP);
  from.base = reg_from;
  from.offset = -4;
  to.base = reg_to;
  to.offset = -4;
  rrr_ins(i_a,reg_from,reg_size,reg_from);
  rrr_ins(i_a,reg_to,reg_size,reg_to);
  rir_ins(i_sr,reg_size,2,R_TMP0);
  mt_ins(i_mtctr,R_TMP0);
  
  set_label(loop);
  ld_ro_ins(i_lu,from,R_TMP0);comment(NIL);
  st_ro_ins(i_stu,R_TMP0,to);comment(NIL);
  uncond_ins(i_bdn,loop);
  
  set_label(zero);

  /* reg_from and reg_to are unchanged */
  return;
}
