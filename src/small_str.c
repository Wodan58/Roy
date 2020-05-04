/*
    module  : small_str.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef SMALL_STR_C
#define SMALL_STR_C

/**
small_str  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void do_small_str(void)
{
    UNARY;
    stack[-1] = !stack[-1] || strlen((char *)stack[-1]) < 2;
}
#endif
