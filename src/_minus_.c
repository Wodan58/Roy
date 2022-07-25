/*
    module  : _minus_.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef _MINUS__C
#define _MINUS__C

/**
1390  -  :  DDA 	M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
void sub_int(void)
{
    value_t tmp1, tmp2;

    INTEGER;
    tmp2 = stack_pop();
    NUMERIC;
    tmp1 = stack[-1];
    if (IS_INTEGER(tmp1))
        stack[-1] = MAKE_INTEGER(GET_AS_INTEGER(tmp1) - GET_AS_INTEGER(tmp2));
    else
        stack[-1] = MAKE_CHAR(GET_AS_CHAR(tmp1) - GET_AS_INTEGER(tmp2));
}

void sub_dbl(void)
{
    double dbl1, dbl2;

    NUMBERS2;
    dbl2 = GET_AS_NUMBER(stack_pop());
    dbl1 = GET_AS_NUMBER(stack[-1]);
    dbl1 -= dbl2;
    stack[-1] = MAKE_DOUBLE(dbl1);
}

void do__minus_(void)
{
    TWOPARAMS;
    if (IS_DOUBLE(stack[-1]) || IS_DOUBLE(stack[-2]))
        sub_dbl();
    else
        sub_int();
}
#endif