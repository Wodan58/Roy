/*
    module  : abs.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef ABS_C
#define ABS_C

/**
abs  :  N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1.
*/
void do_abs(void)
{
    UNARY;
    if (stack[-1] < 0)
	stack[-1] = -stack[-1];
}
#endif
