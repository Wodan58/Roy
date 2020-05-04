/*
    module  : ifinteger.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef IFINTEGER_C
#define IFINTEGER_C

void ifinteger(Stack *prog[])
{
    if (is_integer(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_ifinteger(Stack *prog[])
{
    fprintf(program, "if (is_integer(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
ifinteger  :  X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
void do_ifinteger(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_ifinteger(prog);
    else
#endif
    ifinteger(prog);
}
#endif
