/*
    module  : unary3.c
    version : 1.16
    date    : 06/21/22
*/
#ifndef UNARY3_C
#define UNARY3_C

/**
2530  unary3  :  DDDDAAA	X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
void unary3(Stack *prog)
{
    value_t result[3];

    THREEPARAMS;
    result[2] = stack_pop();	// X3
    result[1] = stack_pop();	// X2
    execute_cond(prog, 0);
    CHECKSTACK;
    result[0] = stack[-1];	// first result
    stack[-1] = result[1];	// restore X2
    execute_cond(prog, 0);
    CHECKSTACK;
    result[1] = stack[-1];	// second result
    stack[-1] = result[2];	// restore X3
    execute(prog);
    CHECKSTACK;
    result[2] = stack[-1];	// third result
    stack[-1] = result[0];
    do_push(result[1]);
    do_push(result[2]);
}

#ifdef COMPILING
void put_unary3(Stack *prog)
{
    fprintf(program, "{ value_t result[3];");
    fprintf(program, "result[2] = stack_pop(); result[1] = stack_pop();");
    compile_cond(prog, 0);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    compile_cond(prog, 0);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[2];");
    compile(prog);
    fprintf(program, "result[2] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); do_push(result[2]); }");
}
#endif

void do_unary3(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_unary3);
    unary3(prog);
}
#endif
