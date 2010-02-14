/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/*
 * main.c - tld program main routine.
 *
 * This file contains the main routine for the TDF linker.  It performs
 * argument parsing, and then calls one of "builder_main", "contents_main",
 * "extract_main" or "linker_main" to do the actual work.  See the files in
 * the "frontends" directory for more details.
 */

#include <stdlib.h>
#include <errno.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/error.h>
#include <exds/dstring.h>
#include <exds/istream.h>

#include "check/check.h"
#include "error/error.h"

#include "adt/name-key.h"
#include "adt/arg-data.h"
#include "adt/solve-cycles.h"

#include "frontend/builder.h"
#include "frontend/contents.h"
#include "frontend/extract.h"
#include "frontend/linker.h"

#include "rename-file.h"
#include "debug.h"
#include "arg-parse.h"
#include "fmt.h"

#define PROGNAME "tld"
#define PROGVER  "4.0#7"

#define USAGE "\
\tusage:[mode][option ...]file ...\n\
\twhere mode is one of: '-mc'(create library), '-ml'(link capsules),\n\
\t'-mt'(library table of contents)or '-mx'(extract from library),\n\
\tand option(for the current mode - default '-ml')is one of:"
#ifndef VERSION
#define VERSION PROGNAME " version " PROGVER
#endif /* !defined (VERSION) */
#ifndef RELEASE
#define RELEASE "LOCAL"
#endif /* !defined (RELEASE) */
#ifndef BANNER
#define BANNER ""
#endif /* !defined (BANNER) */

typedef enum {
    MODE_BUILDER,
    MODE_CONTENTS,
    MODE_EXTRACT,
    MODE_LINKER
} ModeT;

static BoolT    main_used_one_off = FALSE;
static BoolT    main_used_other   = FALSE;
static ArgDataT main_arg_data;

static void
main_print_version(void)
{
    write_cstring(ostream_error, VERSION);
    write_cstring(ostream_error, " (");
    write_cstring(ostream_error, RELEASE);
    write_cstring(ostream_error, ")");
    write_cstring(ostream_error, BANNER);
    write_newline(ostream_error);
    ostream_flush(ostream_error);
}

static void
main_handle_all(char *  option,			 ArgUsageT *usage, 
			 void *  gclosure, 
			 BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_all(&main_arg_data, enable);
}

static void
main_handle_all_hide_defd(char *  option,				   ArgUsageT *usage, 
				   void *  gclosure, 
				   BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_all_hide_defd(&main_arg_data, enable);
}

static void
main_handle_basename(char *  option,			      ArgUsageT *usage, 
			      void *  gclosure, 
			      BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_basename(&main_arg_data, enable);
}

static void
main_handle_debug_file(char *  option,				ArgUsageT *usage, 
				void *  gclosure, 
				char *  debug_file)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_debug_file(&main_arg_data, debug_file);
}

static void
main_handle_help(char *  option,			  ArgUsageT *usage, 
			  void *  gclosure)
{
    UNUSED(option);
    UNUSED(gclosure);
    main_used_one_off = TRUE;
    write_arg_usage(ostream_error, usage);
    write_newline(ostream_error);
    ostream_flush(ostream_error);
}

static void
main_handle_hide(char *  option,			  ArgUsageT *usage, 
			  void *  gclosure, 
			  char *  shape, 
			  char *  name)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_hide(&main_arg_data, shape, name);
}

static void
main_handle_hide_defined(char *  option,				  ArgUsageT *usage, 
				  void *  gclosure, 
				  char *  shape)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_hide_defined(&main_arg_data, shape);
}

static void
main_handle_index(char *  option,			   ArgUsageT *usage, 
			   void *  gclosure, 
			   BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_content_index(&main_arg_data, enable);
}

static void
main_handle_info(char *  option,			  ArgUsageT *usage, 
			  void *  gclosure, 
			  BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    if (enable) {
	error_set_min_report_severity(ERROR_SEVERITY_INFORMATION);
    } else {
	error_set_min_report_severity(ERROR_SEVERITY_ERROR);
    }
}

static void
main_handle_keep(char *  option,			  ArgUsageT *usage, 
			  void *  gclosure, 
			  char *  shape, 
			  char *  name)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_keep(&main_arg_data, shape, name);
}

static void
main_handle_keep_all(char *  option,			      ArgUsageT *usage, 
			      void *  gclosure, 
			      char *  shape)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_keep_all(&main_arg_data, shape);
}

static void
main_handle_library_file(char *  option,				  ArgUsageT *usage, 
				  void *  gclosure, 
				  char *  library_file)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_library_file(&main_arg_data, library_file);
}

static void
main_handle_match_base(char *  option,				ArgUsageT *usage, 
				void *  gclosure, 
				BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_match_base(&main_arg_data, enable);
}

static void
main_handle_output_file(char *  option,				 ArgUsageT *usage, 
				 void *  gclosure, 
				 char *  output_file)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_output_file(&main_arg_data, output_file);
}

static void
main_handle_library_path(char *  option,				  ArgUsageT *usage, 
				  void *  gclosure, 
				  char *  directory)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_library_path(&main_arg_data, directory);
}

static void
main_handle_rename(char *  option,			    ArgUsageT *usage, 
			    void *  gclosure, 
			    char *  shape, 
			    char *  from, 
			    char *  to)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_parse_rename(&main_arg_data, shape, from, to);
}

static void
main_handle_rename_file(char *  option,				 ArgUsageT *usage, 
				 void *  gclosure, 
				 char *  name)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    rename_file_parse(name, &main_arg_data);
}

static void
main_handle_size(char *  option,			  ArgUsageT *usage, 
			  void *  gclosure, 
			  BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_content_size(&main_arg_data, enable);
}

static void
main_handle_suppress(char *  option,			      ArgUsageT *usage, 
			      void *  gclosure, 
			      char *  shape, 
			      char *  name)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_suppress(&main_arg_data, shape, name);
}

static void
main_handle_suppress_all(char *  option,				  ArgUsageT *usage, 
				  void *  gclosure, 
				  char *  shape)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_add_suppress_all(&main_arg_data, shape);
}

static void
main_handle_suppress_mult(char *  option,				   ArgUsageT *usage, 
				   void *  gclosure, 
				   BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_suppress_mult(&main_arg_data, enable);
}

static void
main_handle_tdf_version(char *  option,				 ArgUsageT *usage, 
				 void *  gclosure, 
				 BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_content_version(&main_arg_data, enable);
}

static void
main_handle_unit_file(char *  option,			       ArgUsageT *usage, 
			       void *  gclosure, 
			       char *  unit_file)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    arg_data_set_unit_file(&main_arg_data, unit_file);
}

static void
main_handle_version(char *  option,			     ArgUsageT *usage, 
			     void *  gclosure)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_one_off = TRUE;
    main_print_version();
}

static void
main_handle_warning(char *  option,			     ArgUsageT *usage, 
			     void *  gclosure, 
			     BoolT     enable)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_used_other = TRUE;
    if (enable) {
	error_set_min_report_severity(ERROR_SEVERITY_WARNING);
    } else {
	error_set_min_report_severity(ERROR_SEVERITY_ERROR);
    }
}

static EStringDataT main_description_strings[] = {
    { {
	"description of all",
	"\n\tEnable/disable extraction of all capsules."
    } }, { {
	"description of all-hide-defined",
	"\n\tEnable/disable hiding of all external names of any shape that have a definition."
    } }, { {
	"description of basename",
	"\n\tEnable/disable extraction of capsules to their basename."
    } }, { {
	"description of debug-file",
	" FILE\n\tWrite debugging output to FILE."
    } }, { {
	"description of help",
	"\n\tDisplay an option summary for the current mode."
    } }, { {
	"description of hide",
	" SHAPE NAME\n\tHide the external SHAPE NAME."
    } }, { {
	"description of hide-defined",
	" SHAPE\n\tHide all external SHAPE names that have a definition."
    } }, { {
	"description of include-library",
	" LIBRARY\n\tInclude the contents of LIBRARY in the output library."
    } }, { {
	"description of index",
	"\n\tEnable/disable the display of the library index as well as the capsule names."
    } }, { {
	"description of info",
	"\n\tEnable/disable informational messages."
    } }, { {
	"description of keep",
	" SHAPE NAME\n\tEnsure that external SHAPE NAME is not hidden."
    } }, { {
	"description of keep-all",
	" SHAPE\n\tEnsure that no external SHAPE is hidden."
    } }, { {
	"description of library-file",
	" FILE\n\tUse FILE as a TDF library."
    } }, { {
	"description of l",
	"FILE\n\tUse FILE as a TDF library."
    } }, { {
	"description of match-basename",
	"\n\tEnable/disable matching capsules by their basename"
    } }, { {
	"description of output-file",
	" FILE\n\tWrite output to FILE(default 'library.tl')."
    } }, { {
	"description of path",
	" DIRECTORY\n\tAppend DIRECTORY to library search path."
    } }, { {
	"description of L",
	"DIRECTORY\n\tAppend DIRECTORY to library search path."
    } }, { {
	"description of rename",
	" SHAPE FROM TO\n\tRename SHAPE FROM to TO."
    } }, { {
	"description of rename-file",
	" FILE\n\tParse FILE as a rename file."
    } }, { {
	"description of size",
	"\n\tEnable/disable the display of the size of library capsules as well as their names."
    } }, { {
	"description of suppress",
	" SHAPE NAME\n\tDo not try to find a definition for SHAPE NAME."
    } }, { {
	"description of suppress-all",
	" SHAPE\n\tDo not try to find a definition for any SHAPE."
    } }, { {
	"description of suppress-mult",
	"\n\tEnable/disable the suppression of multiple definitions as library definitions."
    } }, { {
	"description of tdf-version",
	"\n\tEnable/disable the display of the version of a TDF library."
    } }, { {
	"description of unit-file",
	" FILE\n\tRead unit set names from FILE."
    } }, { {
	"description of version",
	"\n\tDisplay the version number on the standard error."
    } }, { {
	"description of warning",
	"\n\tEnable/disable warning messages."
    } }, ERROR_END_STRING_LIST
};

#ifdef __TenDRA__
/* Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis(pointer-pointer)off
#endif

static ArgListT main_builder_arg_list[] = {
    {
	"debug-file", 'd',			AT_FOLLOWING,
	(ArgProcP)main_handle_debug_file,	NULL,
	{ "description of debug-file" }
    }, {
	"help", '?',				AT_EMPTY,
	(ArgProcP)main_handle_help,		NULL,
	{ "description of help" }
    }, {
	"include-library", 'i',			AT_FOLLOWING,
	(ArgProcP)main_handle_library_file,	NULL,
	{ "description of include-library" }
    }, {
	"output-file", 'o',			AT_FOLLOWING,
	(ArgProcP)main_handle_output_file,	NULL,
	{ "description of output-file" }
    }, {
	"suppress", 's',			AT_FOLLOWING2,
	(ArgProcP)main_handle_suppress,	NULL,
	{ "description of suppress" }
    }, {
	"suppress-all", 'S',			AT_FOLLOWING,
	(ArgProcP)main_handle_suppress_all,	NULL,
	{ "description of suppress-all" }
    }, {
	"suppress-mult", 'M',			AT_PROC_SWITCH,
	(ArgProcP)main_handle_suppress_mult,	NULL,
	{ "description of suppress-mult" }
    }, {
	"unit-file", 'u',			AT_FOLLOWING,
	(ArgProcP)main_handle_unit_file,	NULL,
	{ "description of unit-file" }
    }, {
	"version", 'v',				AT_EMPTY,
	(ArgProcP)main_handle_version,		NULL,
	{ "description of version" }
    }, ARG_PARSE_END_LIST
};

static ArgListT main_contents_arg_list[] = {
    {
	"debug-file", 'd',			AT_FOLLOWING,
	(ArgProcP)main_handle_debug_file,	NULL,
	{ "description of debug-file" }
    }, {
	"help", '?',				AT_EMPTY,
	(ArgProcP)main_handle_help,		NULL,
	{ "description of help" }
    }, {
	"index", 'i',				AT_PROC_SWITCH,
	(ArgProcP)main_handle_index,		NULL,
	{ "description of index" }
    }, {
	"size", 's',				AT_PROC_SWITCH,
	(ArgProcP)main_handle_size,		NULL,
	{ "description of size" }
    }, {
	"tdf-version", 't',			AT_PROC_SWITCH,
	(ArgProcP)main_handle_tdf_version,	NULL,
	{ "description of tdf-version" }
    }, {
	"version", 'v',				AT_EMPTY,
	(ArgProcP)main_handle_version,		NULL,
	{ "description of version" }
    }, ARG_PARSE_END_LIST
};

static ArgListT main_extract_arg_list[] = {
    {
	"all", 'a',				AT_PROC_SWITCH,
	(ArgProcP)main_handle_all,		NULL,
	{ "description of all" }
    }, {
	"basename", 'b',			AT_PROC_SWITCH,
	(ArgProcP)main_handle_basename,	NULL,
	{ "description of basename" }
    }, {
	"debug-file", 'd',			AT_FOLLOWING,
	(ArgProcP)main_handle_debug_file,	NULL,
	{ "description of debug-file" }
    }, {
	"help", '?',				AT_EMPTY,
	(ArgProcP)main_handle_help,		NULL,
	{ "description of help" }
    }, {
	"info", 'i',				AT_PROC_SWITCH,
	(ArgProcP)main_handle_info,		NULL,
	{ "description of info" }
    }, {
	"match-basename", 'm',			AT_PROC_SWITCH,
	(ArgProcP)main_handle_match_base,	NULL,
	{ "description of match-basename" }
    }, {
	"version", 'v',				AT_EMPTY,
	(ArgProcP)main_handle_version,		NULL,
	{ "description of version" }
    }, ARG_PARSE_END_LIST
};

static ArgListT main_linker_arg_list[] = {
    {
	"all-hide-defined", 'a',		AT_PROC_SWITCH,
	(ArgProcP)main_handle_all_hide_defd,	NULL,
	{ "description of all-hide-defined" }
    }, {
	"debug-file", 'd',			AT_FOLLOWING,
	(ArgProcP)main_handle_debug_file,	NULL,
	{ "description of debug-file" }
    }, {
	"help", '?',				AT_EMPTY,
	(ArgProcP)main_handle_help,		NULL,
	{ "description of help" }
    }, {
	"hide", 'h',				AT_FOLLOWING2,
	(ArgProcP)main_handle_hide,		NULL,
	{ "description of hide" }
    }, {
	"hide-defined", 'H',			AT_FOLLOWING,
	(ArgProcP)main_handle_hide_defined,	NULL,
	{ "description of hide-defined" }
    }, {
	"keep", 'k',				AT_FOLLOWING2,
	(ArgProcP)main_handle_keep,		NULL,
	{ "description of keep" }
    }, {
	"keep-all", 'K',			AT_FOLLOWING,
	(ArgProcP)main_handle_keep_all,	NULL,
	{ "description of keep-all" }
    }, {
	"library", '\0',			AT_FOLLOWING,
	(ArgProcP)main_handle_library_file,	NULL,
	{ "description of library-file" }
    }, {
	NULL, 'l',			AT_EITHER,
	(ArgProcP)main_handle_library_file,	NULL,
	{ "description of l" }
    }, {
	"output-file", 'o',			AT_FOLLOWING,
	(ArgProcP)main_handle_output_file,	NULL,
	{ "description of output-file" }
    }, {
	"path", '\0',				AT_FOLLOWING,
	(ArgProcP)main_handle_library_path,	NULL,
	{ "description of path" }
    }, {
	NULL, 'L',			AT_EITHER,
	(ArgProcP)main_handle_library_path,	NULL,
	{ "description of L" }
    }, {
	"rename", 'r',				AT_FOLLOWING3,
	(ArgProcP)main_handle_rename,		NULL,
	{ "description of rename" }
    }, {
	"rename-file", 'R',			AT_FOLLOWING,
	(ArgProcP)main_handle_rename_file,	NULL,
	{ "description of rename-file" }
    }, {
	"suppress", 's',			AT_FOLLOWING2,
	(ArgProcP)main_handle_suppress,	NULL,
	{ "description of suppress" }
    }, {
	"suppress-all", 'S',			AT_FOLLOWING,
	(ArgProcP)main_handle_suppress_all,	NULL,
	{ "description of suppress-all" }
    }, {
	"suppress-mult", 'M',			AT_PROC_SWITCH,
	(ArgProcP)main_handle_suppress_mult,	NULL,
	{ "description of suppress-mult" }
    }, {
	"unit-file", 'u',			AT_FOLLOWING,
	(ArgProcP)main_handle_unit_file,	NULL,
	{ "description of unit-file" }
    }, {
	"version", 'v',				AT_EMPTY,
	(ArgProcP)main_handle_version,		NULL,
	{ "description of version" }
    }, {
	"warnings", 'w',			AT_PROC_SWITCH,
	(ArgProcP)main_handle_warning,		NULL,
	{ "description of warning" }
    }, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

static ModeT
main_init(int    argc,		   char **argv)
{
    EStringT * usage_estring = error_define_string("tld usage message", USAGE);
    ModeT     mode          = MODE_LINKER;
    ArgListT * arg_list      = main_linker_arg_list;
    int       skip;

    error_intern_strings(main_description_strings);
    argc--;
    argv++;
  retry:
    if ((argc > 0) && (argv[0][0] == '-') && (argv[0][1] == 'm')) {
	char c = argv[0][2];

	argc--;
	argv++;
	switch (c) {
	  case 'c':
	    mode     = MODE_BUILDER;
	    arg_list = main_builder_arg_list;
	    arg_data_init(&main_arg_data, "library.tl");
	    break;
	  case 't':
	    mode     = MODE_CONTENTS;
	    arg_list = main_contents_arg_list;
	    arg_data_init(&main_arg_data, NULL);
	    break;
	  case 'x':
	    mode     = MODE_EXTRACT;
	    arg_list = main_extract_arg_list;
	    arg_data_init(&main_arg_data, NULL);
	    break;
	  case 'l':
	    goto linker_case;
	  case 'v':
	    main_used_one_off = TRUE;
	    main_used_other   = FALSE;
	    main_print_version();
	    goto retry;
	  default:
		error(ERROR_FATAL, "illegal mode character '%c'; should be "
			"one of 'c', 'l', 't' or 'x'", 
		argv[0][2]);
	    UNREACHED;
	}
    } else {
      linker_case:
	arg_data_init(&main_arg_data, "capsule.j");
    }
    arg_parse_intern_descriptions(arg_list);
    skip = arg_parse_arguments(arg_list, usage_estring, argc, argv);
    argc -= skip;
    argv += skip;
    if (main_used_one_off && (!main_used_other) && (argc == 0)) {
	exit(EXIT_SUCCESS);
	UNREACHED;
    } else if (argc == 0) {
	error(ERROR_FATAL, "no files specified for processing");
	UNREACHED;
    }
    arg_data_set_files(&main_arg_data, argc, argv);
    arg_data_vector_libraries(&main_arg_data);
    debug_set_file(arg_data_get_debug_file(&main_arg_data));
    return(mode);
}

int
main(int    argc,	      char **argv)
{
	set_progname(PROGNAME, PROGVER);
	fmt_init();

    HANDLE {
	istream_setup();
	ostream_setup();
	switch (main_init(argc, argv)) {
	  case MODE_BUILDER:
	    builder_main(&main_arg_data);
	    break;
	  case MODE_CONTENTS:
	    contents_main(&main_arg_data);
	    break;
	  case MODE_EXTRACT:
	    extract_main(&main_arg_data);
	    break;
	  case MODE_LINKER:
	    linker_main(&main_arg_data);
	    break;
	}
    } WITH {
	ExceptionT *exception = EXCEPTION_EXCEPTION();

	if (exception == XX_dalloc_no_memory) {
		error(ERROR_FATAL, "cannot allocate memory");
	    UNREACHED;
	} else if ((exception == XX_istream_read_error) ||
		  (exception == XX_bistream_read_error)) {
	    char * file = (char *)EXCEPTION_VALUE();

		error(ERROR_FATAL, "error reading from file '%s': %s", 
			file, strerror(errno));
	    UNREACHED;
	} else if ((exception == XX_ostream_write_error) ||
		  (exception == XX_bostream_write_error)) {
	    char * file = (char *)EXCEPTION_VALUE();

		error(ERROR_FATAL, "error writing to file '%s': %s", 
			file, strerror(errno));
	    UNREACHED;
	} else {
	    RETHROW();
	    UNREACHED;
	}
    } END_HANDLE
    exit(EXIT_SUCCESS);
    UNREACHED;
}

