/*
    module  : min.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef MIN_C
#define MIN_C

/**
min  :  N1 N2  ->  N
N is the minimum of numeric values N1 and N2.
*/
void do_min(void)
{
    BINARY;
    if (stack[-2] > stack[-1])
	stack[-2] = stack[-1];
    do_zap();
}
#endif
