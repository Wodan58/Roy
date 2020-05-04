/*
    module  : some_set.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef SOME_SET_C
#define SOME_SET_C

void some_set(Stack *prog)
{
    int i;
    intptr_t set, num = 0;

    set = do_pop();
    for (i = 0; i < SETSIZE_; i++)
	if (set & ((intptr_t)1 << i)) {
	    do_push(i);
	    execute(prog);
	    num = do_pop();
	    do_zap();
	    if (num)
		break;
	}
    do_push(num);
}

#ifdef COMPILING
void put_some_set(Stack *prog)
{
    fprintf(program, "{ int i; intptr_t set, num = 0;");
    fprintf(program, "set = do_pop();");
    fprintf(program, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(program, "if (set & ((intptr_t)1 << i)) {");
    fprintf(program, "do_push(i);");
    execute(prog);
    fprintf(program, "num = do_pop(); do_zap();");
    fprintf(program, "if (num) break; }");
    fprintf(program, "do_push(num); }");
}
#endif

/**
some_set  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
void do_some_set(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_some_set(prog);
    else
#endif
    some_set(prog);
}
#endif
