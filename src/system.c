/*
    module  : system.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef SYSTEM_C
#define SYSTEM_C

/**
3040  system  :  D	"command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
void do_system(void)
{
    COMPILE;
    STRING;
    system(get_string(stack_pop()));
}
#endif
