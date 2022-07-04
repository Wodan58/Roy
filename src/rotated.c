/*
    module  : rotated.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef ROTATED_C
#define ROTATED_C

/**
1310  rotated  :  DDDDAAAA	X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
void do_rotated(void)
{
    value_t temp;

    FOURPARAMS;
    temp = stack[-2];
    stack[-2] = stack[-4];
    stack[-4] = temp;
}
#endif
