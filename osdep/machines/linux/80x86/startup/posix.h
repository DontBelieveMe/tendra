/* $Id$ */

#include "ansi.h"

#define _POSIX_SOURCE		1
#define _POSIX_C_SOURCE		1

#ifdef _GLIBC2_12
#define __WRONG_POSIX_SETJMP_H	/* partial */
#define __WRONG_POSIX_SIGNAL_H	/* partial */
#define __WRONG_POSIX_SIGNAL_H_SIGSET_T	/* partial */
#define __WRONG_POSIX_STDIO_H	/* i don't know what to do about va_list */
#define __WRONG_POSIX_TIME_H	/* partial */
#define __WRONG_POSIX_FCNTL_H	/* incompatible dev_t */
#define __WRONG_POSIX_STAT_H	/* incompatible dev_t */
#define __WRONG_POSIX_GRP_H	/* incompatible dev_t */
#define __WRONG_POSIX_PWD_H	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_STAT_H	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_TYPES_H_STAT_T	/* incompatible dev_t */
#define __WRONG_POSIX_UNISTD_H_TCPGRP	/* incompatible dev_t */
#define __WRONG_POSIX_UNISTD_H_U_PROTO	/* incompatible dev_t */
#define __WRONG_POSIX_UTIME_H	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_WAIT_H	/* incompatible dev_t */
#endif

#ifdef _GLIBC2_14
#define __WRONG_POSIX_GRP_H	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_STAT_H	/* incompatible dev_t */
#define __WRONG_POSIX_STDIO_H_CTUID	/* i don't know what to do about va_list */
#define __WRONG_POSIX_SYS_WAIT_H	/* incompatible dev_t */
#define __WRONG_POSIX_STDIO_H	/* i don't know what to do about va_list */
#define __WRONG_POSIX_FCNTL_H	/* incompatible dev_t */
#define __WRONG_POSIX_PWD_H	/* incompatible dev_t */
#define __WRONG_POSIX_UTIME_H	/* incompatible dev_t */
#define __WRONG_POSIX_UNISTD_H_U_PROTO	/* incompatible dev_t */
#define __WRONG_POSIX_SIGNAL_H	/* incompatible dev_t */
#define __WRONG_POSIX_SYS_TYPES_H_STAT_T	/* incompatible dev_t */
#define __WRONG_POSIX_UNISTD_H_TCPGRP	/* incompatible dev_t */
#endif

