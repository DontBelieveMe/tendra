/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
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
  dyninit

  This program extracts all the initialisation procedures from a SunOS
  object file.  It then writes out a .s file containing a function
  (___TDF_main) which contains calls to each of these procedures.
  Initialisation procedures are identified by the ___I.TDF prefix.
  Note: the actual prefix starts with two '_'s but SunOS inserts
  an extra one.

  the command line syntax is

  dyninit <name of object file> <name of destination (.s) file>

*/

#include <stdio.h>
#include <sun3/a.out.h>

#define MAJOR_VERSION		1
#define MINOR_VERSION		1

void fail(char *);
FILE *open_file(char *, char *);
#define open_file_read(x)	open_file(x, "r")
#define open_file_write(x)	open_file(x, "w")


FILE *
open_file(char *filename, char *option)
{
  FILE * ret_fp;
  if (ret_fp = fopen(filename, option)) {
    return ret_fp;
  }
  else{
    fprintf(stderr, "Cannot open file <%s>\n", filename);
    exit(1);
  }
}


typedef struct exec EXEC_STRUCT;

typedef struct nlist SYMBOL_STRUCT;

#define INIT_FUNC_NAME "___TDF_main"

EXEC_STRUCT header;
SYMBOL_STRUCT symbol;


void
fail(char *message)
{
  fprintf(stderr, "*fail* : %s\n", message);
  exit(1);
}


/*#define symbol_is_function(x) (x.n_type & N_TEXT)*/
#define is_intitialisation_function(x)	(!strncmp(x + 1, "__I.TDF", 7))
#define is_function(x)	1


void
print_ass_preamble(FILE *of)
{
  fprintf(of, ".text\n");
  fprintf(of, "\t.even\n");
  fprintf(of, ".globl %s\n", INIT_FUNC_NAME);
  fprintf(of, "%s:\n", INIT_FUNC_NAME);
  return;
}

void
print_ass_postlude(FILE *of)
{
  fprintf(of, "\trts\n");
}

void construct_init_proc
(FILE *fp, long symtab_pos, long stringtab_pos, EXEC_STRUCT header, char *outname)
{
  int i;
  char str[256];
  long keeppos;
  FILE *outfile;
  if (!(outfile = open_file_write(outname))) {
    fail("Cannot Open output file");
  }
  fseek(fp, symtab_pos, 0);
  print_ass_preamble(outfile);
  for (i = 0; i < header.a_syms / sizeof(SYMBOL_STRUCT); ++i) {
    fread(&symbol, sizeof(SYMBOL_STRUCT), 1, fp);
    if (is_function(symbol)) {
      keeppos = ftell(fp);
      fseek(fp, stringtab_pos + symbol.n_un.n_strx, 0);
      fgets(str, 256, fp);
      if (is_intitialisation_function(str)) {
	fprintf(outfile, "\tjbsr\t%s\n", str);
      }
      fseek(fp, keeppos, 0);
    }
  }
  print_ass_postlude(outfile);
  return;
}

void
process_flag(char *option)
{
  switch (option[1]) {
    case 'V':
    case 'v': {
     (void)fprintf(stderr, "Dynamic initialisation linker V%d.%d\n",
		    MAJOR_VERSION, MINOR_VERSION);
      break;
    }
    default: {
     (void)fprintf(stderr, "Error: unknown option %s\n", option);
    }
  }
  return;
}


int
main(int argc, char **argv)
{
  FILE *fp;
  long symtab_pos, stringtab_pos;
  int i;
  int symsize;
  char str[80];
  long keeppos;
  int num_flags = 0;

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      num_flags++;
      process_flag(argv[i]);
    }
  }
  if (argc - num_flags < 3) {
    fprintf(stderr, "*fail*: syntax is %s [-options] <input filename> <output filename>\n", argv[0]);
    exit(1);
  }
  fp = open_file_read(argv[1 + num_flags]);

  fread(&header, sizeof(EXEC_STRUCT), 1, fp);
  if (N_BADMAG(header)) {
    fail("Bad magic number\n");
  }
  symtab_pos = N_SYMOFF(header);

  stringtab_pos = N_STROFF(header);
  construct_init_proc(fp, symtab_pos, stringtab_pos, header,
		      argv[2 + num_flags]);
  return 0;
}
