/*
    module  : dup.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef DUP_C
#define DUP_C

/**
1210  dup  :  A	X  ->  X X
Pushes an extra copy of X onto stack.
*/
void do_dup(void)
{
    ONEPARAM;
    do_push(stack[-1]);
}
#endif
