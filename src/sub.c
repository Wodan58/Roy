/*
    module  : sub.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef SUB_C
#define SUB_C

/**
-  :  M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
*/
void do_sub(void)
{
    BINARY;
    stack[-2] -= stack[-1];
    do_zap();
}
#endif
