/*
    module  : stderr.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef STDERR_C
#define STDERR_C

/**
stderr  :  ->  S
Pushes the standard error stream.
*/
void do_stderr(void)
{
    COMPILE;
    do_push((intptr_t)stderr);
}
#endif
