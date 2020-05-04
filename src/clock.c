/*
    module  : clock.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
void do_clock(void)
{
    COMPILE;
    do_push(clock() - startclock);
}
#endif
