/*
    module  : x.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef X_C
#define X_C

/**
2440  x  :  U 	[P] x  ->  ...
Executes P without popping [P]. So, [P] x  ==  [P] P.
*/
void do_x(void)
{
    ONEPARAM;
    ONEQUOTE;
    execute((Stack *)GET_AS_LIST(stack[-1]));
}
#endif
