/*
    module  : over.c
    version : 1.6
    date    : 01/19/20
*/
#ifndef OVER_C
#define OVER_C

/**
over  :  X Y  ->  X Y X
Pushes an extra copy of the second item X on top of the stack.
*/
void do_over(void)
{
    BINARY;
    do_push(stack[-2]);
}
#endif
