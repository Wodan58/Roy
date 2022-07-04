/*
    module  : not.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef NOT_C
#define NOT_C

/**
1370  not  :  DA	X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
void do_not(void)
{
    ONEPARAM;
    if (IS_SET(stack[-1]))
        stack[-1] = MAKE_SET(~GET_AS_SET(stack[-1]));
    else if (IS_BOOLEAN(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(!GET_AS_BOOLEAN(stack[-1]));
    else if (IS_INTEGER(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(!GET_AS_INTEGER(stack[-1]));
    else if (IS_CHAR(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(!GET_AS_CHAR(stack[-1]));
    else
        BADDATA;
}
#endif
