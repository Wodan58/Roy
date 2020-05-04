/*
    module  : ifstring.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef IFSTRING_C
#define IFSTRING_C

void ifstring(Stack *prog[])
{
    if (is_string(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_ifstring(Stack *prog[])
{
    fprintf(program, "if (is_string(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
ifstring  :  X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
void do_ifstring(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_ifstring(prog);
    else
#endif
    ifstring(prog);
}
#endif
