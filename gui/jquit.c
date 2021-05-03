/*
    module  : jquit.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JQUIT_C
#define JQUIT_C

/**
jquit  :  ->
Cancels the connection to the JAPI Kernel.
*/
PRIVATE void do_jquit(void)
{
    COMPILE;
    j_quit();
}
#endif
