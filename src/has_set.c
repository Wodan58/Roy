/*
    module  : has_set.c
    version : 1.6
    date    : 07/23/20
*/
#ifndef HAS_SET_C
#define HAS_SET_C

/**
has_set  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
void do_has_set(void)
{
    BINARY;
    stack[-2] = (stack[-2] & (intptr_t)1 << stack[-1]) != 0;
    do_pop();
}
#endif
