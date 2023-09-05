/*
    module  : __memoryindex.c
    version : 1.12
    date    : 09/05/23
*/
#ifndef _LOWBAR__LOWBAR_MEMORYINDEX_C
#define _LOWBAR__LOWBAR_MEMORYINDEX_C

/**
3080  __memoryindex  :  A	->  I
Pushes current value of memory.
*/
void do__lowbar__lowbar_memoryindex(void)
{
    do_push(MAKE_INTEGER(GC_get_memory_use() - GC_get_free_bytes()));
}
#endif
