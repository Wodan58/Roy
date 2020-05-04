/*
    module  : rolldown.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

/**
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
void do_rolldown(void)
{
    intptr_t temp;

    TERNARY;
    temp = stack[-3];
    stack[-3] = stack[-2];
    stack[-2] = stack[-1];
    stack[-1] = temp;
}
#endif
