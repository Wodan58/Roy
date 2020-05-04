/*
    module  : unswons_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef UNSWONS_SET_C
#define UNSWONS_SET_C

/**
unswons_set  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void do_unswons_set(void)
{
    int i = 0;
    intptr_t j, set;

    UNARY;
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j)
	    break;
    stack[-1] &= ~j;
    do_push(i);
}
#endif
