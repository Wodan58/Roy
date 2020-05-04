/*
    module  : divide.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef DIVIDE_C
#define DIVIDE_C

/**
/  :  I J  ->  K
Integer K is the (rounded) ratio of integers I and J.
*/
void do_divide(void)
{
    BINARY;
    if (stack[-1])
	stack[-2] /= stack[-1];
    else
	execerror("non-zero divisor", "/");
    do_zap();
}
#endif
