/*
    module  : builtin.c
    version : 1.33
    date    : 03/01/21
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>
#include "stack.h"
#include "parse.h"
#include "builtin.h"
#include "print.h"
#include "yylex.h"
#define kcalloc(N,Z)	GC_malloc((N)*(Z))
#define kmalloc(Z)	GC_malloc(Z)
#define krealloc(P,Z)	GC_realloc(P,Z)
#define kfree(P)
#include "khash.h"
#include "symbol.h"
#include "factor.h"

FILE *my_tmpfile(void);

// #define REPORT

extern YYTABLE yytable[];

#ifdef COMPILING
#define STACK(n)	(library || vec_size(theStack) < (n))
#define COMPILE		if (compiling            ) { print(program, __func__); \
			return; }
#define COMPILE1	if (compiling            ) { print1(program, __func__);\
			return; }
#define UNARY		if (compiling && STACK(1)) { print(program, __func__); \
			return; }
#define UNARY0		if (compiling && STACK(1)) { print(program, __func__); \
			return 0; }
#define BINARY		if (compiling && STACK(2)) { print(program, __func__); \
			return; }
#define TERNARY		if (compiling && STACK(3)) { print(program, __func__); \
			return; }
#define QUATERN		if (compiling && STACK(4)) { print(program, __func__); \
			return; }
#define QUINARY		if (compiling && STACK(5)) { print(program, __func__); \
			return; }
#define CHECK2		if (compiling && (vec_back(theStack) < MIN_INT || \
			vec_back(theStack) > MAX_INT)) print(program, 0)
#define SYNCING		if (compiling) fprintf(program, "clear_stack();")
#else
#define STACK(n)
#define COMPILE
#define COMPILE1
#define UNARY
#define UNARY0
#define BINARY
#define TERNARY
#define QUATERN
#define QUINARY
#define CHECK2
#define SYNCING

YYSTYPE yylval;
#endif

void execute_rest(Stack *ptr, int i);	/* builtin.c */
void execute(Stack *ptr);

intptr_t pack(real_t dbl)
{
    intptr_t Value;
    Stack *List = 0;

    memcpy(&Value, &dbl, sizeof(real_t));
    vec_push(List, Value);
    return (intptr_t)List | JLAP_PACKAGE;
}

real_t unpack(intptr_t num)
{
    real_t dbl;
    Stack *List;

    List = (Stack *)(num & ~JLAP_PACKAGE);
    memcpy(&dbl, &vec_back(List), sizeof(real_t));
    return dbl;
}

/*
 * translate function address to symbol name
 */
char *procname(intptr_t Value)
{
    int i;
    void (*proc)(void);

    proc = (void (*)(void))(Value & ~JLAP_INVALID);
    for (i = 0; yytable[i].proc; i++)
	if (proc == yytable[i].proc)
	    return yytable[i].name;
    return 0;
}

/*
 * translate symbol name to function address
 */
void (*nameproc(const char *name))(void)
{
    int i;

    for (i = 0; yytable[i].proc; i++)
	if (!strcmp(name, yytable[i].name))
	    return yytable[i].proc;
    return 0;
}

#include "stack.c"

#ifdef COMPILING
#include "compile.c"
#else
#include "runtime.h"

void init_decl(void)
{
}
#endif

#undef POP_C

#include "runtime.c"

#ifdef REPORT
double count_execute;

void report_execute(void)
{
    fprintf(stderr, "execute = %.0f\n", count_execute);
}
#endif

void trace(Stack *List, int Index)
{
    write_stack();
    printf(": ");
    writeterm(List, Index);
    printf(" ;\n");
}

void execute_rest(Stack *List, int i)
{
    intptr_t Value;
    const char *Name;
#ifndef COMPILING
    void (*proc)(void);
#endif

#ifdef REPORT
    static int first;

    if (!first) {
	first = 1;
	atexit(report_execute);
    }
    count_execute++;
#endif
#ifdef COMPILING
    if (compiling)
	initcompile();
#endif
    if (i == -1)
	i += vec_size(List);
    for (; i >= 0; i--) {
	if (debugging)
	    trace(List, i);
	Value = vec_at(List, i);
	if ((Value >= MIN_INT && Value <= MAX_INT) || !(Value & JLAP_INVALID))
	    do_push(Value);
	else {
	    Name = (const char *)(Value & ~JLAP_INVALID);
	    if (*Name == '"')
		do_push(Value);
	    else {
#ifdef COMPILING
		Value = lookup(Name);
		if (!(Value & JLAP_INVALID))
		    execute((Stack *)Value);
		else
		    ((void (*)(void))(Value & ~JLAP_INVALID))();
#else
		if ((proc = nameproc(Name)) == 0)
		    proc = (void (*)(void))Name;
		(*proc)();
#endif
	    }
	}
    }
}

void execute(Stack *List)
{
    execute_rest(List, -1);
}
