/*
    module  : rand.c
    version : 1.10
    date    : 03/01/21
*/
#ifndef RAND_C
#define RAND_C

int my_rand(void);

/**
rand  :  ->  I
I is a random integer.
*/
void do_rand(void)
{
    COMPILE;
    do_push(my_rand());
}
#endif
