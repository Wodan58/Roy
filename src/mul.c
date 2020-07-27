/*
    module  : mul.c
    version : 1.11
    date    : 07/23/20
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
    do_pop();
    CHECK2;
}
#endif
