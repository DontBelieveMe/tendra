/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INSTRUCTION_INCLUDED
#define INSTRUCTION_INCLUDED

#include <stdbool.h>

struct zone_tag;

#include "../adt.h"
#include "../localnames.h"


typedef enum arg_type_tag { 
  arg_charP, arg_char_nb,  arg_nb_of_chars, 
  arg_identifier, arg_terminal,
  arg_ignore, arg_return_terminal, arg_none /*Just for error recovery*/ 
} arg_type ;

typedef struct arg_tag {
  arg_type type;
  struct arg_tag* next;
  union {
    unsigned int digit;
    char* literal;
  } u ;
  bool is_reference;
} arg;

/* ordered */
typedef struct args_list_tag {
  arg*  head ;
  arg** tail ;
  int nb_return_terminal;
} args_list ;

typedef enum instruction_type_tag { return_terminal, push_zone, pop_zone, do_nothing , action_call } instruction_type ;

typedef struct instruction_tag {
  instruction_type type;
  struct instruction_tag* next;
  union {
    char* name;  /* token   */
    struct {
      struct zone_tag* z;
      int is_beginendmarker_in_zone ;
    } s;
    struct {
      EntryT* called_act;
      args_list* lhs; 
      args_list* rhs; 
    } act;
  } u;
} instruction ;

/* ordered */
typedef struct instructions_list_tag {
  instruction* head;
  instruction** tail;
  int size;
  LocalNamesT local_names;
  int nb_return_terminal;
} instructions_list;


extern arg* add_arg (arg_type, unsigned int) ;
extern arg* add_identifier_arg ( char* ) ;
extern arg* add_reference_arg ( char* ) ;
extern arg* add_terminal_arg ( char* ) ;
extern arg* add_none_arg ( void ) ;
extern void arg_output(arg*, bool, int, FILE*);
extern args_list* add_args_list (void) ;

extern instruction * add_instruction_return_terminal (char* name);
extern instruction* add_instruction_donothing (void) ;
extern instruction * add_instruction_action (EntryT*, args_list*, args_list*) ;
extern instruction* add_instruction_mapping (char* map) ;

extern instruction* add_instruction_pushzone (struct zone_tag *z) ;
extern instruction* add_instruction_popzone (struct zone_tag *z, int is_endmarker_in_zone) ;
extern instructions_list* add_instructions_list (void) ;

extern LocalNamesT* instructionslist_localnames(instructions_list*);

#endif
