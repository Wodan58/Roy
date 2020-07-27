/*
    module  : frename.c
    version : 1.10
    date    : 07/23/20
*/
#ifndef FRENAME_C
#define FRENAME_C

/**
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
void do_frename(void)
{
    COMPILE;
    stack[-2] = !rename((char *)stack[-2], (char *)stack[-1]);
    do_pop();
}
#endif
