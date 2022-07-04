/*
    module  : _ast_.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef _AST__C
#define _AST__C

/**
1400  *  :  DDA 	I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
void mul_int(void)
{
    INTEGERS2;
    stack[-2]
        = MAKE_INTEGER(GET_AS_INTEGER(stack[-2]) * GET_AS_INTEGER(stack[-1]));
    stack_pop();
}

void mul_dbl(void)
{
    double dbl1, dbl2;

    dbl2 = GET_AS_NUMBER(stack_pop());
    dbl1 = GET_AS_NUMBER(stack[-1]);
    dbl1 *= dbl2;
    stack[-1] = MAKE_DOUBLE(dbl1);
}

void do__ast_(void)
{
    TWOPARAMS;
    NUMBERS2;
    if (IS_DOUBLE(stack[-1]) || IS_DOUBLE(stack[-2]))
        mul_dbl();
    else
        mul_int();
}
#endif
