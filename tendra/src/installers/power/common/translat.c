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
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
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
 */



/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/


/*
 *  Translation is controlled by translate() in this module.
 *  Code generation follows the following phases:
 *
 *  1. The TDF is read in, applying bottom-up optimisations.
 *  2. Top-down optimisations are performed.
 *  3. Register allocation is performed, and TDF idents introduced
 *     so code generation can be performed with no register spills.
 *  4. Code is generated for each procedure, and global declarations processed.
 *  5. Peephole optimisation and instruction scheduling.
 *     (not implemented yet)
 *
 *  In a little more detail:
 *
 *  1) During the TDF reading process for tag declarations and tag
 *  definitions, applications of tokens are expanded as they are
 *  encountered, using the token definitions.  Every token used must have
 *  been previously defined in the bitstream.
 *
 *  The reading of the tag definitions creates a data structure in memory
 *  which directly represents the TDF.  At present, all the tag definitions
 *  are read into memory in this way before any further translation is
 *  performed.  This will shortly be changed, so that translation is
 *  performed in smaller units.  The translator is set up already so that
 *  the change to translate in units of single global definitions (or
 *  groups of these) can easily be made.
 *
 *  During the creation of the data structure bottom-up optimisations
 *  are performed.  These are the optimisations which can be done when a
 *  complete sub-tree of TDF is present, and are independent of the context
 *  in which the sub-tree is used.  They are defined in check.c and
 *  check_id.c.  These optimisation do such things as use the commutative
 *  and associative laws for plus to collect together and evaluate
 *  constants.  More ambitious examples of these bottom-up optimisations
 *  include all constant evaluation, elimination of inaccessible code, and
 *  forward propagation of assignments of constants.
 *
 *  2) After reading in the TDF various optimisations are performed which
 *  cannot be done until the whole context is present.  For example,
 *  constants cannot be extracted from a loop when we just have the loop
 *  itself, because we cannot tell whether the variables used in it are
 *  aliased.
 *
 *  These optimisations are invoked by opt_all_exps which is defined in
 *  indep.c.  They include extraction of constants from loops, common
 *  expression elimination on them and strength reduction for indexing.
 *
 *  3) Allocatable registers are partitioned into two sets, the s regs
 *  which are preserved over calls, and the t regs which are not.
 *
 *  The TDF is scanned introducing TDF idents so that expressions can be
 *  evaluated within the available t regs with no spills.  These new idents
 *  may be later allocated to a s reg later, if the weighting algorithm
 *  (below) considers this worth while.  Otherwise they will be on the stack.
 *
 *  Information is collected to help in global register allocation.  During
 *  a forward recursive scan of the TDF the number of accesses to each
 *  variable is computed (making assumptions about the frequency of
 *  execution of loops).  Then on the return scan of this recursion, for
 *  each declaration, the number of registers which must be free for it to
 *  be worthwhile to use a register is computed, and put into the TDF as
 *  the "break" point.  The procedures to do this are defined in weights.c.
 *
 *  Suitable idents not alive over a procedure call are allocated to a t reg,
 *  and others to s regs.  At the same time stack space requirements are
 *  calculated, so this is known before code for a procedure is generated.
 *
 *  4) Finally the code is generated without register spills.  The code is
 *  generated by make_code() in makecode.c, and make_XXX_code() in proc.c.
 *
 *  Note that loop unrolling optimisations are not currently implemented.
 *  Library procedures such as memcpy() are not treated specially.
 */


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "installglob.h"
#include "basicread.h"
#include "main_reads.h"
#include "optimise.h"
#include "exp.h"
#include "flpt.h"		/* for init_flpt() */
#include "externs.h"		/* for "inits.h" init_XXX() procs */
#include "myassert.h"
#include "tempdecs.h"
#include "weights.h"
#include "procrecs.h"
#include "regalloc.h"
#include "makecode.h"
#include "eval.h"
#include "flags.h"
#include "needscan.h"
#include "machine.h"
#include "diagout.h"
#include "xalloc.h"
#include "comment.h"

#include "translat.h"
#include "readglob.h"
#include "stack.h"
#include "frames.h"
#include "macro.h"
#include "dynamic_init.h"
#include "target_v.h"


#define ALIGNNEXT(bitposn, bitalign)	(((bitposn)+(bitalign)-1) & ~((bitalign)-1))

int optim_level;		/* optimisation level from -O# option */
int maxfix_tregs;		/* The number of t regs allocatable */
FILE *as_file;			/* Assembler output file */
dec **main_globals;		/* The globals decs array */
procrec *procrecs;		/* The proc records array */
dec * diag_def = NULL;
bool environ_externed=0;/* environ bug work around */
long total_no_of_globals = 0;
bool done_scan = 0;

/* 
 * Translate the TDF 
 */
int
translate(char *infname, char *outfname)
{
	/*
	 * Open files.
	 */
	if (!initreader(infname))
	{
		fprintf(stderr, "powertrans: cannot open input file %s\n", infname);
		return 3;
	}
	
	if (strcmp(outfname, "-") == 0)
	{
		/* "-" by convention means stdout */
		as_file = stdout;
		setbuf(as_file, 0);			/* to help debugging */
	}
	else
	{
		as_file = fopen(outfname, "w");
		if (as_file == (FILE *) 0)
		{
			fprintf(stderr, "powertrans: cannot open output file %s\n", outfname);
			return 3;
		}
	}
	
	/* mark the as output as TDF compiled */
#ifdef DO_ASSEMBLER_MACROS
	if (do_macros)
	{
		init_macros();
	}
#endif
	fprintf(as_file, "L.TDF.translated:\n");
	fprintf(as_file, "#\tpowertrans version %d.%d\n", target_version, target_revision);
	
	/* 
	 * Initialise the automatically generated reader modules with 
	 * automatically generated inits.h 
	 */
#include "inits.h"
	
	init_flpt();			/* initialise the floating point array */
	top_def = (dec*)0;		/* top_def starts as nil */
	
	
	
	/* init nowhere */
	setregalt(nowhere.answhere, 0);
	nowhere.ashwhere.ashsize = 0;
	nowhere.ashwhere.ashsize = 0;
	
	
	/* set assembler id prefixes */
	local_prefix = "S.";		/* S for static */
	name_prefix = "";
	
	
	/*
	 * Translate.
	 */
	
	/* 
	 * Start the TDF reader, which calls back to translate_capsule() below 
	 */
	
	d_capsule();
	
	/* check for output errors and close the .s file */
	if (ferror(as_file) != 0 || fclose(as_file) != 0)
	{
		fprintf(stderr, "powertrans: error writing to output file %s\n", outfname);
		return 4;
	}
	
	return good_trans;			/* return 1 for error, 0 for good */
}


/*
 * Translate a TDF capsule 
 */
void
translate_capsule()
{
	int noprocs, noglobals;
	int procno, globalno;
	dec *crt_def;
	space tempregs;
	int r;
	bool anydone;
	
	/*
	 * Do the high level, portable, TDF optimisations 
	 */
	opt_all_exps();
	
	/*
	 * Initialise diagnostic information and produce stab for basic types.
	 */
	if (diagnose)
	{
		init_diag();
	}
	
	
	/*
	 * Generate .extern, .globl, .lglobl, .comm, .lcomm.
	 * Also take the opportunity to count proc and global definitions.
	 *
	 * Note that .lglobl is only generated if diagnose is set (from -g).
	 * It requires an updated IBM assembler with fix:
	 * IX23435 Assembler can't create C_HIDEXT class for static names
	 */
	
	noprocs = 0;
	noglobals = 0;
	
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		shape s = crt_def->dec_u.dec_val.dec_shape;
		bool extnamed = crt_def->dec_u.dec_val.extnamed;
		char *id;
		
		noglobals++;
		/* diag_def needed for find_dd in diagout.c */
		diag_def=crt_def;
		
		if (diagnose)
		{
			/*
			 * It is safe to fixup all names here.  C static within procs
			 * do not get a diag_descriptor so fixup_name does not change
			 * their names.
			 */
			fixup_name(son(tg), top_def, crt_def);
		}
		
		id = crt_def->dec_u.dec_val.dec_id;		/* might be changed by fixup_name() */
		
		FULLCOMMENT4("%s: extnamed=%d no(tg)=%d isvar(tg)=%d", (long)id, extnamed, no(tg), isvar(tg));
		FULLCOMMENT4("\tname(tg)=%d dec_outermost=%d have_def=%d son(tg)!=nilexp=%d",
					 name(tg), crt_def->dec_u.dec_val.dec_outermost, crt_def->dec_u.dec_val.have_def, son(tg) != nilexp);
		if (son(tg) != nilexp)
			FULLCOMMENT3("\tdec_shape, sh(tg), sh(son(tg))=%d,%d,%d", name(s), name(sh(tg)), name(sh(son(tg))));
		
		crt_def->dec_u.dec_val.have_def = (son(tg)!=nilexp);
		
		ASSERT(name(tg) == ident_tag);
		ASSERT(son(tg) == nilexp || name(sh(tg)) == name(s));
		
		if (son(tg) == nilexp)
		{
#if 0
			if (!diagnose && no(tg) == 0)
#else
				if (no(tg)==0)/* only put out an extern instruction if there is a use */
#endif
				{
					/* no use of this tag, do nothing */
				}
				else if (extnamed)
				{
					if (name(s) == prokhd)
					{
						fprintf(as_file, "\t.extern\t%s\n", id);	/* proc descriptor */
						fprintf(as_file, "\t.extern\t.%s\n", id);	/* proc entry point */
					}
					else
					{
#if 1
						if (strcmp(id, "environ") == 0)
						{
							/*
							 * Kludge for environ, .extern for .csect, AIX 3.1.5 ld/library bug maybe?
							 * /lib/syscalls.exp states that environ & errno are specially handled,
							 * located on the stack at fixed addresses.
							 */
							fprintf(as_file, "\t.extern\t%s[RW]\n", id);
							environ_externed=1;
						}
						else
#endif
						{
							fprintf(as_file, "\t.extern\t%s\n", id);
						}
					}
				}
				else
				{
					long byte_size = ALIGNNEXT(shape_size(sh(son(tg))), 64) >> 3;
					/* +++ is .lcomm always kept double aligned?  Otherwise how do we do it? */
					
					ASSERT(extnamed);
					fprintf(as_file, "\t.lcomm\t%s,%ld\n", id, byte_size);
				}
		}
		else if (IS_A_PROC(son(tg)))
		{
			noprocs++;
			
			if (extnamed)
			{
				fprintf(as_file, "\t.globl\t%s\n", id);		/* id proc descriptor */
				fprintf(as_file, "\t.globl\t.%s\n", id);	/* .id entry point */
			}
			else if (diagnose)
			{
				/* .lglobl is not documented, but avoids dbx and gdb becoming confused */
				/* +++ always when .lglobl documented */
				fprintf(as_file, "\t.lglobl\t.%s\n", id);	/* .id entry point */
			}
		}
		else if (is_comm(son(tg)) && (diagnose || extnamed || no(tg) > 0))
		{
			/* zero initialiser needed */
			long size = shape_size(sh(son(tg)));
			long align = shape_align(sh(son(tg)));
			long byte_size = ALIGNNEXT(size, 64) >> 3;	
			/* +++ do we need to round up? */
			int aligncode = ((align > 32 || size > 32) ? 3 : 2);
			/* +++ is .lcomm always kept double aligned?
			 * Otherwise how do we do it? */
			
			/* assembler is happy with .comm of size 0, 
			 * so no need to special case unknown size */
			
			if (extnamed)
			{
				fprintf(as_file, "\t.comm\t%s,%ld,%d\n", id, byte_size, aligncode);
				if (diagnose)
					stab_global(son(tg), id, extnamed);
			}
			else
			{
				if (diagnose)
				{
					char *csect_name = "C.";
					
					/*
					 * assembler is confused if it sees .stabx before any .csect,
					 * so keep it happy with a useless .csect:
					 */
					fprintf(as_file, "\t.csect\t[PR]\n");
					fprintf(as_file, "\t.lcomm\t%s,%ld,%s\n", id, byte_size, csect_name);
					stab_bs(csect_name);
					stab_global(son(tg), id, extnamed);
					stab_es(csect_name);
				}
				else if (no(tg) > 0)			/* used */
				{
					fprintf(as_file, "\t.lcomm\t%s,%ld\n", id, byte_size);
				}
			}
			
			ASSERT((align&63)==0 || align < 64);
			
			/* mark the defininition as processed */
			crt_def->dec_u.dec_val.processed = 1;
		}
		else
		{
			if (extnamed)
				fprintf(as_file, "\t.globl\t%s\n", id);
			else if (diagnose)
				fprintf(as_file, "\t.lglobl\t%s\n", id);
			/* to avoid 'warning: global ignored' message from dbx */
		}
	}
	
#ifdef DO_DYNAMIC_INITIALISATION
	(void)do__main_extern();
#endif
	if (do_profile)
#ifdef TDF_MCOUNT
		fprintf(as_file, "\t.extern\t.TDF_mcount\n");
#else
    fprintf(as_file, "\t.extern\t.mcount\n");
#endif
	
	
	/*
	 * Alloc memory for procrecs array, info retained between phases
	 * about procs and how parameters will be stored.
	 */
	procrecs = (procrec *) xcalloc(noprocs, sizeof (procrec));
	
	/*
	 * Alloc memory for main_globals, used to lookup assembler names.
	 */
	main_globals = (dec**)xcalloc(noglobals, sizeof(dec*));
	
	/*
	 * Generate .toc entries.
	 * Also take opportunity to setup main_globals.
	 */
	fprintf(as_file, "\n\t.toc\n");
	
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		char *id = crt_def->dec_u.dec_val.dec_id;
		/* 
		 * no(tg) is number of uses 
		 * If tg is used in this module, 
		 * generate a .toc entry so it can be addressed 
		 * +++ differentiate proc descriptor/entry point usage 
		 */
		if (no(tg) > 0 || strcmp(id,"__TDFhandler")==0 
			|| strcmp(id,"__TDFstacklim")==0)
		{
			bool extnamed = crt_def->dec_u.dec_val.extnamed;
			char *storage_class;
			
			if (extnamed && son(tg) == nilexp)
			{
				/* extern from another module */
				if (name(crt_def->dec_u.dec_val.dec_shape) == prokhd)
					storage_class = "";	/* proc descriptor */
				else
					storage_class = "";	/* unknown data */
			}
			else
			{
				storage_class = "";		/* this module */
			}
#if 1
			if (strcmp(id, "environ") == 0 && environ_externed)
			{
				/* kludge for environ, .extern for .csect, IBM ld/library bug maybe? */
				storage_class = "[RW]";
				
			}
#endif
			fprintf(as_file, "T.%s:\t.tc\t%s[TC],%s%s\n", id, id, id, storage_class);
		}
	}
	
	
	
	/* number proc defs and setup main_globals */
	procno = 0;
	globalno = 0;
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		
		main_globals[globalno] = crt_def;
		crt_def->dec_u.dec_val.sym_number = globalno;
		globalno++;
		
		if (son(tg) != nilexp && IS_A_PROC(son(tg)))
		{
			no(son(tg)) = procno;	/* index into procrecs in no(proc) */
			procno++;
		}
	}
	
	ASSERT(procno==noprocs);
	ASSERT(globalno==noglobals);
	total_no_of_globals=globalno;
	
	/*
	 * Scan to put proc bodies in POWER form,
	 * and calculate register and stack space needs.
	 */
	
	/*
	 * First work out which t fixed point regs, those not preserved over calls,
	 * can be used.  This needs to be done before scan() which adds idents
	 * so temp reg needs are within available temp reg set.
	 */
	
	/* initial reg sets */
	tempregs.fixed = PROC_TREGS;
	tempregs.flt = PROC_FLT_TREGS;
	
	/* ensure R_TMP0 not allocatable */
	tempregs.fixed |= RMASK(R_TMP0);
	
	/* count t fixed point regs we can use, and set the global maxfix_tregs */
	maxfix_tregs = 0;
	for (r = R_FIRST; r <= R_LAST; r++)
	{
		/* bit clear means allocatable */
		if (IS_TREG(r) && (tempregs.fixed&RMASK(r)) == 0)
			maxfix_tregs++;
	}
	maxfix_tregs -= REGISTER_SAFETY_NUMBER;
	
	COMMENT4("maxfix_tregs=%d(%#x) maxfloat_tregs=%d(%#x)",
			 maxfix_tregs, tempregs.fixed, MAXFLT_TREGS, tempregs.flt);
	
	
	/*
	 * Scan all the procs, to put the TDF in POWER form,
	 * and do register allocation.
	 */
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		
		if (son(tg) != nilexp && IS_A_PROC(son(tg)))
		{
			procrec *pr = &procrecs[no(son(tg))];
			exp *st = &son(tg);
			int freefixed=MAXFIX_SREGS;/* The maximum no of free fixed s regs */
			int freefloat=MAXFLT_SREGS;/* The maximum no of free float s regs */
			int r;
			
			/* 
			 * SCAN the procedure
			 */
			
			pr->needsproc = scan(st, &st);
			set_up_frame_pointer(pr,son(tg));
			/*
			 * WEIGHTS
			 * estimate usage of tags in body of proc,
			 * calculating the break points for register allocation
			 */
			if (!(pr->save_all_sregs))
			{
				(void) weightsv(UNITWEIGHT, bro(son(son(tg))));      
			}
			/* Check to see if we need a frame pointer */
			if (pr->has_fp)
			{
				freefixed--;
			}
			if (pr->has_tp)
			{
				freefixed--;
			}
			/* 
			 * REGALLOC
			 * reg and stack allocation for tags 
			 */
			pr->spacereqproc = regalloc(bro(son(son(tg))), freefixed, freefloat, 0);
			/* 
			 * Ensure that the registers that were not allocated get stored
			 */
			for (r=freefixed+R_13 ; r <= R_31 ; r++)
			{
				pr->spacereqproc.fixdump = pr->spacereqproc.fixdump | RMASK(r);
			}
			if (pr->save_all_sregs)
			{
				pr->spacereqproc.fixdump = 0xffffe000;
				pr->spacereqproc.fltdump = 0xffffc000;
			}
			set_up_frame_info(pr,son(tg));
		}
	}
	done_scan = 1;
	
	/*
	 * Evaluate outer level data initialisers in [RW] section.
	 */
	anydone = 0;
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		char *id = crt_def->dec_u.dec_val.dec_id;
		bool extnamed = crt_def->dec_u.dec_val.extnamed;
		diag_def=crt_def;/* just in case find_dd is called */
		FULLCOMMENT4("no(tg)=%d isvar(tg)=%d extnamed=%d son(tg)==nilexp=%d",
					 no(tg), isvar(tg), extnamed, son(tg)==nilexp);
		if (son(tg) != nilexp)
		{
			/*
			 * Skip if already processed, eg identified as is_comm() 
			 */
			if (crt_def->dec_u.dec_val.processed)
				continue;
			/*
			 * Skip if zero uses and internal to module 
			 * unless generating diagnostics 
			 */
			if (!(diagnose || extnamed || no(tg) > 0))
				continue;
			/* +++ could do better than making everything except strings [RW] */
			if (! IS_A_PROC(son(tg))) 
				/* put all things in [RW] section */
			{
				/* 
				 * Non proc, which is isvar() [variable] for [RW] section 
				 */
				long symdef = crt_def->dec_u.dec_val.sym_number;
				
				/* Check to see if we have made any entries yet */
				if (!anydone)
				{
					anydone = 1;
					fprintf(as_file, "\n\t.csect\tW.[RW]\n");
					if (diagnose)
					{
						stab_bs("W.[RW]");
					}
				}
				
				evaluated(son(tg), -symdef - 1);
				
				if (diagnose)
				{
					stab_global(son(tg), id, extnamed);
				}
				fprintf(as_file, "#\t.enddata\t%s\n\n", id);
				
				/* mark the defininition as processed */
				crt_def->dec_u.dec_val.processed = 1;
			}
		}
	}
	if (diagnose && anydone)
	{
		stab_es("W.[RW]"); /* Close the RW section stab */
	}
	
	
	
	/*
	 * Evaluate outer level data initialisers in [RO] section.
	 */
	anydone = 0;			/* set to 1 after first tag output */
	
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		char *id = crt_def->dec_u.dec_val.dec_id;
		bool extnamed = crt_def->dec_u.dec_val.extnamed;
		diag_def=crt_def;/* just in case find_dd is called */
		if (son(tg) != nilexp)
		{
			/* skip if already processed, eg identified as is_comm() */
			if (crt_def->dec_u.dec_val.processed)
				continue;
			
			/* 
			 * Skip if zero uses and internal to module unless 
			 * generating diagnostics 
			 */
			if (!(diagnose || extnamed || no(tg) > 0))
				continue;
			
			if (!IS_A_PROC(son(tg)))
			{
				/* non proc, which is not isvar() [variable] for [RO] section */
				long symdef = crt_def->dec_u.dec_val.sym_number;
				
				if (!anydone)
				{
					anydone = 1;
					fprintf(as_file, "\n\t.csect\tR.[RO]\n");
					if (diagnose)
					{
						stab_bs("R.[RO]");
					}
				}
				
				evaluated(son(tg), symdef + 1);
				
				if (diagnose)
				{
					stab_global(son(tg), id, extnamed);
				}
				fprintf(as_file, "#\t.enddata\t%s\n\n", id);
				
				/* mark the defininition as processed */
				crt_def->dec_u.dec_val.processed = 1;
			}
		}
	}
	
	if (diagnose && anydone)
	{
		stab_es("R.[RO]");
	}
	anydone=0;
	
	/*
	 * Translate procedures.
	 */
	for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
	{
		exp tg = crt_def->dec_u.dec_val.dec_exp;
		char *id = crt_def->dec_u.dec_val.dec_id;
		bool extnamed = crt_def->dec_u.dec_val.extnamed;
		
		if (son(tg) != nilexp)
		{
			/* skip if already processed */
			if (crt_def->dec_u.dec_val.processed)
				continue;
			
			/* skip if zero uses and internal to module unless generating diagnostics */
			if (!(diagnose || extnamed || no(tg) > 0))
				continue;
			
			if (IS_A_PROC(son(tg)))
			{
				/* translate code for proc */
				fprintf(as_file, "\n");		/* make proc more visable to reader */
				diag_def=crt_def;
				/* switch to correct file */
				if (diagnose && diag_def->dec_u.dec_val.diag_info!=NULL)
				{
					anydone=1;
					stab_proc1(son(tg), id, extnamed);
				}
				
				
				fprintf(as_file, "#\t.proc\n");
				
				/* generate descriptor */
				fprintf(as_file, "\t.csect\t[DS]\n");
				fprintf(as_file, "%s:\n", id);
				fprintf(as_file, "\t.long\t.%s,TOC[tc0],0\n", id);
				
				/* generate code */
				fprintf(as_file, "\t.csect\t[PR]\n");
				fprintf(as_file, ".%s:\n", id);
				
				/* stab proc details */
				if (diagnose && diag_def->dec_u.dec_val.diag_info!=NULL)
				{
					stab_proc2(son(tg), id, extnamed);
				}
				
				seed_label();		/* reset label sequence */
				settempregs(son(tg));	/* reset getreg sequence */
				
				code_here(son(tg), tempregs, nowhere);
				
				if (diagnose && diag_def->dec_u.dec_val.diag_info!=NULL)
				{
					stab_endproc(son(tg), id, extnamed);
				}
				
				fprintf(as_file, "#\t.end\t%s\n", id);
				
				/* mark the defininition as processed */
				crt_def->dec_u.dec_val.processed = 1;
			}
		}
	}
	if (diagnose && anydone)
	{
		stab_end_file();/* Ties up any open .bi's with .ei's */
	}
	
}


/* translate a TDF unit */
void
translate_unit()
{
	if (separate_units)
	{
		dec *crt_def;
		
		translate_capsule();
		
		for (crt_def = top_def; crt_def != (dec *) 0; crt_def = crt_def->def_next)
		{
			exp crt_exp = crt_def->dec_u.dec_val.dec_exp;
			
			no(crt_exp) = 0;
			pt(crt_exp) = nilexp;
		}
		
		crt_repeat = nilexp;
		repeat_list = nilexp;
	}
	
	return;
}


/* output an identification of two names */
void
out_rename(char *old_nm, char *nm)
{
	/* all link information is known by code production time, so no need to do anything */
}

baseoff
find_tg(char *n)
{
	int i;
	exp tg;
	for (i = 0; i < total_no_of_globals; i++) {
		char *id = main_globals[i] -> dec_u.dec_val.dec_id;
		tg = main_globals[i] -> dec_u.dec_val.dec_exp;
		if (strcmp(id, n) == 0) return boff(tg);
	}
	printf("%s\n", n);
	fail("Extension name not declared ");
	tg = main_globals[0] -> dec_u.dec_val.dec_exp;
	return boff(tg);
}
