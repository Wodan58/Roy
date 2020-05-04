/*
    module  : sin.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef SIN_C
#define SIN_C

/**
sin  :  F  ->  G
G is the sine of F.
*/
void do_sin(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = sin(dbl);
    stack[-1] = pack(dbl);
}
#endif
