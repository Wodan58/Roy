/*
    module  : treestep.c
    version : 1.12
    date    : 05/05/20
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
    FILE *fp, *old;

    printf("void treestep_%d();", ++ident);
    fprintf(old = program, "treestep_%d();", ident);
    if ((fp = tmpfile()) == 0)
	yyerror("treestep");
    fprintf(program = fp, "void treestep_%d(intptr_t item) {", ident);
    fprintf(fp, "int i; Stack *item;");
    fprintf(fp, "if (!is_list(stack[-1])) {");
    execute(prog);
    fprintf(fp, "} else { item = (Stack *)do_pop();");
    fprintf(fp, "for (i = vec_size(item) - 1; i >= 0; i--) {");
    fprintf(fp, "do_push(vec_at(item, i)); treestep_%d(); } } }", ident);
    rewind(fp);
    while ((ch = getc(fp)) != EOF)
	putchar(ch);
    fclose(fp);
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
    if (compiling && stack_empty())
	put_treestep(prog);
    else
#endif
    treestep(prog);
}
#endif
