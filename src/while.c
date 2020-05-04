/*
    module  : while.c
    version : 1.16
    date    : 01/19/20
*/
#ifndef WHILE_C
#define WHILE_C

void my_while(Stack *prog[])
{
    for (;;) {
	execute(prog[0]);
	if (!do_pop())
	    break;
	execute(prog[1]);
    }
}

#ifdef COMPILING
void put_while(Stack *prog[])
{
    fprintf(program, "for (;;) {");
    execute(prog[0]);
    fprintf(program, "if (!do_pop()) break;");
    execute(prog[1]);
    fprintf(program, "}");
}
#endif

/**
while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
void do_while(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_while(prog);
    else
#endif
    my_while(prog);
}
#endif
