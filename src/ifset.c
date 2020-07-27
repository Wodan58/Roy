/*
    module  : ifset.c
    version : 1.8
    date    : 06/23/20
*/
#ifndef IFSET_C
#define IFSET_C

void ifset(Stack *prog[])
{
    if (is_set(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_ifset(Stack *prog[])
{
    fprintf(program, "if (is_set(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
ifset  :  X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void do_ifset(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_ifset(prog);
    else
#endif
    ifset(prog);
}
#endif
