/*
    module  : rollupd.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef ROLLUPD_C
#define ROLLUPD_C

/**
rollupd  :  X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
void do_rollupd(void)
{
    intptr_t temp;

    QUATERN;
    temp = stack[-2];
    stack[-2] = stack[-3];
    stack[-3] = stack[-4];
    stack[-4] = temp;
}
#endif
