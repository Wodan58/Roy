/*
    module  : ceil.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef CEIL_C
#define CEIL_C

/**
ceil  :  F  ->  G
G is the float ceiling of F.
*/
void do_ceil(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = ceil(dbl);
    stack[-1] = pack(dbl);
}
#endif
