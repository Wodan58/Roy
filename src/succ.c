/*
    module  : succ.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef SUCC_C
#define SUCC_C

/**
1800  succ  :  DA	M  ->  N
Numeric N is the successor of numeric M.
*/
void do_succ(void)
{
    ONEPARAM;
    NUMERICTYPE;
    if (IS_INTEGER(stack[-1]))
        stack[-1] = MAKE_INTEGER(GET_AS_INTEGER(stack[-1]) + 1);
    else if (IS_CHAR(stack[-1]))
        stack[-1] = MAKE_CHAR(GET_AS_CHAR(stack[-1]) + 1);
    else if (IS_BOOLEAN(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(GET_AS_BOOLEAN(stack[-1]) + 1);
}
#endif
