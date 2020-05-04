/*
    module  : fflush.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
void do_fflush(void)
{
    COMPILE;
    fflush((FILE *)stack[-1]);
}
#endif
