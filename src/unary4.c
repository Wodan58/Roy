/*
    module  : unary4.c
    version : 1.15
    date    : 06/23/20
*/
#ifndef UNARY4_C
#define UNARY4_C

void unary4(Stack *prog)
{
    intptr_t result[4];

    result[3] = do_pop();	// X4
    result[2] = do_pop();	// X3
    result[1] = do_pop();	// X2
    execute(prog);
    result[0] = stack[-1];	// first result
    stack[-1] = result[1];	// restore X2
    execute(prog);
    result[1] = stack[-1];	// second result
    stack[-1] = result[2];	// restore X3
    execute(prog);
    result[2] = stack[-1];	// third result
    stack[-1] = result[3];	// restore X4
    execute(prog);
    result[3] = stack[-1];	// fourth result
    stack[-1] = result[0];
    do_push(result[1]);
    do_push(result[2]);
    do_push(result[3]);
}

#ifdef COMPILING
void put_unary4(Stack *prog)
{
    fprintf(program, "{ intptr_t result[4]; result[3] = do_pop();");
    fprintf(program, "result[2] = do_pop(); result[1] = do_pop();");
    execute(prog);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    execute(prog);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[2];");
    execute(prog);
    fprintf(program, "result[2] = stack[-1]; stack[-1] = result[3];");
    execute(prog);
    fprintf(program, "result[3] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); do_push(result[2]);");
    fprintf(program, "do_push(result[3]); }");
}
#endif

/**
unary4  :  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
void do_unary4(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_unary4(prog);
    else
#endif
    unary4(prog);
}
#endif
