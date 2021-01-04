/*
    module  : has.c
    version : 1.11
    date    : 01/04/21
*/
#ifndef HAS_C
#define HAS_C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
void do_has(void)
{
    int i;
    Stack *List;
    intptr_t Second;

    BINARY;
    Second = do_pop();
    List = (Stack *)stack[-1];
    for (i = vec_size(List) - 1; i >= 0; i--)
	if (is_equal_item(vec_at(List,i), Second))
	    break;
    stack[-1] = i >= 0;
}
#endif
