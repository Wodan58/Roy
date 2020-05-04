/*
    module  : sqrt.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef SQRT_C
#define SQRT_C

/**
sqrt  :  F  ->  G
G is the square root of F.
*/
void do_sqrt(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = sqrt(dbl);
    stack[-1] = pack(dbl);
}
#endif
