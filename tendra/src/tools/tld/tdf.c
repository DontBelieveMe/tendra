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


/*** tdf.c --- Miscellaneous TDF routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements various TDF routines used by the TDF linker.
 *
 *** Change Log:
 * $Log$
 * Revision 1.1  2002/01/26 21:32:05  asmodai
 * Initial version of TenDRA 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:41  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:47:02  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:40  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "tdf.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

unsigned
tdf_int_size PROTO_N ((value))
	     PROTO_T (unsigned value)
{
    unsigned size = 1;

    while (value >>= 3) {
	size ++;
    }
    return (size);
}

void
write_usage PROTO_N ((ostream, use))
	    PROTO_T (OStreamP ostream X
		     unsigned use)
{
    CStringP sep = "";

    write_char (ostream, '{');
    if (use & U_DEFD) {
	write_cstring (ostream, "DEFD");
	sep = ", ";
    }
    if (use & U_MULT) {
	write_cstring (ostream, sep);
	write_cstring (ostream, "MULT");
	sep = ", ";
    }
    if (use & U_DECD) {
	write_cstring (ostream, sep);
	write_cstring (ostream, "DECD");
	sep = ", ";
    }
    if (use & U_USED) {
	write_cstring (ostream, sep);
	write_cstring (ostream, "USED");
    }
    write_char (ostream, '}');
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
