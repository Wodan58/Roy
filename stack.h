/*
    module  : stack.h
    version : 1.14
    date    : 07/19/19
*/
#include <stdint.h>
#include <gc.h>
#define malloc(Z)	GC_MALLOC(Z)
#define realloc(P,Z)	GC_REALLOC(P,Z)
#define free(P)
#include "vector.h"

#define VECTOR
#define BIT_64

#ifdef BIT_64
typedef double real_t;
#endif

#ifdef BIT_32
typedef float real_t;
#endif

#if !defined(BIT_64) && !defined(BIT_32)
#error "one of BIT_64 and BIT_32 must be defined"
#endif

#ifndef _MSC_VER
_Static_assert(sizeof(real_t) == sizeof(intptr_t), "real_t != intptr_t");
#endif

#define JLAP_INVALID	1
#define MAXSTR		128
#define SMALLINT	99999

typedef vector(intptr_t) Stack;

typedef struct {
    char *name;
    void (*proc)(void);
    char *repl;
} YYTABLE;

extern YYTABLE table[];

#ifndef RUNTIME
#ifndef VECTOR
#define VECTOR
#endif
#define COMPILING

extern int compiling, debugging;
#endif
