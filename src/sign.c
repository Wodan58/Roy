/*
    module  : sign.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef SIGN_C
#define SIGN_C

/**
sign  :  N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1.
*/
void do_sign(void)
{
    UNARY;
    if (stack[-1])
	stack[-1] = stack[-1] > 0 ? 1 : -1;
}
#endif
