/*
    module  : __memorymax.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
__memorymax  :  ->  I
Pushes value of total size of memory.
*/
void do___memorymax(void)
{
    COMPILE;
    do_push(stack_max());
}
#endif
