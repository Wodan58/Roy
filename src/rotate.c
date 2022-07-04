/*
    module  : rotate.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
1250  rotate  :  DDDAAA 	X Y Z  ->  Z Y X
Interchanges X and Z.
*/
void do_rotate(void)
{
    value_t temp;

    THREEPARAMS;
    temp = stack[-1];
    stack[-1] = stack[-3];
    stack[-3] = temp;
}
#endif
