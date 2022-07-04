/*
    module  : __memoryindex.c
    version : 1.11
    date    : 06/23/22
*/
#ifndef _LOWBAR__LOWBAR_MEMORYINDEX_C
#define _LOWBAR__LOWBAR_MEMORYINDEX_C

/**
3080  __memoryindex  :  A	->  I
Pushes current value of memory.
*/
void do__lowbar__lowbar_memoryindex(void)
{
    do_push(MAKE_INTEGER(GC_get_heap_size()));
}
#endif
