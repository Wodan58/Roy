/*
    module  : sinh.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef SINH_C
#define SINH_C

/**
sinh  :  F  ->  G
G is the hyperbolic sine of F.
*/
void do_sinh(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = sinh(dbl);
    stack[-1] = pack(dbl);
}
#endif
