/*
    module  : cosh.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef COSH_C
#define COSH_C

/**
cosh  :  F  ->  G
G is the hyperbolic cosine of F.
*/
void do_cosh(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = cosh(dbl);
    stack[-1] = pack(dbl);
}
#endif
