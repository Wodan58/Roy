/*
    module  : fremove.c
    version : 1.10
    date    : 07/23/20
*/
#ifndef FREMOVE_C
#define FREMOVE_C

/**
fremove  :  P  ->  B
The file system object with pathname P is removed from the file system.
B is a boolean indicating success or failure.
*/
void do_fremove(void)
{
    COMPILE;
    stack[-2] = !remove((char *)stack[-1]);
    do_pop();
}
#endif
