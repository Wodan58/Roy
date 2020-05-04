/*
    module  : lt.c
    version : 1.2
    date    : 01/19/20
*/
#ifndef LT_C
#define LT_C

/**
lt  :  X Y  ->  B
X and Y are strings or symbols.
Tests whether X is less than Y.
*/
void do_lt(void)
{
    BINARY;
    stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
		       (char *)(stack[-1] & ~JLAP_INVALID)) < 0;
    do_zap();
}
#endif
