/*
    module  : some.c
    version : 1.10
    date    : 07/23/20
*/
#ifndef SOME_C
#define SOME_C

void some(Stack *prog)
{
    int i;
    Stack *list;
    intptr_t num = 0;

    list = (Stack *)do_pop();
    for (i = vec_size(list) - 1; i >= 0; i--) {
	do_push(vec_at(list, i));
	execute(prog);
	num = do_pop();
	do_pop();
	if (num)
	    break;
    }
    do_push(num);
}

#ifdef COMPILING
void put_some(Stack *prog)
{
    fprintf(program, "{ int i; Stack *list; intptr_t num = 0;");
    fprintf(program, "list = (Stack *)do_pop();");
    fprintf(program, "for (i = vec_size(list) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(list, i));");
    execute(prog);
    fprintf(program, "num = do_pop(); do_pop();");
    fprintf(program, "if (num) break; }");
    fprintf(program, "do_push(num); }");
}
#endif

/**
some  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
void do_some(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_some(prog);
    else
#endif
    some(prog);
}
#endif
