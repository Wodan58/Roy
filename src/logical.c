/*
    module  : logical.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef LOGICAL_C
#define LOGICAL_C

/**
logical  :  X  ->  B
Tests whether X is a logical.
*/
void do_logical(void)
{
    UNARY;
    stack[-1] = is_boolean(stack[-1]);
}
#endif
