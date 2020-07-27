/*
    module  : xor.c
    version : 1.9
    date    : 07/23/20
*/
#ifndef XOR_C
#define XOR_C

/**
xor  :  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
void do_xor(void)
{
    BINARY;
    stack[-2] ^= stack[-1];
    do_pop();
}
#endif
