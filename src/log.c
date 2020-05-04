/*
    module  : log.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef LOG_C
#define LOG_C

/**
log  :  F  ->  G
G is the natural logarithm of F.
*/
void do_log(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = log(dbl);
    stack[-1] = pack(dbl);
}
#endif
