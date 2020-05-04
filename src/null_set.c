/*
    module  : null_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef NULL_SET_C
#define NULL_SET_C

/**
null_set  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void do_null_set(void)
{
    UNARY;
    stack[-1] = !stack[-1];
}
#endif
