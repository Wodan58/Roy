/*
    module  : ferror.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef FERROR_C
#define FERROR_C

/**
ferror  :  S  ->  S B
B is the error status of stream S.
*/
void do_ferror(void)
{
    COMPILE;
    do_push(ferror((FILE *)stack[-1]));
}
#endif
