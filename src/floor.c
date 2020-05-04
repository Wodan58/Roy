/*
    module  : floor.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef FLOOR_C
#define FLOOR_C

/**
floor  :  F  ->  G
G is the floor of F.
*/
void do_floor(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = floor(dbl);
    stack[-1] = pack(dbl);
}
#endif
