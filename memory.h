/*
    module  : memory.h
    version : 1.2
    date    : 09/02/16
*/
#define malloc(x)	GC_malloc(x)
#define realloc(x,n)	GC_realloc(x,n)
#define strdup(x)	GC_strdup(x)
#define free(x)

void *GC_malloc(size_t size);
void *GC_realloc(void *ptr, size_t size);
char *GC_strdup(const char *str);
