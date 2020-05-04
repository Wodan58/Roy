/*
    module  : ftell.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef FTELL_C
#define FTELL_C

/**
ftell  :  S  ->  S I
I is the current position of stream S.
*/
void do_ftell(void)
{
    COMPILE;
    do_push(ftell((FILE *)stack[-1]));
}
#endif
