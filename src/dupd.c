/*
    module  : dupd.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef DUPD_C
#define DUPD_C

/**
1270  dupd  :  DDAAA	Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
void do_dupd(void)
{
    TWOPARAMS;
    do_push(stack[-1]);
    stack[-2] = stack[-3];
}
#endif
