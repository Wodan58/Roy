/*
    module  : acos.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ACOS_C
#define ACOS_C

/**
1490  acos  :  DA	F  ->  G
G is the arc cosine of F.
*/
void do_acos(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = acos(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
