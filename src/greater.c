/*
    module  : greater.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef GREATER_C
#define GREATER_C

/**
>  :  X Y  ->  B
X and Y are numeric.
Tests whether X is greater than Y.
*/
void do_greater(void)
{
    BINARY;
    stack[-2] = stack[-2] > stack[-1];
    do_zap();
}
#endif
