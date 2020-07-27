/*
    module  : less.c
    version : 1.8
    date    : 07/23/20
*/
#ifndef LESS_C
#define LESS_C

/**
<  :  X Y  ->  B
X and Y are numeric.
Tests whether X is less than Y.
*/
void do_less(void)
{
    BINARY;
    stack[-2] = stack[-2] < stack[-1];
    do_pop();
}
#endif
