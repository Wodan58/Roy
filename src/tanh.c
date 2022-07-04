/*
    module  : tanh.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef TANH_C
#define TANH_C

/**
1680  tanh  :  DA	F  ->  G
G is the hyperbolic tangent of F.
*/
void do_tanh(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = tanh(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
