/*
    module  : tan.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef TAN_C
#define TAN_C

/**
1670  tan  :  DA	F  ->  G
G is the tangent of F.
*/
void do_tan(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = tan(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
