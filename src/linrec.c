/*
    module  : linrec.c
    version : 1.19
    date    : 06/21/22
*/
#ifndef LINREC_C
#define LINREC_C

/**
2730  linrec  :  DDDDU	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void linrec(Stack *prog[])
{
    execute_cond(prog[0], 0);
    CHECKSTACK;
    if (GET_AS_BOOLEAN(stack_pop()))
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
    program = my_tmpfile();
    fprintf(program, "void linrec_%d(void) {", ident);
    compile_cond(prog[0], 0);
    fprintf(program, "if (GET_AS_BOOLEAN(stack_pop())) {");
    compile(prog[1]);
    fprintf(program, "} else {");
    compile(prog[2]);
    fprintf(program, "linrec_%d();", ident);
    compile(prog[3]);
    fprintf(program, "} }\n");
    print_tmpfile(old);
}
#endif

void do_linrec(void)
{
    Stack *prog[4];

    FOURPARAMS;
    FOURQUOTES;
    prog[3] = (Stack *)GET_AS_LIST(stack_pop());
    prog[2] = (Stack *)GET_AS_LIST(stack_pop());
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_linrec);
    linrec(prog);
}
#endif
