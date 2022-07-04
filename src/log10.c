/*
    module  : log10.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef LOG10_C
#define LOG10_C

/**
1610  log10  :  DA	F  ->  G
G is the common logarithm of F.
*/
void do_log10(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = log10(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
