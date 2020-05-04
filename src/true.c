/*
    module  : true.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef TRUE_C
#define TRUE_C

/**
true  :  ->  true
Pushes the value true.
*/
void do_true(void)
{
    COMPILE;
    do_push(1);
}
#endif
