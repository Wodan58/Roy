/*
    module  : echo.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef ECHO_C
#define ECHO_C

/**
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
void do_echo(void)
{
#ifdef COMPILING
    COMPILE;
    do_push(getechoflag());
#endif
}
#endif
