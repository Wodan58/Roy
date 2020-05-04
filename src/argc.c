/*
    module  : argc.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef ARGC_C
#define ARGC_C

/**
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
void do_argc(void)
{
    COMPILE;
    do_push(g_argc);
}
#endif
