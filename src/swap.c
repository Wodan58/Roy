/*
    module  : swap.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef SWAP_C
#define SWAP_C

/**
swap  :  X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
void do_swap(void)
{
    intptr_t temp;

    BINARY;
    temp = stack[-1];
    stack[-1] = stack[-2];
    stack[-2] = temp;
}
#endif
