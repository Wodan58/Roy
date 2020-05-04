/*
    module  : fget.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef FGET_C
#define FGET_C

/**
fget  :  S  ->  S F
Reads a factor from stream S and pushes it onto stack.
*/
void do_fget(void)
{
    COMPILE;
    redirect((FILE *)stack[-1]);
    readfactor(yylex());
}
#endif
