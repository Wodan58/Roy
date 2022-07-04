/*
    module  : abs.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef ABS_C
#define ABS_C

/**
1480  abs  :  DA	N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
void do_abs(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    if (IS_DOUBLE(stack[-1])) {
        dbl = GET_AS_DOUBLE(stack[-1]);
        dbl = fabs(dbl);
        stack[-1] = MAKE_DOUBLE(dbl);
    } else if (IS_INTEGER(stack[-1])) {
        if (GET_AS_INTEGER(stack[-1]) < 0)
            stack[-1] = MAKE_INTEGER(-GET_AS_INTEGER(stack[-1]));
    }
}
#endif
