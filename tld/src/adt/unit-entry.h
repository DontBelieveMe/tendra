/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * unit-entry.h - Unit set table entry ADT.
 *
 * See the file "unit-entry.c" for more information.
 */

#ifndef H_UNIT_ENTRY
#define H_UNIT_ENTRY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "map-table.h"
#include "shape-table.h"
#include "tdf-write.h"

typedef struct UnitT {
    struct UnitT	       *next;
    MapTableT *		map_table;
    NStringT			contents;
} UnitT;

typedef struct UnitEntryT {
    struct UnitEntryT	       *next;
    NStringT			key;
    unsigned			order;
    UnitT *		head;
    UnitT *	       *tail;
} UnitEntryT;

typedef struct UnitSetClosureT {
    unsigned			num_unit_sets;
    ShapeTableT *		shapes;
} UnitSetClosureT;

extern void			unit_set_contents
(UnitT *, NStringT *);
extern MapTableT *	unit_map_table
(UnitT *);

extern UnitEntryT *	unit_entry_create
(NStringT *, UnitEntryT *, unsigned);
extern UnitEntryT *	unit_entry_next
(UnitEntryT *);
extern NStringT *		unit_entry_key
(UnitEntryT *);
extern unsigned			unit_entry_order
(UnitEntryT *);
extern UnitT *		unit_entry_add_unit
(UnitEntryT *, unsigned);

extern void			unit_entry_do_count
(UnitEntryT *, void *);
extern void			unit_entry_write_unit_set
(UnitEntryT *, UnitEntryT *, TDFWriterT *);
extern void			unit_entry_write_tld_unit
(UnitEntryT *, ShapeTableT *, TDFWriterT *);
extern void			unit_entry_write_units
(UnitEntryT *, ShapeTableT *, unsigned, TDFWriterT *);

#endif /* !defined (H_UNIT_ENTRY) */
