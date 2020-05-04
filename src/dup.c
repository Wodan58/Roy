/*
    module  : dup.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef DUP_C
#define DUP_C

/**
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
void do_dup(void)
{
    UNARY;
    do_push(stack[-1]);
}
#endif
