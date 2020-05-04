/*
    module  : cos.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef COS_C
#define COS_C

/**
cos  :  F  ->  G
G is the cosine of F.
*/
void do_cos(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = cos(dbl);
    stack[-1] = pack(dbl);
}
#endif
