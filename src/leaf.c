/*
    module  : leaf.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef LEAF_C
#define LEAF_C

/**
2390  leaf  :  DA	X  ->  B
Tests whether X is not a list.
*/
void do_leaf(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(!IS_LIST(stack[-1]));
}
#endif
