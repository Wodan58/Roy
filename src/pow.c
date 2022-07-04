/*
    module  : pow.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef POW_C
#define POW_C

/**
1630  pow  :  DDA	F G  ->  H
H is F raised to the Gth power.
*/
void do_pow(void)
{
    double dbl1, dbl2;

    TWOPARAMS;
    NUMBERS2;
    dbl2 = GET_AS_NUMBER(stack_pop());
    dbl1 = GET_AS_NUMBER(stack[-1]);
    dbl1 = pow(dbl1, dbl2);
    stack[-1] = MAKE_DOUBLE(dbl1);
}
#endif
