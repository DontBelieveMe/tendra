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
+USE "bsd_extn", "sys/time.h";

+IFDEF ~protect ("svid3", "sys/types.h")

+USE ("svid3"), "sys/resource.h";

+ELSE

+TYPE (int) rlimit_t.1;

+TYPE struct rlimit.1;
+FIELD struct rlimit.1 {
    rlimit_t rlim_cur.1;
    rlimit_t rlim_max.1;
};

+CONST rlimit_t RLIM_INFINITY.1;

+CONST int RLIMIT_CORE.1;
+CONST int RLIMIT_CPU.1;
+CONST int RLIMIT_DATA.1;
+CONST int RLIMIT_FSIZE.1;
+CONST int RLIMIT_STACK.1;

+FUNC int getrlimit.1(int, struct rlimit *);
+FUNC int setrlimit.1(int, const struct rlimit *);

+ENDIF
