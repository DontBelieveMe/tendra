/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**** file-name.h --- File name manipulation routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file defines some file name manipulation routines.  It should be
 * replaced on operating systems with a different file name syntax to that
 * used here ('/' separated path names).
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	char *		file_name_basename
 *			PROTO_S ((char *path))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the file name
 * component of the specifed path.
 *
 ** Function:	char *		file_name_dirname
 *			PROTO_S ((char *path))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the directory name
 * component of the specifed path.
 *
 ** Function:	char *		file_name_expand
 *			PROTO_S ((char *dir, char *name,
 *				  char *suffix))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the path name
 * obtained by expanding the specified name in the specified dir.  If the
 * suffix is non nil, it is also appended to the path name, following the
 * suffix seperator character.
 *
 ** Function:	char *		file_name_is_basename
 *			PROTO_S ((char *path))
 ** Exceptions:
 *
 * This function returns true if the specified path has no directory
 * component.
 *
 ** Function:	char *		file_name_is_absolute
 *			PROTO_S ((char *path))
 ** Exceptions:
 *
 * This function returns true if the specified path is an absolute path name.
 *
 ** Function:	void			file_name_populate
 *			PROTO_S ((char *path))
 ** Exceptions:
 *
 * This function tries to create all of the directories on the specified path.
 * The final component of the path is considered to be a file, and is not
 * created as a directory.  There is no confirmation of whether the function
 * succeeds or not - this must be determined in another manner.
 *
 **** Change Log:*/

/****************************************************************************/

#ifndef H_FILE_NAME
#define H_FILE_NAME

#include "config.h"
#include "dalloc.h"

/*--------------------------------------------------------------------------*/

extern char *			file_name_basename(char *);
extern char *			file_name_dirname(char *);
extern char *			file_name_expand(char *, char *, char *);
extern BoolT			file_name_is_basename(char *);
extern BoolT			file_name_is_absolute(char *);
extern void			file_name_populate(char *);

#endif /* !defined (H_FILE_NAME) */
