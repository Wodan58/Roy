/*
    module  : iffloat.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFFLOAT_C
#define IFFLOAT_C

/**
2690  iffloat  :  DDDU 	X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
void iffloat(Stack *prog[])
{
    ONEPARAM;
    if (IS_DOUBLE(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_iffloat(Stack *prog[])
{
    fprintf(program, "if (IS_DOUBLE(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_iffloat(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_iffloat);
    iffloat(prog);
}
#endif
