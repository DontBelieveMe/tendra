/*
 * Copyright (c) 2003, The Tendra Project <http://www.tendra.org/>
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
 *  		 Crown Copyright (c) 1997
 *  
 *  This TenDRA(r) Computer Program is subject to Copyright
 *  owned by the United Kingdom Secretary of State for Defence
 *  acting through the Defence Evaluation and Research Agency
 *  (DERA).  It is made available to Recipients with a
 *  royalty-free licence for its use, reproduction, transfer
 *  to other parties and amendment for any purpose not excluding
 *  product development provided that any such use et cetera
 *  shall be deemed to be acceptance of the following conditions:-
 *  
 *      (1) Its Recipients shall ensure that this Notice is
 *      reproduced upon any copies or amended versions of it;
 *  
 *      (2) Any amended version of it shall be clearly marked to
 *      show both the nature of and the organisation responsible
 *      for the relevant amendment or amendments;
 *  
 *      (3) Its onward transfer from a recipient to another
 *      party shall be deemed to be that party's acceptance of
 *      these conditions;
 *  
 *      (4) DERA gives no warranty or assurance as to its
 *      quality or suitability for any purpose and DERA accepts
 *      no liability whatsoever in relation to any use to which
 *      it may be put.
 *
 * $TenDRA$
 */


#ifndef CHAR_INCLUDED
#define CHAR_INCLUDED


/*
    TYPE REPRESENTING A CHARACTER

    A character consists of a single letter (which may have associated
    data) plus pointers to the next character and to a list of alternative
    characters.
*/

typedef unsigned int letter ;

typedef struct character_tag {
    letter ch ;
    char *defn ;
    char *args ;
    char *cond ;
    struct character_tag *opt ;
    struct character_tag *next ;
} character ;


/*
    TYPE REPRESENTING A CHARACTER GROUP

    A character group is a named array of letters.
*/

typedef struct {
    char *name ;
    letter *defn ;
} char_group ;


/*
    TYPE REPRESENTING A KEYWORD

    A keyword consists of a name plus some associated data.  All keywords
    are formed into a list using the next field.  done is a flag used in
    the output routines.
*/

typedef struct keyword_tag {
    char *name ;
    char *defn ;
    char *args ;
    char *cond ;
    int done ;
    struct keyword_tag *next ;
} keyword ;


/*
    PARAMETERS
*/

#define MAX_GROUPS		31


/*
    SPECIAL LETTERS
*/

#define SIMPLE_LETTER		( ( letter ) 0x0100 )
#define EOF_LETTER		( ( letter ) 0x0100 )
#define LAST_LETTER		( ( letter ) 0x0101 )
#define WHITE_LETTER		( ( letter ) 0x0102 )
#define GROUP_LETTER		( ( letter ) 0x0103 )


/*
    DECLARATIONS FOR CHARACTER ROUTINES
*/

extern letter *white_space ;
extern character *pre_pass ;
extern character *main_pass ;
extern char_group groups [] ;
extern int no_groups ;
extern keyword *keywords ;
extern void add_char PROTO_S ( ( character *, letter *, char ** ) ) ;
extern void make_group PROTO_S ( ( char *, letter * ) ) ;
extern int in_group PROTO_S ( ( letter *, letter ) ) ;
extern letter *make_string PROTO_S ( ( char * ) ) ;
extern letter find_escape PROTO_S ( ( int ) ) ;
extern void add_keyword PROTO_S ( ( char *, char ** ) ) ;


#endif
