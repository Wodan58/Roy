/*
    module  : not_set.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef NOT_SET_C
#define NOT_SET_C

/**
not_set  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
void do_not_set(void)
{
    UNARY;
    stack[-1] = ~stack[-1];
}
#endif
