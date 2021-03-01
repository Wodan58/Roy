/*
    module  : tailrec.c
    version : 1.19
    date    : 03/01/21
*/
#ifndef TAILREC_C
#define TAILREC_C

void tailrec(Stack *prog[])
{
    for (;;) {
	execute(prog[0]);
	if (do_pop()) {
	    execute(prog[1]);
	    break;
	}
	execute(prog[2]);
    }
}

#ifdef COMPILING
void put_tailrec(Stack *prog[])
{
    static int ident;
    int ch;
    FILE *old;

    printf("void tailrec_%d(void);", ++ident);
    fprintf(old = program, "tailrec_%d();", ident);
    if ((program = my_tmpfile()) == 0)
	yyerror("tailrec");
    fprintf(program, "void tailrec_%d(void) {", ident);
    fprintf(program, "for (;;) {");
    execute(prog[0]);
    fprintf(program, "if (do_pop()) {");
    execute(prog[1]);
    fprintf(program, "break; }");
    execute(prog[2]);
    fprintf(program, "} }\n");
    rewind(program);
    while ((ch = getc(program)) != EOF)
	putchar(ch);
    fclose(program);
    program = old;
}
#endif

/**
tailrec  :  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void do_tailrec(void)
{
    Stack *prog[3];

    TERNARY;
    prog[2] = (Stack *)do_pop();
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_tailrec(prog);
    else
#endif
    tailrec(prog);
}
#endif
