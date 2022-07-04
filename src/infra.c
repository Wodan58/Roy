/*
    module  : infra.c
    version : 1.17
    date    : 06/21/22
*/
#ifndef INFRA_C
#define INFRA_C

/**
2830  infra  :  DDA	L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
void infra(Stack *prog, Stack *list)
{
    Stack *save;

    save = stack_copy();
    stack_from_list(list);
    execute(prog);
    list = stack_copy();
    stack_from_list(save);
    do_push(MAKE_LIST(list));
}

#ifdef COMPILING
void put_infra(Stack *prog)
{
    fprintf(program, "{ Stack *list, *save;");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack_pop());");
    fprintf(program, "save = stack_copy();");
    fprintf(program, "stack_from_list(list);");
    compile(prog);
    fprintf(program, "list = stack_copy();");
    fprintf(program, "stack_from_list(save);");
    fprintf(program, "do_push(MAKE_LIST(list)); }");
}
#endif

void do_infra(void)
{
    Stack *prog, *list;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_infra);
    ONEPARAM;
    LIST;
    list = (Stack *)GET_AS_LIST(stack_pop());
    infra(prog, list);
}
#endif
