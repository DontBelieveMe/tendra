/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/**** dstring.h --- String manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a string manipulation facility.  There
 * are two types of strings supported: nstrings (strings are stored as a
 * length, and a vector of characters), and dstrings which are only of use
 * when it is necessary to append characters to a string one at a time with
 * reasonable efficiency.
 *
 * Null pointers are not valid as nstrings or dstrings. Passing a null pointer
 * as the argument to a function will have an undefined effect (on many
 * machines the program will abort, but this is not guaranteed).
 *
 ***=== TYPES ================================================================
 *
 ** Type:	NStringT
 ** Type:	NStringP
 ** Repr:	<private>
 *
 * This is the nstring type.  These strings may contain null characters.
 *
 ** Type:	DStringT
 ** Type:	DStringP
 ** Repr:	<private>
 *
 * This is the dstring type.  It is only for appending characters and C
 * strings to.  Once it has been completely initialised, it should be
 * converted to one of the other string types.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			nstring_init
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function initialises the specified nstring to be an empty nstring.
 *
 ** Function:	void			nstring_init_length
 *			PROTO_S ((NStringP nstring, unsigned length))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified nstring to be an nstring of the
 * specified length.  The initial contents are unspecified.
 *
 ** Function:	void			nstring_assign
 *			PROTO_S ((NStringP to, NStringP from))
 ** Exceptions:
 *
 * This function assigns the from nstring to the to nstring.  The from nstring
 * should not be used afterwards, without reinitialising it.
 *
 ** Function:	void			nstring_copy_cstring
 *			PROTO_S ((NStringP nstring, CStringP cstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified nstring from the content of the
 * specified cstring.
 *
 ** Function:	void			nstring_insert_cstring
 *			PROTO_S ((NStringP nstring, CStringP cstring))
 ** Exceptions:
 *
 * This function inserts the specified cstring into the specified nstring.
 * Sufficient characters are copied to fill up the nstring.
 *
 ** Function:	void			nstring_copy
 *			PROTO_S ((NStringP to, NStringP from))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the specified from nstring into the specified to
 * nstring.
 *
 ** Function:	CStringP		nstring_to_cstring
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated cstring copy of the specified
 * nstring.  If the nstring contains null characters, then the characters
 * after the first null will be ignored in the cstring (although they will
 * still be part of it).
 *
 ** Function:	unsigned		nstring_hash_value
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function returns the hash value associated with the specified nstring.
 * This value is guaranteed to be identical for all nstrings with the same
 * content.
 *
 ** Function:	unsigned		nstring_length
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function returns the length of the specified nstring.
 *
 ** Function:	CStringP		nstring_contents
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function returns the contents of the specified nstring.
 *
 ** Function:	CmpT			nstring_compare
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns ``CMP_LT'', ``CMP_EQ'', or ``CMP_GT'', depending on
 * whether the content of nstring1 is lexicographically less than, equal to,
 * or greater than the content of nstring2.
 *
 ** Function:	BoolT			nstring_equal
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns true if the specified nstrings have the same content,
 * and false otherwise.
 *
 ** Function:	BoolT			nstring_ci_equal
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns true if the specified nstrings have the same content
 * (ignoring differences in case), and false otherwise.
 *
 ** Function:	BoolT			nstring_contains
 *			PROTO_S ((NStringP nstring, char c))
 ** Exceptions:
 *
 * This function returns true if the specified nstring contains the specified
 * character, and false otherwise.
 *
 ** Function:	BoolT			nstring_is_prefix
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns true if the second nstring is a prefix of the first
 * nstring, and false otherwise.
 *
 ** Function:	void			nstring_destroy
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function deallocates the contents of the specified nstring.
 *
 ** Function:	void			write_nstring
 *			PROTO_S ((OStreamP stream, NStringP nstring))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the content of the specified nstring to the specified
 * ostream.
 *
 ** Function:	void			dstring_init
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified dstring to be an empty dstring.
 *
 ** Function:	unsigned		dstring_length
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:
 *
 * This function returns the length of the specified dstring.
 *
 ** Function:	void			dstring_append_char
 *			PROTO_S ((DStringP dstring, char c))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified character to the specified dstring.
 *
 ** Function:	void			dstring_append_cstring
 *			PROTO_S ((DStringP dstring, CStringP cstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the content of the specified cstring to the specified
 * dstring.
 *
 ** Function:	void			dstring_append_nstring
 *			PROTO_S ((DStringP dstring, NStringP nstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the content of the specified nstring to the specified
 * dstring.
 *
 ** Function:	BoolT			dstring_last_char_equal
 *			PROTO_S ((DStringP dstring, char c))
 ** Exceptions:
 *
 * This function returns true if the last character of the specified dstring
 * is the same as the specified character, and false otherwise.  If the
 * dstring is empty, then false is always returned.
 *
 ** Function:	void			dstring_to_nstring
 *			PROTO_S ((DStringP dstring, NStringP nstring_ref))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the content of the specified dstring into the
 * specified nstring.
 *
 ** Functions:	CStringP		dstring_to_cstring
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the content of the specified dstring into a
 * dynamically allocated cstring, and returns it.
 *
 ** Function:	CStringP		dstring_destroy_to_cstring
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function does the equivalent of a call to ``dstring_to_cstring''
 * followed by a call to ``dstring_destroy''.  It returns a cstring that is
 * normally the internal cstring of the dstring (if there isn't enough room
 * for a null character at the end, then the cstring will need to be
 * reallocated).
 *
 ** Function:	void			dstring_destroy
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:
 *
 * This function deallocates the contents of the specified dstring.
 *
 **** Change log:*/

/****************************************************************************/

#ifndef H_DSTRING
#define H_DSTRING

#include "os-interface.h"
#include "cstring.h"
#include "dalloc.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct NStringT {
    unsigned			length;
    CStringP			contents;
} NStringT, *NStringP;

typedef struct DStringT {
    unsigned			length;
    unsigned			max_length;
    CStringP			contents;
} DStringT, *DStringP;

/*--------------------------------------------------------------------------*/

extern void			nstring_init
	PROTO_S ((NStringP));
extern void			nstring_init_length
	PROTO_S ((NStringP, unsigned));
extern void			nstring_assign
	PROTO_S ((NStringP, NStringP));
extern void			nstring_copy_cstring
	PROTO_S ((NStringP, CStringP));
extern void			nstring_insert_cstring
	PROTO_S ((NStringP, CStringP));
extern void			nstring_copy
	PROTO_S ((NStringP, NStringP));
extern CStringP			nstring_to_cstring
	PROTO_S ((NStringP));
extern unsigned			nstring_hash_value
	PROTO_S ((NStringP));
extern unsigned			nstring_length
	PROTO_S ((NStringP));
extern CStringP			nstring_contents
	PROTO_S ((NStringP));
extern CmpT			nstring_compare
	PROTO_S ((NStringP, NStringP));
extern BoolT			nstring_equal
	PROTO_S ((NStringP, NStringP));
extern BoolT			nstring_ci_equal
	PROTO_S ((NStringP, NStringP));
extern BoolT			nstring_contains
	PROTO_S ((NStringP, char));
extern BoolT			nstring_is_prefix
	PROTO_S ((NStringP, NStringP));
extern void			nstring_destroy
	PROTO_S ((NStringP));

extern void			write_nstring
	PROTO_S ((OStreamP, NStringP));

extern void			dstring_init
	PROTO_S ((DStringP));
extern unsigned			dstring_length
	PROTO_S ((DStringP));
extern void			dstring_append_char
	PROTO_S ((DStringP, char));
extern void			dstring_append_cstring
	PROTO_S ((DStringP, CStringP));
extern void			dstring_append_nstring
	PROTO_S ((DStringP, NStringP));
extern BoolT			dstring_last_char_equal
	PROTO_S ((DStringP, char));
extern void			dstring_to_nstring
	PROTO_S ((DStringP, NStringP));
extern CStringP			dstring_to_cstring
	PROTO_S ((DStringP));
extern CStringP			dstring_destroy_to_cstring
	PROTO_S ((DStringP));
extern void			dstring_destroy
	PROTO_S ((DStringP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define nstring_length(s) ((s)->length)
#define nstring_contents(s) ((s)->contents)
#define dstring_length(s) ((s)->length)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_DSTRING) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
