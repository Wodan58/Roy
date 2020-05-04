/*
    module  : primrec_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef PRIMREC_SET_C
#define PRIMREC_SET_C

void primrec_set(Stack *prog[])
{
    int i, num;
    intptr_t j, set;

    set = do_pop();
    for (num = i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    do_push(i);
	    num++;
	}
    execute(prog[0]);
    while (num--)
	execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_set(Stack *prog[])
{
    fprintf(program, "{ int i, num; intptr_t j, set = do_pop();");
    fprintf(program, "for (num = i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) { do_push(i); num++; }");
    execute(prog[0]);
    fprintf(program, "while (num--) {");
    execute(prog[1]);
    fprintf(program, "} }");
}
#endif

/**
primrec_set  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void do_primrec_set(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_primrec_set(prog);
    else
#endif
    primrec_set(prog);
}
#endif
