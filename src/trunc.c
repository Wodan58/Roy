/*
    module  : trunc.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef TRUNC_C
#define TRUNC_C

/**
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
void do_trunc(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    stack[-1] = (intptr_t)dbl;
}
#endif
