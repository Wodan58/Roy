/*
    module  : pop.c
    version : 1.11
    date    : 07/23/20
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
    return stack_pop();
}
#endif
