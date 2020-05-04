/*
    module  : swons_set.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef SWONS_SET_C
#define SWONS_SET_C

/**
swons_set  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_swons_set(void)
{
    BINARY;
    stack[-2] |= (intptr_t)1 << stack[-1];
    do_zap();
}
#endif
