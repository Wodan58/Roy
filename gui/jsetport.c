/*
    module  : jsetport.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETPORT_C
#define JSETPORT_C

/**
jsetport  :  port  ->
Replace the default port by port. This can be useful if the default port is
used by an other application, or if you want to start several independent
kernels on one machine. This function must be called before calling jstart.
*/
void do_jsetport(void)
{
    int port;

    COMPILE;
    port = do_pop();
    j_setport(port);
}
#endif
