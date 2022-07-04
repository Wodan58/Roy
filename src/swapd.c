/*
    module  : swapd.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef SWAPD_C
#define SWAPD_C

/**
1280  swapd  :  DDDAAA	X Y Z  ->  Y X Z
As if defined by:   swapd  ==  [swap] dip
*/
void do_swapd(void)
{
    value_t temp;

    THREEPARAMS;
    temp = stack[-2];
    stack[-2] = stack[-3];
    stack[-3] = temp;
}
#endif
