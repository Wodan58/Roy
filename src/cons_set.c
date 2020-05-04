/*
    module  : cons_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef CONS_SET_C
#define CONS_SET_C

/**
cons_set  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_cons_set(void)
{
    BINARY;
    stack[-2] = stack[-1] | (intptr_t)1 << stack[-2];
    do_zap();
}
#endif
