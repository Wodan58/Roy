/*
    module  : modf.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef MODF_C
#define MODF_C

/**
1620  modf  :  DAA	F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
void do_modf(void)
{
    double dbl, exp;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = modf(dbl, &exp);
    stack[-1] = MAKE_DOUBLE(dbl);
    do_push(MAKE_DOUBLE(exp));
}
#endif
