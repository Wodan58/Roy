/*
    module  : rotate.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
void do_rotate(void)
{
    intptr_t temp;

    TERNARY;
    temp = stack[-1];
    stack[-1] = stack[-3];
    stack[-3] = temp;
}
#endif
