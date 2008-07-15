/* 
 *  Copyright (c) 2002-2008 The TenDRA Project <http://www.tendra.org/>.
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. Neither the name of The TenDRA Project nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific, prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 *  IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * $Id$
 * 
 */


/*
 * Automatically generated by lexi version 2.0
 */

#include "lctlexer.h"


/* Cfile lct header */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/* LOOKUP TABLE */

typedef uint8_t lookup_type;
static lookup_type lookup_tab[257] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00
};

void lexi_lct_push(struct lexi_lct_state *state, const int c) {
	assert(state);
	assert(state->buffer_index < sizeof state->buffer / sizeof *state->buffer);
	state->buffer[state->buffer_index++] = c;
}

int lexi_lct_pop(struct lexi_lct_state *state) {
	assert(state);
	assert(state->buffer_index > 0);
	return state->buffer[--state->buffer_index];
}

void lexi_lct_flush(struct lexi_lct_state *state) {
	state->buffer_index = 0;
}

int lexi_lct_readchar(struct lexi_lct_state *state) {
	if(state->buffer_index) {
		return lexi_lct_pop(state);
	}

	return lexi_lct_getchar();
}

bool lexi_lct_group(enum lexi_lct_groups group, int c) {
	return lookup_tab[c] & group;
}


#include <string.h>
int lexi_lct_keyword(const char *identifier, int notfound) {
	if(!strcmp(identifier, "ACTION")) return lct_lex_action_Hkw;
	if(!strcmp(identifier, "HEADERS")) return lct_lex_header_Hkw;
	if(!strcmp(identifier, "MAP")) return lct_lex_map_Hkw;
	if(!strcmp(identifier, "TRAILERS")) return lct_lex_trailer_Hkw;
	return notfound;
}
/* PRE-PASS ANALYSERS */

void lexi_lct_init(struct lexi_lct_state *state) {
	state->zone_function = lexi_lct_read_token;
	state->buffer_index = 0;
}
/* ZONES PASS ANALYSER PROTOTYPES*/

static int lexi_lct_read_token_code_area(struct lexi_lct_state *state);
static int lexi_lct_read_token_LineComment(struct lexi_lct_state *state);
static int lexi_lct_read_token_Comment(struct lexi_lct_state *state);
/* MAIN PASS ANALYSERS */

/* MAIN PASS ANALYSER for zone code_area*/

static int
lexi_lct_read_token_code_area(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (lexi_lct_group(lexi_lct_group_code_area_white, c0)) goto start;
		if (c0 == '@') {
			int c1 = lexi_lct_readchar(state);
			if (c1 == '&') {
				int c2 = lexi_lct_readchar(state);
				if (lexi_lct_group(lexi_lct_group_alpha, c2)) {
					return get_code_lct_reference(c2);
				}
				lexi_lct_push(state, c2);
			} else if (c1 == '@') {
				return lct_lex_code_Hat;
			} else if (c1 == '}') {
				state->zone_function = lexi_lct_read_token;
				return lct_lex_code_Hend;
			}
			if (lexi_lct_group(lexi_lct_group_alpha, c1)) {
				return get_code_lct_identifier(c1);
			}
			lexi_lct_push(state, c1);
			return lct_lex_lone_Hcode_Hat;
		} else if (c0 == LEXI_EOF) {
			return lct_lex_code_Heof;
		}
		return get_code_lct_string(c0);
	}
}
/* MAIN PASS ANALYSER for zone LineComment*/

static int
lexi_lct_read_token_LineComment(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (lexi_lct_group(lexi_lct_group_LineComment_white, c0)) goto start;
		if (c0 == '\n') {
			state->zone_function = lexi_lct_read_token;
			return lexi_lct_read_token(state);
		}
		goto start;
	}
}
/* MAIN PASS ANALYSER for zone Comment*/

static int
lexi_lct_read_token_Comment(struct lexi_lct_state *state)
{
	start: {
		int c0 = lexi_lct_readchar(state);
		if (lexi_lct_group(lexi_lct_group_Comment_white, c0)) goto start;
		if (c0 == '*') {
			int c1 = lexi_lct_readchar(state);
			if (c1 == '/') {
				state->zone_function = lexi_lct_read_token;
				return lexi_lct_read_token(state);
			}
			lexi_lct_push(state, c1);
		}
		goto start;
	}
}
/* MAIN PASS ANALYSER for zone global*/

int
lexi_lct_read_token(struct lexi_lct_state *state)
{
	if(state->zone_function != lexi_lct_read_token)
		return (*state->zone_function)(state);
	start: {
		int c0 = lexi_lct_readchar(state);
		if (lexi_lct_group(lexi_lct_group_white, c0)) goto start;
		switch (c0) {
			case '&': {
				return lct_lex_reference;
			}
			case '(': {
				return lct_lex_open;
			}
			case ')': {
				return lct_lex_close;
			}
			case ',': {
				return lct_lex_comma;
			}
			case '-': {
				int c1 = lexi_lct_readchar(state);
				if (c1 == '>') {
					return lct_lex_arrow;
				}
				lexi_lct_push(state, c1);
				break;
			}
			case '/': {
				int c1 = lexi_lct_readchar(state);
				if (c1 == '*') {
					state->zone_function = lexi_lct_read_token_Comment;
					return lexi_lct_read_token(state);
				} else if (c1 == '/') {
					state->zone_function = lexi_lct_read_token_LineComment;
					return lexi_lct_read_token(state);
				}
				lexi_lct_push(state, c1);
				break;
			}
			case ':': {
				return lct_lex_colon;
			}
			case ';': {
				return lct_lex_semicolon;
			}
			case '=': {
				return lct_lex_define;
			}
			case '@': {
				int c1 = lexi_lct_readchar(state);
				if (c1 == '{') {
					state->zone_function = lexi_lct_read_token_code_area;
					return lct_lex_code_Hstart;
				}
				lexi_lct_push(state, c1);
				break;
			}
			case LEXI_EOF: {
				return lct_lex_eof;
			}
		}
		if (lexi_lct_group(lexi_lct_group_alpha, c0)) {
			return get_lct_identifier(c0);
		}
		return lct_lex_unknown;
	}
}

/* Cfile lct trailer */

