/*
    module  : float.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef FLOAT_C
#define FLOAT_C

/**
float  :  R  ->  B
Tests whether R is a float.
*/
void do_float(void)
{
    UNARY;
    stack[-1] = is_float(stack[-1]);
}
#endif
