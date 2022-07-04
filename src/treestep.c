/*
    module  : treestep.c
    version : 1.15
    date    : 06/21/22
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
2890  treestep  :  DDU	T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void treestep(Stack *prog)
{
    int i;
    Stack *item;

    if (!IS_LIST(stack[-1]))
        execute(prog);
    else {
        item = (Stack *)GET_AS_LIST(stack_pop());
        for (i = vec_size(item) - 1; i >= 0; i--) {
            do_push(vec_at(item, i));
            treestep(prog);
        }
    }
}

#ifdef COMPILING
void put_treestep(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void treestep_%d();", ++ident);
    fprintf(old = program, "treestep_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void treestep_%d(void) {", ident);
    fprintf(program, "int i; Stack *item;");
    fprintf(program, "if (!IS_LIST(stack[-1])) {");
    compile(prog);
    fprintf(program, "} else { item = (Stack *)GET_AS_LIST(stack_pop());");
    fprintf(program, "for (i = vec_size(item) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(item, i)); treestep_%d(); } } }", ident);
    print_tmpfile(old);
}
#endif

void do_treestep(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_treestep);
    ONEPARAM;
    treestep(prog);
}
#endif
