/*
    module  : exp.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef EXP_C
#define EXP_C

/**
1560  exp  :  DA	F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
void do_exp(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = exp(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
