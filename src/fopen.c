/*
    module  : fopen.c
    version : 1.10
    date    : 07/23/20
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
fopen  :  P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
void do_fopen(void)
{
    COMPILE;
    stack[-2] = (intptr_t)fopen((char *)stack[-2], (char *)stack[-1]);
    do_pop();
}
#endif
