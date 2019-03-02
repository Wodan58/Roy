/*
    module  : joygc.h
    version : 1.4
    date    : 03/02/19
*/
#include "gc.h"

#ifdef strdup
#undef strdup
#endif

#define strdup(x)	GC_strdup(x)
#define malloc(x)	GC_malloc(x)
#define calloc(x,y)	GC_malloc((x) * (y))
#define realloc(x,y)	GC_realloc(x, y)
#define free(x)
