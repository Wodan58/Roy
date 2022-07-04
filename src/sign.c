/*
    module  : sign.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef SIGN_C
#define SIGN_C

/**
1440  sign  :  DA	N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1,
or float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
void do_sign(void)
{
    int num;
    double dbl;

    ONEPARAM;
    NUMBER;
    if (IS_DOUBLE(stack[-1])) {
        dbl = GET_AS_DOUBLE(stack[-1]);
        if (dbl > 0)
            stack[-1] = MAKE_DOUBLE(1.0);
        else if (dbl < 0)
            stack[-1] = MAKE_DOUBLE(-1.0);
        else
            stack[-1] = MAKE_DOUBLE(0.0);
    } else if (IS_INTEGER(stack[-1])) {
        num = GET_AS_INTEGER(stack[-1]);
        if (num > 0)
            stack[-1] = MAKE_INTEGER(1);
        else if (num < 0)
            stack[-1] = MAKE_INTEGER(-1);
    }
}
#endif
