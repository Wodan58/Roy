/*
    module  : times.c
    version : 1.12
    date    : 06/23/20
*/
#ifndef TIMES_C
#define TIMES_C

void times(Stack *Prog)
{
    intptr_t num;

    num = do_pop();
    while (num--)
	execute(Prog);
}

#ifdef COMPILING
void put_times(Stack *Prog)
{
    fprintf(program, "{ intptr_t num = do_pop();");
    fprintf(program, "while (num--) {");
    execute(Prog);
    fprintf(program, "} }");
}
#endif

/**
times  :  N [P]  ->  ...
N times executes P.
*/
void do_times(void)
{
    Stack *Prog;

    UNARY;
    Prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_times(Prog);
    else
#endif
    times(Prog);
}
#endif
