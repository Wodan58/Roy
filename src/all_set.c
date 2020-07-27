/*
    module  : all_set.c
    version : 1.3
    date    : 07/23/20
*/
#ifndef ALL_SET_C
#define ALL_SET_C

void all_set(Stack *prog)
{
    int i;
    intptr_t set, num = 1;

    set = do_pop();
    for (i = 0; i < SETSIZE_; i++)
	if (set & ((intptr_t)1 << i)) {
	    do_push(i);
	    execute(prog);
	    num = do_pop();
	    do_pop();
	    if (!num)
		break;
	}
    do_push(num);
}

#ifdef COMPILING
void put_all_set(Stack *prog)
{
    fprintf(program, "{ int i; intptr_t set, num = 1;");
    fprintf(program, "set = do_pop();");
    fprintf(program, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(program, "if (set & ((intptr_t)1 << i)) {");
    fprintf(program, "do_push(i);");
    execute(prog);
    fprintf(program, "num = do_pop(); do_pop();");
    fprintf(program, "if (!num) break; }");
    fprintf(program, "do_push(num); }");
}
#endif

/**
all_set  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void do_all_set(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_all_set(prog);
    else
#endif
    all_set(prog);
}
#endif
