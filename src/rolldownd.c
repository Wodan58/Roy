/*
    module  : rolldownd.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef ROLLDOWND_C
#define ROLLDOWND_C

/**
rolldownd  :  X Y Z W  ->  Y Z X W
As if defined by:   rolldownd  ==  [rolldown] dip
*/
void do_rolldownd(void)
{
    intptr_t temp;

    QUATERN;
    temp = stack[-4];
    stack[-4] = stack[-3];
    stack[-3] = stack[-2];
    stack[-2] = temp;
}
#endif
