/*
    module  : joy.h
    version : 1.29
    date    : 06/21/22
*/
#ifndef JOY_H
#define JOY_H

#ifndef RUNTIME
#define COMPILING
#endif

#ifndef COSMO
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>        // int64_t, uint64_t
#include <stdbool.h>       // bool, true, false
#include <setjmp.h>
#include <signal.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#ifdef _MSC_VER
#define __func__ __FUNCTION__
#pragma warning(disable : 4244 4996)
#include <io.h>
#else
#include <unistd.h>
#endif
#endif

/*
    The symbol tables may contain GC_allocated strings and data.
*/
#define kcalloc(N, Z)		GC_malloc((N) * (Z))
#define kmalloc(Z)		GC_malloc(Z)
#define krealloc(P, Z)		GC_realloc(P, Z)
#define kfree(P)

#include "decl.h"
#include <gc.h>
#include "kvec.h"
#include "khash.h"

#ifdef MALLOC_DEBUG
#include "rmalloc.h"

#define GC_malloc(s)		Rmalloc((s), RM_FILE_POS)
#define GC_malloc_atomic(s)	Rmalloc((s), RM_FILE_POS)
#define GC_realloc(p, s)	Rrealloc((p), (s), RM_FILE_POS)
#define GC_strdup(s)		Rstrdup((s), RM_FILE_POS)
#endif

#define VECTOR
#include "nanbox2.h"
#include "value.h"
#include "stack.h"
#include "parse.h"

#include "arity.h"
#include "builtin.h"
#include "compare.h"
#include "compile.h"
#include "factor.h"
#include "identify.h"
#include "module.h"
#include "optable.h"
#include "print.h"
#ifdef RUNTIME
#include "lookup.h"
#else
#include "symbol.h"
#endif
#include "tmpfile.h"
#include "yylex.h"

/* main.c */
extern int g_argc, library, compiling, debugging, autoput, tracegc, undeferror;
extern char **g_argv, *filename;
extern clock_t startclock;

void execerror(char *msg, const char *op);

/* builtin.c */
void execute_rest(Stack *list, int i);
void execute(Stack *list);
void execute_cond(Stack *list, int start);
#endif
