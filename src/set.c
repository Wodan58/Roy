/*
    module  : set.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef SET_C
#define SET_C

/**
2360  set  :  DA	X  ->  B
Tests whether X is a set.
*/
void do_set(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_SET(stack[-1]));
}
#endif
