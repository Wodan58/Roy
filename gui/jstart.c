/*
    module  : jstart.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSTART_C
#define JSTART_C

/**
jstart  :  ->  status
Get in touch with a running JAPI kernel or start a new one.
*/
PRIVATE void do_jstart(void)
{
    COMPILE;
    do_push(j_start());
}
#endif
