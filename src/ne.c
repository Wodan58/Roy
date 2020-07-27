/*
    module  : ne.c
    version : 1.3
    date    : 07/23/20
*/
#ifndef NE_C
#define NE_C

/**
ne  :  X Y  ->  B
X and Y are strings or symbols.
Tests whether X is not equal to Y.
*/
void do_ne(void)
{
    BINARY;
    stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
		       (char *)(stack[-1] & ~JLAP_INVALID)) != 0;
    do_pop();
}
#endif
