/*
    module  : in_set.c
    version : 1.2
    date    : 07/23/20
*/
#ifndef HAS_IN_C
#define HAS_IN_C

/**
in_set  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
void do_in_set(void)
{
    BINARY;
    stack[-2] = (stack[-1] & (intptr_t)1 << stack[-2]) != 0;
    do_pop();
}
#endif
