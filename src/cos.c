/*
    module  : cos.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef COS_C
#define COS_C

/**
1540  cos  :  DA	F  ->  G
G is the cosine of F.
*/
void do_cos(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = cos(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
