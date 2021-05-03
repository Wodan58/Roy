/*
    module  : num2dbl.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef NUM2DBL_C
#define NUM2DBL_C

/**
num2dbl  :  I  ->  F
Convert a number to double.
*/
void do_num2dbl(void)
{
    real_t dbl;
    intptr_t num;

    UNARY;
    num = stack[-1];
    dbl = num;
    stack[-1] = pack(dbl);
}
#endif
