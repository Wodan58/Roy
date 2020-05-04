/*
    module  : pop.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef POP_C
#define POP_C

/**
pop  :  X  ->
Removes X from top of the stack.
*/
intptr_t do_pop(void)
{
    UNARY0;
    return do_pop_val();
}
#endif
