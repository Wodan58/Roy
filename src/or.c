/*
    module  : or.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef OR_C
#define OR_C

/**
or  :  X Y  ->  Z
Z is the union of sets X and Y, logical disjunction for truth values.
*/
void do_or(void)
{
    BINARY;
    stack[-2] |= stack[-1];
    do_zap();
}
#endif
