/*
    module  : integer.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef INTEGER_C
#define INTEGER_C

/**
2330  integer  :  DA	X  ->  B
Tests whether X is an integer.
*/
void do_integer(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_INTEGER(stack[-1]));
}
#endif
