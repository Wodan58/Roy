/*
    module  : ifchar.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef IFCHAR_C
#define IFCHAR_C

void ifchar(Stack *prog[])
{
    if (is_char(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_ifchar(Stack *prog[])
{
    fprintf(program, "if (is_char(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
ifchar  :  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void do_ifchar(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_ifchar(prog);
    else
#endif
    ifchar(prog);
}
#endif
