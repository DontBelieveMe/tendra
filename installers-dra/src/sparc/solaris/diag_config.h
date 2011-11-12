/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/solaris/diag_config.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1998/01/09  14:59:58  pwe
 * prep restructure
 *
 * Revision 1.5  1997/10/23  09:33:33  pwe
 * prep extra_diags
 *
 * Revision 1.4  1997/08/23  13:55:10  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/04/17  12:00:21  pwe
 * dwarf2 support
 *
 * Revision 1.2  1997/04/04  15:23:35  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.1  1997/03/24  17:09:57  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.2  1995/09/13  11:01:26  john
 * Fix to prototypes
 *
 * Revision 1.1.1.1  1995/03/13  10:18:58  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:43  djch
 * Initial revision
 *
 * Revision 1.2  93/06/29  14:35:48  14:35:48  ra (Robert Andrews)
 * Minor renaming of diagnostic routines.
 *
 * Revision 1.1  93/06/24  14:59:30  14:59:30  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef STAB_CONF_INCLUDED
#define STAB_CONF_INCLUDED

#include "config.h"

#include "dg_first.h"
#include "diaginfo.h"
#include "exptypes.h"

typedef long OUTPUT_REC;

#ifdef NEWDIAGS

extern int dwarf2;
extern void dw2_proc_start(exp p, dg_name d);
extern void dw2_proc_end(exp p);
extern void dw2_code_info(dg_info d, void(*mcode)(void *), void * args);
extern void dw2_start_basic_block(void);


#define DIAG_VAL_BEGIN(d,g,c,s,e)	if (!dwarf2)\
				  stab_global(d, e, s, g);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,e) if (dwarf2)\
				  dw2_proc_start(e, d);\
				else \
				  stab_proc(d, e, s, g);

#define DIAG_PROC_END(e)	if (dwarf2)\
				  dw2_proc_end(e);\
				else \
				  stab_proc_end();

#define CODE_DIAG_INFO(d,n,x,a)	if (dwarf2)\
				  dw2_code_info(d, x, a);\
				else \
				  code_diag_info(d, x, a);


#define START_BB()		if (dwarf2)\
				  dw2_start_basic_block();


#else

#define DIAG_VAL_BEGIN(d,g,c,s,e)	stab_global(d, e, s, g);

#define DIAG_VAL_END(d)	;

#define DIAG_PROC_BEGIN(d,g,c,s,e)	stab_proc(d, e, s, g);

#define DIAG_PROC_END(e);


#define INSPECT_FILENAME(x)	stab_collect_files(x)
#define NEW_DIAG_GLOBAL(x)	(x)
#define OUTPUT_DIAG_TAGS()	stab_tagdefs()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs()

#endif


#endif /* STAB_CONF_INCLUDED */
