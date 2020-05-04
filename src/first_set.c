/*
    module  : first_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FIRST_SET_C
#define FIRST_SET_C

/**
first_set  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
void do_first_set(void)
{
    int i = 0;
    intptr_t j, set;

    UNARY;
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j)
	    break;
    stack[-1] = i;
}
#endif
