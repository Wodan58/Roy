/*
    module  : _gt_.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef _GT__C
#define _GT__C

/**
2240  >  :  DDA 	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is greater than Y.  Also supports float.
*/
void do__gt_(void)
{
    TWOPARAMS;
    stack[-2] = MAKE_BOOLEAN(Compare(stack[-2], stack[-1]) > 0);
    stack_pop();
}
#endif
