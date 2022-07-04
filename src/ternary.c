/*
    module  : ternary.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef TERNARY_C
#define TERNARY_C

/**
2590  ternary  :  DDDDA 	X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
void do_ternary(void)
{
    Stack *list;

    FOURPARAMS;
    ONEQUOTE;
    list = stack_copy();
    execute((Stack *)GET_AS_LIST(stack_pop()));
    vec_pop(list);
    vec_pop(list);
    vec_pop(list);
    vec_pop(list);
    CHECKSTACK;
    vec_push(list, stack_pop());
    stack_from_list(list);
}
#endif
