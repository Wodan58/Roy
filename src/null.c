/*
    module  : null.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef NULL_C
#define NULL_C

/**
null  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void do_null(void)
{
    UNARY;
    stack[-1] = !stack[-1];
}
#endif
