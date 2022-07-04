/*
    module  : stdin.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef STDIN_C
#define STDIN_C

/**
1170  stdin  :  A	->  S
Pushes the standard input stream.
*/
void do_stdin(void)
{
    COMPILE;
    do_push(MAKE_FILE(stdin));
}
#endif
