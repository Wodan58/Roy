/*
    module  : srand.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef SRAND_C
#define SRAND_C

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
void do_srand(void)
{
    UNARY;
    srand(do_pop());
}
#endif
