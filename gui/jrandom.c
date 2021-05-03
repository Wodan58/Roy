/*
    module  : jrandom.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JRANDOM_C
#define JRANDOM_C

/**
jrandom  :  ->  number
Generates a pseudo randon number. The returned value will be in the range 0 to
2147483647 (2 ^ 31 - 1).
*/
void do_jrandom(void)
{
    COMPILE;
    do_push(j_random());
}
#endif
