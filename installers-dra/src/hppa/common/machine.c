/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include <construct/shapemacs.h>

#include "expmacs.h"
#include "regable.h"

/*
    DOES A PROCEDURE RETURN THE GIVEN SHAPE IN A REGISTER?
*/

int
reg_result(shape sha)
{
    if ( valregable ( sha ) ) return 1;
    if ( is_floating ( name ( sha ) ) ) {
#if use_long_double
	if ( shape_size ( sha ) > 64 ) return 0;
#endif
	return 1;
    }
    return 0;
}


/*
    NAME PREFIXES
*/

char *local_prefix = "" ;
char *name_prefix = "" ;
