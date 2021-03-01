/*
    module  : treestep.c
    version : 1.14
    date    : 03/01/21
*/
#ifndef TREESTEP_C
#define TREESTEP_C

void treestep(Stack *prog)
{
    int i;
    Stack *item;

    if (!is_list(stack[-1]))
	execute(prog);
    else {
	item = (Stack *)do_pop();
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
    if ((program = my_tmpfile()) == 0)
	yyerror("treestep");
    fprintf(program, "void treestep_%d(intptr_t item) {", ident);
    fprintf(program, "int i; Stack *item;");
    fprintf(program, "if (!is_list(stack[-1])) {");
    execute(prog);
    fprintf(program, "} else { item = (Stack *)do_pop();");
    fprintf(program, "for (i = vec_size(item) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(item, i)); treestep_%d(); } } }", ident);
    rewind(program);
    while ((ch = getc(program)) != EOF)
	putchar(ch);
    fclose(program);
    program = old;
}
#endif

/**
treestep  :  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void do_treestep(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_treestep(prog);
    else
#endif
    treestep(prog);
}
#endif
