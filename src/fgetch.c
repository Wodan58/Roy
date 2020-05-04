/*
    module  : fgetch.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
fgetch  :  S  ->  S C
C is the next available character from stream S.
*/
void do_fgetch(void)
{
    COMPILE;
    do_push(getc((FILE *)stack[-1]));
}
#endif
