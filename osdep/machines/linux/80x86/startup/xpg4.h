/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "ansi.h"

#define _XOPEN_SOURCE 1
#define _XOPEN_VERSION 4

#ifdef _GLIBC2_14
#define __WRONG_XPG4_WCHAR_H /* incompatible fputwc and friends */
#define __WRONG_XPG4_SYS_SHM_H_SHM_PROTO /* incompatible shm.shmid_ds.shm_segsz */
#define __WRONG_XPG4_SYS_SEM_H_SEM_PROTO /* incompatible sem.semid_ds.sem_nsems */
#define __WRONG_XPG4_SYS_SHM_H /* incompatible shmid_ds.shm_segsz */
#define __WRONG_XPG4_SYS_SEM_H /* incompatible sem.semid_ds.sem_nsems */
#endif

