/*
    module  : treegenrec.c
    version : 1.12
    date    : 01/19/20
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
    FILE *fp, *old;
    Stack *prog = (Stack *)do_pop();

    printf("void treegenrec_%d(void);", ++ident);
    fprintf(old = program, "treegenrec_%d();", ident);
    if ((fp = tmpfile()) == 0)
	yyerror("treegenrec");
    fprintf(program = fp, "void treegenrec_%d(void) {", ident);
    fprintf(fp, "if (is_list(stack[-1])) {");
    execute((Stack *)vec_at(prog, vec_size(prog) - 2));
    fprintf(fp, "do_list_%d();", FindNode(prog));
    fprintf(fp, "do_push((intptr_t)treegenrec | JLAP_INVALID);");
    fprintf(fp, "do_push(0); do_cons(); do_cons();");
    execute_rest(prog, vec_size(prog) - 3);
    fprintf(fp, "} else {");
    execute((Stack *)vec_at(prog, vec_size(prog) - 1));
    fprintf(fp, "} }");
    rewind(fp);
    while ((ch = getc(fp)) != EOF)
	putchar(ch);
    fclose(fp);
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
    if (compiling && stack_empty())
	put_treegenrec();
    else
#endif
    treegenrec();
}
#endif