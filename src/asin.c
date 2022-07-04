/*
    module  : asin.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ASIN_C
#define ASIN_C

/**
1500  asin  :  DA	F  ->  G
G is the arc sine of F.
*/
void do_asin(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = asin(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
