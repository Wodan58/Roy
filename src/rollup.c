/*
    module  : rollup.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
1230  rollup  :  DDDAAA 	X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
void do_rollup(void)
{
    value_t temp;

    THREEPARAMS;
    temp = stack[-1];
    stack[-1] = stack[-2];
    stack[-2] = stack[-3];
    stack[-3] = temp;
}
#endif
