/*
    module  : ifte.c
    version : 1.20
    date    : 06/23/20
*/
#ifndef IFTE_C
#define IFTE_C

void ifte(Stack *prog[])
{
    execute(prog[0]);
    execute(do_pop() ? prog[1] : prog[2]);
}

#ifdef COMPILING
void put_ifte(Stack *prog[])
{
    execute(prog[0]);
    fprintf(program, "if (do_pop()) {");
    execute(prog[1]);
    fprintf(program, "} else {");
    execute(prog[2]);
    fprintf(program, "}");
}
#endif

/**
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
void do_ifte(void)
{
    Stack *prog[3];

    TERNARY;
    prog[2] = (Stack *)do_pop();
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))	// depends on arity of condition
	put_ifte(prog);
    else
#endif
    ifte(prog);
}
#endif
