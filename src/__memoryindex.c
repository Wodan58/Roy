/*
    module  : __memoryindex.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
__memoryindex  :  ->  I
Pushes current value of memory.
*/
void do___memoryindex(void)
{
    COMPILE;
    do_push(stack_size());
}
#endif
