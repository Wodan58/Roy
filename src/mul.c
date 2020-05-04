/*
    module  : mul.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef MUL_C
#define MUL_C

/**
*  :  I J  ->  K
Integer K is the product of integers I and J.
*/
void do_mul(void)
{
    BINARY;
    stack[-2] *= stack[-1];
    do_zap();
    CHECK2;
}
#endif
