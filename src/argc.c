/*
    module  : argc.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef ARGC_C
#define ARGC_C

/**
3070  argc  :  A	->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
void do_argc(void)
{
    COMPILE;
    do_push(MAKE_INTEGER(g_argc));
}
#endif
