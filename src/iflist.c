/*
    module  : iflist.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef IFLIST_C
#define IFLIST_C

/**
2680  iflist  :  DDDU 	X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
void iflist(Stack *prog[])
{
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        execute(prog[0]);
    else
        execute(prog[1]);
}

#ifdef COMPILING
void put_iflist(Stack *prog[])
{
    fprintf(program, "if (IS_LIST(stack[-1])) {");
    compile(prog[0]);
    fprintf(program, "} else {");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_iflist(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_iflist);
    iflist(prog);
}
#endif
