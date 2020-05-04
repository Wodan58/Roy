/*
    module  : integer.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef INTEGER_C
#define INTEGER_C

/**
integer  :  X  ->  B
Tests whether X is an integer.
*/
void do_integer(void)
{
    UNARY;
    stack[-1] = is_integer(stack[-1]);
}
#endif
