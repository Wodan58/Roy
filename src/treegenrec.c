/*
    module  : treegenrec.c
    version : 1.14
    date    : 03/01/21
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

static intptr_t _treegenrec;

void treegenrec(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
    if (is_list(stack[-1])) {
	execute((Stack *)vec_at(prog, vec_size(prog) - 2));
	do_push((intptr_t)prog);
	do_push(_treegenrec);
	do_cons();
	execute_rest(prog, vec_size(prog) - 3);
    } else
	execute((Stack *)vec_at(prog, vec_size(prog) - 1));
}

#ifdef COMPILING
void put_treegenrec(void)
{
    static int ident;
    int ch;
    FILE *old;
    Stack *prog = (Stack *)do_pop();

    printf("void treegenrec_%d(void);", ++ident);
    fprintf(old = program, "treegenrec_%d();", ident);
    if ((program = my_tmpfile()) == 0)
	yyerror("treegenrec");
    fprintf(program, "void treegenrec_%d(void) {", ident);
    fprintf(program, "if (is_list(stack[-1])) {");
    execute((Stack *)vec_at(prog, vec_size(prog) - 2));
    fprintf(program, "do_list_%d();", FindNode(prog));
    fprintf(program, "do_push((intptr_t)treegenrec | JLAP_INVALID);");
    fprintf(program, "do_push(0); do_cons(); do_cons();");
    execute_rest(prog, vec_size(prog) - 3);
    fprintf(program, "} else {");
    execute((Stack *)vec_at(prog, vec_size(prog) - 1));
    fprintf(program, "} }");
    rewind(program);
    while ((ch = getc(program)) != EOF)
	putchar(ch);
    fclose(program);
    program = old;
}
#endif

/**
treegenrec  :  T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void do_treegenrec(void)
{
    TERNARY;
    if (!_treegenrec) {
	do_push((intptr_t)GC_strdup("_treegenrec") | JLAP_INVALID);
	do_push(0);
	do_cons();
	_treegenrec = do_pop();
	enter("_treegenrec", treegenrec);
    }
    do_cons();
    do_cons();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_treegenrec();
    else
#endif
    treegenrec();
}
#endif
