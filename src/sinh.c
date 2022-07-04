/*
    module  : sinh.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef SINH_C
#define SINH_C

/**
1650  sinh  :  DA	F  ->  G
G is the hyperbolic sine of F.
*/
void do_sinh(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = sinh(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
