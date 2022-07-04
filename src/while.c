/*
    module  : while.c
    version : 1.18
    date    : 06/21/22
*/
#ifndef WHILE_C
#define WHILE_C

/**
2720  while  :  DDU	[B] [D]  ->  ...
While executing B yields true executes D.
*/
void exe_while(Stack *prog[])
{
    for (;;) {
        execute_cond(prog[0], 0);
        CHECKSTACK;
        if (!GET_AS_BOOLEAN(stack_pop()))
            break;
        execute(prog[1]);
    }
}

#ifdef COMPILING
void put_while(Stack *prog[])
{
    fprintf(program, "for (;;) {");
    compile_cond(prog[0], 0);
    fprintf(program, "if (!GET_AS_BOOLEAN(stack_pop())) break;");
    compile(prog[1]);
    fprintf(program, "}");
}
#endif

void do_while(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_while);
    exe_while(prog);
}
#endif
