
/*
 * Automatically generated by lexi version 2.0
 */

#include "lexer.h"



	/* $Id$ */

	/*
	 * Copyright 2002-2011, The TenDRA Project.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#include <stdio.h>
	#include <string.h>
	#include <ctype.h>

	#include <shared/error.h>
	#include <shared/xalloc.h>

	#include "lexer.h"
	#include "syntax.h"

	struct lexi_state lexer_state;

	/*
	 * This buffer is used by read_token to hold the values of identifiers
	 * and strings.
	 */
	char tokbuf[2000];
	char *token_end = tokbuf + sizeof tokbuf;
	static char* token_current;
	unsigned int numbuf;

	/*
	 * CURRENT TOKEN
	 *
	 * These variables are used by the parser to hold the current and former
	 * lexical tokens.
	 */
	int crt_lex_token;
	int saved_lex_token;

	#define lexi_unknown_token lex_unknown

	/*
	 * GET THE NEXT CHARACTER
	 *
	 * This routine reads the next character, either from the pending buffer
	 * or from the input file.
	 */
	static int
	lexi_getchar(struct lexi_state* state)
	{
		int c;

		c = fgetc(state->input);

		if (c == EOF) {
			return LEXI_EOF;
		}

		if (c == '\n') {
			crt_line_no++;
		}

		c &= 0xff; /* XXX: why? */

		return c;
	}

#include <stdbool.h>
#include <stdint.h>

int lexi_readchar(struct lexi_state *state) {
	if (state->buffer_index) {
		return lexi_pop(state);
	}

	return lexi_getchar(state);
}
void lexi_push(struct lexi_state *state, const int c) {
	state->buffer[state->buffer_index++] = c;
}

int lexi_pop(struct lexi_state *state) {
	return state->buffer[--state->buffer_index];
}

void lexi_flush(struct lexi_state *state) {
	state->buffer_index = 0;
}


/* LOOKUP TABLE */

typedef uint8_t lookup_type;
static lookup_type lookup_tab[] = {
	   0,    0,    0,    0,    0,    0,    0,    0,    0, 0x10, 0x10,    0, 
	   0, 0x10,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0, 0x10,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,  0x1,    0,    0, 
	 0x7,  0x7,  0x7,  0x7,  0x7,  0x7,  0x7,  0x7,  0x7,  0x7,    0,    0, 
	   0,    0,    0,    0,    0,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb, 
	 0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb, 
	 0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,    0,    0,    0,    0,  0xb, 
	   0,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb, 
	 0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb,  0xb, 
	 0xb,  0xb,  0xb,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0
};

bool lexi_group(enum lexi_groups group, int c) {
	if (c == LEXI_EOF) {
		return 0;
	}
	return lookup_tab[c] & group;
}


#include <string.h>
int lexi_keyword(const char *identifier, int notfound) {
	if (0 == strcmp(identifier, "ACTION")) return lex_kw_Haction;
	if (0 == strcmp(identifier, "DEFAULT")) return lex_default;
	if (0 == strcmp(identifier, "GROUP")) return lex_kw_Hgroup;
	if (0 == strcmp(identifier, "KEYWORD")) return lex_kw_Hkeyword;
	if (0 == strcmp(identifier, "MAPPING")) return lex_kw_Hmapping;
	if (0 == strcmp(identifier, "TOKEN")) return lex_kw_Htoken;
	if (0 == strcmp(identifier, "TYPE")) return lex_kw_Htype;
	if (0 == strcmp(identifier, "ZONE")) return lex_kw_Hzone;
	if (0 == strcmp(identifier, "white")) return lex_white;
	return notfound;
}
/* PRE-PASS ANALYSERS */

void lexi_init(struct lexi_state *state, FILE_P input) {
	state->zone = lexi_read_token;
	state->buffer_index = 0;
	state->input = input;
}
/* ZONES PASS ANALYSER PROTOTYPES*/

static int lexi_read_token_sidident(struct lexi_state *state);
static int lexi_read_token_ident(struct lexi_state *state);
static int lexi_read_token_string(struct lexi_state *state);
static void lexi_read_token_linecomment(struct lexi_state *state);
static void lexi_read_token_comment(struct lexi_state *state);
static int lexi_read_token_arg_char_num(struct lexi_state *state);
/* MAIN PASS ANALYSERS */


/* MAIN PASS ANALYSER for sidident */
static int
lexi_read_token_sidident(struct lexi_state *state)
{
	start: {
		int c0 = lexi_readchar(state);
		if (!lexi_group(lexi_group_alnumhy, c0)) {
			lexi_push(state, c0);
			/* ACTION <fini_tokbuf> */
			{

	if (token_current == token_end) {
		error(ERROR_FATAL, "Buffer overflow: trailing 0");
		*(token_end-1) = 0;
	} else {
		*token_current++ = 0;
	}
			}
			/* END ACTION <fini_tokbuf> */
			return lex_sid_Hident;
		}

		/* DEFAULT */
		/* ACTION <push_tokbuf> */
		{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c0;
	}
		}
		/* END ACTION <push_tokbuf> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for ident */
static int
lexi_read_token_ident(struct lexi_state *state)
{
	start: {
		int c0 = lexi_readchar(state);
		if (!lexi_group(lexi_group_alnum, c0)) {
			lexi_push(state, c0);
			/* ACTION <fini_tokbuf> */
			{

	if (token_current == token_end) {
		error(ERROR_FATAL, "Buffer overflow: trailing 0");
		*(token_end-1) = 0;
	} else {
		*token_current++ = 0;
	}
			}
			/* END ACTION <fini_tokbuf> */
			/* ACTION <keyword> */
			{
				int ZT1;

	ZT1 = lexi_keyword(tokbuf, lex_ident);
				return ZT1;
			}
			/* END ACTION <keyword> */
		}

		/* DEFAULT */
		/* ACTION <push_tokbuf> */
		{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c0;
	}
		}
		/* END ACTION <push_tokbuf> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for string */
static int
lexi_read_token_string(struct lexi_state *state)
{
	start: {
		int c0 = lexi_readchar(state);
		switch (c0) {
		case '\n': {
				/* ACTION <E_newline_in_string> */
				{

	error(ERROR_SERIOUS, "Unexpected newline in string");
				}
				/* END ACTION <E_newline_in_string> */
				goto start; /* leaf */
			}

		case LEXI_EOF: {
				/* ACTION <E_eof_in_string> */
				{

	error(ERROR_SERIOUS, "Unexpected eof in string");
				}
				/* END ACTION <E_eof_in_string> */
				goto start; /* leaf */
			}

		case '\\': {
				int c1 = lexi_readchar(state);
				switch (c1) {
				case '\\': {
						/* ACTION <push_tokbuf> */
						{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c0;
	}
						}
						/* END ACTION <push_tokbuf> */
						/* ACTION <push_tokbuf> */
						{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c0;
	}
						}
						/* END ACTION <push_tokbuf> */
						goto start; /* leaf */
					}

				case '"': {
						/* ACTION <push_tokbuf> */
						{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c1;
	}
						}
						/* END ACTION <push_tokbuf> */
						goto start; /* leaf */
					}

				}
				lexi_push(state, c1);
			}
			break;

		case '"': {
				/* ACTION <fini_tokbuf> */
				{

	if (token_current == token_end) {
		error(ERROR_FATAL, "Buffer overflow: trailing 0");
		*(token_end-1) = 0;
	} else {
		*token_current++ = 0;
	}
				}
				/* END ACTION <fini_tokbuf> */
				return lex_string;
			}

		}

		/* DEFAULT */
		/* ACTION <push_tokbuf> */
		{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c0;
	}
		}
		/* END ACTION <push_tokbuf> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for linecomment */
static void
lexi_read_token_linecomment(struct lexi_state *state)
{
	start: {
		int c0 = lexi_readchar(state);
		if (c0 == '\n') {
			return;
		}

		/* DEFAULT */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for comment */
static void
lexi_read_token_comment(struct lexi_state *state)
{
	start: {
		int c0 = lexi_readchar(state);
		if (c0 == '*') {
			int c1 = lexi_readchar(state);
			if (c1 == '/') {
				return;
			}
			lexi_push(state, c1);
		}

		/* DEFAULT */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for arg_char_num */
static int
lexi_read_token_arg_char_num(struct lexi_state *state)
{
	start: {
		int c0 = lexi_readchar(state);
		if (lexi_group(lexi_group_white, c0)) goto start;
		if (!lexi_group(lexi_group_digit, c0)) {
			lexi_push(state, c0);
			return lex_arg_Hchar_Hnum;
		}

		/* DEFAULT */
		/* ACTION <numbuf_push_digit> */
		{

	numbuf *= 10;
	numbuf += c0 - '0';
		}
		/* END ACTION <numbuf_push_digit> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for the global zone */
int
lexi_read_token(struct lexi_state *state)
{
	if (state->zone != lexi_read_token)
		return state->zone(state);
	start: {
		int c0 = lexi_readchar(state);
		if (lexi_group(lexi_group_white, c0)) goto start;
		switch (c0) {
		case '"': {
				/* ACTION <init_tokbuf> */
				{

	token_current=tokbuf;
				}
				/* END ACTION <init_tokbuf> */
				return lexi_read_token_string(state);
			}

		case '/': {
				int c1 = lexi_readchar(state);
				switch (c1) {
				case '/': {
						lexi_read_token_linecomment(state);
						goto start;	/* pure function */
					}

				case '*': {
						lexi_read_token_comment(state);
						goto start;	/* pure function */
					}

				}
				lexi_push(state, c1);
			}
			break;

		case '!': {
				return lex_arg_Hignore;
			}

		case '#': {
				int c1 = lexi_readchar(state);
				switch (c1) {
				case '*': {
						return lex_arg_Hchar_Hstring;
					}

				case 'n': {
						return lex_arg_Hchar_Hcount;
					}

				}
				if (lexi_group(lexi_group_digit, c1)) {
					/* ACTION <numbuf_init> */
					{

	numbuf = 0;
					}
					/* END ACTION <numbuf_init> */
					/* ACTION <numbuf_push_digit> */
					{

	numbuf *= 10;
	numbuf += c1 - '0';
					}
					/* END ACTION <numbuf_push_digit> */
					return lexi_read_token_arg_char_num(state);
				}
				lexi_push(state, c1);
			}
			break;

		case '[': {
				int c1 = lexi_readchar(state);
				if (c1 == '.') {
					int c2 = lexi_readchar(state);
					if (c2 == '.') {
						int c3 = lexi_readchar(state);
						if (c3 == '.') {
							int c4 = lexi_readchar(state);
							switch (c4) {
							case ')': {
									return lex_range_Hclosed_Hopen;
								}

							case ']': {
									return lex_range_Hclosed_Hclosed;
								}

							}
							lexi_push(state, c4);
						}
						lexi_push(state, c3);
					}
					lexi_push(state, c2);
				}
				lexi_push(state, c1);
			}
			break;

		case '.': {
				int c1 = lexi_readchar(state);
				if (c1 == '.') {
					int c2 = lexi_readchar(state);
					if (c2 == '.') {
						return lex_range;
					}
					lexi_push(state, c2);
				}
				lexi_push(state, c1);
			}
			break;

		case LEXI_EOF: {
				return lex_eof;
			}

		case ',': {
				return lex_comma;
			}

		case '$': {
				int c1 = lexi_readchar(state);
				if (c1 == '$') {
					return lex_nothing_Hmarker;
				}
				if (lexi_group(lexi_group_alpha, c1)) {
					/* ACTION <init_tokbuf> */
					{

	token_current=tokbuf;
					}
					/* END ACTION <init_tokbuf> */
					/* ACTION <push_tokbuf> */
					{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c1;
	}
					}
					/* END ACTION <push_tokbuf> */
					return lexi_read_token_sidident(state);
				}
				lexi_push(state, c1);
				return lex_arg_Hreturn;
			}

		case '+': {
				return lex_plus;
			}

		case '=': {
				return lex_equal;
			}

		case ';': {
				return lex_semicolon;
			}

		case '&': {
				return lex_ref;
			}

		case ':': {
				return lex_colon;
			}

		case '-': {
				int c1 = lexi_readchar(state);
				if (c1 == '>') {
					return lex_arrow;
				}
				lexi_push(state, c1);
			}
			break;

		case '}': {
				return lex_close_Hbrace;
			}

		case '{': {
				int c1 = lexi_readchar(state);
				switch (c1) {
				case '0': {
						int c2 = lexi_readchar(state);
						if (c2 == '-') {
							int c3 = lexi_readchar(state);
							if (c3 == '9') {
								int c4 = lexi_readchar(state);
								if (c4 == '}') {
									return lex_digit;
								}
								lexi_push(state, c4);
							}
							lexi_push(state, c3);
						}
						lexi_push(state, c2);
					}
					break;

				case 'a': {
						int c2 = lexi_readchar(state);
						if (c2 == '-') {
							int c3 = lexi_readchar(state);
							if (c3 == 'z') {
								int c4 = lexi_readchar(state);
								if (c4 == '}') {
									return lex_lower;
								}
								lexi_push(state, c4);
							}
							lexi_push(state, c3);
						}
						lexi_push(state, c2);
					}
					break;

				case 'A': {
						int c2 = lexi_readchar(state);
						if (c2 == '-') {
							int c3 = lexi_readchar(state);
							if (c3 == 'Z') {
								int c4 = lexi_readchar(state);
								if (c4 == '}') {
									return lex_upper;
								}
								lexi_push(state, c4);
							}
							lexi_push(state, c3);
						}
						lexi_push(state, c2);
					}
					break;

				}
				lexi_push(state, c1);
				return lex_open_Hbrace;
			}

		case '>': {
				return lex_end_Haction;
			}

		case '<': {
				return lex_begin_Haction;
			}

		case ')': {
				return lex_close;
			}

		case '(': {
				return lex_open;
			}

		}
		if (lexi_group(lexi_group_alpha, c0)) {
			/* ACTION <init_tokbuf> */
			{

	token_current=tokbuf;
			}
			/* END ACTION <init_tokbuf> */
			/* ACTION <push_tokbuf> */
			{

	if (token_current == token_end - 1) {
		error(ERROR_FATAL, "Buffer overflow");
	} else {
		*token_current++ = c0;
	}
			}
			/* END ACTION <push_tokbuf> */
			return lexi_read_token_ident(state);
		}

		/* DEFAULT */
		return lexi_unknown_token;
	}
}


