/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: addrtypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/08/16  15:38:39  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/***************************************************************** 

		addressingtypes.h

	Types for usable addressing modes are defined here :-
baseoff, instore, freg, ans, where

*****************************************************************/



#ifndef addressingtkey
#define addressingtkey 1

#include "config.h"

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

struct instoret {
  baseoff b;
  bool adval;			/* if true then b is itself an address
				   value i.e not a pointer to a value */
};
typedef struct instoret instore;

struct fregt {
  int   fr;			/* floating point reg (actually fr*2) */
        bool dble;		/* double precision */
};
typedef struct fregt  freg;

struct somefregt {
  int  *fr;
        bool dble;
};
typedef struct somefregt  somefreg;

struct someregt {
  int  *r;
};				/* extra struct is to get over bug in MIPS
				   cc */
typedef struct someregt somereg;


union anstu {
  int   regans;			/* register number */
  freg fregans;
  instore instoreans;
  somefreg somefregans;		
  somereg someregans;
};

enum ansdiscrim {
  inreg, infreg, notinreg, insomereg, insomefreg
};
 /* use to discriminate the above union type */

struct anst {
  enum ansdiscrim discrim;
  union anstu val;
};
typedef struct anst ans;	/* this type used as union of a fixpnt
				   reg, 				
				   a float reg and an instore value */

struct wheret {
  ans answhere;			/* reg or store position */
  ash ashwhere;			/* size and alignment, see ashtypes.h */
};

typedef struct wheret where;

struct mmt {
  long  maxi;
  long  mini;
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
