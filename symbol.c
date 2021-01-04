/*
    module  : symbol.c
    version : 1.24
    date    : 01/04/21
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h"
#include "builtin.h"
#define kcalloc(N,Z)	GC_malloc((N)*(Z))
#define kmalloc(Z)	GC_malloc(Z)
#define krealloc(P,Z)	GC_realloc(P,Z)
#define kfree(P)
#include "khash.h"
				/* builtin.c */
const char *identifier(const char *str);

void inilinebuffer(char *str);	/* yylex.c */

char *classify(char *name);	/* module.c */

YYTABLE yytable[2];		/* print.c */

KHASH_MAP_INIT_STR(Used, char);

static khash_t(Used) *usedTab;	/* table with used symbols */

KHASH_MAP_INIT_STR(Sym, intptr_t);

static khash_t(Sym) *theTable;	/* symbol table */
static int sym;			/* symbol */

int symtabmax(void)
{
    return kh_n_buckets(theTable);
}

int symtabindex(void)
{
    return kh_size(theTable);
}

int inuse(const char *str)
{
    return kh_get(Used, usedTab, str) != kh_end(usedTab);
}

intptr_t lookup(const char *str)
{
    int dummy;
    khiter_t key;
    intptr_t rv = 0;

    if ((key = kh_get(Sym, theTable, str)) != kh_end(theTable)) {
	rv = kh_value(theTable, key);
	if (compiling)
	    if (rv & JLAP_INVALID)
		kh_put(Used, usedTab, str, &dummy);
    }
    return rv;
}

void enter(char *str, void (*proc)(void))
{
    int rv;
    khiter_t key;

    key = kh_put(Sym, theTable, str, &rv);
    kh_value(theTable, key) = (intptr_t)proc | JLAP_INVALID;
}

void initsym(void)
{
    static int init;

    if (init)
	return;
    init = 1;
    yytable[0].name = "quit";
    yytable[0].proc = (void (*)(void))((intptr_t)do_quit | JLAP_INVALID);
    inilinebuffer(filename);
    usedTab = kh_init(Used);
    theTable = kh_init(Sym);
#include "trans.c"
}

void enterdef(char *Name, Stack *List)
{
    int rv;
    khiter_t key;

    Name = classify(Name);
    key = kh_put(Sym, theTable, Name, &rv);
    kh_value(theTable, key) = (intptr_t)List;
}

char *my_strupr(char *str)
{
    int i;
    char *ptr;

    for (i = 0; str[i]; i++)
	if (!isalnum(str[i]) && str[i] != '_')
	    return 0;
    ptr = GC_strdup(str);
    for (i = 0; ptr[i]; i++)
	ptr[i] = toupper(ptr[i]);
    return ptr;
}

void dump(void)
{
    char *ptr;
    khiter_t key;
    intptr_t Value;
    const char *Name;

    for (key = kh_begin(theTable); key != kh_end(theTable); key++)
	if (kh_exist(theTable, key)) {
	    Value = kh_value(theTable, key);
	    if (Value & JLAP_INVALID) {
		Name = kh_key(theTable, key);
		if (!inuse(Name)) {
		    if ((ptr = my_strupr(identifier(Name))) != 0) {
			fprintf(stderr, "#define %s_X\n", ptr);
			fprintf(stderr, "#define %s_C\n", ptr);
		    }
		} else if (!strcmp(Name, "pop"))
		    printf("{ \"pop\", (void (*)(void))do_pop },");
		else
		    printf("{ \"%s\", do_%s },", Name, identifier(Name));
	    }
	}
}

const char *dump1(int start, khiter_t *key)
{
    if (start)
	*key = kh_begin(theTable);
    else
	(*key)++;
    while (*key != kh_end(theTable)) {
	if (kh_exist(theTable, *key)) {
	    if (!kh_value(theTable, *key))
		return kh_key(theTable, *key);
	}
	(*key)++;
    }
    return 0;
}

const char *dump2(int start, khiter_t *key)
{
    if (start)
	*key = kh_begin(theTable);
    else
	(*key)++;
    while (*key != kh_end(theTable)) {
	if (kh_exist(theTable, *key))
	    return kh_key(theTable, *key);
	(*key)++;
    }
    return 0;
}
