/*
    module  : iflogical.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFLOGICAL_C
#define IFLOGICAL_C

/**
2650  iflogical  :  DDDU	X [T] [E]  ->  ...
If X is a logical or truth value, executes T else executes E.
*/
void iflogical(Stack *prog[])
{
    ONEPARAM;
    if (IS_BOOLEAN(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_iflogical(Stack *prog[])
{
    fprintf(program, "if (IS_BOOLEAN(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_iflogical(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_iflogical);
    iflogical(prog);
}
#endif
