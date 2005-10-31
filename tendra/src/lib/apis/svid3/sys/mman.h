#   		 Crown Copyright (c) 1997
#
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
# $TenDRA$
#
+USE "svid3", "", "config";
+IF %% __SYSV_KERNEL_EXTENSION %%
+USE "svid3", "sys/types.h";

+CONST int PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE;
+CONST int MAP_SHARED, MAP_PRIVATE, MAP_FIXED;
+CONST int MS_ASYNC, MS_SYNC, MS_INVALIDATE;

+FUNC caddr_t mmap(caddr_t, size_t, int, int, int, off_t);
+FUNC int mprotect(caddr_t, size_t, int);
+FUNC int msync(caddr_t, size_t, int);
+FUNC int munmap(caddr_t, size_t);

+IF %% __SYSV_REAL_TIME %%

+CONST int SHARED, PRIVATE, PROC_TEXT, PROC_DATA, MC_LOCK, MC_LOCKAS;
+CONST int MC_SYNC, MC_UNLOCK, MC_UNLOCKAS, MCL_CURRENT, MCL_FUTURE;

/* Error in book? */
+FUNC int memcntl(caddr_t, size_t, caddr_t, int, int, int);
+FUNC int mlock(caddr_t, size_t);
+FUNC int munlock(caddr_t, size_t);
+FUNC int mlockall(int);
+FUNC int munlockall(void);

+ENDIF
+ENDIF
