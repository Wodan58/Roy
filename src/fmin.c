/*
    module  : fmin.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FMIN_C
#define FMIN_C

/**
fmin  :  N1 N2  ->  N
N is the minimum of numeric values N1 and N2.
*/
void do_fmin(void)
{
    intptr_t temp;
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(temp = do_pop());
    dbl1 = unpack(stack[-1]);
    if (dbl1 > dbl2)
	stack[-1] = temp;
}
#endif
