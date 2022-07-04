/*
    module  : clock.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
1130  clock  :  A	->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
void do_clock(void)
{
    COMPILE;
    do_push(MAKE_INTEGER(clock() - startclock));
}
#endif
