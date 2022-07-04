/*
    module  : or.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef OR_C
#define OR_C

/**
1340  or  :  DDA	X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
void do_or(void)
{
    TWOPARAMS;
    SAME2TYPES;
    if (IS_SET(stack[-1]))
        stack[-2] = MAKE_SET(GET_AS_SET(stack[-2]) | GET_AS_SET(stack[-1]));
    else if (IS_BOOLEAN(stack[-1]))
        stack[-2] = MAKE_BOOLEAN(
            GET_AS_BOOLEAN(stack[-2]) | GET_AS_BOOLEAN(stack[-1]));
    else
        BADDATA;
    stack_pop();
}
#endif
