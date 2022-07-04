/*
    module  : ifinteger.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFINTEGER_C
#define IFINTEGER_C

/**
2630  ifinteger  :  DDDU	X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
void ifinteger(Stack *prog[])
{
    ONEPARAM;
    if (IS_INTEGER(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_ifinteger(Stack *prog[])
{
    fprintf(program, "if (IS_INTEGER(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_ifinteger(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_ifinteger);
    ifinteger(prog);
}
#endif
