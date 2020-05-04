/*
    module  : swapd.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef SWAPD_C
#define SWAPD_C

/**
swapd  :  X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
void do_swapd(void)
{
    intptr_t temp;

    TERNARY;
    temp = stack[-2];
    stack[-2] = stack[-3];
    stack[-3] = temp;
}
#endif
