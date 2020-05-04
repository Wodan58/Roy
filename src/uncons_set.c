/*
    module  : uncons_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef UNCONS_SET_C
#define UNCONS_SET_C

/**
uncons_set  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void do_uncons_set(void)
{
    int i = 0;
    intptr_t j, set;

    UNARY;
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j)
	    break;
    stack[-1] = i;
    do_push(set & ~j);
}
#endif
