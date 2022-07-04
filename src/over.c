/*
    module  : over.c
    version : 1.7
    date    : 06/21/22
*/
#ifndef OVER_C
#define OVER_C

/**
3220  over  :  A	X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
void do_over(void)
{
    TWOPARAMS;
    do_push(stack[-2]);
}
#endif
