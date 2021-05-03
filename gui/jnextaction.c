/*
    module  : jnextaction.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JNEXTACTION_C
#define JNEXTACTION_C

/**
jnextaction  :  ->  event
Waits for the next event.
*/
void do_jnextaction(void)
{
    COMPILE;
    do_push(j_nextaction());
}
#endif
