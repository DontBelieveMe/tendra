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


#include "config.h"
#include "calculus.h"
#include "code.h"
#include "common.h"
#include "disk.h"
#include "output.h"
#include "suffix.h"
#include "type_ops.h"


/*
 *    OUTPUT ENUMERATION READING ROUTINE
 *
 *    This routine outputs code for reading an enumeration type from disk.
 *    This is done in two sections for long enumeration types.
 */

static void
disk_read_enum(void)
{
    number n = log_2 (DEREF_number (en_order (CRT_ENUM)));
    if (n <= 16) {
		output ("    x_ = (%EN) READ_BITS (%n);\n", n);
    } else {
		n -= 16;
		output ("    x_ = (%EN) READ_BITS (16);\n");
		output ("    x_ += (((%EN) READ_BITS (%n)) << 16);\n", n);
    }
    return;
}


/*
 *    OUTPUT STRUCTURE READING ROUTINE
 *
 *    This routine outputs code for reading a structure type from disk.
 */

static void
disk_read_struct(void)
{
    LOOP_STRUCTURE_COMPONENT {
		TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
		output ("    x_.%CN = READ_%TI ();\n", t);
    }
    return;
}


/*
 *    OUTPUT UNION READING ROUTINE
 *
 *    This routine outputs code for reading a union type from disk.
 */

static void
disk_read_union(void)
{
    output ("\tx_ = NULL_%UM;\n");
    output ("\tif (READ_BITS (1) == 1) {\n");
    LOOP_UNION_COMPONENT output ("\t\t%CT %CN;\n");
    output ("\t\tunsigned tag_ = READ_BITS (%UO2);\n");
    output ("\t\tswitch (tag_) {\n");
    LOOP_UNION_FIELD {
		int al = DEREF_int (fld_flag (CRT_FIELD));
		output ("\t\tcase %UM_%FN_tag : {\n");
		LOOP_FIELD_COMPONENT output ("\t\t\t%CT %CN;\n");

		/* Deal with aliasing */
		if (al) {
			output ("\t\t\tunsigned alias_ = READ_ALIAS ();\n");
			output ("\t\t\tif (READ_BITS (1) == 0) {\n");
			output ("\t\t\t\tx_ = FIND_ALIAS_%UM_%FN (alias_);\n");
			output ("\t\t\t\tbreak;\n");
			output ("\t\t\t}\n");
			if (al == 2) {
				output ("\t\t\tUNALIAS_%UM_%FN (x_);\n");
				output ("\t\t\tSET_ALIAS_%UM_%FN (x_, alias_);\n");
			} else {
				output ("\t\t\tNEW_ALIAS_%UM_%FN (x_, alias_);\n");
			}
		}

		/* Read the components */
		LOOP_UNION_COMPONENT {
			TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
			output ("\t\t\t%CN = READ_%TI ();\n", t);
		}
		LOOP_FIELD_COMPONENT {
			TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
			output ("\t\t\t%CN = READ_%TI ();\n", t);
		}

		/* Assign components into x_ */
		if (al == 2) {
			output ("\t\t\tUNIFY_%UM_%FN (");
			LOOP_UNION_COMPONENT output ("%CN, ");
			LOOP_FIELD_COMPONENT output ("%CN, ");
			output ("x_);\n");
			output ("\t\t\tSET_ALIAS_%UM_%FN (x_, alias_);\n");
		} else if (al) {
			LOOP_UNION_COMPONENT {
				TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
				output ("\t\t\tCOPY_%TM (%UM_%CN (x_), %CN);\n", t);
			}
			LOOP_FIELD_COMPONENT {
				TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
				output ("\t\t\tCOPY_%TM (%UM_%FN_%CN (x_), %CN);\n", t);
			}
		} else {
			int def = 0;
			output ("\t\t\tMAKE_%UM_%FN (");
			LOOP_UNION_COMPONENT {
				string v = DEREF_string (cmp_value (CRT_COMPONENT));
				if (v == NULL) {
					output ("%CN, ");
				} else {
					def = 1;
				}
			}
			LOOP_FIELD_COMPONENT {
				string v = DEREF_string (cmp_value (CRT_COMPONENT));
				if (v == NULL) {
					output ("%CN, ");
				} else {
					def = 1;
				}
			}
			output ("x_);\n");
			if (def) {
				/* Override default values */
				LOOP_UNION_COMPONENT {
					string v = DEREF_string (cmp_value (CRT_COMPONENT));
					if (v) {
						TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
						output ("\t\t\tCOPY_%TM ", t);
						output ("(%UM_%CN (x_), %CN);\n");
					}
				}
				LOOP_FIELD_COMPONENT {
					string v = DEREF_string (cmp_value (CRT_COMPONENT));
					if (v) {
						TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
						output ("\t\t\tCOPY_%TM ", t);
						output ("(%UM_%FN_%CN (x_), %CN);\n");
					}
				}
			}
		}
		output ("\t\t\tbreak;\n");
		output ("\t\t}\n");
    }
    output ("\t\t}\n");
    output ("\t}\n");
    return;
}


/*
 *    PRINT THE DISK READING DEFINITIONS
 *
 *    This routine prints all the routines for reading the various types
 *    from disk.
 */

static void
disk_read_def(char *dir)
{
    open_file (dir, READ_PREFIX, DEF_SUFFIX);
    print_include ();

    comment ("Disk reading function declarations");
    LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type (t);
		unsigned tag = TAG_type (t0);
		if (is_identity_type (t)) {
			output ("#ifndef READ_%TI\n", t);
			output ("#define\tREAD_%TI() READ_%TJ()\n", t, t);
			output ("#endif\n\n");
		} else if (tag != type_primitive_tag) {
			output ("#ifndef READ_%TI\n", t);
			output ("static %TT READ_%TI(void);\n", t, t);
			output ("#endif\n\n");
		}
    }
    output ("\n");

    /* Function definitions */
    LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type (t);
		unsigned tag = TAG_type (t0);
		if (!is_identity_type (t) && tag != type_primitive_tag) {
			/* Function header */
			output ("/* Disk reading routine for %TT */\n\n", t);
			output ("#ifndef READ_%TI\n\n", t);
			output ("static %TT\nREAD_%TI", t, t);
			output ("(void)\n");
			output ("{\n");
			output ("\t%TT x_;\n", t);

			/* Function body */
			switch (tag) {

			case type_enumeration_tag : {
				ENUM_P p = DEREF_ptr (type_enumeration_en (t0));
				LOOP_ENUM {
					if (EQ_ptr (CRT_ENUM, p)) {
						disk_read_enum ();
						break;
					}
				}
				break;
			}

			case type_structure_tag : {
				STRUCTURE_P p = DEREF_ptr (type_structure_struc (t0));
				LOOP_STRUCTURE {
					if (EQ_ptr (CRT_STRUCTURE, p)) {
						disk_read_struct ();
						break;
					}
				}
				break;
			}

			case type_onion_tag : {
				UNION_P p = DEREF_ptr (type_onion_un (t0));
				LOOP_UNION {
					if (EQ_ptr (CRT_UNION, p)) {
						disk_read_union ();
						break;
					}
				}
				break;
			}

			case type_ptr_tag : {
				TYPE_P s = DEREF_ptr (type_ptr_sub (t0));
				output ("\tif (READ_BITS (1) == 0) {\n");
				output ("\t\tx_ = NULL_ptr (%TT);\n", s);
				output ("\t} else {\n");
				output ("\t\tx_ = MAKE_ptr (%TS);\n", s);
				output ("\t\tCOPY_%TM (x_, READ_%TI ());\n", s, s);
				output ("\t}\n");
				break;
			}

			case type_list_tag : {
				TYPE_P s = DEREF_ptr (type_list_sub (t0));
				output ("\tx_ = NULL_list (%TT);\n", s);
				output ("\twhile (READ_BITS (1)) {\n");
				output ("\t\t%TT y_;\n", s);
				output ("\t\t%TT z_;\n", t);
				output ("\t\ty_ = READ_%TI ();\n", s);
				output ("\t\tCONS_%TM (y_, NULL_list (%TT), z_);\n",
						s, s);
				output ("\t\tx_ = APPEND_list (x_, z_);\n");
				output ("\t}\n");
				break;
			}

			case type_stack_tag : {
				TYPE_P s = DEREF_ptr (type_stack_sub (t0));
				output ("\tLIST (%TT) w_;\n", s);
				output ("\tw_ = NULL_list (%TT);\n", s);
				output ("\twhile (READ_BITS (1)) {\n");
				output ("\t\t%TT y_;\n", s);
				output ("\t\t%TT z_;\n", t);
				output ("\t\ty_ = READ_%TI ();\n", s);
				output ("\t\tCONS_%TM (y_, NULL_list (%TT), z_);\n",
						s, s);
				output ("\t\tw_ = APPEND_list (w_, z_);\n");
				output ("\t}\n");
				output ("\tx_ = STACK_list (w_);\n");
				break;
			}

			case type_vec_tag : {
				TYPE_P s = DEREF_ptr (type_vec_sub (t0));
				output ("\tPTR (%TT) y_;\n", s);
				output ("\t%X_dim n_ = (%X_dim) READ_DIM ();\n");
				output ("\tMAKE_vec (%TS, n_, x_);\n", s);
				output ("\ty_ = PTR_vec_ptr (");
				output ("VEC_PTR_vec (x_));\n");
				output ("\twhile (n_--) {\n");
				output ("\t\tCOPY_%TM (y_, READ_%TI ());\n", s, s);
				output ("\t\ty_ = STEP_ptr (y_, %TS);\n", s);
				output ("\t}\n");
				break;
			}

			case type_vec_ptr_tag : {
				TYPE_P s = DEREF_ptr (type_vec_ptr_sub (t0));
				output ("\tVEC (%TT) y_;\n", s);
				output ("\tPTR (%TT) z_;\n", s);
				output ("\tMAKE_vec (%TS, (%X_dim) 1, y_);\n", s);
				output ("\tx_ = VEC_PTR_vec (y_);\n");
				output ("\tz_ = PTR_vec_ptr (x_);\n");
				output ("\tCOPY_%TM (z_, READ_%TI ());\n", s, s);
				break;
			}
			}

			/* Function trailer */
			output ("\treturn (x_);\n");
			output ("}\n\n");
			output ("#endif\n\n\n", t);
		}
    }

    close_file ();
    return;
}


/*
 *    OUTPUT ENUMERATION WRITING ROUTINE
 *
 *    This routine outputs code for writing an enumeration type to disk.
 *    This is done in two sections for long enumeration types.
 */

static void
disk_write_enum(void)
{
    number n = log_2 (DEREF_number (en_order (CRT_ENUM)));
    if (n <= 16) {
		output ("\tWRITE_BITS (%n, (unsigned) x_);\n", n);
    } else {
		n -= 16;
		output ("\tWRITE_BITS (16, (unsigned) (x_ & 0xffff));\n");
		output ("\tWRITE_BITS (%n, (unsigned) (x_ >> 16));\n", n);
    }
    return;
}


/*
 *    OUTPUT STRUCTURE WRITING ROUTINE
 *
 *    This routine outputs code for writing a structure type to disk.
 */

static void
disk_write_struct(void)
{
    LOOP_STRUCTURE_COMPONENT {
		TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
		output ("\tWRITE_%TI (x_.%CN);\n", t);
    }
    return;
}


/*
 *    OUTPUT UNION WRITING ROUTINE
 *
 *    This routine outputs code for writing a union type to disk.
 */

static void
disk_write_union(void)
{
    int have_ucmp = 0;
    output ("\tif (IS_NULL_%UM (x_)) {\n");
    output ("\t\tWRITE_BITS (1, (unsigned) 0);\n");
    output ("\t} else {\n");
    LOOP_UNION_COMPONENT {
		output ("\t\t%CT %CN;\n");
		have_ucmp = 1;
    }
    output ("\t\tunsigned tag_ = TAG_%UM (x_);\n");
    output ("\t\tWRITE_BITS (1, (unsigned) 1);\n");
    output ("\t\tWRITE_BITS (%UO2, tag_);\n");
    output ("\t\tswitch (tag_) {\n");
    LOOP_UNION_FIELD {
		int have_cmp = have_ucmp;
		int al = DEREF_int (fld_flag (CRT_FIELD));
		output ("\t\tcase %UM_%FN_tag : {\n");
		LOOP_FIELD_COMPONENT {
			output ("\t\t\t%CT %CN;\n");
			have_cmp = 1;
		}

		/* Deal with aliasing */
		if (al) {
			output ("\t\t\tunsigned alias_ = GET_ALIAS_%UM_%FN (x_);\n");
			output ("\t\t\tif (alias_) {\n");
			output ("\t\t\t\tWRITE_ALIAS (alias_);\n");
			output ("\t\t\t\tWRITE_BITS (1, (unsigned) 0);\n");
			output ("\t\t\t\tbreak;\n");
			output ("\t\t\t}\n");
			output ("\t\t\talias_ = ++crt_%X_alias;\n");
			output ("\t\t\tSET_ALIAS_%UM_%FN (x_, alias_);\n");
			output ("\t\t\tWRITE_ALIAS (alias_);\n");
			output ("\t\t\tWRITE_BITS (1, (unsigned) 1);\n");
		}

		/* Deconstruct union */
		if (have_cmp) {
			output ("\t\t\tDECONS_%UM_%FN (");
			LOOP_UNION_COMPONENT output ("%CN, ");
			LOOP_FIELD_COMPONENT output ("%CN, ");
			output (" x_);\n");
		}

		/* Process further if necessary */
		if (al == 2) {
			output ("\t\t\tALIAS_%UM_%FN (");
			LOOP_UNION_COMPONENT output ("%CN, ");
			LOOP_FIELD_COMPONENT output ("%CN, ");
			output (" x_);\n");
		}

		/* Write out components */
		LOOP_UNION_COMPONENT {
			TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
			output ("\t\t\tWRITE_%TI (%CN);\n", t);
		}
		LOOP_FIELD_COMPONENT {
			TYPE_P t = DEREF_ptr (cmp_type (CRT_COMPONENT));
			output ("\t\t\tWRITE_%TI (%CN);\n", t);
		}
		output ("\t\t\tbreak;\n");
		output ("\t\t}\n");
    }
    output ("\t\t}\n");
    output ("\t}\n");
    return;
}


/*
 *    PRINT THE DISK WRITING DEFINITIONS
 *
 *    This routine outputs all the routines for writing the various types
 *    to disk.
 */

static void
disk_write_def(char *dir)
{
    open_file (dir, WRITE_PREFIX, DEF_SUFFIX);
    print_include ();

    comment ("Disk writing function declarations");
    LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type (t);
		unsigned tag = TAG_type (t0);
		if (is_identity_type (t)) {
			output ("#ifndef WRITE_%TI\n", t);
			output ("#define\tWRITE_%TI(A) WRITE_%TJ (A)\n", t, t);
			output ("#endif\n\n");
		} else if (tag != type_primitive_tag) {
			output ("#ifndef WRITE_%TI\n", t);
			output ("static void WRITE_%TI(%TT);\n", t, t);
			output ("#endif\n\n");
		}
    }
    output ("\n");

    /* Function definitions */
    LOOP_TYPE {
		TYPE_P t = CRT_TYPE;
		TYPE t0 = DEREF_type (t);
		unsigned tag = TAG_type (t0);
		if (!is_identity_type (t) && tag != type_primitive_tag) {
			/* Function header */
			output ("/* Disk writing routine for %TT */\n\n", t);
			output ("#ifndef WRITE_%TI\n\n", t);
			output ("static void\nWRITE_%TI", t);
			output ("(%TT x_)\n", t);
		       	output ("{\n");

			/* Function body */
			switch (tag) {

			case type_enumeration_tag : {
				ENUM_P p = DEREF_ptr (type_enumeration_en (t0));
				LOOP_ENUM {
					if (EQ_ptr (CRT_ENUM, p)) {
						disk_write_enum ();
						break;
					}
				}
				break;
			}

			case type_structure_tag : {
				STRUCTURE_P p = DEREF_ptr (type_structure_struc (t0));
				LOOP_STRUCTURE {
					if (EQ_ptr (CRT_STRUCTURE, p)) {
						disk_write_struct ();
						break;
					}
				}
				break;
			}

			case type_onion_tag : {
				UNION_P p = DEREF_ptr (type_onion_un (t0));
				LOOP_UNION {
					if (EQ_ptr (CRT_UNION, p)) {
						disk_write_union ();
						break;
					}
				}
				break;
			}

			case type_ptr_tag : {
				TYPE_P s = DEREF_ptr (type_ptr_sub (t0));
				output ("\tif (IS_NULL_ptr (x_)) {\n");
				output ("\t\tWRITE_BITS (1, (unsigned) 0);\n");
				output ("\t} else {\n");
				output ("\t\t%TT y_;\n\t\t", s);
				print_deref (s, "x_", "y_");
				output ("\t\tWRITE_BITS (1, (unsigned) 1);\n");
				output ("\t\tWRITE_%TI (y_);\n", s);
				output ("\t}\n");
				break;
			}

			case type_list_tag : {
				TYPE_P s = DEREF_ptr (type_list_sub (t0));
				output ("\twhile (!IS_NULL_list (x_)) {\n");
				output ("\t\t%TT y_;\n\t\t", s);
				print_deref (s, "HEAD_list (x_)", "y_");
				output ("\t\tWRITE_BITS (1, (unsigned) 1);\n");
				output ("\t\tWRITE_%TI (y_);\n", s);
				output ("\t\tx_ = TAIL_list (x_);\n");
				output ("\t}\n");
				output ("\tWRITE_BITS (1, (unsigned) 0);\n");
				break;
			}

			case type_stack_tag : {
				TYPE_P s = DEREF_ptr (type_stack_sub (t0));
				output ("\tLIST (%TT) w_ = LIST_stack (x_);\n", s);
				output ("\twhile (!IS_NULL_list (w_)) {\n");
				output ("\t%TT y_;\n\t\t", s);
				print_deref (s, "HEAD_list (w_)", "y_");
				output ("\t\tWRITE_BITS (1, (unsigned) 1);\n");
				output ("\t\tWRITE_%TI (y_);\n", s);
				output ("\t\tw_ = TAIL_list (w_);\n");
				output ("\t}\n");
				output ("\tWRITE_BITS (1, (unsigned) 0);\n");
				break;
			}

			case type_vec_tag : {
				TYPE_P s = DEREF_ptr (type_vec_sub (t0));
				output ("\t%X_dim n_ = DIM_vec (x_);\n");
				output ("\tPTR (%TT) y_ ", s);
				output (" = PTR_vec_ptr (VEC_PTR_vec (x_));\n");
				output ("\tWRITE_DIM ((unsigned) n_);\n");
				output ("\twhile (n_--) {\n");
				output ("\t\t%TT z_;\n\t\t", s);
				print_deref (s, "y_", "z_");
				output ("\t\tWRITE_%TI (z_);\n", s);
				output ("\t\ty_ = STEP_ptr (y_, %TS);\n", s);
				output ("\t}\n");
				break;
			}

			case type_vec_ptr_tag : {
				TYPE_P s = DEREF_ptr (type_vec_ptr_sub (t0));
				output ("\tPTR (%TT) y_ = PTR_vec_ptr (x_);\n", s);
				output ("\t%TT z_;\n\t", s);
				print_deref (s, "y_", "z_");
				output ("\tWRITE_%TI (z_);\n", s);
				break;
			}
			}

			/* Function trailer */
			output ("\treturn;\n");
			output ("}\n\n");
			output ("#endif\n\n\n");
		}
    }
    close_file ();
    return;
}


/*
 *    MAIN DISK ACTION
 *
 *    This routine prints all the output files for reading and writing the
 *    calculus to disk.
 */

void
disk_action(char *dir)
{
    disk_read_def (dir);
    disk_write_def (dir);
    return;
}
