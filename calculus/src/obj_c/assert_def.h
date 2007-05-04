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

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.2)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

/* Assertion function definitions */

#ifndef assert_calculus
static void
assert_calculus
(char *s, char *fn, int ln)
{
    (void)fprintf(stderr, "Assertion %s failed, %s, line %d.\n", s, fn, ln);
    abort();
}
#endif

calculus *
check_null_calculus
(calculus *p, char *fn, int ln)
{
    if (p == NULL) assert_calculus("Null pointer", fn, ln);
    return(p);
}

calculus *
check_tag_calculus
(calculus *p, unsigned t, char *fn, int ln)
{
    p = check_null_calculus(p, fn, ln);
    if (p->ag_tag != t) assert_calculus("Union tag", fn, ln);
    return(p);
}

calculus *
check_tag_etc_calculus
(calculus *p, unsigned tl, unsigned tb X char *fn X int ln)
{
    p = check_null_calculus(p, fn, ln);
    if (p->ag_tag < tl || p->ag_tag >= tb) {
	assert_calculus("Union tag", fn, ln);
    }
    return(p);
}

#endif
