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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: sortmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/12/04  19:50:10  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.2  1997/08/23  13:31:04  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef sortmacs_key
#define sortmacs_key



/* code numbers for each of the TDF sorts */

#define ALIGNMENT_SORT 1
#define BITFIELD_VARIETY 2
#define BOOL 3
#define ERROR_TREATMENT 4
#define EXP_S 5
#define FLOATING_VARIETY 6
#define LABEL 7 
#define NAT 8
#define NTEST 9
#define ROUNDING_MODE 10
#define SHAPE 11
#define SIGNED_NAT 12
#define TAG  13
#define VARIETY 14
#define TOKEN 15
#define AL_TAG 16
#define DIAG_FILENAME 17	/* OLD DIAGS */
#define DIAG_TYPE_SORT 18	/* OLD DIAGS */
#define FOREIGN 19
#define ACCESS_SORT 20
#define TRANSFER_MODE_SORT 21
#define PROCPROPS 22
#define STRING 23
#define DG_SORT 24		/* NEW DIAGS */
#define DG_DIM_SORT 25		/* NEW DIAGS */
#define DG_FILENAME_SORT 26	/* NEW DIAGS */
#define DG_IDNAME_SORT 27	/* NEW DIAGS */
#define DG_NAME_SORT 28		/* NEW DIAGS */
#define DG_TYPE_SORT 29		/* NEW DIAGS */



#endif