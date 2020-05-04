/*
    module  : set.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef SET_C
#define SET_C

/**
set  :  X  ->  B
Tests whether X is a set.
*/
void do_set(void)
{
    UNARY;
    stack[-1] = is_set(stack[-1]);
}
#endif
