/*
    module  : neg.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef NEG_C
#define NEG_C

/**
1450  neg  :  DA	I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
void do_neg(void)
{
    double dbl;

    ONEPARAM;
    NUMBER;
    if (IS_DOUBLE(stack[-1])) {
        dbl = GET_AS_DOUBLE(stack[-1]);
        dbl = -dbl;
        stack[-1] = MAKE_DOUBLE(dbl);
    } else if (IS_INTEGER(stack[-1]))
        stack[-1] = MAKE_INTEGER(-GET_AS_INTEGER(stack[-1]));
}
#endif
