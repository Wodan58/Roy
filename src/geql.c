/*
    module  : geql.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef GEQL_C
#define GEQL_C

/**
>=  :  X Y  ->  B
X and Y are numeric.
Tests whether X is greater than or equal to Y.
*/
void do_geql(void)
{
    BINARY;
    stack[-2] = stack[-2] >= stack[-1];
    do_zap();
}
#endif
