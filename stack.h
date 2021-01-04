/*
    module  : stack.h
    version : 1.24
    date    : 01/04/21
*/
#ifndef STACK_H
#define STACK_H

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif
#include <stdint.h>
#include <time.h>
#include <gc.h>
#define mem_malloc(Z)		GC_malloc(Z)
#define mem_realloc(P,Z)	GC_realloc(P,Z)
#define chk_malloc(Z)		GC_malloc(Z)
#define chk_realloc(P,Z)	GC_realloc(P,Z)
#define free(P)
#include "decl.h"
#include "kvec.h"

// #define VECTOR
#define BIT_64

#ifndef RUNTIME
#define VECTOR
#define COMPILING
#endif

#ifdef BIT_64
#define SETSIZE_	64
#define MAXINT_		9223372036854775807LL
typedef double real_t;
#endif

#ifdef BIT_32
#define SETSIZE_	32
#define MAXINT_		2147483647
typedef float real_t;
#endif

#if !defined(BIT_64) && !defined(BIT_32)
#error "either BIT_64 or BIT_32 must be defined"
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4244, 4996)
#endif

#ifndef _MSC_VER
_Static_assert(sizeof(real_t) == sizeof(intptr_t), "real_t != intptr_t");
#endif

typedef vector(intptr_t) Stack;

typedef struct {
    char *name;
    void (*proc)(void);
#if 0
    char *repl;
#endif
} YYTABLE;

/* optable.c */
typedef struct optable_t {
    char *name, *messg1, *messg2;
} optable_t;

extern optable_t optable[];

/* main.c */
extern int g_argc, library, compiling, debugging, autoput, tracegc, undeferror;
extern char **g_argv, *filename;
extern clock_t startclock;
void execerror(char *msg, const char *op);
#endif
