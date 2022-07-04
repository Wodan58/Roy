/*
    module  : atan.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ATAN_C
#define ATAN_C

/**
1510  atan  :  DA	F  ->  G
G is the arc tangent of F.
*/
void do_atan(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = atan(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
