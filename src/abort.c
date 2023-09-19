/*
    module  : abort.c
    version : 1.9
    date    : 09/19/23
*/
#ifndef ABORT_C
#define ABORT_C

/**
OK 3120  abort  :  N	->
Aborts execution of current Joy program, returns to Joy main cycle.
*/
void abort_(pEnv env)
{
    abortexecution_(MY_ABORT);
    /* nothing */
}
#endif
