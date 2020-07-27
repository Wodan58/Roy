/*
    module  : max.c
    version : 1.8
    date    : 07/23/20
*/
#ifndef MAX_C
#define MAX_C

/**
max  :  N1 N2  ->  N
N is the maximum of numeric values N1 and N2.
*/
void do_max(void)
{
    BINARY;
    if (stack[-2] < stack[-1])
	stack[-2] = stack[-1];
    do_pop();
}
#endif
