/*
    module  : step_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef STEP_SET_C
#define STEP_SET_C

void step_set(Stack *Prog)
{
    int i;
    intptr_t j, set;

    set = do_pop();
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    do_push(i);
	    execute(Prog);
	}
}

#ifdef COMPILING
void put_step_set(Stack *Prog)
{
    fprintf(program, "{ int i; intptr_t j, set = do_pop();");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) { do_push(i);");
    execute(Prog);
    fprintf(program, "} }");
}
#endif

/**
step_set  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void do_step_set(void)
{
    Stack *Prog;

    UNARY;
    Prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_step_set(Prog);
    else
#endif
    step_set(Prog);
}
#endif
