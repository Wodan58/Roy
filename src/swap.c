/*
    module  : swap.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef SWAP_C
#define SWAP_C

/**
1220  swap  :  DDAA	X Y  ->  Y X
Interchanges X and Y on top of the stack.
*/
void do_swap(void)
{
    value_t temp;

    TWOPARAMS;
    temp = stack[-1];
    stack[-1] = stack[-2];
    stack[-2] = temp;
}
#endif
