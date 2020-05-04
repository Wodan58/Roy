/*
    module  : small.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef SMALL_C
#define SMALL_C

/**
small  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void do_small(void)
{
    UNARY;
    stack[-1] = !stack[-1] || vec_size((Stack *)stack[-1]) < 2;
}
#endif
