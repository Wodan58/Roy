/*
    module  : _sol_.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef _SOL__C
#define _SOL__C

/**
1410  /  :  DDA 	I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
void div_int(void)
{
    INTEGERS2;
    if (GET_AS_INTEGER(stack[-1]))
        stack[-2] = MAKE_INTEGER(
            GET_AS_INTEGER(stack[-2]) / GET_AS_INTEGER(stack[-1]));
    stack_pop();
}

void div_dbl(void)
{
    double dbl1, dbl2;

    dbl2 = GET_AS_NUMBER(stack_pop());
    dbl1 = GET_AS_NUMBER(stack[-1]);
    dbl1 /= dbl2;
    stack[-1] = MAKE_DOUBLE(dbl1);
}

void do__sol_(void)
{
    TWOPARAMS;
    NUMBERS2;
    CHECKZERO;
    if (IS_DOUBLE(stack[-1]) || IS_DOUBLE(stack[-2]))
        div_dbl();
    else
        div_int();
}
#endif
