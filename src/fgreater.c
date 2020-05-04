/*
    module  : fgreater.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef FGREATER_C
#define FGREATER_C

/**
.>  :  X Y  ->  B
Tests whether X is greater than Y.
*/
void do_fgreater(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    stack[-1] = dbl1 > dbl2;
}
#endif
