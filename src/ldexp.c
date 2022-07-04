/*
    module  : ldexp.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef LDEXP_C
#define LDEXP_C

/**
1590  ldexp  :  DDA	F I  ->  G
G is F times 2 to the Ith power.
*/
void do_ldexp(void)
{
    int exp;
    double dbl;

    TWOPARAMS;
    INTEGER;
    exp = GET_AS_INTEGER(stack_pop());
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = ldexp(dbl, exp);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
