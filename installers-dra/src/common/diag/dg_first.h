/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dg_first_key
#define dg_first_key

/* breaks type cycles */

#include "config.h"


typedef struct dg_name_t *dg_name;
typedef struct dg_type_t *dg_type;
typedef struct dg_info_t *dg_info;
typedef struct file_t *dg_filename;

#ifdef NEWDIAGS
typedef struct dg_info_t diag_info;
typedef struct dg_name_t diag_global;
#endif

#endif
