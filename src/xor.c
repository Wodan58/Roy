/*
    module  : xor.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef XOR_C
#define XOR_C

/**
1350  xor  :  DDA	X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
void do_xor(void)
{
    TWOPARAMS;
    SAME2TYPES;
    if (IS_SET(stack[-1]))
        stack[-2] = MAKE_SET(GET_AS_SET(stack[-2]) ^ GET_AS_SET(stack[-1]));
    else if (IS_BOOLEAN(stack[-1]))
        stack[-2] = MAKE_BOOLEAN(
            GET_AS_BOOLEAN(stack[-2]) ^ GET_AS_BOOLEAN(stack[-1]));
    else
        BADDATA;
    stack_pop();
}
#endif
