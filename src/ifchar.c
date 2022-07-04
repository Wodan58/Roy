/*
    module  : ifchar.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
2640  ifchar  :  DDDU 	X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar(Stack *prog[])
{
    ONEPARAM;
    if (IS_CHAR(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_ifchar(Stack *prog[])
{
    fprintf(program, "if (IS_CHAR(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_ifchar(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_ifchar);
    ifchar(prog);
}
#endif
