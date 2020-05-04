/*
    module  : infra.c
    version : 1.15
    date    : 01/19/20
*/
#ifndef INFRA_C
#define INFRA_C

#ifdef STACK_X
#undef STACK_X
#undef STACK_C
#endif
#ifdef UNSTACK_X
#undef UNSTACK_X
#undef UNSTACK_C
#endif

#include "stack.c"
#include "unstack.c"

void infra(Stack *prog)
{
    Stack *save, *list;

    list = (Stack *)do_pop();
    save = stk2lst();
    lst2stk(list);
    execute(prog);
    list = stk2lst();
    lst2stk(save);
    do_push((intptr_t)list);
}

#ifdef COMPILING
void put_infra(Stack *prog)
{
    fprintf(program, "{ Stack *save, *list = (Stack *)do_pop();");
    fprintf(program, "save = stk2lst();");
    fprintf(program, "lst2stk(list);");
    execute(prog);
    fprintf(program, "list = stk2lst();");
    fprintf(program, "lst2stk(save);");
    fprintf(program, "do_push((node_t)list); }");
}
#endif

/**
infra  :  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
void do_infra(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_infra(prog);
    else
#endif
    infra(prog);
}
#endif
