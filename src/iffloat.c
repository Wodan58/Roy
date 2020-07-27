/*
    module  : iffloat.c
    version : 1.8
    date    : 06/23/20
*/
#ifndef IFFLOAT_C
#define IFFLOAT_C

void iffloat(Stack *prog[])
{
    if (is_float(stack_top()))
	execute(prog[0]);
    else
	execute(prog[1]);
}

#ifdef COMPILING
void put_iffloat(Stack *prog[])
{
    fprintf(program, "if (is_float(stack_top())) {");
    execute(prog[0]);
    fprintf(program, "} else {");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
iffloat  :  X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
void do_iffloat(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_iffloat(prog);
    else
#endif
    iffloat(prog);
}
#endif
