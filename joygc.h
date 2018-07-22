/*
    module  : joygc.h
    version : 1.3
    date    : 07/22/18
*/
#if 0
#ifdef DEBUG
#define MALLOC_DEBUG
#endif

#include "rmalloc.h"
#endif

#if 1
#include "gc.h"

#ifdef strdup
#undef strdup
#endif

#define strdup(x)	GC_strdup(x)
#define malloc(x)	GC_malloc(x)
#define calloc(x,y)	GC_malloc((x) * (y))
#define realloc(x,y)	GC_realloc(x,y)
#define free(x)
#endif
