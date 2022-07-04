/*
    module  : binrec.c
    version : 1.19
    date    : 06/21/22
*/
#ifndef BINREC_C
#define BINREC_C

/**
2750  binrec  :  DDDDU	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void binrec(Stack *prog[4])
{
    value_t temp;

    execute_cond(prog[0], 0);
    CHECKSTACK;
    if (GET_AS_BOOLEAN(stack_pop()))
        execute(prog[1]);
    else {
        execute(prog[2]);
        temp = stack_pop();
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
    Stack *list;

    printf("void binrec_%d(void);", ++ident);
    fprintf(old = program, "binrec_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void binrec_%d(void) {", ident);
    fprintf(program, "value_t temp;");
    compile_cond(prog[0], 0);
    fprintf(program, "if (GET_AS_BOOLEAN(stack_pop())) {");
    compile(prog[1]);
    fprintf(program, "} else {");
    compile(prog[2]);
    fprintf(program, "temp = stack_pop();");
    fprintf(program, "binrec_%d();", ident);
    fprintf(program, "do_push(temp);");
    fprintf(program, "binrec_%d();", ident);
    compile(prog[3]);
    fprintf(program, "} }");
    print_tmpfile(old);
}
#endif

void do_binrec(void)
{
    Stack *prog[4];

    FOURPARAMS;
    FOURQUOTES;
    prog[3] = (Stack *)GET_AS_LIST(stack_pop());
    prog[2] = (Stack *)GET_AS_LIST(stack_pop());
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_binrec);
    binrec(prog);
}
#endif
