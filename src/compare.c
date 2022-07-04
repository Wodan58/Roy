/*
    module  : compare.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef COMPARE_C
#define COMPARE_C

/**
2060  compare  :  DDA 	A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <, =, >.
*/
void do_compare(void)
{
    value_t temp;

    TWOPARAMS;
    temp = stack_pop();
    stack[-1] = MAKE_INTEGER(Compare(stack[-1], temp));
}
#endif
