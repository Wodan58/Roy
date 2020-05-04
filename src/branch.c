/*
    module  : branch.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef BRANCH_C
#define BRANCH_C

#ifdef COMPILING
void put_branch(Stack *prog[])
{
    fprintf(program, "{ if (do_pop()) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "} }");
}
#endif

/**
branch  :  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
void do_branch(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_branch(prog);
    else
#endif
    execute(do_pop() ? prog[0] : prog[1]);
}
#endif
