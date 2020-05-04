/*
    module  : pow.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef POW_C
#define POW_C

/**
pow  :  F G  ->  H
H is F raised to the Gth power.
*/
void do_pow(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    dbl1 = pow(dbl1, dbl2);
    stack[-1] = pack(dbl1);
}
#endif
