/*
    module  : i.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef I_C
#define I_C

/**
i  :  [P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
void do_i(void)
{
    UNARY;
    execute((Stack *)do_pop());
}
#endif
