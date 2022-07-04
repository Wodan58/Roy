/*
    module  : float.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef FLOAT_C
#define FLOAT_C

/**
2410  float  :  DA	R  ->  B
Tests whether R is a float.
*/
void do_float(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_DOUBLE(stack[-1]));
}
#endif
