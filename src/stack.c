/*
    module  : stack.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef STACK_C
#define STACK_C

/**
1040  stack  :  A	.. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
void do_stack(void)
{
    COMPILE;
    do_push(MAKE_LIST(stack_copy()));
}
#endif
