/*
    module  : sin.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef SIN_C
#define SIN_C

/**
1640  sin  :  DA	F  ->  G
G is the sine of F.
*/
void do_sin(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = sin(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
