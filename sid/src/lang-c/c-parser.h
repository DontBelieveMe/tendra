/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

 * Automatically generated from the files:
 *	c-parser.sid
 * and
 *	c-parser.act
 * by:
 *	sid
 */
/* BEGINNING OF HEADER */
#line 239 "c-parser.act"


	/*
	 * c-parser.h - SID C parser.
	 *
	 * This file specifies the interface to the SID C definition file parser that
	 * is produced from the file "c-parser.sid".
	 */

	#include "../adt/table.h"

	#include "c-lexer.h"
	#include "c-out-info.h"

	CLexerStreamT *c_current_stream;
	COutputInfoT  *c_current_out_info;
	TableT        *c_current_table;

#line 61 "c-parser.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void c_parse_grammar(void);
/* BEGINNING OF TRAILER */

#line 1208 "c-parser.act"


#line 71 "c-parser.h"

/* END OF FILE */
