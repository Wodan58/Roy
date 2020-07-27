/*
    module  : linrec.c
    version : 1.17
    date    : 06/23/20
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
    FILE *fp, *old;

    printf("void linrec_%d(void);", ++ident);
    fprintf(old = program, "linrec_%d();", ident);
    if ((fp = tmpfile()) == 0)
	yyerror("linrec");
    fprintf(program = fp, "void linrec_%d(void) {", ident);
    execute(prog[0]);
    fprintf(fp, "if (do_pop()) {");
    execute(prog[1]);
    fprintf(fp, "} else {");
    execute(prog[2]);
    fprintf(fp, "linrec_%d();", ident);
    execute(prog[3]);
    fprintf(fp, "} }\n");
    rewind(fp);
    while ((ch = getc(fp)) != EOF)
	putchar(ch);
    fclose(fp);
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
