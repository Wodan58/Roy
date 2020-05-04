/*
    module  : small_int.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef SMALL_INT_C
#define SMALL_INT_C

/**
small_int  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void do_small_int(void)
{
    UNARY;
    stack[-1] = stack[-1] < 2;
}
#endif
