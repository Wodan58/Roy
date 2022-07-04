/*
    module  : cleave.c
    version : 1.17
    date    : 06/21/22
*/
#ifndef CLEAVE_C
#define CLEAVE_C

/**
2600  cleave  :  DDDAA	X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
void cleave(Stack *prog[])
{
    value_t result[2];

    ONEPARAM;
    result[1] = stack[-1]; 	// copy X
    execute_cond(prog[0], 1);	// P[1]
    result[0] = stack[-1];	// first result
    stack[-1] = result[1];	// restore X
    execute(prog[1]);		// P[2]
    result[1] = stack[-1];	// second result
    stack[-1] = result[0];	// R1
    do_push(result[1]);		// R2
}

#ifdef COMPILING
void put_cleave(Stack *prog[])
{
    Stack *list;

    fprintf(program, "{ value_t result[2];");
    fprintf(program, "result[1] = stack[-1];"); // copy X
    compile_cond(prog[0], 1);                   // P[1]
    fprintf(program, "result[0] = stack[-1];"); // first result
    fprintf(program, "stack[-1] = result[1];"); // restore X
    compile(prog[1]);                           // P[2]
    fprintf(program, "result[1] = stack[-1];"); // second result
    fprintf(program, "stack[-1] = result[0];"); // R1
    fprintf(program, "do_push(result[1]); }");  // R2
}
#endif

void do_cleave(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_cleave);
    cleave(prog);
}
#endif
