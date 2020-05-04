/*
    module  : feof.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef FEOF_C
#define FEOF_C

/**
feof  :  S  ->  S B
B is the end-of-file status of stream S.
*/
void do_feof(void)
{
    COMPILE;
    do_push(feof((FILE *)stack[-1]));
}
#endif
