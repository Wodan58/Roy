/*
    module  : system.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
system  :  "command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
void do_system(void)
{
    COMPILE;
    system((char *)do_pop());
}
#endif
