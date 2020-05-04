/*
    module  : acos.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef ACOS_C
#define ACOS_C

/**
acos  :  F  ->  G
G is the arc cosine of F.
*/
void do_acos(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = acos(dbl);
    stack[-1] = pack(dbl);
}
#endif
