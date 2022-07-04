/*
    module  : undeferror.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
1100  undeferror  :  A		->  I
Pushes current value of undefined-is-error flag.
*/
void do_undeferror(void)
{
    COMPILE;
    do_push(MAKE_INTEGER(undeferror));
}
#endif
