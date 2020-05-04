/*
    module  : rollup.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
void do_rollup(void)
{
    intptr_t temp;

    TERNARY;
    temp = stack[-1];
    stack[-1] = stack[-2];
    stack[-2] = stack[-3];
    stack[-3] = temp;
}
#endif
