/*
    module  : rand.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef RAND_C
#define RAND_C

/**
rand  :  ->  I
I is a random integer.
*/
void do_rand(void)
{
    COMPILE;
    do_push(rand());
}
#endif
