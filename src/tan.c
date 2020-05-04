/*
    module  : tan.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef TAN_C
#define TAN_C

/**
tan  :  F  ->  G
G is the tangent of F.
*/
void do_tan(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = tan(dbl);
    stack[-1] = pack(dbl);
}
#endif
