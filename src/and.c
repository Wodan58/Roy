/*
    module  : and.c
    version : 1.9
    date    : 07/23/20
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
    do_pop();
}
#endif
