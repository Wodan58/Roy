/*
    module  : rest_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef REST_SET_C
#define REST_SET_C

/**
rest_set  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void do_rest_set(void)
{
    int i = 0;
    intptr_t j, set;

    UNARY;
    if ((set = stack[-1]) != 0) {
	for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	    if (set & j)
		break;
	stack[-1] &= ~j;
    }
}
#endif
