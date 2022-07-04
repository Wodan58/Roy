/*
    module  : pred.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef PRED_C
#define PRED_C

/**
1790  pred  :  DA	M  ->  N
Numeric N is the predecessor of numeric M.
*/
void do_pred(void)
{
    ONEPARAM;
    NUMERICTYPE;
    if (IS_INTEGER(stack[-1]))
        stack[-1] = MAKE_INTEGER(GET_AS_INTEGER(stack[-1]) - 1);
    else if (IS_CHAR(stack[-1]))
        stack[-1] = MAKE_CHAR(GET_AS_CHAR(stack[-1]) - 1);
    else if (IS_BOOLEAN(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(GET_AS_BOOLEAN(stack[-1]) - 1);
}
#endif
