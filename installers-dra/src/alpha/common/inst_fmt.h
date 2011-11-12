/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   instfmtdecs.h
   declarations of functions used to output assembler instructions.
*/
#ifndef INSTFMTDECS_H
#define INSTFMTDECS_H
#include "addresstypes.h"
#include "cross.h"
#include "instypes.h"
#include "ins_data.h"
#include "exptypes.h"
#include "procrectypes.h"
#include "installtypes.h"
#if DO_SCHEDULE
#include "scheduler.h"
#endif
#define IMMEDIATE_MAX	255
#define IMMEDIATE_MIN	-128

extern char *outass(char *);
extern void load_store(instruction,int,baseoff);
extern void load_store_immediate(instruction,int,INT64);
extern void load_store_label(instruction,int,int);
extern void integer_branch(instruction,int,int);
extern void integer_jump(instruction,int,int,int);
extern void integer_jump_external(instruction,int,baseoff);
extern void integer_jump_fn(instruction,int,exp,space);
extern void operate_fmt(instruction,int,int,int);
extern void operate_fmt_immediate(instruction,int,int,int);
extern void operate_fmt_big_immediate(instruction,int,INT64,int);
extern void float_load_store(instruction,int,baseoff);
extern void float_branch(instruction,int,int);
extern void float_op(instruction,int,int,int);
extern void float_convert(instruction,int,int);
extern void float_load_store_immediate(instruction,int,char*);
extern void call_pal(instruction, instruction);
extern void fetch(instruction,baseoff);
extern void no_parameter_instructions(instruction);
extern void single_parameter_instructions(instruction,int);
extern void memory_fmt(instruction,int,int);
extern void operate_fmt(instruction,int,int,int);
#if DO_SCHEDULE
extern void out_code(Instruction_data);
extern void add_instruction(Instruction);
extern Instruction_data get_new_ins_data(void);
extern void output_instruction(Class,char*,char*);
extern void output_data(char*,char*);

typedef struct String_dat
{
    char data;
    struct String_dat *next;
} StringData;

typedef struct
{
    StringData *head,*tail;
} String;

#else
#define output_instruction(class,string,op)op
#define output_data(string,op)op
#endif

#endif /*INSTFMTDECS_H*/






