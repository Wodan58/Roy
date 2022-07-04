/*
    module  : frexp.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FREXP_C
#define FREXP_C

/**
1580  frexp  :  DAA	F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
void do_frexp(void)
{
    int exp;
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = frexp(dbl, &exp);
    stack[-1] = MAKE_DOUBLE(dbl);
    do_push(MAKE_INTEGER(exp));
}
#endif
