/*
    module  : nullary.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef NULLARY_C
#define NULLARY_C

/**
2500  nullary  :  DA	[P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
void do_nullary(void)
{
    Stack *list;

    ONEPARAM;
    ONEQUOTE;
    list = stack_copy();
    execute((Stack *)GET_AS_LIST(stack_pop()));
    vec_pop(list);
    CHECKSTACK;
    vec_push(list, stack_pop());
    stack_from_list(list);
}
#endif
