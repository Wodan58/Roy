/*
    module  : in.c
    version : 1.12
    date    : 06/23/20
*/
#ifndef IN_C
#define IN_C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

/**
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
void do_in(void)
{
    int i;
    Stack *List;

    BINARY;
    List = (Stack *)do_pop();
    for (i = vec_size(List) - 1; i >= 0; i--)
	if (is_equal_item(stack[-1], vec_at(List,i)))
	    break;
    stack[-1] = i >= 0;
}
#endif
