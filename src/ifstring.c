/*
    module  : ifstring.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFSTRING_C
#define IFSTRING_C

/**
2670  ifstring  :  DDDU 	X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
void ifstring(Stack *prog[])
{
    ONEPARAM;
    if (IS_USR_STRING(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_ifstring(Stack *prog[])
{
    fprintf(program, "if (IS_USR_STRING(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_ifstring(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_ifstring);
    ifstring(prog);
}
#endif
