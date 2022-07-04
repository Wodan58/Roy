/*
    module  : branch.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef BRANCH_C
#define BRANCH_C

/**
2610  branch  :  DDDU 	B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
#ifdef COMPILING
void put_branch(Stack *prog[])
{
    fprintf(program, "{ if (GET_AS_BOOLEAN(stack_pop())) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "} }");
}
#endif

void do_branch(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_branch);
    ONEPARAM;
    execute(GET_AS_BOOLEAN(stack_pop()) ? prog[0] : prog[1]);
}
#endif
