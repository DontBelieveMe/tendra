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

 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "flags.h"
#include "shapemacs.h"
#include "inl_norm.h"


#define crit_inline 50
#define decs_allowed 4
#define decs_with_apply 0

static int  complexity PROTO_S ((exp e, int count, int newdecs));

/* applies complexity to the members of a list */
static int  sbl
    PROTO_N ( (e, count, newdecs) )
    PROTO_T ( exp e X int count X int newdecs )
{
  int  c = complexity (e, count,newdecs);
  if (c < 0)
    return (c);
  if (last (e))
    return (c);
  return (sbl (bro (e), c, newdecs));
}

static int  complexity
    PROTO_N ( (e, count, newdecs) )
    PROTO_T ( exp e X int count X int newdecs )
{
  unsigned char  n = name (e);
  if (count < 0 || newdecs >= decs_allowed)
    return (-1);
  if (son(e) == nilexp) return count;
  switch (n) {
  	case apply_tag: {
  	   if (newdecs > decs_with_apply)
		 return -1;
  	   return(sbl(son(e), count-1, newdecs));
  	}
  	case res_tag: return complexity(son(e), count-1, newdecs);
        case ident_tag:
	  if (isloadparam(son(e)))
	    return sbl(son(e), count-1, newdecs);
	  else
	    return sbl(son(e), count-1, newdecs+1);
        case top_tag: case clear_tag: case prof_tag: return count;
	case case_tag: return (complexity (son (e), count - 1, newdecs));
	case name_tag: case string_tag: case env_offset_tag:
        case general_env_offset_tag:
               return (count - 1);
	case labst_tag: return (complexity (bro (son (e)), count,
                        newdecs));
	case solve_tag: case seq_tag: return sbl(son(e), count, newdecs);
	default: return (sbl (son (e), count - 1, newdecs));
  }
}

int inlinechoice
    PROTO_N ( (t, def, total) )
    PROTO_T ( exp t X exp def X int total )
{
	/* delivers 0 if no uses of this proc can be inlined.
	   delivers 1 if this use cannot be inlined
	   delivers 2 if this use can be inlined.
	*/
  exp apars;
  exp fpars;
  int newdecs = 0;
  shape shdef = pt(def) /* Oh, yes it is! */;
  UNUSED(total);

  if (!eq_shape(sh(father(t)), shdef) ) {
      /* shape required by application is different from definition */
	return 1;
  }

  apars = t; /* only uses are applications */
  fpars = son(def);

  for(;;) {
     if (name(fpars)!=ident_tag || !isparam(fpars)) {
	if (!last(apars)) return 1;
      	break;
     }

     if (last(apars)) return 1;
     apars = bro(apars);

     switch (name(apars)) {
      case val_tag: case real_tag: case string_tag: case name_tag:
      	   break;
      case cont_tag: {
      	   if (name(son(apars))==name_tag && isvar(son(son(apars))) &&
      	        		!isvar(fpars) ) break;
      	   } /* ... else continue */
      default: newdecs++;
     }
     fpars = bro(son(fpars));
  }
        /* newdecs is now the number of declarations (which will not be
      	     optimised out) arising from actual parameters */



  if (complexity(fpars, crit_inline, newdecs) >= 0)
    return 2;
  else if (newdecs == 0)
    return 0;
  return 1;
}
