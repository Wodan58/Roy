/*
    module  : iffile.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFFILE_C
#define IFFILE_C

/**
2700  iffile  :  DDDU 	X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
void iffile(Stack *prog[])
{
    ONEPARAM;
    if (IS_FILE(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_iffile(Stack *prog[])
{
    fprintf(program, "if (IS_FILE(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_iffile(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_iffile);
    iffile(prog);
}
#endif
