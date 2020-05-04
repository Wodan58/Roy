/*
    module  : stdin.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef STDIN_C
#define STDIN_C

/**
stdin  :  ->  S
Pushes the standard input stream.
*/
void do_stdin(void)
{
    COMPILE;
    do_push((intptr_t)stdin);
}
#endif
