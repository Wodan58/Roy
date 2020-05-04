/*
    module  : undeferror.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
void do_undeferror(void)
{
    COMPILE;
    do_push(undeferror);
}
#endif
