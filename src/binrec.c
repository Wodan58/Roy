/*
    module  : binrec.c
    version : 1.18
    date    : 03/01/21
*/
#ifndef BINREC_C
#define BINREC_C

void binrec(Stack *prog[])
{
    intptr_t temp;

    execute(prog[0]);
    if (do_pop())
	execute(prog[1]);
    else {
	execute(prog[2]);
	temp = do_pop();
	binrec(prog);
	do_push(temp);
	binrec(prog);
	execute(prog[3]);
    }
}

#ifdef COMPILING
void put_binrec(Stack *prog[4])
{
    static int ident;
    int ch;
    FILE *old;

    printf("void binrec_%d(void);", ++ident);
    fprintf(old = program, "binrec_%d();", ident);
    if ((program = my_tmpfile()) == 0)
	yyerror("binrec");
    fprintf(program, "void binrec_%d(void) {", ident);
    fprintf(program, "intptr_t temp;");
    execute(prog[0]);
    fprintf(program, "if (do_pop()) {");
    execute(prog[1]);
    fprintf(program, "} else {");
    execute(prog[2]);
    fprintf(program, "temp = do_pop();");
    fprintf(program, "binrec_%d();", ident);
    fprintf(program, "do_push(temp);");
    fprintf(program, "binrec_%d();", ident);
    execute(prog[3]);
    fprintf(program, "} }");
    rewind(program);
    while ((ch = getc(program)) != EOF)
	putchar(ch);
    fclose(program);
    program = old;
}
#endif

/**
binrec  :  [P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void do_binrec(void)
{
    Stack *prog[4];

    QUATERN;
    prog[3] = (Stack *)do_pop();
    prog[2] = (Stack *)do_pop();
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_binrec(prog);
    else
#endif
    binrec(prog);
}
#endif
