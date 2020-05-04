/*
    module  : condlinrec.c
    version : 1.18
    date    : 01/20/20
*/
#ifndef CONDLINREC_C
#define CONDLINREC_C

void condnestrec(Stack *list)
{
    int i;
    Stack *quot, *next;

    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	execute((Stack *)vec_back(quot));
	if (do_pop())
	    break;
    }
    if (i) {
	vec_copy(next, quot);
	vec_pop(next);
    } else
	next = (Stack *)vec_at(list, 0);
    execute((Stack *)vec_back(next));
    for (i = vec_size(next) - 2; i >= 0; i--) {
	condnestrec(list);
	if ((quot = (Stack *)vec_at(next, i)) != 0)
	    execute(quot);
    }
}

#ifdef COMPILING
void put_condnestrec(Stack *list)
{
    static int ident;
    int i, ch;
    FILE *fp, *old;
    Stack *quot, *next;

    printf("void condnestrec_%d(void);", ++ident);
    fprintf(old = program, "condnestrec_%d();", ident);
    if ((fp = tmpfile()) == 0)
	yyerror("condnestrec");
    fprintf(program = fp, "void condnestrec_%d(void) {", ident);
    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	execute((Stack *)vec_back(quot));
	fprintf(program, "if (do_pop()) {");
	vec_copy(next, quot);
	vec_pop(next);
	execute((Stack *)vec_back(next));
	for (i = vec_size(next) - 2; i >= 0; i--) {
	    fprintf(program, "condnestrec_%d();", ident);
	    if ((quot = (Stack *)vec_at(next, i)) != 0)
		execute(quot);
	}
	fprintf(program, "return; }");
    }
    next = (Stack *)vec_at(list, 0);
    execute((Stack *)vec_back(next));
    for (i = vec_size(next) - 2; i >= 0; i--) {
	fprintf(program, "condnestrec_%d();", ident);
	if ((quot = (Stack *)vec_at(next, i)) != 0)
	    execute(quot);
    }
    fprintf(program, "}");
    rewind(fp);
    while ((ch = getc(fp)) != EOF)
	putchar(ch);
    fclose(fp);
    program = old;
}
#endif

/**
condlinrec  :  [ [C1] [C2] .. [D] ]  ->  ...
Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].
Tries each B. If that yields true and there is just a [T], executes T and exit.
If there are [R1] and [R2], executes R1, recurses, executes R2.
Subsequent case are ignored. If no B yields true, then [D] is used.
It is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.
For the latter executes R1, recurses, executes R2.
*/
void do_condlinrec(void)
{
    Stack *list;

    UNARY;
    list = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_condnestrec(list);
    else
#endif
    condnestrec(list);
}
#endif
