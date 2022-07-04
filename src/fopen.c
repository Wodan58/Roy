/*
    module  : fopen.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef FOPEN_C
#define FOPEN_C

/**
1900  fopen  :  DDA	P M  ->  S
The file system object with pathname P is opened with mode M (r, w, a, etc.)
and stream object S is pushed; if the open fails, file:NULL is pushed.
*/
void do_fopen(void)
{
    COMPILE;
    TWOPARAMS;
    STRINGS2;
    stack[-2] = MAKE_FILE(fopen(get_string(stack[-2]), get_string(stack[-1])));
    stack_pop();
}
#endif
