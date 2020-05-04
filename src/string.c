/*
    module  : string.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef STRING_C
#define STRING_C

/**
string  :  X  ->  B
Tests whether X is a string.
*/
void do_string(void)
{
    UNARY;
    stack[-1] = is_string(stack[-1]);
}
#endif
