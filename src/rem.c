/*
    module  : rem.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef REM_C
#define REM_C

/**
1420  rem  :  DDA	I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
void frem(void)
{
    double dbl1, dbl2;

    dbl2 = GET_AS_NUMBER(stack_pop());
    dbl1 = GET_AS_NUMBER(stack[-1]);
    dbl1 = fmod(dbl1, dbl2);
    stack[-1] = MAKE_DOUBLE(dbl1);
}

void irem(void)
{
    INTEGERS2;
    stack[-2]
        = MAKE_INTEGER(GET_AS_INTEGER(stack[-2]) % GET_AS_INTEGER(stack[-1]));
    stack_pop();
}

void do_rem(void)
{
    TWOPARAMS;
    NUMBERS2;
    CHECKZERO;
    if (IS_DOUBLE(stack[-1]) || IS_DOUBLE(stack[-2]))
        frem();
    else
        irem();
}
#endif
