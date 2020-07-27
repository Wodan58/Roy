/*
    module  : step_str.c
    version : 1.5
    date    : 06/23/20
*/
#ifndef STEP_STR_C
#define STEP_STR_C

void step_str(Stack *Prog)
{
    int i;
    char *str;

    if ((str = (char *)do_pop()) == 0)
	return;
    for (i = 0; str[i]; i++) {
	do_push(str[i]);
	execute(Prog);
    }
}

#ifdef COMPILING
void put_step_str(Stack *Prog)
{
    fprintf(program, "{ int i; char *str;");
    fprintf(program, "if ((str = (char *)do_pop()) == 0) return;");
    fprintf(program, "for (i = 0; str[i]; i++) { do_push(str[i]);");
    execute(Prog);
    fprintf(program, "} }");
}
#endif

/**
step_str  :  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void do_step_str(void)
{
    Stack *Prog;

    UNARY;
    Prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_step_str(Prog);
    else
#endif
    step_str(Prog);
}
#endif
