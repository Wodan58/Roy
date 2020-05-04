/*
    module  : iflist.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef IFLIST_C
#define IFLIST_C

void iflist(Stack *prog[])
{
    if (is_list(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_iflist(Stack *prog[])
{
    fprintf(program, "if (is_list(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
iflist  :  X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
void do_iflist(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_iflist(prog);
    else
#endif
    iflist(prog);
}
#endif
