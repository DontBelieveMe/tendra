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


/* linux/diag_config.h */

/**********************************************************************
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:12  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/02/25  12:32:45  release
 * Initial version
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/03/17  18:29:49  pwe
 * stabs diagnostics for solaris and linux
 *
 * Revision 1.2  1995/01/30  12:57:13  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1995/01/27  17:25:32  jmf
 * Initial revision
 *
 * Revision 1.2  1994/07/13  07:59:32  jmf
 * Added Log
 *
**********************************************************************/

#ifndef diag_config_key
#define diag_config_key


typedef long OUTPUT_REC ;
typedef diag_descriptor diag_global ;

#define INSPECT_FILENAME( x )	stab_collect_files ( x )
#define NEW_DIAG_GLOBAL( x )	( x )
#define OUTPUT_DIAG_TAGS()	stab_tagdefs ()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs ()

#define STABS

extern void stab_collect_files PROTO_S ((filename f));
extern void stab_tagdefs PROTO_S((void));
extern void stab_typedefs PROTO_S((void));
extern void init_stab_aux PROTO_S((void));

#endif
