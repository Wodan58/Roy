/*
    module  : and.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef AND_C
#define AND_C

/**
1360  and  :  DDA	X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
void do_and(void)
{
    TWOPARAMS;
    SAME2TYPES;
    if (IS_SET(stack[-1]))
        stack[-2] = MAKE_SET(GET_AS_SET(stack[-2]) & GET_AS_SET(stack[-1]));
    else if (IS_BOOLEAN(stack[-1]))
        stack[-2] = MAKE_BOOLEAN(
            GET_AS_BOOLEAN(stack[-2]) & GET_AS_BOOLEAN(stack[-1]));
    else
        BADDATA;
    stack_pop();
}
#endif
