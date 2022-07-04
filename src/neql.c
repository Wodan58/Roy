/*
    module  : neql.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef NEQL_C
#define NEQL_C

/**
2270  !=  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is not equal to Y.  Also supports float.
*/
void do_neql(void)
{
    TWOPARAMS;
    stack[-2] = MAKE_BOOLEAN(Compare(stack[-2], stack[-1]) != 0);
    stack_pop();
}
#endif
