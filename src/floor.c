/*
    module  : floor.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef FLOOR_C
#define FLOOR_C

/**
1570  floor  :  DA	F  ->  G
G is the floor of F.
*/
void do_floor(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    dbl = GET_AS_NUMBER(stack[-1]);
    dbl = floor(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
