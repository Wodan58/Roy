/*
    module  : srand.c
    version : 1.10
    date    : 03/01/21
*/
#ifndef SRAND_C
#define SRAND_C

void my_srand(unsigned num);

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
void do_srand(void)
{
    UNARY;
    my_srand(do_pop());
}
#endif
