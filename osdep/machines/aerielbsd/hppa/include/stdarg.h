/* $Id$ */

#ifndef __HACKED_STDARG_H
#define __HACKED_STDARG_H

/*
 * libc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */
#ifdef _AERIELBSD1
#ifndef __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS

typedef double * va_list;

/*
 * The tokens __va_t, __va_start, va_arg and va_end are as in the
 * ansi:stdarg header. The only difference is that va_list is defined
 * as its implementation type, rather than being a tokenised type.
 */

#pragma token TYPE __va_t # ~__va_t
#pragma token PROC ( EXP rvalue : __va_t : ) EXP rvalue : va_list : __va_start # ansi.stdarg.__va_start
#pragma token PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : va_arg # ansi.stdarg.va_arg
#pragma token PROC ( EXP lvalue : va_list : ) EXP rvalue : void : va_end # ansi.stdarg.va_end
#pragma interface __va_t __va_start va_arg va_end

#pragma TenDRA ident ... allow

#define va_start(__ap, __arg) ((void) ((__ap) = __va_start(...)))

#else

/*
 * Implementation of stdarg
 */

#include_next <machine/stdarg.h>

#endif
#endif

#endif

