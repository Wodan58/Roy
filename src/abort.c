/*
    module  : abort.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef ABORT_C
#define ABORT_C

/**
3150  abort  :  N	->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void do_abort(void)
{
    COMPILE;
    exit(0);
}
#endif
