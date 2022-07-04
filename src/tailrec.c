/*    
    module  : tailrec.c
    version : 1.20
    date    : 06/21/22
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
2740  tailrec  :  DDDU	[P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec(Stack *prog[])
{
    for (;;) {
        execute_cond(prog[0], 0);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack_pop())) {
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
    program = my_tmpfile();
    fprintf(program, "void tailrec_%d(void) {", ident);
    fprintf(program, "for (;;) {");
    compile_cond(prog[0], 0);
    fprintf(program, "if (GET_AS_BOOLEAN(stack_pop())) {");
    compile(prog[1]);
    fprintf(program, "break; }");
    compile(prog[2]);
    fprintf(program, "} }");
    print_tmpfile(old);
}
#endif

void do_tailrec(void)
{
    Stack *prog[3];

    THREEPARAMS;
    THREEQUOTES;
    prog[2] = (Stack *)GET_AS_LIST(stack_pop());
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_tailrec);
    tailrec(prog);
}
#endif
