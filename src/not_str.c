/*
    module  : not_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef NOT_STR_C
#define NOT_STR_C

/**
not_str  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
void do_not_str(void)
{
    char *str;

    UNARY;
    str = (char *)stack[-1];
    stack[-1] = !str || !*str;
}
#endif
