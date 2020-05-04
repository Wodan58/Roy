/*
    module  : all.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef ALL_C
#define ALL_C

void all(Stack *prog)
{
    int i;
    Stack *list;
    intptr_t num = 1;

    list = (Stack *)do_pop();
    for (i = vec_size(list) - 1; i >= 0; i--) {
	do_push(vec_at(list, i));
	execute(prog);
	num = do_pop();
	do_zap();	// TODO
	if (!num)
	    break;
    }
    do_push(num);
}

#ifdef COMPILING
void put_all(Stack *prog)
{
    fprintf(program, "{ int i; Stack *list; intptr_t num = 1;");
    fprintf(program, "list = (Stack *)do_pop();");
    fprintf(program, "for (i = vec_size(list) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(list, i));");
    execute(prog);
    fprintf(program, "num = do_pop(); do_zap();");
    fprintf(program, "if (!num) break; }");
    fprintf(program, "do_push(num); }");
}
#endif

/**
all  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void do_all(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_all(prog);
    else
#endif
    all(prog);
}
#endif
