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
#include "defs.h"
#include "fmm.h"
#include "msgcat.h"
#include "streams.h"
#include "enc_nos.h"
#include "errors.h"


TDF * current_TDF;

static Chunk * free_chunks = (Chunk*)0;


Chunk *
create_chunk(void)
{
    Chunk * ans;
    if (free_chunks != (Chunk*)0) {
		ans = free_chunks;
		free_chunks = free_chunks->next;
    } else {
		ans = xalloc(sizeof(*ans));
    }
    ans->next = (Chunk*)0;
    ans->usage = 0;
    ans->offst = 0;  ans->aligned = 0;
    ans->data[0] = 0;
    return ans;
}


static void
free_chunk(Chunk * x)
{
    x->next = free_chunks;
    free_chunks = x;
}


void
out_basic_int(unsigned long num, unsigned int bts)
    /* outputs num onto current stream in bts bits */
{
    Chunk * t_ch = current_TDF->last;
    unsigned disp = t_ch->offst;
    unsigned space = 8 - disp;
    for (;bts>=space;bts-=space,space=8,disp=0){
		(t_ch->data)[t_ch->usage]|=UC((num>>(bts-space))&255);
		t_ch->usage+=1;t_ch->offst=0;
		if (t_ch->usage == DATA_SIZE) {
			Chunk * nch = create_chunk();
			t_ch->next = nch;
			current_TDF->last = nch;
			t_ch = nch;
		}
		else (t_ch->data)[t_ch->usage] = 0;
    }
    if (bts){
		unsigned garbage=8-bts;
		(t_ch->data)[t_ch->usage]|=UC(((num<<garbage)&255)>>disp);
		t_ch->offst+=UC(bts);
    }
}


void
append_TDF(TDF * tdf, Bool free_it) /* appends the stream tdf onto current stream; if free_it, chunks in tdf will be reused */
{
    Chunk * t_ch = current_TDF->last;
    Chunk * a_ch = tdf->first;

    if (t_ch->usage < DATA_SIZE -1 - a_ch->usage) {
		/* room to put it in current chunk */
		int i;
		int offst = a_ch->offst;
		Chunk * nextch = a_ch->next;
		for (i=0; i<a_ch->usage; i++) {
			out_basic_int(UL(a_ch->data[i]),UI(8));
		}
		if (a_ch ->offst != 0) {
			out_basic_int(UL(a_ch->data[i])>>(8-offst), UI(offst));
		}
		if (free_it) free_chunk(a_ch);
		a_ch = nextch;
    }
    if (a_ch != (Chunk*)0) {
		if (free_it) {	/* use existing chunks */
			t_ch->next = a_ch;
			current_TDF->last = tdf->last;
		} else {  /* copy chunks */
			while (a_ch != (Chunk*)0) {
				Chunk *nch = create_chunk();
				t_ch->next = nch;
				t_ch = current_TDF->last = nch;
				*nch = *a_ch;
				a_ch = a_ch->next;
			}
		}
    }
    SET_RSORT(tdf->sort);
    if (free_it) {
		tdf->first = tdf->last = (Chunk*)0; /* Don't use it again! */
    }
    return;
}


unsigned long
bits_in_TDF(TDF * tdf)
{
    Chunk * t_ch = tdf->first;
    unsigned long ans = 0;
    while (t_ch != (Chunk*)0) {
		Assert(!t_ch->aligned);
		ans+= (UL(t_ch->usage)<<3) + UL(t_ch->offst);
		t_ch = t_ch->next;
    }
    return ans;
}


void
out_extendable_int(unsigned long num, unsigned int bts)
{
    if (num < (UL(1)<<bts)) {
		out_basic_int(num,bts);
    } else {
		out_basic_int(UL(0), bts);
		out_extendable_int(num-(UL(1)<<bts)+1, bts);
    }
}


void
out_tdfint32(unsigned long n) /* output 32 bit int as tdfint */
{
    int sh;
    Bool sig = 0;
    for (sh=30; sh>0; sh-=3) {
		unsigned long i = (n>>sh)&7;
		if (sig || i!=0) {
			out_basic_int(i, UI(4));
			sig = 1;
		}
    }
    out_basic_int((n &7)+8, 4);
    SET_RSORT(s_tdfint);
}


void
out_tdfbool(Bool b)
{
    out_basic_int(UL(b), UI(1));
    SET_RSORT(s_tdfbool);
}


void
out_tdfstring_bytes(char * s, unsigned int k,
					unsigned int n)
{
    unsigned int i;
    out_tdfint32(UL(k));
    out_tdfint32(UL(n));
    for (i=0; i<n; i++) {
		out_basic_int(UL(s[i]), k);
    }
    SET_RSORT(s_tdfstring);
}


void
byte_align()
{
    Chunk * ch = current_TDF->last;
    if (ch->aligned !=0) {
		if (ch->offst !=0) out_basic_int(UL(0), UI(8-ch->offst));
		Assert(ch->offst == 0);
    } else {
		Chunk * nch = create_chunk();
		nch->aligned = 1;
		ch->next = nch;
		current_TDF->last = nch;
    }
}


void
out_tdfident_bytes(char *s)
{
    unsigned long i;
    unsigned long n = (unsigned long) strlen(s);
    byte_align();
    out_tdfint32(UL(8));
    out_tdfint32(n);
    byte_align();
    for (i=0; i<n; i++) {
		out_basic_int(UL(s[i]), UI(8));
    }
    SET_RSORT(s_tdfident);
}


void
append_bytestream(TDF * tdf, Bool free_it)
{
    unsigned long len = bits_in_TDF(tdf);
    unsigned long lenb = (len+7)>>3;
    out_tdfint32(lenb);
    byte_align();
    append_TDF(tdf, free_it);
    if ((lenb<<3) != len) {
		out_basic_int(UL(0), UI((lenb<<3)-len));
    }
    SET_RSORT(s_bytestream);
}
