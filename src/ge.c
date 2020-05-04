/*
    module  : ge.c
    version : 1.2
    date    : 01/19/20
*/
#ifndef GE_C
#define GE_C

/**
ge  :  X Y  ->  B
X and Y are strings or symbols.
Tests whether X is greater than or equal to Y.
*/
void do_ge(void)
{
    BINARY;
    stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
		       (char *)(stack[-1] & ~JLAP_INVALID)) >= 0;
    do_zap();
}
#endif
