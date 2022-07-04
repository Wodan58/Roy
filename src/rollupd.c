/*
    module  : rollupd.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef ROLLUPD_C
#define ROLLUPD_C

/**
1290  rollupd  :  DDDDAAAA	X Y Z W  ->  Z X Y W
As if defined by:   rollupd  ==  [rollup] dip
*/
void do_rollupd(void)
{
    value_t temp;

    FOURPARAMS;
    temp = stack[-2];
    stack[-2] = stack[-3];
    stack[-3] = stack[-4];
    stack[-4] = temp;
}
#endif
