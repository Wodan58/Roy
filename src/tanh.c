/*
    module  : tanh.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef TANH_C
#define TANH_C

/**
tanh  :  F  ->  G
G is the hyperbolic tangent of F.
*/
void do_tanh(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = tanh(dbl);
    stack[-1] = pack(dbl);
}
#endif
