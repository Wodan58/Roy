/*
    module  : stdout.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
1180  stdout  :  A	->  S
Pushes the standard output stream.
*/
void do_stdout(void)
{
    COMPILE;
    do_push(MAKE_FILE(stdout));
}
#endif
