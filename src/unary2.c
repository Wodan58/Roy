/*
    module  : unary2.c
    version : 1.17
    date    : 01/19/20
*/
#ifndef UNARY2_C
#define UNARY2_C

void unary2(Stack *prog)
{
    intptr_t result[2];

    result[1] = do_pop();	// X2
    execute(prog);
    result[0] = stack[-1];	// first result
    stack[-1] = result[1];	// restore X2
    execute(prog);
    result[1] = stack[-1];	// second result
    stack[-1] = result[0];
    do_push(result[1]);
}

#ifdef COMPILING
void put_unary2(Stack *prog)
{
    fprintf(program, "{ intptr_t result[2]; result[1] = do_pop();");
    execute(prog);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    execute(prog);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); }");
}
#endif

/**
unary2  :  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void do_unary2(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_unary2(prog);
    else
#endif
    unary2(prog);
}
#endif
