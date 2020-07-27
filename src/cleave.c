/*
    module  : cleave.c
    version : 1.16
    date    : 06/23/20
*/
#ifndef CLEAVE_C
#define CLEAVE_C

void cleave(Stack *prog[])
{
    intptr_t result[2];

    result[1] = stack[-1];	// copy X
    execute(prog[0]);
    result[0] = stack[-1];	// first result
    stack[-1] = result[1];	// restore X
    execute(prog[1]);
    result[1] = stack[-1];	// second result
    stack[-1] = result[0];
    do_push(result[1]);
}

#ifdef COMPILING
void put_cleave(Stack *prog[])
{
    fprintf(program, "{ intptr_t result[2]; result[1] = stack[-1];");
    execute(prog[0]);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    execute(prog[1]);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); }");
}
#endif

/**
cleave  :  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
void do_cleave(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_cleave(prog);
    else
#endif
    cleave(prog);
}
#endif
