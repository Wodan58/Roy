/*
    module  : factor.c
    version : 1.2
    date    : 08/05/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "node.h"
#include "parse.h"

extern function_t funTable[];

static int locate(char *str)
{
    int i;

    for (i = 0; funTable[i].proc; i++)
	if (!strcmp(funTable[i].name, str))
	    return i;
    return -1;
}

/*
 * Perform lexical analysis on a string: type is either 0 on end of file,
 * or [, ], Char, Int, Symbol; value contains the value of Char or Int;
 * symbol contains the start of the symbol; return value is the next position
 * in the string.
 */
static char *readnext(char *str, int *type, int *value, char **symbol)
{
    *value = 0;
    while (isspace(*str))
	str++;
    if (!*str) {
	*type = 0;
	return str;
    }
    if (strchr("[]", *str)) {
	*type = *str++;
	return str;
    }
    if (*str == '\'') {
	*type = Char;
	if (*++str == '\\') {
	    *value = atoi(++str);
	    while (isdigit(*str))
		str++;
	    return str;
	} else {
	    *value = *str++;
	    return str;
	}
    }
    if ((*str == '-' && isdigit(str[1])) || isdigit(*str)) {
	*type = Int;
	*value = atoi(str);
	if (*str == '-')
	    str++;
	while (isdigit(*str))
	    str++;
	return str;
    }
    *type = Symbol;
    *symbol = str;
    while (*str && !isspace(*str) && *str != ']')
	str++;
    return str;
}

static node_t *readterm(char **str, int *type, int *value, char **symbol);

/*
 * Read a factor and return a node containing the result.
 */
static node_t *readfactor(char **str, int *type, int *value, char **symbol)
{
    int index;
    char *ptr, *tmp;

    switch (*type) {
    case '[':
	*str = readnext(*str, type, value, symbol);
	return readterm(str, type, value, symbol);
    case Symbol:
	for (ptr = *symbol; *ptr && !isspace(*ptr) && *ptr != ']'; ptr++)
	    ;
	tmp = calloc(1, ptr - *symbol + 1);
	strncpy(tmp, *symbol, ptr - *symbol);
	if ((index = locate(tmp)) != -1)
	    return newfunction(funTable[index].proc);
	return newsymbol(tmp);
    case Char:
    case Int:
	return newnode(*type, *value);
    default:
	return 0;	/* error */
    }
}

/*
 * Read a term from str and return the result.
 */
static node_t *readterm(char **str, int *type, int *value, char **symbol)
{
    node_t *root, **cur;

    root = newlist(0);
    cur = &root->ptr;
    while (*type && *type != ']') {
       *cur = readfactor(str, type, value, symbol);
	cur = &(*cur)->next;
       *str = readnext(*str, type, value, symbol);
    }
    return root;
}

/*
 * Read a term from str and return the result; readnext is called first.
 */
node_t *parse(char *str)
{
    char *symbol;
    node_t *root;
    int type, value;

    str = readnext(str, &type, &value, &symbol);
    root = readterm(&str, &type, &value, &symbol);
    return root->ptr;
}
