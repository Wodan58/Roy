/*
    module  : rolldown.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

/**
1240  rolldown  :  DDDAAA	X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
void do_rolldown(void)
{
    value_t temp;

    THREEPARAMS;
    temp = stack[-3];
    stack[-3] = stack[-2];
    stack[-2] = stack[-1];
    stack[-1] = temp;
}
#endif
