/*
    module  : times.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef TIMES_C
#define TIMES_C

/**
2820  times  :  DDU	N [P]  ->  ...
N times executes P.
*/
void exe_times(Stack *prog)
{
    int num;

    INTEGER;
    num = GET_AS_INTEGER(stack_pop());
    while (num--)
        execute(prog);
}

#ifdef COMPILING
void put_times(Stack *prog)
{
    fprintf(program, "{ int num;");
    fprintf(program, "num = GET_AS_INTEGER(stack_pop());");
    fprintf(program, "while (num--) {");
    compile(prog);
    fprintf(program, "} }");
}
#endif

void do_times(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_times);
    exe_times(prog);
}
#endif
