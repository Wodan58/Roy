/*
    module  : fmax.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FMAX_C
#define FMAX_C

/**
fmax  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.
*/
void do_fmax(void)
{
    intptr_t temp;
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(temp = do_pop());
    dbl1 = unpack(stack[-1]);
    if (dbl1 < dbl2)
	stack[-1] = temp;
}
#endif
