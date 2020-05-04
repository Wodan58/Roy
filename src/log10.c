/*
    module  : log10.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef LOG10_C
#define LOG10_C

/**
log10  :  F  ->  G
G is the common logarithm of F.
*/
void do_log10(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = log10(dbl);
    stack[-1] = pack(dbl);
}
#endif
