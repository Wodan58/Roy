/*
    module  : primrec_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef PRIMREC_STR_C
#define PRIMREC_STR_C

void primrec_str(Stack *prog[])
{
    int num;
    char *str;

    str = (char *)do_pop();
    for (num = strlen(str); *str; str++)
	do_push(*str);
    execute(prog[0]);
    while (num--)
	execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_str(Stack *prog[])
{
    fprintf(program, "{ int num; char *str = (char *)do_pop();");
    fprintf(program, "for (num = strlen(str); *str; str++) do_push(*str);");
    execute(prog[0]);
    fprintf(program, "while (num--) {");
    execute(prog[1]);
    fprintf(program, "} }");
}
#endif

/**
primrec_str  :  X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void do_primrec_str(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_primrec_str(prog);
    else
#endif
    primrec_str(prog);
}
#endif
