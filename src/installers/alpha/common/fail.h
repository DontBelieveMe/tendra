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


/* 	$Id: fail.h,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

/*
$Log: fail.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:07  john
 * Entered into CVS
 *
 * Revision 1.12  1995/01/12  15:05:48  john
 * Changed error messages
 *
*/


#ifndef FAIL_H
#define FAIL_H
#define MAX_WARNINGS 10
typedef enum {FILE_OPEN,
	      USEAGE,
	      OVERFLOW,
	      CROSS_IMPLEMENTATION,
	      REG_ALLOC,
	      IMPLEMENTATION,
	      INSTRUCTION_OUTPUT,
	      MISC,
	      INTERNAL
	      } fail_conditions;
extern void alphafail PROTO_S ((fail_conditions,char *,char *));
extern void failer PROTO_S ((char *));
  
#define alphawarn(X) fprintf(stderr,"alphatrans: warning!: %s\n",X);

/* Error messages */

#define NO_ERROR_HANDLER       INTERNAL,"Error handler not present",""
#define TAG_NOT_IMPLEMENTED    IMPLEMENTATION,"Unimplemented tag",""
#define BIG_LABEL		IMPLEMENTATION,"64 bit labels not supported",""
#define BIG_MULTIPLICATION	OVERFLOW,"64 bit multiplication failed",""
#define BIG_DIVISION		OVERFLOW,"64 bit division failed",""
#define BIG_ADDITION		OVERFLOW,"64 bit addition failed",""
#define BIG_SUBTRACTION	OVERFLOW,"64 bit subtraction failed",""
#define ILLEGAL_FLAG		USEAGE,"Illegal flag"
#define TOO_FEW_PARAMETERS	USEAGE,"Not enough parameters",""
#define OPENING_T_FILE		INTERNAL,"Cannot open .t file:"
#define CANNOT_OPEN_FILE	FILE_OPEN,""
#define OUT_OF_TREGS		REG_ALLOC,"Too many fixed point t-regs required",""
#define OUT_OF_F_TREGS		REG_ALLOC,"Too many floating point t-regs required",""
#define ILLEGAL_BLOCK_COPY	REG_ALLOC,"illegal block copy.  This should not happen",""
#define NO_DIAGNOSTICS_IN_TDF	INTERNAL,"This TDF does not contain diagnostic information",""
#endif

