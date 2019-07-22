/*
    module  : lookup.c
    version : 1.7
    date    : 07/08/19
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "parse.h"

void reverse(Stack *List);	/* builtin.c */

/*
 *  Perform lexical analysis on a string: type is either 0 on end of string,
 *  or [, ], Char, Int, Symbol; value contains the value of Char, Int, or Symbol;
 *  the return value is the next position in the string.
 */
char *readnext(char *str, int *type, intptr_t *value)
{
    int i;
    size_t leng;
    char *ptr, tmp[MAXSTR];

    *type = *value = 0;
    while (isspace(*str))
	str++;
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
	}
	*value = *str++;
	return str;
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
    for (ptr = str; !strchr("[]", *str) && !isspace(*str); str++)
	;
    leng = str - ptr;
    strncpy(tmp, ptr, leng);
    tmp[leng] = 0;
    for (i = 0; table[i].name; i++)
	if (!strcmp(tmp, table[i].name)) {
	    *value = (intptr_t)table[i].proc | JLAP_INVALID;
	    break;
	}
    if (!*value)
	*value = (intptr_t)GC_strdup(tmp) | JLAP_INVALID;
    return str;
}

/*
 *  Read a term from str and return the resulting stack.
 */
Stack *readterm(char **str, int *type, intptr_t *value)
{
    Stack *List = 0, *List1;

    while (*type && *type != ']') {
	switch (*type) {
	case Boolean:
	case Char:
	case Int:
	case Symbol:
	    if (!List)
		vec_init(List);
	    vec_add(List, *value);
	    break;
	case '[':
	    *str = readnext(*str, type, value);
	    List1 = readterm(str, type, value);
	    if (!List)
		vec_init(List);
	    vec_add(List, (intptr_t)List1);
	default:
	    break;
	}
	*str = readnext(*str, type, value);
    }
    reverse(List);
    return List;
}

/*
 *  Read a term from table[i].repl and return the result;
 *  readnext is called first.
 */
intptr_t lookup(const char *name)
{
    char *str;
    int i, type;
    intptr_t value;

    for (i = 0; table[i].repl; i++)
	if (!strcmp(name, table[i].name)) {
	    str = readnext(table[i].repl, &type, &value);
	    return (intptr_t)readterm(&str, &type, &value);
	}
    return 0;
}
