/*
    module  : ifte.c
    version : 1.21
    date    : 06/21/22
*/
#ifndef IFTE_C
#define IFTE_C

/**
2620  ifte  :  DDDU	[B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
void ifte(Stack *prog[3])
{
    execute_cond(prog[0], 0);
    CHECKSTACK;
    execute(GET_AS_BOOLEAN(stack_pop()) ? prog[1] : prog[2]);
}

#ifdef COMPILING
void put_ifte(Stack *prog[3])
{
    compile_cond(prog[0], 0);
    fprintf(program, "if (GET_AS_BOOLEAN(stack_pop())) {");
    compile(prog[1]);
    fprintf(program, "} else {");
    compile(prog[2]);
    fprintf(program, "}");
}
#endif

void do_ifte(void)
{
    Stack *prog[3];

    THREEPARAMS;
    THREEQUOTES;
    prog[2] = (Stack *)GET_AS_LIST(stack_pop());
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_ifte);
    ifte(prog);
}
#endif
