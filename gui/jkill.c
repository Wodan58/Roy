/*
    module  : jkill.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JKILL_C
#define JKILL_C

/**
jkill  :  ->
Stop the JAPI kernel, or something.
*/
PRIVATE void do_jkill(void)
{
    COMPILE;
    j_kill();
}
#endif
