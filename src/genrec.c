/*
    module  : genrec.c
    version : 1.19
    date    : 03/01/21
*/
#ifndef GENREC_C
#define GENREC_C

static intptr_t _genrec;

void genrec(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
    execute((Stack *)vec_at(prog, vec_size(prog) - 1));
    if (do_pop())
	execute((Stack *)vec_at(prog, vec_size(prog) - 2));
    else {
	execute((Stack *)vec_at(prog, vec_size(prog) - 3));
	do_push((intptr_t)prog);
	do_push(_genrec);
	do_cons();
	execute_rest(prog, vec_size(prog) - 4);
    }
}

#ifdef COMPILING
void put_genrec(void)
{
    static int ident;
    int ch;
    FILE *old;
    Stack *prog = (Stack *)do_pop();

    printf("void genrec_%d(void);", ++ident);
    fprintf(old = program, "genrec_%d();", ident);
    if ((program = my_tmpfile()) == 0)
	yyerror("genrec");
    fprintf(program, "void genrec_%d(void) {", ident);
    execute((Stack *)vec_at(prog, vec_size(prog) - 1));
    fprintf(program, "if (do_pop()) {");
    execute((Stack *)vec_at(prog, vec_size(prog) - 2));
    fprintf(program, "} else {");
    execute((Stack *)vec_at(prog, vec_size(prog) - 3));
    fprintf(program, "do_list_%d();", FindNode(prog));
    fprintf(program, "do_push((intptr_t)genrec | JLAP_INVALID);");
    fprintf(program, "do_push(0); do_cons(); do_cons();");
    execute_rest(prog, vec_size(prog) - 4);
    fprintf(program, "} }");
    rewind(program);
    while ((ch = getc(program)) != EOF)
	putchar(ch);
    fclose(program);
    program = old;
}
#endif

/**
genrec  :  [B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void do_genrec(void)
{
    QUATERN;
    if (!_genrec) {
	do_push((intptr_t)GC_strdup("_genrec") | JLAP_INVALID);
	do_push(0);
	do_cons();
	_genrec = do_pop();
	enter("_genrec", genrec);
    }
    do_cons();
    do_cons();
    do_cons();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_genrec();
    else
#endif
    genrec();
}
#endif
