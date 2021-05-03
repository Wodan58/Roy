/*
    module  : jsleep.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSLEEP_C
#define JSLEEP_C

/**
jsleep  :  msec  ->
Suspends the execution for msec milliseconds.
*/
void do_jsleep(void)
{
    int msec;

    COMPILE;
    msec = do_pop();
    j_sleep(msec);
}
#endif
