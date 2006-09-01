/*
    		 Crown Copyright (c) 1997, 1998
    
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
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.2)
*/

#ifndef GRAPH_OPS_H_INCLUDED
#define GRAPH_OPS_H_INCLUDED

/* Operations for union GRAPH */

#pragma token PROC(EXP : GRAPH :) EXP : unsigned : TAG_graph #
#pragma interface TAG_graph


/* Operations for component head of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(CLASS_TYPE) : graph_head #
#pragma interface graph_head

/* Operations for component access of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(DECL_SPEC) : graph_access #
#pragma interface graph_access

/* Operations for component tails of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(LIST(GRAPH)) : graph_tails #
#pragma interface graph_tails

/* Operations for component top of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(GRAPH) : graph_top #
#pragma interface graph_top

/* Operations for component equal of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(GRAPH) : graph_equal #
#pragma interface graph_equal

/* Operations for component up of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(GRAPH) : graph_up #
#pragma interface graph_up

/* Operations for component no of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(unsigned) : graph_no #
#pragma interface graph_no

/* Operations for component off of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(OFFSET) : graph_off #
#pragma interface graph_off

/* Operations for component member of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(LIST(IDENTIFIER)) : graph_member #
#pragma interface graph_member

/* Operations for component tok1 of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(ulong_type) : graph_tok1 #
#pragma interface graph_tok1

/* Operations for component tok2 of union GRAPH */

#pragma token PROC(EXP : GRAPH :)\
    EXP : PTR(ulong_type) : graph_tok2 #
#pragma interface graph_tok2

/* Operations for field basic of union GRAPH */

#pragma token EXP const : unsigned : graph_basic_tag #
#pragma token PROC(EXP : GRAPH :) EXP : int : IS_graph_basic #
#pragma interface graph_basic_tag IS_graph_basic

#pragma token PROC(\
	EXP : CLASS_TYPE :,\
	EXP : DECL_SPEC :,\
	EXP lvalue : GRAPH :\
    ) STATEMENT MAKE_graph_basic #
#pragma interface MAKE_graph_basic

#pragma token PROC(\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : GRAPH :\
    ) STATEMENT DECONS_graph_basic #
#pragma interface DECONS_graph_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : LIST(GRAPH) :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : GRAPH :\
    ) STATEMENT DESTROY_graph_basic #
#pragma interface DESTROY_graph_basic


#endif
