/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "system.h"
#include "c_types.h"
#include "error.h"
#include "file.h"
#include "ustring.h"
#include "xalloc.h"


/*
 *    FILE SEEKING FLAG
 *
 *    The flag good_fseek is true if a simple fseek on the byte count has
 *    the desired effect, and false otherwise (for example on DOS machines).
 *    Similarly binary_mode is true if there are separate text and binary
 *    file modes.  The flag good_stat is true if the st_dev and st_ino
 *    fields of struct stat are sufficient to uniquely identify a file
 *    (this may not be true for machines with small ino_t types and
 *    file systems mounted from machines with large ino_t types).
 */

int good_fseek = 1;
int good_stat = 0;
int text_mode = 0;
int binary_mode = 0;
int file_sep = '/';
int drive_sep = 0;


/*
 *    SEEK A POSITION IN A FILE
 *
 *    This routine seeks a position n bytes from the start of the file f.
 *    It returns 0 if good_fseek is false, otherwise it returns 1 for
 *    successful seeks and -1 otherwise.
 */

int
file_seek(FILE *f, long n)
{
    if (n == 0) {
		/* Can always rewind a file */
		rewind (f);
		return (1);
    }
    if (good_fseek) {
		/* Use fseek if it works */
		int s = fseek (f, n, SEEK_SET);
		if (s == -1) return (-1);
		return (1);
    }
    return (0);
}


/*
 *    CONVERT A TIME TO AN UNSIGNED LONG
 *
 *    This macro converts the time_t value A to an unsigned long.  Since
 *    time_t may be any arithmetic type, this may not be totally portable.
 */

#define time_value(A)		((unsigned long) (A))


/*
 *    CURRENT TIME
 *
 *    These variables are used to hold the current time as a struct tm.
 *    The date is also used to form a string which is unique for each
 *    translation unit.
 */

char uniq_string [50];
unsigned long crt_time = 0;
static int have_crt_time = 0;
static struct tm crt_time_str;


/*
 *    FIND THE CURRENT TIME
 *
 *    This routine assigns the current time to the variables above, returning
 *    a pointer to crt_time_str.  Note that the actual time is taken only the
 *    first time the function is called.
 */

static struct tm
*get_crt_time()
{
    if (!have_crt_time) {
		const char *s1, *s2;
		time_t t = time (NIL (time_t));
		if (t == (time_t) -1) {
			/* Use a (seemingly) random date if time fails */
			struct tm *st = &crt_time_str;
			st->tm_mday = 24;
			st->tm_mon = 6 /* July */;
			st->tm_year = 62;
			st->tm_hour = 23;
			st->tm_min = 30;
			st->tm_sec = 0;
			error (ERROR_INTERNAL, "Can't find current date");
		} else {
			struct tm *st = localtime (&t);
			crt_time_str = *st;
			crt_time = time_value (t);
		}
		have_crt_time = 1;
		s1 = find_time ("%.2d%.2d%.2d");
		s2 = find_date ("%s%.2d_%d");
		sprintf_v (uniq_string, "%s_%s", s1, s2);
    }
    return (&crt_time_str);
}


/*
 *    PRINT THE CURRENT DATE
 *
 *    This routine returns a string giving the current date in the form
 *    given by fmt.  This is used in the __DATE__ built-in macro.
 */

const char
*find_date(const char *fmt)
{
    static char buff [20];
    static const char *month_name [12] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    struct tm *st = get_crt_time ();
    int day = st->tm_mday;
    const char *month = month_name [ st->tm_mon ];
    int year = 1900 + st->tm_year;
    sprintf_v (buff, fmt, month, day, year);
    return (buff);
}


/*
 *    PRINT THE CURRENT TIME
 *
 *    This routine returns a string giving the current time in the form
 *    given by fmt.  This is used in the __TIME__ built-in macro.
 */

const char
*find_time(const char *fmt)
{
    static char buff [20];
    struct tm *st = get_crt_time ();
    int hour = st->tm_hour;
    int min = st->tm_min;
    int sec = st->tm_sec;
    sprintf_v (buff, fmt, hour, min, sec);
    return (buff);
}


/*
 *    FIND FILE STATISTICS
 *
 *    This routine finds the file statistics for the file with pathname nm
 *    and assigns them into fs.  It returns fs if this is successful and the
 *    null pointer otherwise.
 */

STAT_TYPE
*stat_func(char *nm, STAT_TYPE *fs)
{
#if FS_POSIX
    int s = stat (nm, fs);
    if (s != -1) return (fs);
#endif
    UNUSED (nm);
    return (NULL);
}


/*
 *    FIND A FILE DATE
 *
 *    This routine converts the date from the file statistics fs to an
 *    unsigned long.
 */

unsigned long
stat_date(STAT_TYPE *fs)
{
    unsigned long date = 0;
    if (fs) date = time_value (fs->st_mtime);
    return (date);
}


/*
 *    ARE TWO FILES EQUAL?
 *
 *    This routine checks whether the files given by the statistics fs and
 *    gs represent the same file.  Two files are the same if their device
 *    and inode numbers are equal (except on machines where good_stat is
 *    false).
 */

int
stat_equal(STAT_TYPE *fs, STAT_TYPE *gs)
{
    if (fs && gs) {
		if (fs->st_dev == gs->st_dev && fs->st_ino == gs->st_ino) {
			return (good_stat);
		}
    }
    return (0);
}


/*
 *    FIND THE CURRENT WORKING DIRECTORY
 *
 *    This routine finds the current working directory, returning '.' if
 *    this cannot be found.
 */

const char
*find_cwd()
{
    static const char *crt_directory = NULL;
    if (crt_directory == NULL) {
#if FS_POSIX
		char buff [1024];
		char *nm = getcwd (buff, 1024);
		if (nm) {
			/* Copy result */
			string dir = xustrcpy (ustrlit (nm));
			dir = make_pathname (dir);
			crt_directory = strlit (dir);
		} else {
			crt_directory = ".";
		}
#else
		crt_directory = ".";
#endif
    }
    return (crt_directory);
}


/*
 *    FIND THE CURRENT MACHINE
 *
 *    This routine finds the name of the machine on which the program is
 *    running, returning the empty string if this cannot be found.
 */

const char
*find_machine()
{
    static const char *machine_name = NULL;
    if (machine_name == NULL) {
#if FS_UTSNAME
		struct utsname un;
		if (uname (&un) != -1) {
			string s = ustrlit (un.nodename);
			s = xustrcpy (s);
			machine_name = strlit (s);
			return (machine_name);
		}
#endif
		machine_name = "";
    }
    return (machine_name);
}
