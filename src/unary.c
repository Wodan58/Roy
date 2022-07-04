/*
    module  : unary.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef UNARY_C
#define UNARY_C

/**
2510  unary  :  DDA	X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
void do_unary(void)
{
    Stack *list;

    TWOPARAMS;
    ONEQUOTE;
    list = stack_copy();
    execute((Stack *)GET_AS_LIST(stack_pop()));
    vec_pop(list);
    vec_pop(list);
    CHECKSTACK;
    vec_push(list, stack_pop());
    stack_from_list(list);
}
#endif
