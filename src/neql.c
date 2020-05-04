/*
    module  : neql.c
    version : 1.7
    date    : 01/19/20
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
    do_zap();
}
#endif
