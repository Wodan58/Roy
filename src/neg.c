/*
    module  : neg.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef NEG_C
#define NEG_C

/**
neg  :  I  ->  J
Integer J is the negative of integer I.
*/
void do_neg(void)
{
    UNARY;
    stack[-1] = -stack[-1];
}
#endif
