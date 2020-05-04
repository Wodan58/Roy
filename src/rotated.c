/*
    module  : rotated.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef ROTATED_C
#define ROTATED_C

/**
rotated  :  X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
void do_rotated(void)
{
    intptr_t temp;

    QUATERN;
    temp = stack[-2];
    stack[-2] = stack[-4];
    stack[-4] = temp;
}
#endif
