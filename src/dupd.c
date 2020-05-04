/*
    module  : dupd.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef DUPD_C
#define DUPD_C

/**
dupd  :  Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
void do_dupd(void)
{
    BINARY;
    do_push(stack[-1]);
    stack[-2] = stack[-3];
}
#endif
