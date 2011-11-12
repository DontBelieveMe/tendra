/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

	/* **************************************************** */
	/*							*/
	/*  Target Dependency Token Definitions for aix_rs6000	*/
	/*							*/
	/* **************************************************** */




	/* LOCAL TOKENS */


Tokdef REP_V = [] VARIETY
	/* variety for integer widths and float_sequence */
var_width (false, 16);


Tokdef NATTEST = [a:NAT, comp:NTEST, b:NAT] EXP
	/* comparison of nats, for static conditionals */
? { ?(snat_from_nat(false,a)(REP_V) comp snat_from_nat(false,b)(REP_V));
    1(REP_V)
  | 0(REP_V)
};


Tokdef PUN = [from_sh:SHAPE, to_sh:SHAPE, val:EXP] EXP
	/* representation preserving conversion */
component (to_sh,
  Cons [ shape_offset(from_sh) .max. shape_offset(to_sh) ] (
    offset_zero(alignment(from_sh)) : val
  ),
  offset_zero(alignment(to_sh))
);


Tokdef PTR_V = [] VARIETY
	/* variety for converted pointers */
var_width (true, 32);




	/* INTEGER VARIETY REPRESENTATIONS */


Tokdef .~rep_var_width = [w:NAT] NAT
NAT ? ( NATTEST [w, <=, 8],
  8,
  NAT ? ( NATTEST [w, <=, 16],
    16,
    NAT ? ( NATTEST [w, <=, 32],
      32,
      NAT ? ( NATTEST [w, <=, 64],
        64,
        0
      )
    )
  )
);


Tokdef .~rep_atomic_width = [] NAT
32;




	/* FLOATING VARIETY REPRESENTATIONS */

/* sequence: 1=single, 2=double, 3=extended */


Tokdef .~rep_fv = [n:NAT] FLOATING_VARIETY
FLOATING_VARIETY ? ( NATTEST [n, ==, 1],
  flvar_parms (2, 24, 126, 127),
  FLOATING_VARIETY ? ( NATTEST [n, ==, 2],
    flvar_parms (2, 53, 1022, 1023),
    flvar_parms(
	computed_nat(#"No extended floats on current implementation"),
	0, 0, 0)
  )
);


Tokdef .~rep_fv_width = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  32,
  NAT ? ( NATTEST [n, ==, 2],
    64,
    0		/* provides test for end of range */
    )
);


Tokdef .~rep_fv_radix = [n:NAT] NAT
2;


Tokdef .~rep_fv_mantissa = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  24,
  53
);


Tokdef .~rep_fv_min_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  149,
  1074
);


Tokdef .~rep_fv_max_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  127,
  1023
);


Tokdef .~rep_fv_epsilon = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
  (2r1.0 E -23 (.~rep_fv[n])),
  (2r1.0 E -52 (.~rep_fv[n]))
);


Tokdef .~rep_fv_min_val = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
  (2r1.0 E -149 (.~rep_fv[n])),
  (2r1.0 E -1074 (.~rep_fv[n]))
);


Tokdef .~rep_fv_max_val = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
  (8r3.77777774 E 42 (.~rep_fv[n])),
  (8r1.777777777777777774 E 341 (.~rep_fv[n]))
);




	/* NON-NUMERIC REPRESENTATIONS */


Tokdef .~ptr_width = [] NAT
32;


Tokdef .~best_div = [] NAT
2;


Tokdef .~little_endian = [] BOOL
false;




	/* COMMON CONVERSION ROUTINES */


Tokdef .~ptr_to_ptr = [a1:ALIGNMENT, a2:ALIGNMENT, p:EXP] EXP
PUN [ pointer(a1), pointer(a2), p ];


Tokdef .~ptr_to_int = [a:ALIGNMENT, v:VARIETY, p:EXP] EXP
([v] PUN [ pointer(a), integer(PTR_V), p ]);


Tokdef .~int_to_ptr = [v:VARIETY, a:ALIGNMENT, i:EXP] EXP
PUN [ integer(PTR_V), pointer(a), [PTR_V] i ];


Tokdef .~f_to_ptr = [a:ALIGNMENT, fn:EXP] EXP
PUN [ proc, pointer(a), fn ];


Tokdef .~ptr_to_f = [a:ALIGNMENT, p:EXP] EXP
PUN [ pointer(a), proc, p ];




Keep (
.~rep_var_width, .~rep_atomic_width,
.~rep_fv, .~rep_fv_width, .~rep_fv_radix, .~rep_fv_mantissa, .~rep_fv_min_exp, 
.~rep_fv_max_exp, .~rep_fv_epsilon, .~rep_fv_min_val, .~rep_fv_max_val,
.~ptr_width, .~best_div, .~little_endian,
.~ptr_to_ptr, .~ptr_to_int, .~int_to_ptr, .~f_to_ptr, .~ptr_to_f
)
