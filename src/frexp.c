/*
    module  : frexp.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FREXP_C
#define FREXP_C

/**
frexp  :  F  ->  G I
G is the mantissa and I is the exponent of F.
Unless F = 0, 0.5 <= abs(G) < 1.0.
*/
void do_frexp(void)
{
    int exp;
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = frexp(dbl, &exp);
    stack[-1] = pack(dbl);
    do_push(exp);
}
#endif
