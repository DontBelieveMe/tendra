/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef STR_OPS_H_INCLUDED
#define STR_OPS_H_INCLUDED

/* Operations for union STRING */

#define TAG_str(P)			((unsigned) 0)


/* Operations for component next of union STRING */

#define str_next(P)			(CHECK_NULL(P) + 0)


/* Operations for field simple of union STRING */

#define str_simple_tag			((unsigned)0)
#define IS_str_simple(P)		1

#define str_simple_len(P)		((P) + 1)
#define str_simple_text(P)		((P) + 2)
#define str_simple_kind(P)		((P) + 3)
#define str_simple_tok(P)		((P) + 4)

#define MAKE_str_simple(len_, text_, kind_, c_class_str)\
    {\
	c_class *x483_ = GEN_c_class(5, TYPEID_str);\
	COPY_str(x483_ + 0, NULL_str);\
	COPY_ulong(x483_ + 1, (len_));\
	COPY_string(x483_ + 2, (text_));\
	COPY_unsigned(x483_ + 3, (kind_));\
	COPY_ulong(x483_ + 4, LINK_NONE);\
	(c_class_str) = x483_;\
    }

#define DECONS_str_simple(next_, len_, text_, kind_, tok_, c_class_str)\
    {\
	c_class *x484_ = (c_class_str);\
	(next_) = DEREF_str(x484_ + 0);\
	(len_) = DEREF_ulong(x484_ + 1);\
	(text_) = DEREF_string(x484_ + 2);\
	(kind_) = DEREF_unsigned(x484_ + 3);\
	(tok_) = DEREF_ulong(x484_ + 4);\
    }

#define DESTROY_str_simple(destroyer_, next_, len_, text_, kind_, tok_, c_class_str)\
    {\
	c_class *x485_ = (c_class_str);\
	(next_) = DEREF_str(x485_ + 0);\
	(len_) = DEREF_ulong(x485_ + 1);\
	(text_) = DEREF_string(x485_ + 2);\
	(kind_) = DEREF_unsigned(x485_ + 3);\
	(tok_) = DEREF_ulong(x485_ + 4);\
	(destroyer_)(x485_, (unsigned)5);\
    }


#endif
