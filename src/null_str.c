/*
    module  : null_str.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef NULL_STR_C
#define NULL_STR_C

/**
null_str  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
void do_null_str(void)
{
    char *str;

    UNARY;
    str = (char *)stack[-1];
    stack[-1] = !str || !*str;
}
#endif
