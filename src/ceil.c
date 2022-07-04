/*
    module  : ceil.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef CEIL_C
#define CEIL_C

/**
1530  ceil  :  DA	F  ->  G
G is the float ceiling of F.
*/
void do_ceil(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = ceil(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
