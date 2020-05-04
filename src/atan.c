/*
    module  : atan.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef ATAN_C
#define ATAN_C

/**
atan  :  F  ->  G
G is the arc tangent of F.
*/
void do_atan(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = atan(dbl);
    stack[-1] = pack(dbl);
}
#endif
