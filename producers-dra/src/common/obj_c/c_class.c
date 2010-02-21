/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
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
#include "c_types.h"
#include "error.h"
#include "xalloc.h"


/*
    CHECK FOR CORRECT HEADERS

    The functions defined in this file give the implementations of various
    support functions used by the c_class implementation.  They should
    therefore be compiled with the c_class implementation rather than the
    specification.
*/

#if c_class_SPECIFICATION
FAIL_COMPILER(Implementation functions compiled with token specifications)
#endif


/*
    FREE OBJECTS

    These variables indicate the free c_classes.  There is an array
    containing lists of small blocks, plus a single larger block.
*/

#define SMALL_BLOCK		24
#define ALLOC_BLOCK		2048

#if (c_class_GEN_MAX > SMALL_BLOCK)
FAIL_COMPILER(Free block array is too small)
#endif

static c_class *free_c_classes = NULL;
static unsigned free_c_classes_left = 0;
unsigned total_c_classes = 0;

static c_class *free_c_class_array[SMALL_BLOCK] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/*
    GENERATE A NEW OBJECT BLOCK

    This routine generates a new block of c_classes of size sz.  Small
    blocks are allocated from the c_class array, others from the main
    c_class list.
*/

c_class *
gen_c_class(unsigned sz)
{
	c_class *p;
	unsigned n = sz;
	if (n < SMALL_BLOCK) {
		/* Allocate from small block array */
		if (n == 0) {
			return(NULL);
		}
		p = free_c_class_array[n];
		if (p) {
			free_c_class_array[n] = TAIL_list(p);
			return(p);
		}
	}
	if (n > free_c_classes_left) {
		/* Allocate new blocks */
		unsigned m = ALLOC_BLOCK;
		if (n > m) {
			m = n;
		}
		free_c_classes = xmalloc_nof(c_class, m);
		free_c_classes_left = m;
	}
	p = free_c_classes;
	free_c_classes += n;
	free_c_classes_left -= n;
	return(p);
}


/*
    MARK AN OBJECT AS FREE

    This routine is used in the object destruction routines to mark an
    object as having been freed.  This only has any effect in conjunction
    with the debugging routine below.
*/

#ifdef RUNTIME
#define clean_c_class(P, Z)\
    {\
	ASSERT(TYPEID(P) != TYPEID_free);\
	TYPEID(P) = TYPEID_free ;\
	total_c_classes -= (Z);\
    }
#else
#define clean_c_class(P, Z)	/* empty */
#endif


/*
    GENERATE A NEW OBJECT BLOCK (DEBUG VERSION)

    This routine is identical to gen_c_class except that it includes the
    run-time type information t in the allocated block.
*/

#ifdef RUNTIME

c_class *
debug_c_class(unsigned sz, unsigned t)
{
	c_class *p;
	unsigned n = sz;
	total_c_classes += n;
	if (n < SMALL_BLOCK) {
		/* Allocate from small block array */
		if (n == 0) {
			return(NULL);
		}
		p = free_c_class_array[n];
		if (p) {
			free_c_class_array[n] = TAIL_list(p);
			ASSERT(TYPEID(p) == TYPEID_free);
			TYPEID(p) = t;
			return(p);
		}
	}
	n += 1;
	if (n > free_c_classes_left) {
		/* Allocate new blocks */
		unsigned m = ALLOC_BLOCK;
		if (n > m) {
			m = n;
		}
		free_c_classes = xmalloc_nof(c_class, m);
		free_c_classes_left = m;
	}
	p = free_c_classes + 1;
	TYPEID(p) = t;
	free_c_classes += n;
	free_c_classes_left -= n;
	return(p);
}

#endif /* RUNTIME */


/*
    DESTROY AN OBJECT BLOCK

    This routine destroys the block of c_classes p of size sz.
*/

void
destroy_c_class(c_class *p, unsigned sz)
{
	if (p) {
		unsigned n = sz;
		c_class **r = free_c_class_array;
		if (n < SMALL_BLOCK) {
			r += n;
		}
		clean_c_class(p, n);
		TAIL_list(p) = *r;
		*r = p;
	}
	return;
}


/*
    DUMMY OBJECT BLOCK DESTRUCTOR

    This routine is a dummy destructor which does nothing.
*/

void
dummy_destroy_c_class(c_class *p, unsigned sz)
{
	UNUSED(p);
	UNUSED(sz);
	return;
}


/*
    DESTROY A LIST OF OBJECT BLOCKS

    This routine destroys the list p of blocks of c_classes of size sz.
    The list is added to the appropriate entry of the free c_class array.
*/

void
destroy_c_class_list(c_class *p, unsigned sz)
{
	if (p) {
		c_class *q = p;
		unsigned n = sz + 1;
		c_class **r = free_c_class_array;
		if (n < SMALL_BLOCK) {
			r += n;
		}
		while (TAIL_list(p)) {
			clean_c_class(p, n);
			p = TAIL_list(p);
		}
		clean_c_class(p, n);
		TAIL_list(p) = *r;
		*r = q;
	}
	return;
}


/*
    FIND THE LENGTH OF A LIST

    This routine calculates the length of the list p.
*/

unsigned
length_c_class_list(c_class *p)
{
	unsigned n = 0;
	c_class *q = p;
	while (q) {
		n++;
		q = TAIL_list(q);
	}
	return(n);
}


/*
    REVERSE A LIST

    This routine reverses the order of the list p.
*/

c_class *
reverse_c_class_list(c_class *p)
{
	c_class *r = NULL;
	c_class *q = p;
	while (q) {
		c_class *nq = TAIL_list(q);
		TAIL_list(q) = r;
		r = q;
		q = nq;
	}
	return(r);
}


/*
    APPEND TWO LISTS

    This routine appends the lists of c_class blocks p and q.
*/

c_class *
append_c_class_list(c_class *p, c_class *q)
{
	c_class *r = p;
	if (r == NULL) {
		return(q);
	}
	while (TAIL_list(r)) {
		r = TAIL_list(r);
	}
	TAIL_list(r) = q;
	return(p);
}


/*
    FIND THE LAST MEMBER OF A LIST

    This routine returns the last member of the list of c_class blocks p.
*/

c_class *
end_c_class_list(c_class *p)
{
	c_class *r = p;
	if (r == NULL) {
		return(NULL);
	}
	while (TAIL_list(r)) {
		r = TAIL_list(r);
	}
	return(r);
}


/*
   GENERIC EMPTY VECTOR

   This c_class represents the generic empty vector.  It is only defined
   if vector operations have been enabled.  Note that the element field
   of a vector is not be NULL, even if the vector is empty.
 */

#ifdef VEC
static c_class dummy_elem;
c_class_VEC empty_c_class_vec = {0, {&dummy_elem, &dummy_elem}};
#endif


#ifdef c_class_IO_ROUTINES

/*
   ALIASING VARIABLES

   These variables give respectively the current alias number and the
   list of all aliases.
 */

unsigned crt_c_class_alias = 0;
static c_class *crt_alias_list = NULL;


/*
   SET AN ALIAS

   This routine sets up an alias of p to n.
 */

void
set_c_class_alias(c_class *p, unsigned n)
{
	c_class *q = GEN_c_class(2, TYPEID_list);
	TAIL_list(q) = crt_alias_list;
	HEAD_list(q) ->ag_ptr = p;
	ASSERT(p != NULL);
	p->ag_tag = n;
	crt_alias_list = q;
	return;
}


/*
    FIND AN ALIAS

    This routine searches for alias number n.
*/

c_class *
find_c_class_alias(unsigned n)
{
	c_class *p = crt_alias_list;
	while (p) {
		c_class *q = HEAD_list(p) ->ag_ptr;
		if (q->ag_tag == n) {
			return (q);
		}
		p = TAIL_list(p);
	}
	error(ERROR_INTERNAL, "Can't find alias %u", n);
	return (NULL);
}


/*
    CLEAR ALL ALIASES

    This routine clears all aliases.  Each alias in the list is reset to
    zero, and the list itself is freed.
*/

void
clear_c_class_alias(void)
{
	c_class *p = crt_alias_list;
	c_class *q = NULL;
	while (p) {
		HEAD_list(p)->ag_ptr->ag_tag = 0;
		q = p;
		p = TAIL_list(p);
	}
	if (q) {
		TAIL_list(q) = free_c_class_array[2];
		free_c_class_array[2] = crt_alias_list;
	}
	crt_c_class_alias = 0;
	crt_alias_list = NULL;
	return;
}

#endif /* c_class_IO_ROUTINES */


/*
    ASSERTION ROUTINES

    These routine implement the assertion checks.
*/

#ifdef ASSERTS
#define assert_c_class	assertion
#include "assert_def.h"
#endif
