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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/


#define SPARCTRANS_CODE
#include "config.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "tags.h"
#include "move.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "common_types.h"
#include "regmacs.h"
#include "regexps.h"
#include "myassert.h"
#include "comment.h"
#include "flags.h"
#ifdef NEWDWARF
#include "dw2_config.h"
#include "dw2_extra.h"
#endif


/*
    ARRAY OF REGISTER-EXP ASSOCIATIONS

    0-31 represent the fixed point registers, 32-47 the floating point
    registers.
*/

regpeep regexps [48] ;


/*
    ARE TWO SHAPES OF THE SAME SIZE, ALIGNMENT AND FLOATING-POINT-NESS?
*/

bool eq_sze 
    PROTO_N ( ( as, bs ) )
    PROTO_T ( shape as X shape bs )
{
    if ( is_floating ( name ( as ) ) ) {
	return ( ( bool ) ( name ( as ) == name ( bs ) ) ) ;
    }
    if ( is_floating ( name ( bs ) ) ) {
	return ( 0 ) ;
    }
    return ( ( bool ) ( shape_size ( as ) == shape_size ( bs ) &&
			shape_align ( as ) == shape_align ( bs ) ) ) ;
}


/*
    ARE TWO LISTS OF EXPRESSIONS SIMILAR?
*/

bool sim_explist 
    PROTO_N ( ( al, bl ) )
    PROTO_T ( exp al X exp bl )
{
    if ( al == nilexp && bl == nilexp ) return ( 1 ) ;
    if ( al == nilexp || bl == nilexp ) return ( 0 ) ;
    if ( !sim_exp ( al, bl ) ) return ( 0 ) ;
    if ( last ( al ) && last ( bl ) ) return ( 1 ) ;
    if ( last ( al ) || last ( bl ) ) return ( 0 ) ;
    return ( sim_explist ( bro ( al ), bro ( bl ) ) ) ;
}


/*
    ARE TWO EXPRESSIONS SIMILAR?

    Basically this is the same as eq_exp except that equal shapes requirement
    is weakened to equal size and alignment.
*/

bool sim_exp 
    PROTO_N ( ( a, b ) )
    PROTO_T ( exp a X exp b )
{
    if ( name ( a ) == name ( b ) ) {
	if ( name ( a ) == name_tag ) {
	    return ( ( bool ) ( son ( a ) == son ( b ) &&
				no ( a ) == no ( b ) &&
				eq_sze ( sh ( a ), sh ( b ) ) ) ) ;
	}
	if ( !is_a ( name ( a ) ) || !eq_sze ( sh ( a ), sh ( b ) ) ) {
	    return ( 0 ) ;
	}
	return ( ( bool ) ( no ( a ) == no ( b ) &&
			    sim_explist ( son ( a ), son ( b ) ) 
			    && ((name(a) != current_env_tag) || 
				(props(a) == props(b)))));
    }
    return ( 0 ) ;
}


/*
    FORGET ALL REGISTER-EXP ASSOCIATIONS
*/

void clear_all 
    PROTO_Z ()
{
    int i ;
    for ( i = 0 ; i < 48 ; i++ ) {
	regexps [i].keptexp = nilexp ;
	setregalt ( regexps [i].inans, 0 ) ;
#ifdef NEWDWARF
	if (dwarf2)
	  dw_close_regassn (i);
#endif
    }
    return ;
}


/*
    FORGET THE EXP ASSOCIATED WITH REGISTER i
*/

void clear_reg 
    PROTO_N ( ( i ) )
    PROTO_T ( int i )
{
    i = ABS_OF ( i ) ;
    if ( i >= 0 && i < 48 ) {
	regexps [i].keptexp = nilexp ;
	setregalt ( regexps [i].inans, 0 ) ;
#ifdef NEWDWARF
	if (dwarf2)
	  dw_close_regassn (i);
#endif
    }
    return ;
}


/*
    HAS AN EXPRESSION ALREADY BEEN EVALUATED INTO A REGISTER?
*/

ans iskept 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    int i ;
    ans nilans ;
    setregalt ( nilans, 0 ) ;

#ifdef NO_KEPT_OPTS
    /* no register tracking */
    return ( nilans ) ;
#endif

    if ( name ( sh ( e ) ) == cpdhd ) {
	/* Tracking of unions is unsafe */
	return ( nilans ) ;
    }

    for ( i = 0 ; i < 48 ; i++ ) {
	exp ke = regexps [i].keptexp ;
	bool isc = regexps [i].iscont ;

	if ( ke != nilexp ) {
	    /* there is an association with register i? */
	    if ( ( ( !isc && sim_exp ( ke, e ) ) ||
		 ( name ( e ) == cont_tag && isc &&
		   eq_sze ( sh ( ke ), sh ( e ) ) &&
		   sim_exp ( ke, son ( e ) )  && 
		   al1(sh(son(e))) == al1(sh(ke))  ) ) ) {
		ans aa ;
		aa = regexps [i].inans ;

		switch ( discrim ( aa ) ) {

		    case notinreg : {
			if ( !aa.val.instoreans.adval ) {
			    /* the expression is given indirectly, it may
			       also be in another register */
			    continue ;
			}
			/* FALL THROUGH */
		    }

		    default : {
#ifdef NEWDWARF
			if (dwarf2)
			  dw_used_regassn (i);
#endif
			return ( aa ) ;
		    }
		}
	    } else if ( name ( ke ) == cont_tag && !isc ) {
		ans aq ;

		aq = regexps [i].inans ;
		if ( discrim ( aq ) == notinreg ) {
		    instore is ;
		    is = insalt ( aq ) ;
		    if ( !is.adval && is.b.offset == 0 &&
			 IS_FIXREG ( is.b.base ) &&
			 sim_exp ( son ( ke ), e ) ) {
			/* the contents of required expression is here as
			   a register-offset */
#ifdef NEWDWARF
			if (dwarf2)
			  dw_used_regassn (i);
#endif
			is.adval = 1 ;
			setinsalt ( aq, is ) ;
			return ( aq ) ;
		    }
		}
	    } else if ( name ( ke ) == reff_tag && !isc ) {
		ans aq ;
		aq = regexps [i].inans ;
		if ( discrim ( aq ) == notinreg ) {
		    instore is ;
		    is = insalt ( aq ) ;
		    if ( is.adval && is.b.offset == ( no ( ke ) / 8 ) &&
			 IS_FIXREG ( is.b.base ) &&
			 sim_exp ( son ( ke ), e ) ) {
			/* a ref selection of required expression is here as
			   a register-offset */
#ifdef NEWDWARF
			if (dwarf2)
			  dw_used_regassn (i);
#endif
			is.adval = 1 ;
			is.b.offset = 0 ;
			setinsalt ( aq, is ) ;
			return ( aq ) ;
		    }
		}
	    }
	}
    }
    return ( nilans ) ;
}


/*
    SET UP AN EXP-LOCATION ASSOCIATION
*/

void keepexp 
    PROTO_N ( ( e, loc ) )
    PROTO_T ( exp e X ans loc )
{
    int reg ;

    /* Find the register number */
    switch ( discrim ( loc ) ) {
	case insomereg :
	case insomefreg : {
	    fail ( "Illegal location in keepexp" ) ;
	    return ;
	}
	case inreg : {
	    reg = regalt ( loc ) ;
	    break ;
	}
	case infreg : {
	    reg = fregalt ( loc ).fr + 32 ;
	    break ;
	}
	case notinreg : {
	    reg = insalt ( loc ).b.base ;
	    if ( !IS_FIXREG ( reg ) ) return ;
	    break ;
	}
    }

    assert ( reg >= 0 && reg < 48 ) ;
    assert ( reg != R_TMP ) ;
    regexps [ reg ].keptexp = e ;
    regexps [ reg ].inans = loc ;
    regexps [ reg ].iscont = 0 ;
#ifdef NEWDWARF
    if (dwarf2)
	dw_init_regassn (reg);
#endif
    return ;
}


/*
    SET UP A CONTENTS-REGISTER ASSOCIATION
*/

void keepcont 
    PROTO_N ( ( e, regcode ) )
    PROTO_T ( exp e X int regcode )
{
    freg fr ;
    int reg = ABS_OF ( regcode ) ;
    assert ( reg >= 0 && reg < 48 ) ;
    assert ( reg != R_TMP ) ;

    if ( reg > 31 ) {
	fr.dble = ( bool ) ( regcode < 0 ) ;
	fr.fr = reg - 32 ;
	setfregalt ( regexps [ reg ].inans, fr ) ;
    } else {
	instore is ;
	is.b.base = regcode ;
	is.b.offset = 0 ;
	is.adval = 1 ;
	setinsalt ( regexps [ reg ].inans, is ) ;
    }

    regexps [ reg ].keptexp = e ;
    regexps [ reg ].iscont = 1 ;
#ifdef NEWDWARF
    if (dwarf2)
	dw_init_regassn (reg);
#endif
    return ;
}


/*
    SET UP AN EXP-REGISTER ASSOCIATION
*/

void keepreg 
    PROTO_N ( ( e, regcode ) )
    PROTO_T ( exp e X int regcode )
{
    freg fr ;
    int reg = ABS_OF ( regcode ) ;
    assert ( reg >= 0 && reg < 48 ) ;
    assert ( reg != R_TMP ) ;

    if ( reg > 31 ) {
	fr.dble = ( bool ) ( regcode < 0 ) ;
	fr.fr = reg - 32 ;
	setfregalt ( regexps [ reg ].inans, fr ) ;
    } else {
	instore is ;
	is.b.base = regcode ;
	is.b.offset = 0 ;
	is.adval = 1 ;
	setinsalt ( regexps [ reg ].inans, is ) ;
    }

    regexps [ reg ].keptexp = e ;
    regexps [ reg ].iscont = 0 ;
#ifdef NEWDWARF
    if (dwarf2)
	dw_init_regassn (reg);
#endif
    return ;
}


/*
    COULD e BE lhs?
*/

bool couldbe 
    PROTO_N ( ( e, lhs ) )
    PROTO_T ( exp e X exp lhs )
{
    unsigned char ne = name ( e ) ;
    exp s = son ( e ) ;

    if ( ne == name_tag ) {
	if ( lhs != 0 && s == son ( lhs ) ) return ( 1 ) ;
	if ( isvar ( s ) ) 
	  return ( ( bool ) ( lhs == 0 && 
			     (isvis ( s ) || isglob(s)))) ;
	if ( name ( s ) == proc_tag ) return ( ( bool ) ( lhs == 0 ) ) ;
	if ( son ( s ) == nilexp ) return ( 1 ) ;
	return ( couldbe ( son ( s ), lhs ) ) ;
    }
    if ( ne == cont_tag ) {
	if ( lhs != 0 && name ( s ) == name_tag && son ( s ) != nilexp ) {
	    return ( ( bool ) ( son ( s ) == son ( lhs ) ||
				isvis ( son ( lhs ) ) ||
				isvis ( son ( s ) ) ) ) ;
	}
	return ( 1 ) ;
    }
    if ( ne == reff_tag || ne == field_tag ) {
	return ( couldbe ( s, lhs ) ) ;
    }
    if ( ne == addptr_tag || ne == subptr_tag ) {
	return ( ( bool ) ( couldbe ( s, lhs ) ||
			    couldeffect ( bro ( s ), lhs ) ) ) ;
    }
    return ( 1 ) ;

}

/*
    COULD AN ALTERATION TO z EFFECT e?
*/

bool couldeffect 
    PROTO_N ( ( e, z ) )
    PROTO_T ( exp e X exp z )
{
    unsigned char ne = name ( e ) ;

    if ( ne == cont_tag ) return ( couldbe ( son ( e ), z ) ) ;
    if ( ne == name_tag ) {
	if ( isvar ( son ( e ) ) ) {
	    return ( ( bool ) ( z == 0 && isvis ( son ( e ) ) ) ) ;
	}
	if ( name ( son ( e ) ) == proc_tag ) return ( 0 ) ;
	if ( son ( son ( e ) ) == nilexp ) return ( 1 ) ;
	return ( couldeffect ( son ( son ( e ) ), z ) ) ;

    }
    if ( ne < plus_tag || ne == contvol_tag ) return ( 1 ) ;

    e = son ( e ) ;
    while ( e != nilexp ) {
	if ( couldeffect ( e, z ) ) return ( 1 ) ;
	if ( last ( e ) ) return ( 0 ) ;
	e = bro ( e ) ;
    }
    return ( 0 ) ;
}


/*
    DOES e DEPEND ON z?
*/

bool dependson 
    PROTO_N ( ( e, isc, z ) )
    PROTO_T ( exp e X bool isc X exp z )
{
    if (e == nilexp) {
	return 0;
    }
    for ( ; ; ) {
	if ( name ( z ) == reff_tag || name ( z ) == addptr_tag ||
	     name ( z ) == subptr_tag ) {
	    z = son ( z ) ;
	}
	if ( name ( z ) != name_tag ) {
	    if ( name ( z ) != cont_tag ) return ( 1 ) ;
	    z = 0 ;
	    break ;
	}
	
	if ( isvar ( son ( z ) ) ) break ;
	if ( name ( son ( z ) ) == proc_tag ) {
	    z = 0 ;
	    break ;
	}
	if ( son ( son ( z ) ) == nilexp ) {
	    /* can it happen? */
	    return ( 1 ) ;
	}
	z = son ( son ( z ) ) ;
    }

    /* z is now unambiguous variable name or 0 (meaning some contents) */
    return ( ( bool ) ( isc ? couldbe ( e, z ) : couldeffect ( e, z ) ) ) ;
}


/*
    REMOVE ASSOCATIONS OF ANY REGISTERS DEPENDING ON lhs
*/

void clear_dep_reg 
    PROTO_N ( ( lhs ) )
    PROTO_T ( exp lhs )
{
  int i ;
  for ( i = 0 ; i < 48 ; i++ )
  {
    if (regexps[i].keptexp != nilexp)
      switch(name(regexps[i].keptexp))
      {
       case val_tag:
       case null_tag:
       case real_tag:
       case string_tag:
       case name_tag:
	if (!regexps[i].iscont)
	{			/* constant value, cannot be changed
				   by assign */
	  continue;
	}
       default:
	if ( dependson ( regexps [i].keptexp, regexps [i].iscont, lhs ) ) 
	{	
	  regexps [i].keptexp = nilexp ;
	  setregalt ( regexps [i].inans, 0 ) ;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_close_regassn (i);
#endif
	}
      }
  }
  return ;
}
