/*
    module  : time.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef TIME_C
#define TIME_C

/**
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
void do_time(void)
{
    COMPILE;
    do_push(time(0));
}
#endif
