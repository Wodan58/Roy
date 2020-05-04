/*
    module  : leql.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef LEQL_C
#define LEQL_C

/**
<=  :  X Y  ->  B
X and Y are numeric.
Tests whether X is less than or equal to Y.
*/
void do_leql(void)
{
    BINARY;
    stack[-2] = stack[-2] <= stack[-1];
    do_zap();
}
#endif
