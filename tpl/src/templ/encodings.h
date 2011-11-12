/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

    
    
    
    
    

#ifndef ENCODING_INCLUDED
#define ENCODING_INCLUDED


@use all
@loop sort
@if sort.simple
/* CONSTRUCTS FOR %ST */
@loop sort.cons

@if cons.params
#define o_%CN(%
@loop cons.param
 p%PE,%
@end
%b )\
@else
#define o_%CN\
@endif
@if cons.token
    TOK_APP (\
@if cons.extends
	out_extendable_int((unsigned long)e_%CN, (unsigned)%SB),\
@else
	out_basic_int((unsigned long)e_%CN, (unsigned)%SB),\
@endif
	s_%SN, p0, p1)
@else
@if cons.cond
    TDF_COND (\
@if cons.extends
	out_extendable_int((unsigned long)e_%CN, (unsigned)%SB),\
@else
	out_basic_int((unsigned long)e_%CN, (unsigned)%SB),\
@endif
	s_%SN, p0, p1, p2)
@else
    {\
@if sort.basic
@if cons.extends
	out_extendable_int((unsigned long)e_%CN, (unsigned)%SB);\
@else
	out_basic_int((unsigned long)e_%CN, (unsigned)%SB);\
@endif
@endif
@loop cons.param
@if param.sort.compound
	o_%PSN(p%PE);\
@else
	p%PE;\
	ASSERT_SORT(s_%PSN);\
@endif
@end
	SET_RSORT(s_%SN);\
    }
@endif
@endif
@end


@endif
@end
/* CONSTRUCTS FOR COMPOUND SORTS */

@loop sort
@if sort.option
#define o_%SN(p)	%40tTDF_OPTION(p, s_%SSN)
@else
@if sort.list
#define o_%SN(p)	%40tTDF_LIST(p, s_%SSN)
@else
@if sort.slist
#define o_%SN(p)	%40tTDF_SLIST(p, s_%SSN)
@endif
@endif
@endif
@end


#endif
