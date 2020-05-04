/*
    module  : not.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef NOT_C
#define NOT_C

/**
not  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
void do_not(void)
{
    UNARY;
    stack[-1] = !stack[-1];
}
#endif
