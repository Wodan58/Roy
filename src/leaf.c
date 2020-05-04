/*
    module  : leaf.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef LEAF_C
#define LEAF_C

/**
leaf  :  X  ->  B
Tests whether X is not a list.
*/
void do_leaf(void)
{
    UNARY;
    if (stack[-1])
	stack[-1] = !is_list(stack[-1]);
}
#endif
