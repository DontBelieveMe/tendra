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
$Date: 1998/02/04 10:43:44 $
$Revision: 1.2 $
$Log: syms.c,v $
 * Revision 1.2  1998/02/04  10:43:44  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/12  10:59:44  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/05/05  08:13:07  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/*  syms.c   - produce symbol numbers for binasm (dense numbers)

*/

#include "config.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <symconst.h>
#else
#include CROSS_INCLUDE/symconst.h>
#endif

#include "common_types.h"
#include "symtab.h"
#include "xalloc.h"
#include "flags.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "syms.h"
#include "tags.h"
#include "main.h"
#include "basicread.h"
#include "mipsdiags.h"
#include "new_symbol.h"

extern long currentfile;

int  *symnos;
int  *tempsnos = (int *) 0;

int   next_temps = 0;
int   no_temps = 0;



int
symnoforext(dec * ex, int filen)
{
				/* produce a symbolno for global given by
				   ex in file filen */
        exp tg = ex -> dec_u.dec_val.dec_exp;
  shape s = ex -> dec_u.dec_val.dec_shape;
  diag_type dt = (diag_type)0;
  short   symtype;
  short   symclass;
  long  v = 0;
  char *id = ex -> dec_u.dec_val.dec_id;
  if (diagnose) {
    diag_descriptor * t = ex ->dec_u.dec_val.diag_info;
    if (t != (diag_descriptor *) 0) {
      id = t -> data.id.nme.ints.chars;
      dt = t -> data.id.new_type;
      filen = find_file(t ->data.id.whence.file->file.ints.chars);
    }
  }


  if (ex -> dec_u.dec_val.extnamed) {/* it is global */
    if (name (s) == prokhd && !isvar (tg)
		&& (son(tg) == nilexp || name(son(tg))== proc_tag
		|| name(son(tg)) == general_proc_tag))
   {/* a declared procedure */
      if (son (tg) != nilexp) {	/* a defined procedure will be output
				   later with this symbolno */
	return add_dense_no (0, 0);
      }
      else {
      	symtype = stGlobal;
        symclass = scNil;
      }
    }
    else {			/* some other global */
      ash a;
      symtype = stGlobal;
      symclass =
	(son (tg) != nilexp) ?
	((name (son (tg))) != clear_tag ? scData : scCommon)
	: scNil;
      a = ashof (s);
      v = (a.ashsize + 7) >> 3;
    }
    return new_esym_d (id, v, symtype, symclass, dt, filen);
  }
  else {			/* statics */
    if (name (s) == prokhd && !isvar (tg)
		&& (son(tg) == nilexp || name(son(tg))== proc_tag
		|| name(son(tg)) == general_proc_tag))
    {/* a procedure */
      symtype = stStaticProc;
      if (son (tg) != nilexp)
	return add_dense_no (0, 0);
      /* a defined procedure will be output later with this symbolno */
      failer ("Static procs should have bodies ");
      symclass = scNil;
    }
    else {			/* other statics */
      symtype = stStatic;
      symclass = (son(tg)== nilexp || name (son (tg)) != clear_tag)
                     ? scData : scCommon;
    }
    return new_lsym_d (id, v, symtype, symclass, dt, filen);
  }
}

int
symnoforstart(int i, int filen)
{
				/* output symbolno for start of proc */
  dec * ex = main_globals[i];
  short   symtype = (ex -> dec_u.dec_val.extnamed) ? stProc : stStaticProc;
  char *id = ex -> dec_u.dec_val.dec_id;
  diag_type dt = (diag_type)0;
  if (diagnose) {
    diag_descriptor * t = ex ->dec_u.dec_val.diag_info;
    if (t != (diag_descriptor *) 0) {
      id = t ->data.id.nme.ints.chars;
      dt = t -> data.id.new_type;
      filen = find_file(t ->data.id.whence.file->file.ints.chars);
    }
  }

  return new_lsym (id, symnos[i], symtype, scText, dt, filen);
}

int
symnoforend(dec * ex, int filen)
{
				/* output symbolno for end of proc */
  char *id = ex -> dec_u.dec_val.dec_id;
  diag_type dt = (diag_type)0;
  if (diagnose) {
    diag_descriptor * t = ex ->dec_u.dec_val.diag_info;
    if (t != (diag_descriptor *) 0) {
      id = t -> data.id.nme.ints.chars;
      dt = t -> data.id.new_type;
      filen = find_file(t -> data.id.whence.file->file.ints.chars);
    }
  }

  return new_lsym_d (id, 0, stEnd, scText, dt, filen);
}

int
symnofordata(int data_lab)
{
				/* output symbol number for data_lab and
				   remember it in tempsnos */
  int   a = data_lab - 32;
  if (a >= no_temps) {
    tempsnos = (int *) xrealloc ((char *) tempsnos, (100 + a) * sizeof (int));
    no_temps = a + 100;
  }

  return tempsnos[a] = add_dense_no (currentfile, 1048575 /* ???? */ );
}
