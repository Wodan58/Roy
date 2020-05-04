/*
    module  : first_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FIRST_STR_C
#define FIRST_STR_C

/**
first_str  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
void do_first_str(void)
{
    char *str;

    UNARY;
    str = (char *)stack[-1];
    stack[-1] = *str;
}
#endif
