/*
    module  : jbeep.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JBEEP_C
#define JBEEP_C

/**
jbeep  :  ->
Emits an audio beep.
*/
PRIVATE void do_jbeep(void)
{
    COMPILE;
    j_beep();
}
#endif
