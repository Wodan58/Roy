/*
    module  : _gt__equals_.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef _GT__EQUALS__C
#define _GT__EQUALS__C

/**
2230  >=  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is greater than or equal to Y.  Also supports float.
*/
void do__gt__equals_(void)
{
    TWOPARAMS;
    stack[-2] = MAKE_BOOLEAN(Compare(stack[-2], stack[-1]) >= 0);
    stack_pop();
}
#endif
