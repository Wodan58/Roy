/*
    module  : __memorymax.c
    version : 1.11
    date    : 06/23/22
*/
#ifndef _LOWBAR__LOWBAR_MEMORYMAX_C
#define _LOWBAR__LOWBAR_MEMORYMAX_C

/**
1160  __memorymax  :  A 	->  I
Pushes value of total size of memory.
*/
void do__lowbar__lowbar_memorymax(void)
{
    do_push(MAKE_INTEGER(GC_get_memory_use()));
}
#endif
