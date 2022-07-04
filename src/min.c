/*
    module  : min.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef MIN_C
#define MIN_C

/**
1820  min  :  DDA	N1 N2  ->  N
N is the minimum of numeric values N1 and N2.  Also supports float.
*/
void f_min(void)
{
    value_t temp;
    double dbl1, dbl2;

    NUMBERS2;
    temp = stack_pop();
    dbl2 = GET_AS_NUMBER(temp);
    dbl1 = GET_AS_NUMBER(stack[-1]);
    if (dbl1 > dbl2)
        stack[-1] = temp;
}

void i_min(void)
{
    value_t tmp1, tmp2;

    SAME2TYPES;
    NUMERICTYPE;
    tmp2 = stack_pop();
    tmp1 = stack[-1];
    if (IS_INTEGER(tmp1)) {
        if (GET_AS_INTEGER(tmp1) > GET_AS_INTEGER(tmp2))
            stack[-1] = tmp2;
    } else if (IS_CHAR(tmp1)) {
        if (GET_AS_CHAR(tmp1) > GET_AS_CHAR(tmp2))
            stack[-1] = tmp2;
    } else if (IS_BOOLEAN(tmp1)) {
        if (GET_AS_BOOLEAN(tmp1) > GET_AS_BOOLEAN(tmp2))
            stack[-1] = tmp2;
    }
}

void do_min(void)
{
    TWOPARAMS;
    if (IS_DOUBLE(stack[-1]) || IS_DOUBLE(stack[-2]))
        f_min();
    else
        i_min();
}
#endif
