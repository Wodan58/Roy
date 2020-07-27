/*
    module  : le.c
    version : 1.3
    date    : 07/23/20
*/
#ifndef LE_C
#define LE_C

/**
le  :  X Y  ->  B
X and Y are strings or symbols.
Tests whether X is less than or equal to Y.
*/
void do_le(void)
{
    BINARY;
    stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
		       (char *)(stack[-1] & ~JLAP_INVALID)) <= 0;
    do_pop();
}
#endif
