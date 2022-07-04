/*
    module  : rolldownd.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ROLLDOWND_C
#define ROLLDOWND_C

/**
1300  rolldownd  :  DDDDAAAA	X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
void do_rolldownd(void)
{
    value_t temp;

    FOURPARAMS;
    temp = stack[-4];
    stack[-4] = stack[-3];
    stack[-3] = stack[-2];
    stack[-2] = temp;
}
#endif
