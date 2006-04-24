/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 80x86/is_worth.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: is_worth.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/01/30  12:56:29  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.5  1994/07/15  13:58:07  jmf
 * Admit global real consts. Safeguard father.
 *
 * Revision 1.4  1994/07/12  15:13:07  jmf
 * protected father for test_tag
 *
 * Revision 1.3  1994/07/12  15:12:11  jmf
 * Replaced keywords
 *
 * Revision 1.1  1994/07/12  14:35:40  jmf
 * Initial revision
 *
**********************************************************************/


#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "is_worth.h"

/* PROCEDURES */

int is_worth
(exp c)
{
				/* decide if constant c is worth declaring
				   separately */
  unsigned char cnam = name(c);

  if (name(sh(c)) == realhd && cnam == cont_tag &&
	name(son(c)) == name_tag && isvar(son(son(c))) &&
	isglob(son(son(c))))
    return 1;

  if (cnam == cont_tag && name(son(c)) == name_tag &&
       !isvar(son(son(c)))) {
    return 1;
  }

  return((!is_o(cnam) && cnam != clear_tag &&
	   cnam != int_to_bitf_tag && cnam != bitf_to_int_tag) ||
  /* ignore simple things unless ... */
     (cnam == cont_tag && name(son(c)) == cont_tag &&
	name(son(son(c))) == name_tag)
      || (cnam == name_tag &&
         (isloadparam(son(c)) || isparam(son(c))) &&
          !isvar(son(c)) &&
          shape_size(sh(c)) <= 32

          && name(sh(c))!= shrealhd

        )
      || (cnam == cont_tag && name(son(c)) == name_tag &&
	   isvar(son(son(c))) && isglob(son(son(c))) &&
	  ((last(c) && bro(c)!= nilexp) ||
		(!last(c) && last(bro(c)) && bro(bro(c))!= nilexp)) &&
	   name(father(c)) == test_tag)
   );
}
