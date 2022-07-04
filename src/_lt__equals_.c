/*
    module  : _lt__equals_.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef _LT__EQUALS__C
#define _LT__EQUALS__C

/**
2250  <=  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is less than or equal to Y.  Also supports float.
*/
void do__lt__equals_(void)
{
    TWOPARAMS;
    stack[-2] = MAKE_BOOLEAN(Compare(stack[-2], stack[-1]) <= 0);
    stack_pop();
}
#endif
