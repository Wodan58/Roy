/*
    module  : treerec.c
    version : 1.14
    date    : 06/23/20
*/
#ifndef TREEREC_C
#define TREEREC_C

static intptr_t _treerec;

void treerec(void)
{
    Stack *prog;

    if (is_list(stack[-2])) {
	do_push(_treerec);
	do_cons();
	prog = (Stack *)stack[-1];
	prog = (Stack *)vec_at(prog, vec_size(prog) - 1);
	execute_rest(prog, vec_size(prog) - 2);
    } else {
	prog = (Stack *)do_pop();
	prog = (Stack *)vec_at(prog, vec_size(prog) - 1);
	execute(prog);
    }
}

#ifdef COMPILING
void put_treerec(void)
{
    static int ident;
    int ch;
    FILE *fp, *old;
    Stack *prog = (Stack *)do_pop();

    printf("void treerec_%d(void);", ++ident);
    fprintf(old = program, "treerec_%d();", ident);
    if ((fp = tmpfile()) == 0)
	yyerror("treerec");
    fprintf(program = fp, "void treerec_%d(void) {", ident);
    fprintf(fp, "if (is_list(stack[-2])) {");
    fprintf(fp, "do_list_%d();", FindNode(prog));
    fprintf(fp, "do_push((intptr_t)treerec | JLAP_INVALID);");
    fprintf(fp, "do_push(0); do_cons(); do_cons();");
    prog = (Stack *)stack[-1];
    prog = (Stack *)vec_at(prog, vec_size(prog) - 1);
    execute_rest(prog, vec_size(prog) - 2);
    fprintf(fp, "} else {");
    prog = (Stack *)do_pop();
    prog = (Stack *)vec_at(prog, vec_size(prog) - 1);
    execute(prog);
    fprintf(fp, "} }");
    rewind(fp);
    while ((ch = getc(fp)) != EOF)
	putchar(ch);
    fclose(fp);
    program = old;
}
#endif

/**
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void do_treerec(void)
{
    BINARY;
    if (!_treerec) {
	do_push((intptr_t)GC_strdup("_treerec") | JLAP_INVALID);
	do_push(0);
	do_cons();
	_treerec = do_pop();
	enter("_treerec", treerec);
    }
    do_cons();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_treerec();
    else
#endif
    treerec();
}
#endif
