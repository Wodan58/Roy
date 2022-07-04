/*
    module  : ifset.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFSET_C
#define IFSET_C

/**
2660  ifset  :  DDDU	X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void ifset(Stack *prog[])
{
    ONEPARAM;
    if (IS_SET(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_ifset(Stack *prog[])
{
    fprintf(program, "if (IS_SET(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_ifset(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_ifset);
    ifset(prog);
}
#endif
