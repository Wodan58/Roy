/*
    module  : stack.c
    version : 1.12
    date    : 01/19/20
*/
#ifndef STACK_C
#define STACK_C

Stack *stk2lst(void)
{
    return copy_stack();
}

/**
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
void do_stack(void)
{
    UNARY;
    do_push((intptr_t)copy_stack());
}
#endif
