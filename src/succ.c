/*
    module  : succ.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef SUCC_C
#define SUCC_C

/**
succ  :  M  ->  N
Numeric N is the successor of numeric M.
*/
void do_succ(void)
{
    UNARY;
    ++stack[-1];
}
#endif
