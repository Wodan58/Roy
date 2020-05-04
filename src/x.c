/*
    module  : x.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef X_C
#define X_C

/**
x  :  [P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
void do_x(void)
{
    UNARY;
    execute((Stack *)stack[-1]);
}
#endif
