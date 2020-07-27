/*
    module  : eql.c
    version : 1.9
    date    : 07/23/20
*/
#ifndef EQL_C
#define EQL_C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

/**
=  :  X Y  ->  B
X and Y are numeric.
Tests whether X is equal to Y.
*/
void do_eql(void)
{
    BINARY;
    stack[-2] = is_equal_item(stack[-2], stack[-1]);
    do_pop();
}
#endif
