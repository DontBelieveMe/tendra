/* $Id$ */

#ifndef __HACKED_LIBC_STDDEF_H
#define __HACKED_LIBC_STDDEF_H

/*
 * We're providing this primarily for offset(), because the system header
 * has the typical implementation which gives a non-constant expression.
 * Unfortunately it's not in an #ifndef guard, and so we can't override
 * just that macro.
 */
#ifdef _FREEBSD8_3

#include_next <sys/cdefs.h>
#include_next <sys/_null.h>
#include_next <sys/_types.h>

typedef __ptrdiff_t ptrdiff_t;

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif

#ifndef _WCHAR_T_DECLARED
typedef __wchar_t wchar_t;
#define _WCHAR_T_DECLARED
#endif

#pragma TenDRA begin
#pragma TenDRA keyword __literal for keyword literal
#pragma TenDRA conversion analysis (pointer-int) off
#define offsetof(__s, __m) (__literal (size_t) &(((__s *) 0)->__m))
#pragma TenDRA end

#endif

#endif

