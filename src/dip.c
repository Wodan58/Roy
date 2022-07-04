/*
    module  : dip.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef DIP_C
#define DIP_C

/**
2450  dip  :  DDAU	X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
void dip(Stack *prog)
{
    value_t temp;

    ONEPARAM;
    temp = stack_pop();
    execute(prog);
    do_push(temp);
}

#ifdef COMPILING
void put_dip(Stack *prog)
{
    fprintf(program, "{ value_t temp;");
    fprintf(program, "temp = stack_pop();");
    compile(prog);
    fprintf(program, "do_push(temp); }");
}
#endif

void do_dip(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_dip);
    dip(prog);
}
#endif
