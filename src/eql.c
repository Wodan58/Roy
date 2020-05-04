/*
    module  : eql.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef EQL_C
#define EQL_C

/**
=  :  X Y  ->  B
X and Y are numeric.
Tests whether X is equal to Y.
*/
void do_eql(void)
{
    BINARY;
    if (is_string(stack[-1]) && is_string(stack[-2]))
	stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
			   (char *)(stack[-1] & ~JLAP_INVALID)) == 0;
    else
	stack[-2] = stack[-2] == stack[-1];
    do_zap();
}
#endif
