/*
    module  : time.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef TIME_C
#define TIME_C

/**
1140  time  :  A	->  I
Pushes the current time (in seconds since the Epoch).
*/
void do_time(void)
{
    COMPILE;
    do_push(MAKE_INTEGER(time(0)));
}
#endif
