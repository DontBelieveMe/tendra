/* $TenDRA$ */
#include "ansi.h"

#undef	__STDC_VERSION__
#define	__STDC_VERSION__	199901
#define	__WRONG_ISO99_FENV_H
#define	__WRONG_ISO99_MATH_H

#include <osreldate.h>
#if __FreeBSD_version < 502113
#define	__WRONG_ISO99_STDINT_H
#endif
