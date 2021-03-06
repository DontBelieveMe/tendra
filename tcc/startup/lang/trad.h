/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Traditional C. It is quite useless for portability
 * checking and is only provided for compiling old code.
 */

#pragma TenDRA declaration block Xt__startup begin
#pragma TenDRA begin

#include "../literal/trad.h"
#include "../promotion/sign.h"

#undef __STDC__
#define __STDC__ 0

#pragma TenDRA weak prototype analysis off
#pragma TenDRA incompatible interface declaration allow

#pragma TenDRA unify external linkage on
#pragma TenDRA linkage resolution : (internal) warning
#pragma external volatile

#pragma TenDRA directive assert allow
#pragma TenDRA directive file allow
#pragma TenDRA directive ident allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive weak allow

#pragma TenDRA compatible type : char * == void * : allow
#pragma TenDRA conditional lvalue allow
#pragma TenDRA extra ; allow
#pragma TenDRA extra bitfield int type allow
#pragma TenDRA extra type definition allow
#pragma TenDRA ignore struct/union/enum tag warning
#pragma TenDRA implicit int type for external declaration warning
#pragma TenDRA initialization of struct/union (auto) warning
#pragma TenDRA no external declaration allow
#pragma TenDRA prototype warning
#pragma TenDRA text after directive allow
#pragma TenDRA unknown escape warning
#pragma TenDRA unknown pragma warning
#pragma TenDRA weak macro equality allow

/* The pragmas below replace #pragma nepc */

#pragma TenDRA character escape overflow allow
#pragma TenDRA no nline after file end allow
#pragma TenDRA bitfield overflow allow

/* The pragmas below replace #pragma not_ansi */

#pragma TenDRA extra ... allow
#pragma TenDRA extra , allow
#pragma TenDRA incomplete type as object type allow
#pragma TenDRA dollar as ident allow
#pragma TenDRA variable initialization allow
#pragma TenDRA extra macro definition allow
#pragma TenDRA incompatible type qualifier allow
#pragma TenDRA no directive/nline after ident allow
#pragma TenDRA unknown directive allow
#pragma TenDRA no ident after # allow
#pragma TenDRA block function static allow
#pragma TenDRA unknown struct/union allow
#pragma TenDRA conversion analysis (int-pointer implicit) off
#pragma TenDRA conversion analysis (pointer-pointer implicit) off

#ifndef __NO_PRINTF_CHECKS
#define __NO_PRINTF_CHECKS 1
#endif

#pragma TenDRA declaration block end

