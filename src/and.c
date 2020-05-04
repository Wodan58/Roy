/*
    module  : and.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef AND_C
#define AND_C

/**
and  :  X Y  ->  Z
Z is the intersection of sets X and Y, logical conjunction for truth values.
*/
void do_and(void)
{
    BINARY;
    stack[-2] &= stack[-1];
    do_zap();
}
#endif
