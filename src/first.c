/*
    module  : first.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef FIRST_C
#define FIRST_C

/**
first  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
void do_first(void)
{
    UNARY;
    if (stack[-1])
	stack[-1] = vec_back((Stack *)stack[-1]);
}
#endif
