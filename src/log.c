/*
    module  : log.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef LOG_C
#define LOG_C

/**
1600  log  :  DA	F  ->  G
G is the natural logarithm of F.
*/
void do_log(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = log(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
