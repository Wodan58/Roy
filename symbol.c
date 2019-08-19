/*
    module  : symbol.c
    version : 1.14
    date    : 07/19/19
*/
#include <stdio.h>
#include "stack.h"
#include "builtin.h"
#define calloc(N,Z)	GC_MALLOC((N)*(Z))
#define malloc(Z)	GC_MALLOC(Z)
#define realloc(P,Z)	GC_REALLOC(P,Z)
#define free(P)
#include "khash.h"

				/* builtin.c */
const char *identifier(const char *str);

YYTABLE table[] = { { 0 } };	/* print.c */

KHASH_MAP_INIT_STR(Sym, intptr_t);

static khash_t(Sym) *theTable;	/* symbol table */
static int sym;			/* symbol */

intptr_t lookup(const char *str)
{
    khiter_t key;

    if ((key = kh_get(Sym, theTable, str)) != kh_end(theTable))
	return kh_value(theTable, key);
    return 0;
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
    theTable = kh_init(Sym);
    enter("+", do_add);
    enter("*", do_mul);
    enter("=", do_eql);
    enter("swap", do_swap);
    enter("<", do_lss);
    enter("or", do_or);
    enter("and", do_and);
    enter("not", do_not);
    enter("step", do_step);
    enter("cons", do_cons);
    enter("dip", do_dip);
    enter("i", do_i);
    enter("dup", do_dup);
    enter("uncons", do_uncons);
    enter("index", do_index);
    enter("pop", (void (*)(void))do_pop);
    enter("put", do_put);
    enter("putch", do_putch);
    enter("get", do_get);
    enter("-", do_sub);
    enter("/", do_div);
    enter("stack", do_stack);
    enter("unstack", do_unstack);
    enter("body", do_body);
    enter("lt", do_lt);
    enter("put_bool", do_put_bool);
    enter("put_int", do_put_int);
    enter("put_str", do_put_str);
}

void enterdef(char *Name, Stack *List)
{
    int rv;
    khiter_t key;

    Name = (char *)((intptr_t)Name & ~JLAP_INVALID);
    key = kh_put(Sym, theTable, Name, &rv);
    kh_value(theTable, key) = (intptr_t)List;
}

void dump(void)
{
    khiter_t key;
    intptr_t Value;
    const char *Name;

    for (key = kh_begin(theTable); key != kh_end(theTable); key++) {
	if (kh_exist(theTable, key)) {
	    Value = kh_value(theTable, key);
	    if (Value & JLAP_INVALID) {
		Name = kh_key(theTable, key);
		if (!strcmp(Name, "pop"))
		    printf("{ \"pop\", (void (*)(void))do_pop },");
		else if (strcmp(Name, "get"))
		    printf("{ \"%s\", do_%s },", Name, identifier(Name));
	    }
	}
    }
}
