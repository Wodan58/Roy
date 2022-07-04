/*
    module  : i.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef I_C
#define I_C

/**
2430  i  :  DU	[P]  ->  ...
Executes P. So, [P] i  ==  P.
*/
void do_i(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    execute(prog);
}
#endif
