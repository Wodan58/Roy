/*
    module  : unstack.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef UNSTACK_C
#define UNSTACK_C

/**
2010  unstack  :  DU	[X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
void do_unstack(void)
{
    SYNCING;
    ONEPARAM;
    LIST;
    stack_from_list(GET_AS_LIST(stack_pop()));
}
#endif
