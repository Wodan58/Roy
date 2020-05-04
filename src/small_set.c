/*
    module  : small_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef SMALL_SET_C
#define SMALL_SET_C

/**
small_set  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void do_small_set(void)
{
    int i, k = 0;
    intptr_t j, set;

    UNARY;
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j)
	    k++;
    stack[-1] = k < 2;
}
#endif
