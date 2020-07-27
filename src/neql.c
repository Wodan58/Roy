/*
    module  : neql.c
    version : 1.8
    date    : 07/23/20
*/
#ifndef NEQL_C
#define NEQL_C

/**
!=  :  X Y  ->  B
X and Y are numeric.
Tests whether X is not equal to Y.
*/
void do_neql(void)
{
    BINARY;
    stack[-2] = stack[-2] != stack[-1];
    do_pop();
}
#endif
