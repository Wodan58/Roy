/*
    module  : sqrt.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef SQRT_C
#define SQRT_C

/**
1660  sqrt  :  DA	F  ->  G
G is the square root of F.
*/
void do_sqrt(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = sqrt(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
