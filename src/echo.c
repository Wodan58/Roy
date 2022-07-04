/*
    module  : echo.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef ECHO_C
#define ECHO_C

/**
1120  echo  :  A	->  I
Pushes value of echo flag, I = 0..3.
*/
void do_echo(void)
{
#ifdef COMPILING
    COMPILE;
    do_push(MAKE_INTEGER(getechoflag()));
#endif
}
#endif
