/*
    module  : abort.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef ABORT_C
#define ABORT_C

/**
abort  :  ->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void do_abort(void)
{
    COMPILE;
    exit(1);
}
#endif
