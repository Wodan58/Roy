/*
    module  : pop.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef POP_C
#define POP_C

/**
1320  pop  :  D 	X  ->
Removes X from top of the stack.
*/
void do_pop(void)
{
    ONEPARAM;
    stack_pop();
}
#endif
