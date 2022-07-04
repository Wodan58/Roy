/*
    module  : unary2.c
    version : 1.19
    date    : 06/21/22
*/
#ifndef UNARY2_C
#define UNARY2_C

/**
2520  unary2  :  DDDAA	X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void unary2(Stack *prog)
{
    value_t result[2];

    TWOPARAMS;
    result[1] = stack_pop();	// X2
    execute_cond(prog, 1);
    CHECKSTACK;
    result[0] = stack[-1];	// first result
    stack[-1] = result[1];	// restore X2
    execute(prog);
    CHECKSTACK;
    result[1] = stack[-1];	// second result
    stack[-1] = result[0];
    do_push(result[1]);
}

#ifdef COMPILING
void put_unary2(Stack *prog)
{
    fprintf(program, "{ value_t result[2];");
    fprintf(program, "result[1] = stack_pop();");
    compile_cond(prog, 1);
    fprintf(program, "result[0] = stack[-1]; stack[-1] = result[1];");
    compile(prog);
    fprintf(program, "result[1] = stack[-1]; stack[-1] = result[0];");
    fprintf(program, "do_push(result[1]); }");
}
#endif

void do_unary2(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_unary2);
    unary2(prog);
}
#endif
