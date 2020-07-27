/*
    module  : primrec.c
    version : 1.13
    date    : 06/23/20
*/
#ifndef PRIMREC_C
#define PRIMREC_C

void primrec(Stack *prog[])
{
    int i, num;
    Stack *list;

    list = (Stack *)do_pop();
    for (num = vec_size(list), i = num - 1; i >= 0; i--)
	do_push(vec_at(list, i));
    execute(prog[0]);
    while (num--)
	execute(prog[1]);
}

#ifdef COMPILING
void put_primrec(Stack *prog[])
{
    fprintf(program, "{ int i, num; Stack *list = (Stack *)do_pop();");
    fprintf(program, "for (num = vec_size(list), i = num - 1; i >= 0; i--)");
    fprintf(program, "do_push(vec_at(list, i));");
    execute(prog[0]);
    fprintf(program, "while (num--) {");
    execute(prog[1]);
    fprintf(program, "} }");
}
#endif

/**
primrec  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void do_primrec(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_primrec(prog);
    else
#endif
    primrec(prog);
}
#endif
