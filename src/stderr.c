/*
    module  : stderr.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef STDERR_C
#define STDERR_C

/**
1190  stderr  :  A	->  S
Pushes the standard error stream.
*/
void do_stderr(void)
{
    COMPILE;
    do_push(MAKE_FILE(stderr));
}
#endif
