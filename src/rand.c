/*
    module  : rand.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef RAND_C
#define RAND_C

/**
1150  rand  :  A	->  I
I is a random integer.
*/
void do_rand(void)
{
    COMPILE;
    do_push(MAKE_INTEGER(rand()));
}
#endif
