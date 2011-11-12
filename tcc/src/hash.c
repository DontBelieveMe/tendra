/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#define _POSIX_SOURCE

#include <sys/stat.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "utility.h"
#include "environ.h"
#include "flags.h"
#include "hash.h"
#include "options.h"


struct hash {
	struct hash *next;
	const char *value;
	const char *name;
	unsigned int flag;
	const char *file;
	int  line_num;
	enum hash_precedence precedence;
};


/*
 * Reconcile the table of user-defined env options. At present this function
 * just makes sure that non-tccenv(5) variables declared by the user were used
 * in the env files. If not, it's likely a subtle bug or typo, and a warning
 * issues if the version -v switch is used.
 */
void
reconcile_envopts(const struct hash *h)
{
	const struct hash *n;

	/*
	 * If no -Y args were given whatsoever, give a warning even without
	 * verbose being set.
	 */
	if (environ_count == 0)
		error(ERROR_USAGE, "not invoked with any -Y env arguments");

	/*
	 * If the global env table is NULL, no -Y args succeeded, or none were
	 * given.
	 */
	/* TODO: this needs reworking, now; it cannot happen
	if (environ_hashtable == NULL)
		error(ERROR_FATAL, "failed to load any environment files");
	*/

	if (!verbose) {
		return;
	}

	for (n = h; n != NULL; n = n->next) {
		if ((h->flag & HASH_USR) && !(h->flag & HASH_READ)) {
			error(ERROR_WARNING,
			    "%s, line %d: environment option %s declared"
			    " but never used", h->file, h->line_num, h->name);
		}

		/*
		 * Additional error checking for those platforms supporting stat() for
		 * variables which represent paths on the filesystem.
		 */
		if (0 == strncmp(n->name, "PREFIX_", 7) && strlen(n->value) > 0) {
			struct stat sb;

			if (stat(n->value, &sb) == -1) {
				error(ERROR_SERIOUS, "%s: %s", n->value, strerror(errno));
				return;
			}

			if (!S_ISDIR(sb.st_mode)) {
				error(ERROR_SERIOUS, "%s expected to be a directory");
				return;
			}
		}
	}
}

/*
 * PRINT OUT AN ENVIRONMENT
 */
void
dump_env(const struct hash *h)
{
	const struct hash *n;

	assert(h != NULL);

	IGNORE printf("Environment dump:\n");

	for (n = h; n != NULL; n = n->next) {
		IGNORE printf("\t%c%-18.*s = %s\n",
			(~n->flag & HASH_USR)  ? '$' : ' ',
			(int) strcspn(n->name, "$"), n->name, n->value);
	}
}

/*
 * SET A VARIABLE
 */
void
envvar_set(struct hash **h, const char *name, const char *value,
	enum hash_order order, enum hash_precedence precedence)
{
	struct hash *n;

	assert(h != NULL);
	assert(name != NULL);
	assert(value != NULL);

	for (n = *h; n != NULL; n = n->next) {
		if (0 == strcmp(name, n->name)) {
			break;
		}
	}

	/* Case 1.  Node was not found; push */
	if (n == NULL) {
		n = xmalloc(sizeof *n);

		n->flag       = option_istccopt(name) ? 0 : HASH_USR;
		n->name       = xstrdup(name);
		n->value      = xstrdup(value);
		n->file       = NULL;	/* TODO */
		n->line_num   = -1;	/* TODO */
		n->precedence = precedence;

		n->next = *h;
		*h = n;

		return;
	}

	assert(n->value != NULL);

	/* Decline to update if we're lower precedence than the existing value */
	if (precedence < n->precedence) {
		return;
	}

	n->precedence = precedence;

	/* Case 2.  Update with a value */
	switch (order) {
	case HASH_ASSIGN:
		n->value = value;
		break;

	case HASH_APPEND:
		n->value = string_append(n->value, value, ' ');
		break;

	case HASH_PREPEND:
		n->value = string_append(value, n->value, ' ');
		break;

	default:
		error(ERROR_FATAL, "Attempt to update hash with invalid order %d\n",
			(int) order);
	}
}

/*
 * GET THE FLAGS FOR A VARIABLE
 */
unsigned int
envvar_flags(const struct hash *h, const char *name)
{
	const struct hash *n;

	assert(name != NULL);

	for (n = h; n != NULL; n = n->next) {
		if (0 == strcmp(name, n->name)) {
			return n->flag;
		}
	}

	return 0;
}

/*
 * GET A VARIABLE
 *
 * Lookup value for tccenv(5) variables. This function takes in an escape
 * sequence from an env file, and attempts to find a definition. For example,
 * <PREFIX> may be passed in, and be mapped to the value supplied previously
 * by -y arguments.
 *
 * This function performs all error handling; it will return a valid char *,
 * or fail.
 */
const char *
envvar_dereference(struct hash *h, const char *name, char *end,
	const char *nm, int line_num)
{
	struct hash *n;
	char tmp;

	/* temporarily replace '>' with '\0' to facilitate lookup */
	/* TODO: modify the key_match function instead */
	/* TODO: or do this in the caller */
	tmp = *end;
	*end = '\0';

	for (n = h; n != NULL; n = n->next) {
		if (0 == strcmp(name, n->name)) {
			n->flag |= HASH_READ;
			break;
		}
	}

	*end = tmp;

	if (n == NULL) {
		/* TODO: %.*s based on *end */
		error(ERROR_FATAL, "Undefined variable <%s> in %s line %d",
			  name, nm, line_num);
	}

	assert(n->value != NULL);

	return n->value;
}
