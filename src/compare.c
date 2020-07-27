/*
    module  : compare.c
    version : 1.9
    date    : 07/23/20
*/
#ifndef COMPARE_C
#define COMPARE_C

/**
compare  :  A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <, =, >.
*/
void do_compare(void)
{
    BINARY;
    if (stack[-2] < stack[-1])
	stack[-2] = -1;
    else if (stack[-2] > stack[-1])
	stack[-2] = 1;
    else
	stack[-2] = 0;
    do_pop();
}
#endif
