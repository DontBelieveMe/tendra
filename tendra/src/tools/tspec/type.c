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
#include "fmm.h"
#include "msgcat.h"

#include "object.h"
#include "hash.h"
#include "type.h"
#include "utility.h"


/*
 *    FUNDAMENTAL TYPES
 *
 *    These types represent the fundamental C types.
 */

#define BUILTIN(TYPE, NAME, VERS, ID)	type *TYPE
#include "builtin.h"


/*
 *    INITIALISE THE FUNDAMENTAL TYPES
 *
 *    This routine initialises the fundamental C types.
 */

void
init_types(void)
{
#define BUILTIN(TYPE, NAME, VERS, ID)\
    TYPE = make_type (NAME, VERS, ID)
#include "builtin.h"
    return;
}


/*
 *    FIND THE NAMESPACE FOR A TYPE IDENTIFIER
 *
 *    This routine returns the hash table for types with identifier id.  In
 *    most cases this is types, but it can be tags.  If flds is true the
 *    corresponding field hash table is returned.
 */

static hash_table *
find_namespace(int id, int fld)
{
    switch (id) {
	case TYPE_STRUCT_TAG :
	case TYPE_UNION_TAG :
	case TYPE_ENUM_TAG : {
	    return (fld ? tag_fields : tags);
	}
    }
    return (fld ? type_fields : types);
}


/*
 *    ALLOCATE A NEW TYPE
 *
 *    This routine allocates space for a new type.
 */

static type *
new_type(void)
{
    type *t;
    t = xalloc (sizeof (*t));
    t->state = 0;
    return (t);
}


/*
 *    FIND A BASIC TYPE
 *
 *    This routine maps the combination of basic type specifiers n to a
 *    type.
 */

type *
basic_type(unsigned n)
{
    type *t;
    switch (n) {
	case BTYPE_CHAR : {
	    t = type_char;
	    break;
	}
	case (BTYPE_SIGNED | BTYPE_CHAR) : {
	    t = type_schar;
	    break;
	}
	case (BTYPE_UNSIGNED | BTYPE_CHAR) : {
	    t = type_uchar;
	    break;
	}
	case BTYPE_SHORT :
	case (BTYPE_SHORT | BTYPE_INT) : {
	    t = type_short;
	    break;
	}
	case (BTYPE_SIGNED | BTYPE_SHORT) :
	case (BTYPE_SIGNED | BTYPE_SHORT | BTYPE_INT) : {
	    t = type_sshort;
	    break;
	}
	case (BTYPE_UNSIGNED | BTYPE_SHORT) :
	case (BTYPE_UNSIGNED | BTYPE_SHORT | BTYPE_INT) : {
	    t = type_ushort;
	    break;
	}
	case BTYPE_INT : {
	    t = type_int;
	    break;
	}
	case BTYPE_SIGNED :
	case (BTYPE_SIGNED | BTYPE_INT) : {
	    t = type_sint;
	    break;
	}
	case BTYPE_UNSIGNED :
	case (BTYPE_UNSIGNED | BTYPE_INT) : {
	    t = type_uint;
	    break;
	}
	case BTYPE_LONG :
	case (BTYPE_LONG | BTYPE_INT) : {
	    t = type_long;
	    break;
	}
	case (BTYPE_SIGNED | BTYPE_LONG) :
	case (BTYPE_SIGNED | BTYPE_LONG | BTYPE_INT) : {
	    t = type_slong;
	    break;
	}
	case (BTYPE_UNSIGNED | BTYPE_LONG) :
	case (BTYPE_UNSIGNED | BTYPE_LONG | BTYPE_INT) : {
	    t = type_ulong;
	    break;
	}
	case (BTYPE_LONG | BTYPE_LLONG) :
	case (BTYPE_LONG | BTYPE_LLONG | BTYPE_INT) : {
	    t = type_llong;
	    break;
	}
	case (BTYPE_SIGNED | BTYPE_LONG | BTYPE_LLONG) :
	case (BTYPE_SIGNED | BTYPE_LONG | BTYPE_LLONG | BTYPE_INT) : {
	    t = type_sllong;
	    break;
	}
	case (BTYPE_UNSIGNED | BTYPE_LONG | BTYPE_LLONG) :
	case (BTYPE_UNSIGNED | BTYPE_LONG | BTYPE_LLONG | BTYPE_INT) : {
	    t = type_ullong;
	    break;
	}
	default : {
	    if (n == BTYPE_FLOAT) {
			t = type_float;
	    } else if (n == BTYPE_DOUBLE) {
			t = type_double;
	    } else if (n == (BTYPE_LONG | BTYPE_DOUBLE)) {
			t = type_ldouble;
	    } else if (n == BTYPE_VOID) {
			t = type_void;
	    } else {
			MSG_invalid_type_specifier ();
			t = type_int;
	    }
	    break;
	}
    }
    return (t);
}


/*
 *    FIND A SPECIAL TYPE NAME
 *
 *    This routine returns the special type described by the string s.
 */

type *
special_type(char *s)
{
    if (streq (s, "bottom")) return (type_bottom);
    if (streq (s, "printf")) return (type_printf);
    if (streq (s, "scanf")) return (type_scanf);
    MSG_unknown_special_type (s);
    return (type_int);
}


/*
 *    MAKE A NEW TYPE
 *
 *    This routine creates a type called nm (version vers) with identifier id.
 */

type *
make_type(char *nm, int vers, int id)
{
    type *t = new_type ();
    object *p = make_object (nm, OBJ_TYPE);
    p->u.u_type = t;
    t->id = id;
    t->u.obj = p;
    t->v.obj2 = null;
    p = add_hash (find_namespace (id, 0), p, vers);
    return (p->u.u_type);
}


/*
 *    FIND A TYPE
 *
 *    This routine looks up a type called nm (version vers) with identifier
 *    id.  If it does not exist then it creates one, also printing an error
 *    if force is true.
 */

type *
find_type(char *nm, int vers, int id, int force)
{
    type *t;
    object *p;
    hash_table *h = find_namespace (id, 0);
    p = search_hash (h, nm, vers);
    if (p == null) {
		if (force == 0) return (null);
		MSG_type_not_defined (h->name, nm);
		return (make_type (nm, vers, id));
    }
    t = p->u.u_type;
    if (id != TYPE_GENERIC && id != t->id) {
		MSG_type_used_inconsistently (h->name, nm, p->filename, p->line_no);
    }
    return (t);
}


/*
 *    CREATE A NEW COMPOUND TYPE
 *
 *    This routine creates a compound type with identifier id and subtype t.
 */

type *
make_subtype(type *t, int id)
{
    type *s = new_type ();
    s->id = id;
    s->u.subtype = t;
    s->v.obj2 = null;
    return (s);
}


/*
 *    FORM A QUALIFIED TYPE
 *
 *    This type forms a type from the incomplete type qualifier s and
 *    the type t.
 */

type *
inject_type(type *s, type *t)
{
    type *p = s;
    if (p == null) return (t);
    if (t) {
		while (p->u.subtype) p = p->u.subtype;
		p->u.subtype = t;
    }
    return (s);
}


/*
 *    CONSTRUCT A FIELD
 *
 *    This routine creates a field called nm (version vers) which is a field
 *    of the structure of union s of type t.
 */

field *
make_field(char *nm, int vers, type *s, type *t)
{
    char *n;
    field *r;
    object *p = make_object (nm, OBJ_FIELD);
    r = xalloc (sizeof (*r));
    r->obj = p;
    r->stype = s;
    r->ftype = t;
    n = strchr (nm, '.');
    r->fname = (n ? n + 1 : nm);
    p->u.u_field = r;
    p = add_hash (find_namespace (s->id, 1), p, vers);
    return (p->u.u_field);
}


/*
 *    EXPAND A TYPE
 *
 *    This routine expands the type t by replacing any typedefs by their
 *    definitions.
 */

type *
expand_type(type *t)
{
    while (t && t->id == TYPE_DEFINED) {
		t = t->v.next;
    }
    return (t);
}


/*
 *    AUXILIARY TYPE CHECKING ROUTINE
 *
 *    This routine applies various checks to the type t.
 */

static type *
check_type_aux(type *t, int obj, int c, int ret)
{
    if (t == null) return (null);
    switch (t->id) {
	case TYPE_VOID : {
	    if ((obj || c) && !ret) {
			MSG_type_void_is_incomplete ();
	    }
	    break;
	}
	case TYPE_ARRAY : {
	    if (c && t->v.str [0] == 0) {
			MSG_incomplete_array_type ();
	    }
	    if (ret) {
			MSG_function_cant_return_an_array ();
	    }
	    t->u.subtype = check_type_aux (t->u.subtype, 1, 1, 0);
	    break;
	}
	case TYPE_BITFIELD : {
	    type *s = expand_type (t->u.subtype);
	    if (s) {
			switch (s->id) {
		    case TYPE_INT :
		    case TYPE_SIGNED :
		    case TYPE_UNSIGNED : {
				break;
		    }
		    default : {
				MSG_non_integral_bitfield_type ();
				break;
		    }
			}
	    }
	    break;
	}
	case TYPE_QUALIFIER : {
	    t->u.subtype = check_type_aux (t->u.subtype, obj, c, ret);
	    break;
	}
	case TYPE_LIST : {
	    t->u.subtype = check_type_aux (t->u.subtype, obj, c, ret);
	    t->v.next = check_type_aux (t->v.next, obj, c, ret);
	    break;
	}
	case TYPE_LVALUE : {
	    t->u.subtype = check_type_aux (t->u.subtype, 1, 0, ret);
	    break;
	}
	case TYPE_RVALUE : {
	    t->u.subtype = check_type_aux (t->u.subtype, 1, 1, ret);
	    break;
	}
	case TYPE_PROC : {
	    if (obj) MSG_object_type_expected ();
	    t->u.subtype = check_type_aux (t->u.subtype, 1, 1, 1);
	    if (t->v.next && t->v.next->v.next == null) {
			/* Check for '(void)' */
			type *s = t->v.next->u.subtype;
			if (s && s->id == TYPE_VOID) break;
	    }
	    t->v.next = check_type_aux (t->v.next, 1, 0, 0);
	    break;
	}
	case TYPE_PTR : {
	    t->u.subtype = check_type_aux (t->u.subtype, 0, 0, 0);
	    break;
	}
	case TYPE_DEFINED : {
	    t->v.next = check_type_aux (t->v.next, obj, c, ret);
	    break;
	}
    }
    return (t);
}


/*
 *    CHECK A TYPE
 *
 *    This routine checks that the type t is a valid type for an object of
 *    type id.  It returns an equivalent type.
 */

type *
check_type(type *t, int id)
{
    if (t) {
		switch (id) {
	    case OBJ_EXP :
	    case OBJ_EXTERN : {
			t = check_type_aux (t, 1, 0, 0);
			break;
	    }
	    case OBJ_CONST :
	    case OBJ_FIELD : {
			t = check_type_aux (t, 1, 1, 0);
			break;
	    }
	    case OBJ_FUNC : {
			if (t->id != TYPE_PROC) {
				MSG_function_type_expected ();
			}
			t = check_type_aux (t, 0, 0, 0);
			break;
	    }
	    case OBJ_TYPE :
	    case OBJ_MACRO :
	    case OBJ_STATEMENT : {
			t = check_type_aux (t, 0, 0, 0);
			break;
	    }
		}
    }
    return (t);
}
