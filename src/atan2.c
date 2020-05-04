/*
    module  : atan2.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef ATAN2_C
#define ATAN2_C

/**
atan2  :  F G  ->  H
H is the arc tangent of F / G.
*/
void do_atan2(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    dbl1 = atan2(dbl1, dbl2);
    stack[-1] = pack(dbl1);
}
#endif
