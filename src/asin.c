/*
    module  : asin.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef ASIN_C
#define ASIN_C

/**
asin  :  F  ->  G
G is the arc sine of F.
*/
void do_asin(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = asin(dbl);
    stack[-1] = pack(dbl);
}
#endif
