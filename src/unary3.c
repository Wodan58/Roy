/*
    module  : unary3.c
    version : 1.14
    date    : 01/19/20
*/
#ifndef UNARY3_C
#define UNARY3_C

void unary3(Stack *prog)
{
    intptr_t result[3];

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
    stack[-1] = result[0];
    do_push(result[1]);
    do_push(result[2]);
}

#ifdef COMPILING
void put_unary3(Stack *prog)
{
    fprintf(program, "{ intptr_t result[3]; result[2] = do_pop();");
    fprintf(program, "result[1] = do_pop();");
    execute(prog);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    execute(prog);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[2];");
    execute(prog);
    fprintf(program, "result[2] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); do_push(result[2]); }");
}
#endif

/**
unary3  :  X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
void do_unary3(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_unary3(prog);
    else
#endif
    unary3(prog);
}
#endif
