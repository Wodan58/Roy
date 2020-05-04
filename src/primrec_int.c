/*
    module  : primrec_int.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef PRIMREC_INT_C
#define PRIMREC_INT_C

void primrec_int(Stack *prog[])
{
    intptr_t i, num;

    num = do_pop();
    for (i = num; i; i--)
	do_push(i);
    execute(prog[0]);
    while (num--)
	execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_int(Stack *prog[])
{
    fprintf(program, "{ intptr_t i, num = do_pop();");
    fprintf(program, "for (i = num; i; i--) do_push(i);");
    execute(prog[0]);
    fprintf(program, "while (num--) {");
    execute(prog[1]);
    fprintf(program, "} }");
}
#endif

/**
primrec_int  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void do_primrec_int(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_primrec_int(prog);
    else
#endif
    primrec_int(prog);
}
#endif
