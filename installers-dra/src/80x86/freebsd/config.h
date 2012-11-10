/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* freebsd/config.h */

#ifndef config_key
#define config_key 1


/* API SPECIFICATION */
#include <reader/ossg_api.h>
#include <reader/ossg.h>

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	1
#endif

#define has_setcc 1
#define has_byte_regs 1
#define has_byte_ops 1
#define only_lengthen_ops 1
#define has_neg_shift 0
#define regable_union 0
#define substitute_params 1
#define special_fns 1
#define shift_is_byte 1
#define only_inline_static 0
#define remove_zero_offsets 1
#define replace_compound 1
#define no_bitfield_ops 1
#define dont_unpad_apply 0
#define diagnose_registers 1
#define DWARF 0
#define load_ptr_pars 1
#define use_long_double 1
#define has64bits 1
#define keep_PIC_vars 0
#define div0_implemented 1
#define substitute_complex 1
#define has_rotate 1


#define maxmin_implemented 1
#define condassign_implemented 0

#define target_dbl_maxexp 308

#define value_of_null 0
#define no_trap_on_nil_contents 1

#define AVOID_INTOV 0	/* No software interrupts */


/* Parameters for foralls optimisations */

#define remove_unused_counters 0
#define remove_unused_index_counters 0
#define good_index_factor(f)	0
#define good_pointer_factor(f)	((f)!= 1 && (f)!= 2 && (f)!= 4 && (f)!= 8)

#define temp_mips 0

#endif
