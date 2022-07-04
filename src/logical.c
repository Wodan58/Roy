/*
    module  : logical.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef LOGICAL_C
#define LOGICAL_C

/**
2350  logical  :  DA	X  ->  B
Tests whether X is a logical.
*/
void do_logical(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_BOOLEAN(stack[-1]));
}
#endif
