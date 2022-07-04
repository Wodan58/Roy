/*
    module  : unary4.c
    version : 1.16
    date    : 06/21/22
*/
#ifndef UNARY4_C
#define UNARY4_C

/**
2540  unary4  :  DDDDDAAAA	X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
void unary4(Stack *prog)
{
    value_t result[4];

    FOURPARAMS;
    result[3] = stack_pop();	// X4
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
    execute_cond(prog, 0);
    CHECKSTACK;
    result[2] = stack[-1];	// third result
    stack[-1] = result[3];	// restore X4
    execute(prog);
    CHECKSTACK;
    result[3] = stack[-1];	// fourth result
    stack[-1] = result[0];
    do_push(result[1]);
    do_push(result[2]);
    do_push(result[3]);
}

#ifdef COMPILING
void put_unary4(Stack *prog)
{
    fprintf(program, "{ value_t result[4];");
    fprintf(program, "result[3] = stack_pop();");
    fprintf(program, "result[2] = stack_pop(); result[1] = stack_pop();");
    compile_cond(prog, 0);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    compile_cond(prog, 0);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[2];");
    compile_cond(prog, 0);
    fprintf(program, "result[2] = stack[-1]; stack[-1] = result[3];");
    compile(prog);
    fprintf(program, "result[3] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); do_push(result[2]);");
    fprintf(program, "do_push(result[3]); }");
}
#endif

void do_unary4(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_unary4);
    unary4(prog);
}
#endif
