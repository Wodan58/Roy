/*
    module  : exp.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef EXP_C
#define EXP_C

/**
exp  :  F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
void do_exp(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = exp(dbl);
    stack[-1] = pack(dbl);
}
#endif
