/*
    module  : fmul.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef FMUL_C
#define FMUL_C

/**
.*  :  I J  ->  K
Float K is the product of floats I and J.
*/
void do_fmul(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    dbl1 *= dbl2;
    stack[-1] = pack(dbl1);
}
#endif
