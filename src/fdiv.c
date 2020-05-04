/*
    module  : fdiv.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef FDIV_C
#define FDIV_C

/**
./  :  I J  ->  K
Float K is the ratio of floats I and J.
*/
void do_fdiv(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    dbl1 /= dbl2;
    stack[-1] = pack(dbl1);
}
#endif
