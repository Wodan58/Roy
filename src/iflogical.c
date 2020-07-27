/*
    module  : iflogical.c
    version : 1.8
    date    : 06/23/20
*/
#ifndef IFLOGICAL_C
#define IFLOGICAL_C

void iflogical(Stack *prog[])
{
    if (is_boolean(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_iflogical(Stack *prog[])
{
    fprintf(program, "if (is_boolean(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
iflogical  :  X [T] [E]  ->  ...
If X is a logical or truth value, executes T else executes E.
*/
void do_iflogical(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_iflogical(prog);
    else
#endif
    iflogical(prog);
}
#endif
