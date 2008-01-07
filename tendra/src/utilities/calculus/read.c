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


#define calculus_IO_ROUTINES
#include "config.h"
#include "read.h"
#include "calculus.h"
#include "cstring.h"
#include "common.h"
#include "fmm.h"
#include "msgcat.h"
#include "output.h"


/*
 *    BITMASKS
 *
 *    This array gives the masks for each bit value.
 */

unsigned long bitmask [ CHAR_BIT ];


/*
 *    INITIALISE MASKS
 *
 *    This routine initialises the array of bitmasks.  This is done
 *    dynamically rather than statically in case CHAR_BIT is not 8.
 */

void
init_bitmask(void)
{
    int i;
    for (i = 0; i < CHAR_BIT; i++) bitmask [i] = MASK (i);
    return;
}


/*
 *    INPUT FILE
 *
 *    These variables describe the input file.  There is a one byte input
 *    buffer.
 */

static FILE *input_file;
static unsigned long input_buff = 0;
static int input_bits = 0;


/*
 *    READ A NUMBER OF BITS
 *
 *    This routine reads the next n bits from the input file.
 */

static unsigned long
read_bits(int n)
{
    int b = input_bits;
    unsigned long m = input_buff;
    unsigned long r = 0;
    while (n) {
		if (b == 0) {
			/* Read next byte */
			int c = getc (input_file);
			if (c == EOF) {
				MSG_premature_eof ();
			} else {
				m = (((unsigned long) c) & MASK (CHAR_BIT));
			}
			b = CHAR_BIT;
		}
		if (n >= b) {
			r = (r << b) | m;
			n -= b;
			b = 0;
		} else {
			int c = b - n;
			r = (r << n) | (m >> c);
			m &= bitmask [c];
			n = 0;
			b = c;
		}
    }
    input_bits = b;
    input_buff = m;
    return (r);
}


/*
 *    READ AN INTEGER
 *
 *    This routine reads an integer from the input file.  This is encoded
 *    as a sequence of octal digits with a marker bit for the end of the
 *    number.
 */

static unsigned long
read_int(void)
{
    unsigned long r = 0, d;
    while (d = read_bits (4), (d & 0x08) == 0) {
		r = (r << 3) | d;
    }
    r = (r << 3) | (d & 0x07);
    return (r);
}


/*
 *    READ A STRING
 *
 *    This routine reads an integer from the input file.  This is encoded
 *    as the string length followed by the characters comprising the
 *    string (8 bits each).
 */

static char
*read_string(void)
{
    unsigned long i, n = read_int ();
    char *s = fmm_malloc(n + 1, memtype_str);

    for (i = 0; i < n; i++) {
		s [i] = (char) read_bits (8);
    }
    s [n] = 0;
    return (s);
}


/*
 *    READ A FILENAME
 *
 *    File names are just strings, however they are buffered to save
 *    space.
 */

static char
*read_filename(void)
{
    char *s;
    static char *last_filename = "????";
    if (read_bits (1)) {
		s = last_filename;
    } else {
		s = read_string ();
		last_filename = s;
    }
    return (s);
}


/*
 *    AUTOMATICALLY GENERATED DISK READING ROUTINES
 *
 *    The main disk reading routines are automatically generated.  The
 *    various macros are used to customise these routines.
 */

#define READ_BITS(N)		((unsigned) read_bits (N))
#define READ_ALIAS()		((unsigned) read_int ())
#define READ_DIM()		((unsigned) read_int ())
#define READ_int()		((int) read_int ())
#define READ_number()		((number) read_int ())
#define READ_string()		read_string ()
#define READ_name_string()	read_filename ()
#define READ_zero_int()		0

#include "read_def.h"


/*
 *    READ AN INPUT FILE
 *
 *    This routine reads an algebra from the input file nm.
 */

void
read_file(char *nm)
{
    char *s;

    /* Open file */
    crt_line_no = -1;
    crt_file_name = nm;
    input_file = fopen (nm, "rb");
    if (input_file == NULL) {
		MSG_cant_open_input_file (nm);
		return;
    }
    init_bitmask ();
    input_buff = 0;
    input_bits = 0;

    /* Confirm file header */
    s = READ_string ();
    if (!streq (s, calculus_NAME)) {
		MSG_invalid_file_header_identifier ();
    }
    s = READ_string ();
    if (!streq (s, calculus_VERSION)) {
		MSG_invalid_file_header_version (s);
    }

    /* Read the algebra */
    algebra->name = READ_string ();
    algebra->major_no = READ_int ();
    algebra->minor_no = READ_int ();
    algebra->types = READ_list_ptr_type ();
    clear_calculus_alias ();

    /* Extract lists of primitives etc */
    LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type (t);
		switch (TAG_type (t0)) {
	    case type_primitive_tag : {
			PRIMITIVE_P p = DEREF_ptr (type_primitive_prim (t0));
			CONS_ptr (p, algebra->primitives, algebra->primitives);
			break;
	    }
	    case type_ident_tag : {
			IDENTITY_P p = DEREF_ptr (type_ident_id (t0));
			CONS_ptr (p, algebra->identities, algebra->identities);
			break;
	    }
	    case type_enumeration_tag : {
			ENUM_P p = DEREF_ptr (type_enumeration_en (t0));
			CONS_ptr (p, algebra->enumerations, algebra->enumerations);
			break;
	    }
	    case type_structure_tag : {
			STRUCTURE_P p = DEREF_ptr (type_structure_struc (t0));
			CONS_ptr (p, algebra->structures, algebra->structures);
			break;
	    }
	    case type_onion_tag : {
			UNION_P p = DEREF_ptr (type_onion_un (t0));
			CONS_ptr (p, algebra->unions, algebra->unions);
			break;
	    }
		}
    }

    /* Close file */
    (void)fclose (input_file);
    return;
}
