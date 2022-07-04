/*
    module  : cosh.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef COSH_C
#define COSH_C

/**
1550  cosh  :  DA	F  ->  G
G is the hyperbolic cosine of F.
*/
void do_cosh(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = cosh(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
