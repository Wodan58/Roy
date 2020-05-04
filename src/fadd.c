/*
    module  : fadd.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef FADD_C
#define FADD_C

/**
.+  :  M I  ->  N
Float N is the result of adding float I to float M.
*/
void do_fadd(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    dbl1 += dbl2;
    stack[-1] = pack(dbl1);
}
#endif
