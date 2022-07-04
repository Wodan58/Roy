/*
    module  : binary.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef BINARY_C
#define BINARY_C

/**
2580  binary  :  DDDA 	X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
void do_binary(void)
{
    Stack *list;

    THREEPARAMS;
    ONEQUOTE;
    list = stack_copy();
    execute((Stack *)GET_AS_LIST(stack_pop()));
    vec_pop(list);
    vec_pop(list);
    vec_pop(list);
    CHECKSTACK;
    vec_push(list, stack_pop());
    stack_from_list(list);
}
#endif
