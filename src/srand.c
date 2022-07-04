/*
    module  : srand.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef SRAND_C
#define SRAND_C

/**
1780  srand  :  D	I  ->
Sets the random integer seed to integer I.
*/
void do_srand(void)
{
    COMPILE;
    ONEPARAM;
    srand(GET_AS_INTEGER(stack_pop()));
}
#endif
