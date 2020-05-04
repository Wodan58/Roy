/*
    module  : lookup.c
    version : 1.11
    date    : 01/20/20
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "parse.h"

extern YYTABLE yytable[];

/*
 *  Perform lexical analysis on a string: type is either 0 on end of string,
 *  or [, ], Char, Int, Symbol; value contains the value of Char, Int, or
 *  Symbol; *  the return value is the next position in the string.
 */
static char *readnext(char *str, int *type, intptr_t *value)
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
	*type = CHAR_;
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
	*type = INTEGER_;
	*value = atoi(str);
	if (*str == '-')
	    str++;
	while (isdigit(*str))
	    str++;
	return str;
    }
    *type = USR_;
    for (ptr = str; !strchr("[]", *str) && !isspace(*str); str++)
	;
    leng = str - ptr;
    strncpy(tmp, ptr, leng);
    tmp[leng] = 0;
    for (i = 0; yytable[i].name; i++)
	if (!strcmp(tmp, yytable[i].name)) {
	    *value = (intptr_t)yytable[i].proc | JLAP_INVALID;
	    break;
	}
    if (!*value)
	*value = (intptr_t)GC_strdup(tmp) | JLAP_INVALID;
    return str;
}

/*
 *  Read a term from str and return the resulting stack.
 */
static Stack *readterm(char **str, int *type, intptr_t *value)
{
    Stack *List = 0, *List1;

    while (*type && *type != ']') {
	switch (*type) {
	case BOOLEAN_ :
	case CHAR_ :
	case INTEGER_ :
	case USR_ :
	    vec_push(List, *value);
	    break;
	case '[' :
	    *str = readnext(*str, type, value);
	    List1 = readterm(str, type, value);
	    vec_push(List, (intptr_t)List1);
	default :
	    break;
	}
	*str = readnext(*str, type, value);
    }
    vec_push(List, 0);
    vec_reverse(List);
    return List;
}

/*
 *  Read a term from yytable[i].repl and return the result;
 *  readnext is called first.
 */
intptr_t lookup(const char *name)
{
#if 0
    char *str;
    int i, type;
    intptr_t value;

    for (i = 0; yytable[i].repl; i++)
	if (!strcmp(name, yytable[i].name)) {
	    str = readnext(yytable[i].repl, &type, &value);
	    return (intptr_t)readterm(&str, &type, &value);
	}
#endif
    return 0;
}
