/*
    module  : frename.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
1940  frename  :  DDA 	P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
void do_frename(void)
{
    COMPILE;
    TWOPARAMS;
    STRINGS2;
    stack[-2]
        = MAKE_BOOLEAN(!rename(get_string(stack[-2]), get_string(stack[-1])));
    stack_pop();
}
#endif
