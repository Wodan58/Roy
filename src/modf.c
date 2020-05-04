/*
    module  : modf.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef MODF_C
#define MODF_C

/**
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
void do_modf(void)
{
    real_t dbl, exp;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = modf(dbl, &exp);
    stack[-1] = pack(dbl);
    do_push(pack(exp));
}
#endif
