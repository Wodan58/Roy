/*
    module  : linrec.c
    version : 1.18
    date    : 03/01/21
*/
#ifndef LINREC_C
#define LINREC_C

void linrec(Stack *prog[])
{
    execute(prog[0]);
    if (do_pop())
	execute(prog[1]);
    else {
	execute(prog[2]);
	linrec(prog);
	execute(prog[3]);
    }
}

#ifdef COMPILING
void put_linrec(Stack *prog[])
{
    static int ident;
    int ch;
    FILE *old;

    printf("void linrec_%d(void);", ++ident);
    fprintf(old = program, "linrec_%d();", ident);
    if ((program = my_tmpfile()) == 0)
	yyerror("linrec");
    fprintf(program, "void linrec_%d(void) {", ident);
    execute(prog[0]);
    fprintf(program, "if (do_pop()) {");
    execute(prog[1]);
    fprintf(program, "} else {");
    execute(prog[2]);
    fprintf(program, "linrec_%d();", ident);
    execute(prog[3]);
    fprintf(program, "} }\n");
    rewind(program);
    while ((ch = getc(program)) != EOF)
	putchar(ch);
    fclose(program);
    program = old;
}
#endif

/**
linrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void do_linrec(void)
{
    Stack *prog[4];

    QUATERN;
    prog[3] = (Stack *)do_pop();
    prog[2] = (Stack *)do_pop();
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_linrec(prog);
    else
#endif
    linrec(prog);
}
#endif
