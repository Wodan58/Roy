/*
    module  : atan2.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ATAN2_C
#define ATAN2_C

/**
1520  atan2  :  DDA	F G  ->  H
H is the arc tangent of F / G.
*/
void do_atan2(void)
{
    double dbl1, dbl2;

    TWOPARAMS;
    NUMBERS2;
    dbl2 = GET_AS_NUMBER(stack_pop());
    dbl1 = GET_AS_NUMBER(stack[-1]);
    dbl1 = atan2(dbl1, dbl2);
    stack[-1] = MAKE_DOUBLE(dbl1);
}
#endif
