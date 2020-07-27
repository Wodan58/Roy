/*
    module  : step.c
    version : 1.13
    date    : 06/23/20
*/
#ifndef STEP_C
#define STEP_C

void step(Stack *Prog)
{
    int i;
    Stack *Quot;

    Quot = (Stack *)do_pop();
    for (i = vec_size(Quot) - 1; i >= 0; i--) {
	do_push(vec_at(Quot, i));
	execute(Prog);
    }
}

#ifdef COMPILING
void put_step(Stack *Prog)
{
    fprintf(program, "{ int i; Stack *Quot = (Stack *)do_pop();");
    fprintf(program, "for (i = vec_size(Quot) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(Quot, i));");
    execute(Prog);
    fprintf(program, "} }");
}
#endif

/**
step  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void do_step(void)
{
    Stack *Prog;

    UNARY;
    Prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_step(Prog);
    else
#endif
    step(Prog);
}
#endif
