/*
    module  : iffile.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef IFFILE_C
#define IFFILE_C

void iffile(Stack *prog[])
{
    if (is_file(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_iffile(Stack *prog[])
{
    fprintf(program, "if (is_file(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
iffile  :  X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
void do_iffile(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_iffile(prog);
    else
#endif
    iffile(prog);
}
#endif
