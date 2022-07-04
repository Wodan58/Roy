/*
    module  : lookup.c
    version : 1.13
    date    : 06/21/22
*/
#define RUNTIME
#include "joy.h"

YYSTYPE yylval; /* used in yylex.c */

/*
   The following code is able to add a replacement string to the symbol table.
   This replacement string is currently not part of the symbol table.
*/
#if 0
/*
 *  Perform lexical analysis on a string: type is either 0 on end of string,
 *  or [, ], Char, Int, Symbol; value contains the value of Char, Int, or
 *  Symbol; the return value is the next position in the string.
 */
static char *readnext(char *str, int *type, value_t *value)
{
    int i;
    size_t leng;
    char *ptr, tmp[MAXSTR];

    *type = 0;
    while (isspace(*str))
        str++;
    if (strchr("[]", *str)) {
        *type = *str++;
        return str;
    }
    if (*str == '\'') {
        *type = CHAR_;
        if (*++str == '\\') {
            *value = MAKE_CHAR(atoi(++str));
            while (isdigit(*str))
                str++;
            return str;
        }
        *value = MAKE_CHAR(*str++);
        return str;
    }
    if ((*str == '-' && isdigit(str[1])) || isdigit(*str)) {
        *type = INTEGER_;
        *value = MAKE_INTEGER(atoi(str));
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
            *value = MAKE_ANON_FUNCT(yytable[i].proc);
            break;
        }
    if (!*value)
        *value = MAKE_USR_STRING(GC_strdup(tmp));
    return str;
}

/*
 *  Read a term from str and return the resulting stack.
 */
static Stack *readterm(char **str, int *type, value_t *value)
{
    Stack *list = 0, *quot;

    while (*type && *type != ']') {
        switch (*type) {
        case BOOLEAN_ :
        case CHAR_ :
        case INTEGER_ :
        case USR_ :
            vec_push(list, *value);
            break;
        case '[' :
            *str = readnext(*str, type, value);
            quot = readterm(str, type, value);
            vec_push(list, MAKE_LIST(quot));
        default :
            break;
        }
        *str = readnext(*str, type, value);
    }
    vec_push(list, 0);
    vec_reverse(list);
    return list;
}

/*
 *  Read a term from yytable[i].repl and return the result;
 *  readnext is called first.
 */
value_t lookup(const char *name, int *found)
{
    char *str;
    int i, type;
    value_t value;

    for (*found = i = 0; yytable[i].proc; i++)
        if (!strcmp(name, yytable[i].name)) {
            str = readnext(yytable[i].repl, &type, &value);
            return MAKE_LIST(readterm(&str, &type, &value));
        }
    return MAKE_USR_STRING((NANBOX_POINTER_TYPE)name);
}
#endif

/*
    lookup - return a procedure using the name as key or return the name itself.
*/
value_t lookup(const char *name, int *location)
{
    int i;

    for (*location = i = 0; yytable[i].proc; i++)
        if (!strcmp(name, yytable[i].name)) {
            *location = i;
            return MAKE_ANON_FUNCT(yytable[i].proc);
        }
    return MAKE_USR_STRING((NANBOX_POINTER_TYPE)name);
}

/*
    qualify - return a nanboxed function or string.
*/
value_t qualify(char *name)
{
    int location;

    return lookup(name, &location);
}

/*
    find - return the name of a procedure or, if not found, an empty name.
*/
const char *find(void (*proc)(void))
{
    int i;

    for (i = 0; yytable[i].proc; i++)
        if (proc == yytable[i].proc)
            return yytable[i].name;
    return "";
}

/*
    dump_table - dump the symbol table. Only the name is printed.
*/
void dump_table(void)
{
    int i;

    for (i = 0; yytable[i].proc; i++)
        printf("%s\n", yytable[i].name);
}

/*
    arity - this is used in compiled programs and the return value of 1 means
            that the arity is ok en no save/restore of the stack is needed.
            This is faster, but requires that the developer made sure that the
            arity is indeed 1.
*/
int arity(Stack *quot, int num)
{
    return 1;
}

/*
    print - this is used in execerror, but compiled programs do not execute
            the code that calls this function.
*/
void print(const char *str)
{
}

/*
    str_locate - this is used in writefactor.
*/
const char *str_locate(int location)
{
    return "";
}
