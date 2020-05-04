/*
    module  : eq.c
    version : 1.2
    date    : 01/19/20
*/
#ifndef EQ_C
#define EQ_C

/**
eq  :  X Y  ->  B
X and Y are strings or symbols.
Tests whether X is equal to Y.
*/
void do_eq(void)
{
    BINARY;
    stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
		       (char *)(stack[-1] & ~JLAP_INVALID)) == 0;
    do_zap();
}
#endif
