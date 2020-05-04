/*
    module  : stdout.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
stdout  :  ->  S
Pushes the standard output stream.
*/
void do_stdout(void)
{
    COMPILE;
    do_push((intptr_t)stdout);
}
#endif
