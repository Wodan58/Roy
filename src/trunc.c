/*
    module  : trunc.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef TRUNC_C
#define TRUNC_C

/**
1690  trunc  :  DA	F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
void do_trunc(void)
{
    double dbl;
    int64_t num;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    num = dbl;
    stack[-1] = MAKE_INTEGER(num);
}
#endif
