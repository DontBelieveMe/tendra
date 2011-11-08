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


/* 	$Id: addresstypes.h,v 1.1.1.1 1998/01/17 15:55:58 release Exp $	 */


/*
   
  addresstypes.h

  Types for usable addressing modes are defined here :-
  baseoff, instore, freg, ans, where

*/



#ifndef addressingtkey
#define addressingtkey 1


#include "config.h"

#include "exptypes.h"
#include "cross.h"
#include "installtypes.h"
#include "localtypes.h"


struct makeansst {
  int   lab;
  int   regmove;
};
typedef struct makeansst  makeans;

#define NOREG 100

struct baseofft {
  int   base;			/* base register for addressing */
  long  offset;			/* offset in words */
};
typedef struct baseofft baseoff;

typedef struct source_t{
  bool reg;
  int value;
} source;



struct instoret {
  baseoff b;
  bool adval;	/* if true then b is itself an address
		   value i.e not a pointer to a value */
};

typedef struct instoret instore;

typedef enum {
  VAX_single,VAX_double,IEEE_single,IEEE_double
} float_reg_contents;


typedef struct fregt{
  int fr;
  float_reg_contents type;
} freg;


typedef struct somefregt {
  int  *fr;
  float_reg_contents type;
} somefreg;


struct someregt {
  int  *r;
};		
		
typedef struct someregt somereg;


union anstu {
  int   regans;			/* register number */
  freg fregans;
  instore instoreans;
  somefreg somefregans;		
  somereg someregans;
};

enum ansdiscrim {
  inreg, infreg, notinreg,insomereg, insomefreg
};
 /* use to discriminate the above union type */

struct anst {
  enum ansdiscrim discrim;
  union anstu val;
};
typedef struct anst ans;	/* this type used as union of a fixpnt
				   reg, a float reg and an instore 
				   value */

struct wheret {
  ans answhere;			/* reg or store position */
  ash ashwhere;			/* size and alignment, see ashtypes.h */
};

typedef struct wheret where;

struct mmt {
  INT64  maxi;
  INT64  mini;
  char *fmt;
};
typedef struct mmt  mm;

/******************************************************************
macros for ease of use of unions, allow 'hiding' of discriminator.
******************************************************************/

#define regalt(x) (x).val.regans
#define fregalt(x) (x).val.fregans
#define insalt(x) (x).val.instoreans
#define someregalt(x) (x).val.someregans.r;
#define somefregalt(x) (x).val.somefregans;

/* assign to field of union, discriminator set as appropriate */
#define setregalt(x,y) (x).discrim = inreg; (x).val.regans = y
#define setfregalt(x,y) (x).discrim = infreg; (x).val.fregans = y
#define setinsalt(x,y) (x).discrim = notinreg; (x).val.instoreans =y
#define setsomeregalt(x,y) (x).discrim = insomereg; (x).val.someregans.r =y
#define setsomefregalt(x,y) (x).discrim = insomefreg; (x).val.somefregans=y
#endif


