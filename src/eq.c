/*
    module  : eq.c
    version : 1.4
    date    : 07/23/20
*/
#ifndef EQ_C
#define EQ_C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

/**
eq  :  X Y  ->  B
X and Y are strings or symbols.
Tests whether X is equal to Y.
*/
void do_eq(void)
{
    BINARY;
    stack[-2] = is_equal_item(stack[-2], stack[-1]);
    do_pop();
}
#endif
