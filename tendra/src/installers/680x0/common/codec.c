/*
    		 Crown Copyright (c) 1996

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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------
$Log$
Revision 1.1  2002/01/26 21:31:10  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.3  1997/11/13 08:27:09  ma
All avs test passed (except add_to_ptr).

Revision 1.2  1997/11/09 14:06:53  ma
Rounding mode represented with names.

Revision 1.1.1.1  1997/10/13 12:42:47  ma
First version.

Revision 1.5  1997/10/13 08:48:58  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.4  1997/09/25 06:44:49  ma
All general_proc tests passed

Revision 1.3  1997/06/18 10:09:22  ma
Checking in before merging with Input Baseline changes.

Revision 1.2  1997/04/20 11:30:17  ma
Introduced gcproc.c & general_proc.[ch].
Added cases for apply_general_proc next to apply_proc in all files.

Revision 1.1.1.1  1997/03/14 07:50:10  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:52  john
 *
 * Revision 1.3  1996/07/30  16:29:34  john
 * Fixed bug, discarding side-effecting operations
 *
 * Revision 1.2  1996/07/05  14:16:20  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:08  john
 *
 * Revision 1.5  94/11/16  10:36:02  10:36:02  ra (Robert Andrews)
 * Added integer absolute construct.
 * -
 *
 * Revision 1.4  94/06/29  14:18:00  14:18:00  ra (Robert Andrews)
 * Added div0, rem0, max and min for TDF 3.0.
 *
 * Revision 1.3  93/11/19  16:14:42  16:14:42  ra (Robert Andrews)
 * Corrected order of arguments in offset_subtract.
 *
 * Revision 1.2  93/03/03  14:46:05  14:46:05  ra (Robert Andrews)
 * Added error handling routines.
 *
 * Revision 1.1  93/02/22  17:15:17  17:15:17  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "flags.h"
#include "shapemacs.h"
#include "install_fns.h"
#include "tags.h"
#include "mach.h"
#include "where.h"
#include "codec.h"
#include "coder.h"
#include "operations.h"
#include "utility.h"
#include "mach.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "f64.h"
#include "me_fns.h"
#include "evaluate.h"
#include "ops_shared.h"
#include "mach_ins.h"

extern bool have_cond ;


/*
    CONSTRUCT A SIMILAR EXP

    This routine, given a where, copies the corresponding exp, and sets
    its sh equal to the given shape.
*/

exp sim_exp
    PROTO_N ( ( sha, w ) )
    PROTO_T ( shape sha X where w )
{
    exp e = copyexp ( w.wh_exp ) ;
    sh ( e ) = sha ;
    return ( e ) ;
}


/*
    PROCESS A UNARY OPERATION

    This routine processes the unary operation described by the routine
    op.  The operand is given by a and the result, which is of shape
    sha, is put into dest.  The stack argument describes the current
    state of the stack.
*/

static void uop
    PROTO_N ( ( op, sha, a, dest, stack ) )
    PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
	      shape sha X exp a X where dest X ash stack )
{
    int old_rmode ;
    if ( !is_o ( name ( a ) ) ) {
	/* If a is not an operand, we need to calculate its value first */
	if ( whereis ( dest ) == Dreg ) {
	    /* If dest is in a D register, code a into dest */
	    old_rmode = crt_rmode ;
	    coder ( dest, stack, a ) ;
	    crt_rmode = old_rmode ;
	    /* Now apply op to dest */
	    ( *op ) ( sha, dest, dest ) ;
	    return ;
	} else {
	    /* Code a into D1 */
	    where w ;
	    exp e = sim_exp ( sha, D1 ) ;
	    w = zw ( e ) ;
	    regsinproc |= regmsk ( REG_D1 ) ;
	    old_rmode = crt_rmode ;
	    coder ( w, stack, a ) ;
	    crt_rmode = old_rmode ;
	    /* Apply op to D1 */
	    ( *op ) ( sha, w, dest ) ;
	    retcell ( e ) ;
	    if ( have_cond == 3 ) have_cond = 1 ;
	    return ;
	}
    }
    /* If a is an operand, apply op directly to a */
    ( *op ) ( sha, zw ( a ), dest ) ;
    return ;
}


/*
    PROCESS A BINARY OPERATION

    This routine processes the binary operation described by the routine
    op.  The operands are given by a and b and the result, which is of
    shape sha, is put into dest.  The stack argument describes the current
    state of the stack.
*/

static void bop
    PROTO_N ( ( op, sha, a, b, dest, stack ) )
    PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where, where ) ) X
	      shape sha X exp a X exp b X where dest X ash stack )
{
    where w, t ;
    bool noa = !is_o ( name ( a ) ) ;
    bool nob = !is_o ( name ( b ) ) ;
    if ( noa ) {
	/* If a is not an operand, we need to calculate its value first */
	if ( nob ) {
	    /* a and b cannot both not be operands */
	    error ( "Illegal binary operation" ) ;
	}
	t = zw ( b ) ;
	if ( whereis ( dest ) == Dreg && !interfere ( dest, t ) ) {
	    /* If dest is in a D register which is not used in b,
	       code a into dest */
	    coder ( dest, stack, a ) ;
	    /* Apply op to dest and b */
	    ( *op ) ( sha, dest, t, dest ) ;
	    return ;
	} else {
	    /* Code a into D1 */
	    exp e = sim_exp ( sha, D1 ) ;
	    w = zw ( e ) ;
	    regsinproc |= regmsk ( REG_D1 ) ;
	    coder ( w, stack, a ) ;
	    /* Apply op to D1 and b */
	    ( *op ) ( sha, w, t, dest ) ;
	    retcell ( e ) ;
	    if ( have_cond == 3 ) have_cond = 1 ;
	    return ;
	}
    }
    if ( nob ) {
	/* If b is not an operand, we need to calculate its value first */
	t = zw ( a ) ;
	if ( whereis ( dest ) == Dreg && !interfere ( dest, t ) ) {
	    /* If dest is in a D register which is not used in a,
	       code b into dest */
	    coder ( dest, stack, b ) ;
	    /* Apply op to a and dest */
	    ( *op ) ( sha, t, dest, dest ) ;
	    return ;
	} else {
	    /* Code b into D1 */
	    exp e = sim_exp ( sha, D1 ) ;
	    w = zw ( e ) ;
	    regsinproc |= regmsk ( REG_D1 ) ;
	    coder ( w, stack, b ) ;
	    /* Apply op to a and D1 */
	    ( *op ) ( sha, t, w, dest ) ;
	    retcell ( e ) ;
	    if ( have_cond == 3 ) have_cond = 1 ;
	    return ;
	}
    }
    /* If a and b are both operands, apply op directly */
    ( *op ) ( sha, zw ( a ), zw ( b ), dest ) ;
    return ;
}


/*
    PROCESS A LOGICAL OPERATION

    This routine processes the logical operation described by the routine
    op.  This operation will be binary, commutative and associative.  The
    operands are given by the bro-list starting at the son of e.  The
    result is put into dest.  The stack argument describes the current
    state of the stack.
*/

static void logop
    PROTO_N ( ( op, e, dest, stack ) )
    PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where, where ) ) X
	      exp e X where dest X ash stack )
{
    exp arg1 = son ( e ) ;	/* First argument */
    exp arg2 = bro ( arg1 ) ;	/* Second argument */
    exp t, u, v ;
    where w ;

    if ( last ( arg1 ) ) {
	/* If there is of one argument, code it into dest */
	coder ( dest, stack, arg1 ) ;
	return ;
    }

    if ( last ( arg2 ) ) {
	/* If there are two arguments, use bop */
	bop ( op, sh ( e ), arg1, arg2, dest, stack ) ;
	return ;
    }

    /* Three or more arguments : need to take care about overlap between
       dest and args, so use D1. */

    regsinproc |= regmsk ( REG_D1 ) ;
    v = sim_exp ( sh ( e ), D1 ) ;
    w = zw ( v ) ;
    t = arg1 ;

    /* Scan the arguments.  t will hold either the first non-operand,
       or nilexp if all the arguments are operands.  There should be
       at most one non-operand.  */

    while ( 1 ) {
	if ( !is_o ( name ( t ) ) ) break ;
	if ( last ( t ) ) {
	    t = nilexp ;
	    break ;
	}
	t = bro ( t ) ;
    }

    /*
       Deal with the case where all the arguments are operands.  This
       does :
		D1 = op ( arg1, arg2 )
		D1 = op ( arg3, D1 )
		D1 = op ( arg4, D1 )
		....................
		dest = op ( argn, D1 )
    */

    if ( t == nilexp ) {
	/* Process the first two terms */
	( *op ) ( sh ( e ), zw ( arg1 ), zw ( arg2 ), w ) ;
	t = bro ( arg2 ) ;
	while ( !last ( t ) ) {
	    /* Process the third, fourth, ... terms */
	    ( *op ) ( sh ( e ), zw ( t ), w, w ) ;
	    t = bro ( t ) ;
	}
	/* Process the last term */
	reuseables |= regmsk ( REG_D1 ) ;
	( *op ) ( sh ( e ), zw ( t ), w, dest ) ;
	reuseables &= ~regmsk ( REG_D1 ) ;
	retcell ( v ) ;
	if ( have_cond == 3 ) have_cond = 1 ;
	return ;
    }

    /*
	Deal with the case where one argument, say arg2, is a non-operand.
	This does :
		D1 = arg2
		D1 = op ( arg1, D1 )
		D1 = op ( arg3, D1 )
		....................
		dest = op ( argn, D1 )
    */

    coder ( w, stack, t ) ;
    u = arg1 ;
    while ( 1 ) {
	if ( t != u ) {
	    if ( last ( u ) || ( bro ( u ) == t && last ( bro ( u ) ) ) ) {
		( *op ) ( sh ( e ), zw ( u ), w, dest ) ;
	    } else {
		( *op ) ( sh ( e ), zw ( u ), w, w ) ;
	    }
	}
	if ( last ( u ) ) break ;
	u = bro ( u ) ;
    }
    retcell ( v ) ;
    if ( have_cond == 3 ) have_cond = 1 ;
    return ;
}


/*
  PROCESS ADD AND SUBTRACT

  This routine processes the binary operation add.  It does dest = b + a.
  The second argument, a, may be of the form neg ( a1 ), in which case
  we use sub.
*/

static void addsub
    PROTO_N ( ( sha, a, b, dest, stack ) )
    PROTO_T ( shape sha X where a X where b X where dest X ash stack )
{
    exp e = a.wh_exp ;
    if ( name ( e ) == neg_tag ) {
      bop ( sub, sha, son ( e ), b.wh_exp, dest, stack ) ;
    }
    else {
      bop ( add, sha, e, b.wh_exp, dest, stack ) ;
    }
    return ;
}


/*
  Some constructs only set the overflow bit for 32 bit results.
  This checks values of other varieties to determine whether or not an
  overflow has occured
*/
void check_unset_overflow
    PROTO_N ( (dest,shp) )
    PROTO_T ( where dest X shape shp )
{
  exp max_val = getexp(shp,nilexp,0,nilexp,nilexp,0,range_max(shp),
		       val_tag);
  exp min_val = getexp(shp,nilexp,0,nilexp,nilexp,0,range_min(shp),
		       val_tag);
  bool sw;
  move(shp,dest,D0);
  if(is_signed(shp) && (shape_size(shp) < 32)) {
    ins1((shape_size(shp) == 16)?m_extl : m_extbl,32,D0,1);
  }
  sw = cmp(is_signed(shp)?slongsh:ulongsh,D0,zw(max_val),tst_gr);
  test_overflow2(branch_ins(tst_gr,sw,is_signed(shp),is_floating(name(shp))));

  sw = cmp(is_signed(shp)?slongsh:ulongsh,D0,zw(min_val),tst_ls);
  test_overflow2(branch_ins(tst_ls,sw,is_signed(shp), is_floating(name(shp))));

  kill_exp(max_val,max_val);
  kill_exp(min_val,min_val);
  return;
}


/*
  MAIN OPERATION CODING ROUTINE

  This routine creates code to evaluate e, putting the result into dest.
  The stack argument describes the current stack position.
*/

void codec
    PROTO_N ( ( dest, stack, e ) )
    PROTO_T ( where dest X ash stack X exp e )
{
    if ( e == nilexp ) {
	error ( "Internal coding error" ) ;
	return ;
    }

    switch ( name ( e ) ) {

	case plus_tag : {
	    /*
	       Addition is treated similarly to logical operations -
	       see the routine logop above.  It takes a variable number
	       of arguments in the form of a bro-list starting with
	       the son of e.  Each argument may be of the form
	       neg ( x ).
	    */
	    exp arg1 = son ( e ) ;	/* First argument */
	    exp arg2 = bro ( arg1 ) ;	/* Second argument */
	    exp s, t, u, v ;
	    where w ;
            int prev_ov ;

	    if ( last ( arg1 ) ) {
		/* One argument */
		coder ( dest, stack, arg1 ) ;
		return ;
	    }

	    prev_ov = set_overflow ( e ) ;

	    if ( last ( arg2 ) ) {
		/* Two arguments */
		addsub ( sh ( e ), zw ( arg2 ), zw ( arg1 ), dest, stack ) ;
		clear_overflow ( prev_ov ) ;
		return ;
	    }

	    /* Three or more arguments - use D1 */
	    t = arg1 ;
	    regsinproc |= regmsk ( REG_D1 ) ;
	    s = sim_exp ( sh ( e ), D1 ) ;
	    w = zw ( s ) ;

	    /* Look for the non-operand if there is one */
	    while ( 1 ) {
		if ( !is_o ( name ( t ) ) &&
		     ( name ( t ) != neg_tag ||
		       !is_o ( name ( son ( t ) ) ) ) ) break ;
		if ( last( t ) ) {
		    t = nilexp ;
		    break ;
		}
		t = bro( t ) ;
	    }
	    if ( t == nilexp && name ( arg1 ) == neg_tag &&
		 name ( arg2 ) == neg_tag ) t = arg1 ;

	    /* Deal with the case where all the arguments are operands */
	    if ( t == nilexp ) {
		t = bro ( arg2 ) ;
		/* Deal with the first two arguments */
		if ( name ( arg1 ) == neg_tag ) {
		    addsub ( sh ( e ), zw ( arg1 ), zw ( arg2 ),
			     ( ( t == e ) ? dest : w ), stack ) ;
		} else {
		    addsub ( sh ( e ), zw ( arg2 ), zw ( arg1 ),
			     ( ( t == e ) ? dest : w ), stack ) ;
		}
		if ( t == e ) {
		    clear_overflow ( prev_ov ) ;
		    return ;
		}
		/* Deal with the third, fourth, ... arguments */
		while ( !last ( t ) ) {
		    u = bro ( t ) ;
		    addsub ( sh ( e ), zw ( t ), w, w, stack ) ;
		    t = u ;
		}
		/* Deal with the last argument */
		addsub ( sh ( e ), zw ( t ), w, dest, stack ) ;
		retcell ( s ) ;
		if ( have_cond == 3 ) have_cond = 1 ;
		clear_overflow ( prev_ov ) ;
		return ;
	    }

	    /* Deal with the case where one argument is a non-operand */
	    coder ( w, stack, t ) ;
	    u = arg1 ;
	    while ( 1 ) {
		v = bro ( u ) ;
		if ( t != u ) {
		    if ( last ( u ) || ( v == t && last ( v ) ) ) {
			addsub ( sh ( e ), zw ( u ), w, dest, stack ) ;
		    } else {
			addsub ( sh ( e ), zw ( u ), w, w, stack ) ;
		    }
		}
		if ( last ( u ) ) break ;
		u = v ;
	    }
	    retcell ( s ) ;
	    if ( have_cond == 3 ) have_cond = 1 ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

#ifndef tdf3

          case addptr_tag : {
             exp pointer = son ( e ) ;
             exp offset  = son ( pointer ) ;

             make_comment("addptr_tag ...") ;
             mova ( zw ( e ), dest ) ;
             make_comment("addptr_tag done") ;
             return ;
          }
#endif
	case chvar_tag : {
	    /* Change variety, the son of e, a, gives the argument */
	    exp a = son ( e ) ;
	    int prev_ov = set_overflow(e);
	    if ( !is_o ( name ( a ) ) ) {
		/* If a is not an operand */
		if ( whereis ( dest ) != Dreg ) {
		    /* If dest is not a D register, code a into D1 */
		    where w ;
		    exp s = sim_exp ( sh ( a ), D1 ) ;
		    w = zw ( s ) ;
		    regsinproc |= regmsk ( REG_D1 ) ;
		    coder ( w, stack, a ) ;
		    /* Preform the change variety on D1 */
		    change_var ( sh ( e ), w, dest ) ;
		    retcell ( s ) ;
		    if ( have_cond == 3 ) have_cond = 1 ;
		    clear_overflow ( prev_ov ) ;
		    return ;
		}
		/* If dest is a D register, code a into dest */
		coder ( dest, stack, a ) ;
		/* Preform the change variety on dest */
		change_var_sh ( sh ( e ), sh ( a ), dest, dest ) ;
		clear_overflow ( prev_ov ) ;
		return ;
	    }
	    /* If a is an operand, call change_var directly */
	    change_var ( sh ( e ), zw ( a ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case minus_tag : {
	    /* Minus, subtract pointer etc are binary operations */
	    int prev_ov = set_overflow ( e ) ;
	    bop ( sub, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}
#ifndef tdf3
        case make_stack_limit_tag :
#endif
	case subptr_tag :
	case minptr_tag : {
	    /* Minus, subtract pointer etc are binary operations */
	    bop ( sub, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	    return ;
	}

	case mult_tag : {
	    /* Multiply is treated as a logical operation */
	    int prev_ov = set_overflow ( e ) ;
	    logop ( mult, e, dest, stack ) ;
	    if (!optop(e)&&(name(sh(e))!=slonghd)&&(name(sh(e))!=ulonghd)) {
	      check_unset_overflow(dest,sh(e));
	    }
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case div0_tag :
	case div2_tag : {
	    /* Division is a binary operation */
	  int prev_ov = set_overflow(e);
	  bop ( div2, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	  if (!optop(e)&&(name(sh(e))!=slonghd)&&(name(sh(e))!=ulonghd)) {
	    check_unset_overflow(dest,sh(e));
	  }
	  clear_overflow( prev_ov );
	  return ;
	}

	case div1_tag : {
	    /* Division is a binary operation */
	  int prev_ov = set_overflow(e);
	  bop ( div1, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	  if (!optop(e)&&(name(sh(e))!=slonghd)&&(name(sh(e))!=ulonghd)) {
	    check_unset_overflow(dest,sh(e));
	  }
	  clear_overflow( prev_ov );
	  return ;
	}

	case neg_tag : {
	    /* Negation is a unary operation */
	    int prev_ov = set_overflow ( e ) ;
	    uop ( negate, sh ( e ), son ( e ), dest, stack ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case abs_tag : {
           /* Abs is a unary operation */
           int prev_ov = set_overflow(e);
           uop ( absop, sh ( e ), son ( e ), dest, stack ) ;
           clear_overflow( prev_ov ) ;
           return ;
	}

	case shl_tag : {
	    /* Shifting left is a binary operation */
	    int prev_ov = set_overflow ( e ) ;
	    bop ( shift, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case shr_tag : {
	    /* Shifting right is a binary operation */
	    bop ( rshift, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	    return ;
	}

	case mod_tag : {
	    /* Remainder is a binary operation */
	    int prev_ov = set_overflow ( e ) ;
	    bop ( rem1, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case rem0_tag :
	case rem2_tag : {
	    /* Remainder is a binary operation */
	    int prev_ov = set_overflow ( e ) ;
	    bop ( rem2, sh ( e ), bro ( son ( e ) ), son ( e ),
		  dest, stack ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case round_tag : {
	    /* Rounding a floating point number is a unary operation */
	    int prev_ov = set_overflow ( e ) ;
	    set_continue(e);
	    crt_rmode = round_number ( e ) ;
	    uop ( round_float, sh ( e ), son ( e ), dest, stack ) ;
	    clear_overflow ( prev_ov ) ;
	    clear_continue(e);
	    return ;
	}

	case fmult_tag : {
	    /* Floating multiplication is a floating binary operation */
	    exp f1 = son ( e ) ;
	    exp f2 = bro ( f1 ) ;
	    int prev_ov = set_overflow ( e ) ;
	    if(last(f2)) {
	      /* two arguments */
	      fl_binop ( fmult_tag, sh ( e ), zw ( f1 ), zw ( f2 ), dest ) ;
	    }
	    else {
	      /* more than two arguments; use %fp1.  Assumes that all
	       parameters are operands */
	      where w;
	      exp s = sim_exp(sh(e), FP1);
	      regsinproc |= regmsk(REG_FP1);
	      w = zw(s);

	      fl_binop(fmult_tag,sh(e),zw(f1),zw(f2),w);
	      while(!last(f2)) {
		f2 = bro(f2);
		fl_binop(fmult_tag,sh(e),w,zw(f2),(last(f2)?dest:w));
	      }
	    }

	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case fminus_tag : {
	    /* Floating subtraction is a floating binary operation */
	    exp f1 = son ( e ) ;
	    exp f2 = bro ( f1 ) ;
	    int prev_ov = set_overflow ( e ) ;
	    fl_binop ( fminus_tag, sh ( e ), zw ( f2 ), zw ( f1 ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case fdiv_tag : {
	    /* Floating division is a floating binary operation */
	    exp f1 = son ( e ) ;
	    exp f2 = bro ( f1 ) ;
	    int prev_ov = set_overflow ( e ) ;
	    fl_binop ( fdiv_tag, sh ( e ), zw ( f2 ), zw ( f1 ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case fneg_tag : {
	    /* Floating negation is simple */
	    int prev_ov = set_overflow ( e ) ;
	    negate_float ( sh ( e ), zw ( son ( e ) ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case fabs_tag : {
	    /* Floating absolute value is simple */
	    int prev_ov = set_overflow ( e ) ;
	    abs_float ( sh ( e ), zw ( son ( e ) ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case float_tag : {
	    /* Casting to a floating point number is simple */
	    int prev_ov = set_overflow ( e ) ;
	    int_to_float ( sh ( e ), zw ( son ( e ) ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case chfl_tag : {
	    /* Changing a floating variety is simple */
	    int prev_ov = set_overflow ( e ) ;
	    change_flvar ( sh ( e ), zw ( son ( e ) ), dest ) ;
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	case and_tag : {
	    /* And is a logical operation */
	    logop ( and, e, dest, stack ) ;
	    return ;
	}

	case or_tag : {
	    /* Or is a logical operation */
	    logop ( or, e, dest, stack ) ;
	    return ;
	}

	case xor_tag : {
	    /* Xor is a logical operation */
	    logop ( xor, e, dest, stack ) ;
	    return ;
	}

	case not_tag : {
	    /* Not is a unary operation */
	    uop ( not, sh ( e ), son ( e ), dest, stack ) ;
	    return ;
	}

	case absbool_tag : {
	    /* The setcc instruction is not used */
	    error ( "Not implemented" ) ;
	    return ;
	}

	case fplus_tag : {
	    /* Floating addition is similar to integer addition */
	    exp f1 = son ( e ) ;	/* First argument */
	    exp f2 = bro ( f1 ) ;	/* Second argument */
	    exp t ;
	    long count_dest = 2 ;
	    exp de = dest.wh_exp ;

	    int prev_ov = set_overflow ( e ) ;

	    if ( last ( f1 ) ) {
		/* If there is only one argument things are simple */
		move ( sh ( e ), zw ( f1 ), dest ) ;
		clear_overflow ( prev_ov ) ;
		return ;
	    }

	    if ( last ( f2 ) ) {
		/* If there are two arguments code directly */
		if ( name ( f2 ) == fneg_tag ) {
		    f2 = son ( f2 ) ;
		    fl_binop ( fminus_tag, sh ( e ), zw ( f2 ),
			       zw ( f1 ), dest ) ;
		} else {
		    fl_binop ( fplus_tag, sh ( e ), zw ( f1 ),
			       zw ( f2 ), dest ) ;
		}
		clear_overflow ( prev_ov ) ;
		return ;
	    }

	    if ( last ( bro ( f2 ) ) &&
		 name ( bro ( f2 ) ) == real_tag &&
		 name ( dest.wh_exp ) != apply_tag
              && name ( dest.wh_exp ) != tail_call_tag
              && name ( dest.wh_exp ) != apply_general_tag ) {
		/* If there are 3 arguments, the last of which is constant */
		if ( name ( f2 ) == fneg_tag ) {
		    f2 = son ( f2 ) ;
		    fl_binop ( fminus_tag, sh ( e ), zw ( f2 ),
			       zw ( f1 ), dest ) ;
		    fl_binop ( fplus_tag, sh ( e ), zw ( bro ( f2 ) ),
			       dest, dest ) ;
		} else {
		    fl_binop ( fplus_tag, sh ( e ), zw ( f1 ),
			       zw ( f2 ), dest ) ;
		    fl_binop ( fplus_tag, sh ( e ), zw ( bro ( f2 ) ),
			       dest, dest ) ;
		}
		clear_overflow ( prev_ov ) ;
		return ;
	    }

	    if ( name ( de ) == ass_tag &&
		 name ( son ( de ) ) == name_tag &&
		 ( ( props ( son ( son ( de ) ) ) & 0x9 ) == 0x9 ) ) {
		count_dest = 0 ;
		t = f1 ;
		if ( eq_where ( dest, zw ( t ) ) ) count_dest++ ;
		while ( !last ( t ) ) {
		    t = bro ( t ) ;
		    if ( name ( t ) == fneg_tag ) {
			if ( eq_where ( zw ( son ( t ) ), dest ) )
			    count_dest = 2 ;
		    } else {
			if ( eq_where ( zw ( t ), dest ) ) count_dest++ ;
		    }
		}
	    }

	    if ( count_dest < 2 && (name ( dest.wh_exp ) != apply_tag
                                &&  name ( dest.wh_exp ) != tail_call_tag
                                &&  name ( dest.wh_exp ) != apply_general_tag) ) {
		if ( count_dest == 1 ) {
		    t = f1 ;
		} else {
		    if ( name ( f2 ) == fneg_tag ) {
			exp m = son ( f2 ) ;
			fl_binop ( fminus_tag, sh ( e ), zw ( m ),
				   zw ( f1 ), dest ) ;
		    } else {
			fl_binop ( fplus_tag, sh ( e ), zw ( f1 ),
				   zw ( f2 ), dest ) ;
		    }
		    t = bro ( f2 ) ;
		}

		for ( ; ; ) {
		    where tw ;
		    if ( name ( t ) == fneg_tag ) {
			tw = zw ( son ( t ) ) ;
			if ( !eq_where ( dest, tw ) ) {
			    fl_binop ( fminus_tag, sh ( e ), tw, dest, dest ) ;
			}
		    } else {
			tw = zw ( t ) ;
			if ( !eq_where ( dest, tw ) ) {
			    fl_binop ( fplus_tag, sh ( e ), tw, dest, dest ) ;
			}
		    }
		    if ( last ( t ) ) break ;
		    t = bro ( t ) ;
		}
	    } else {
		if ( name ( f2 ) == fneg_tag ) {
		    fl_binop ( fminus_tag, sh ( e ), zw ( son ( f2 ) ),
			       zw ( f1 ), FP0 ) ;
		} else {
		    fl_binop ( fplus_tag, sh ( e ), zw ( f1 ),
			       zw ( f2 ), FP0 ) ;
		}
		t = bro ( f2 ) ;
		while ( !last ( t ) ) {
		    if ( name ( t ) == fneg_tag ) {
			fl_binop ( fminus_tag, sh ( e ), zw ( son ( t ) ),
				   FP0, FP0 ) ;
		    } else {
			fl_binop ( fplus_tag, sh ( e ), zw ( t ), FP0, FP0 ) ;
		    }
		    t = bro ( t ) ;
		}
		if ( name ( t ) == fneg_tag ) {
		    fl_binop ( fminus_tag, sh ( e ), zw ( son ( t ) ),
			       FP0, dest ) ;
		} else {
		    fl_binop ( fplus_tag, sh ( e ), zw ( t ), FP0, dest ) ;
		}
	    }
	    clear_overflow ( prev_ov ) ;
	    return ;
	}

	/*
	     Note : in the following offset operations I have put the
	     shape as slongsh rather than sh ( e ).  This is because
	     the system stddef.h wrongly says that ptrdiff_t is unsigned
	     and I don't trust people to put it right when making up
	     TDF libraries.  If this was right sh ( e ) would be slongsh.
	*/

	case offset_add_tag : {
           make_comment("offset_add_tag...");
	    /* Offset addition is a binary operation */
	    bop ( add, slongsh, son ( e ), bro ( son ( e ) ), dest, stack ) ;
           make_comment("offset_add_tag done");
	    return ;
	}

	case offset_subtract_tag : {
	    /* Offset subtraction is a binary operation */
	    bop ( sub, slongsh, bro ( son ( e ) ), son ( e ), dest, stack ) ;
	    return ;
	}

	case offset_mult_tag : {
           make_comment("offset_mult_tag...");
	    /* Offset multiplication is a binary operation */
	    bop ( mult, slongsh, son ( e ), bro ( son ( e ) ), dest, stack ) ;
           make_comment("offset_mult_tag done");
	    return ;
	}

	case offset_negate_tag : {
	    /* Offset negation is a unary operation */
	    uop ( negate, slongsh, son ( e ), dest, stack ) ;
	    return ;
	}

	case offset_div_tag :
        case offset_div_by_int_tag : {
	  /* Offset division is a binary operation */
	  if(name(sh(bro(son(e)))) < slonghd){
	    exp changer = me_u3(slongsh,bro(son(e)),chvar_tag);
	    bro(son(e)) = changer;
	  }
	  bop ( div2, slongsh, bro ( son ( e ) ), son ( e ), dest, stack ) ;
	  return ;
	}

	case offset_pad_tag : {
           /* Pad an operand */
           exp  cur_offset = son ( e ) ;
           long cur_align  = al2 ( sh ( cur_offset ) ) ;
           long next_align = al2 ( sh ( e ) ) ;

           make_comment("offset_pad ...") ;

           /* does current alignment include next alignment? */

           if ( cur_align  >= next_align ) {

	      if( ( next_align !=1 ) || ( cur_align ==1 ) ) {
                 coder ( dest, stack, cur_offset ) ;
	      }
	      else {
                 /* left shift */
                 shift( sh(e), mnw(3), zw(cur_offset),dest);
	      }

           } else {
              /* cur_align  < next_align */
              where r ;
              if ( whereis ( dest ) == Dreg ) {
                 r = dest ;
              } else {
                 r = D1 ;
                 regsinproc |= regmsk ( REG_D1 ) ;
              }
              codec ( r, stack, cur_offset ) ;

              if( cur_align == 1){
                 add ( slongsh, mnw ( next_align - 1 ), r, r ) ;
                 and ( slongsh, mnw ( -next_align ), r, dest ) ;
                 rshift(sh(e),mnw(3),dest,dest);
              }
              else {
                 long al = next_align / 8 ;
                 add ( slongsh, mnw ( al - 1 ), r, r ) ;
                 and ( slongsh, mnw ( -al ), r, dest ) ;
              }
           }
           make_comment("offset_pad done") ;
           return ;
	}

	case bitf_to_int_tag : {
	    if ( whereis ( dest ) == Dreg ) {
		coder ( dest, stack, son ( e ) ) ;
		change_var_sh ( sh ( e ), sh ( son ( e ) ), dest, dest ) ;
	    } else {
		regsinproc |= regmsk ( REG_D1 ) ;
		coder ( D1, stack, son ( e ) ) ;
		change_var_sh ( sh ( e ), sh ( son ( e ) ), D1, dest ) ;
	    }
	    return ;
	}

	case int_to_bitf_tag : {
	    where r ;
	    long nbits = shape_size ( sh ( e ) ) ;
	    long mask = lo_bits [ nbits ] ;
	    r = ( whereis ( dest ) == Dreg ? dest : D0 ) ;
	    move ( slongsh, zw ( son ( e ) ), r ) ;
	    and ( slongsh, mnw ( mask ), r, dest ) ;
	    return ;
	}
	case offset_max_tag :
	case max_tag : {
	    /* Maximum */
	    bop ( maxop, sh ( e ), son ( e ), bro ( son ( e ) ), dest, stack ) ;
	    return ;
	}

	case min_tag : {
	    /* Minimum */
	    bop ( minop, sh ( e ), son ( e ), bro ( son ( e ) ), dest, stack ) ;
	    return ;
	}

	case cont_tag : {
           make_comment("cont_tag ...") ;

           if ( name ( sh ( e ) ) == bitfhd ) {
              bitf_to_int ( e, sh ( e ), dest, stack ) ;
              return ;
           }

           move ( sh ( e ), zw ( e ), dest ) ;

           make_comment("cont_tag done") ;
           return ;
	}

	default : {

	    if ( !is_o ( name ( e ) ) ) {
		/* If e is not an operand, code e into a register */
		exp s ;
		where w ;
		if (   name ( e ) == apply_tag
                    || name ( e ) == apply_general_tag
                    || name ( e ) == tail_call_tag ) {
		    s = sim_exp ( sh ( e ), D0 ) ;
		} else {
		    if ( whereis ( dest ) == Dreg ) {
/*			error ( "Untested optimization" ) ;*/
			s = sim_exp ( sh ( e ), dest ) ;
		    } else {
			regsinproc |= regmsk ( REG_D1 ) ;
			s = sim_exp ( sh ( e ), D1 ) ;
		    }
		}
		w = zw ( s ) ;

		coder ( w, stack, e ) ;

		/* Move the value of this register into dest */
		move ( sh ( e ), w, dest ) ;
		retcell ( s ) ;
		if ( have_cond == 3 ) have_cond = 1 ;
		return ;
	    }

	    if ( name ( e ) == reff_tag && shape_size ( sh ( e ) ) != 32 ) {
		/* Deal with pointers to bitfields */
                exp s ;
		where d ;
/*                s = sim_exp ( sh ( e ), D0 ) ; */
		d = mw ( dest.wh_exp, dest.wh_off + 32 ) ;
		if ( shape_size ( sh ( son ( e ) ) ) == 32 ) {
                    make_comment("Pointer to bitfield (32) ...") ;
		    coder ( dest, stack, son ( e ) ) ;
		    move ( slongsh, mnw ( no ( e ) ), d ) ;
                    make_comment("Pointer to bitfield (32) done") ;
		    return ;
		}
		make_comment("Pointer to bitfield ...") ;
		coder ( dest, stack, son ( e ) ) ;
		add ( slongsh, mnw ( no ( e ) ), d, d ) ;
		make_comment("Pointer to bitfield done") ;
		return ;
	    }

	    if ( name ( e ) == reff_tag &&
		 ( name ( son ( e ) ) == name_tag ||
		 ( name ( son ( e ) ) == cont_tag &&
		   name ( son ( son ( e ) ) ) == name_tag ) ) ) {
		/* Deal with pointers with offsets */
		long off = no ( e ) / 8 ;
                make_comment("reff_tag ...");
		add ( slongsh, zw ( son ( e ) ), mnw ( off ), dest ) ;
                make_comment("reff_tag done");
		return ;
	    }

	    if ( ( name ( e ) == name_tag && isvar ( son ( e ) ) ) ||
		 name ( e ) == reff_tag){
	      /* Deal with pointers */
	      mova ( zw ( e ), dest ) ;
	      return ;
	    }

	    if ( name ( e ) == clear_tag ) {
		/* Deal with clear shapes */
		char sn = name ( sh ( e ) ) ;
		if ( sn >= shrealhd && sn <= doublehd ) {
		    move ( sh ( e ), fzero, dest ) ;
		}
#ifndef tdf3
                if(name (dest.wh_exp) == apply_tag ||
                   name (dest.wh_exp) == apply_general_tag ||
                   name (dest.wh_exp) == tail_call_tag ) {
                   move ( sh ( e ), zero, dest ) ;
                }
#endif
		return ;
	    }

	    if (name(e) == val_tag && ((name(sh(e)) == s64hd) ||
				      name(sh(e)) == u64hd)){
	      flt64 bval;
	      where w;
	      bval = exp_to_f64(e);
              if ( eq_where ( dest, D0_D1 ) ) {
                 move_const(slongsh,32,bval.big, D1);
                 move_const(slongsh,32,bval.small, D0);
              }
              else {
                 w = dest;
                 move_const(sh(e),32,bval.small,w);
                 w.wh_off += 32;
                 move_const(sh(e),32,bval.big,w);
              }
	      return;
	    }


	    /* If all else fails, use move */
	    if ( name ( e ) == top_tag ) return ;

	    move ( sh ( e ), zw ( e ), dest ) ;
	    return ;
	}
    }
}
