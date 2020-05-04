/*
    module  : some_str.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef SOME_STR_C
#define SOME_STR_C

void some_str(Stack *prog)
{
    char *str;
    intptr_t num = 0;

    str = (char *)do_pop();
    for (; str && *str; str++) {
	do_push(*str);
	execute(prog);
	num = do_pop();
	do_zap();
	if (num)
	    break;
    }
    do_push(num);
}

#ifdef COMPILING
void put_some_str(Stack *prog)
{
    fprintf(program, "{ int i; Stack *list; intptr_t num = 0;");
    fprintf(program, "list = (Stack *)do_pop();");
    fprintf(program, "for (i = vec_size(list) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(list, i));");
    execute(prog);
    fprintf(program, "num = do_pop(); do_zap();");
    fprintf(program, "if (num) break; }");
    fprintf(program, "do_push(num); }");
}
#endif

/**
some_str  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
void do_some_str(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_some_str(prog);
    else
#endif
    some_str(prog);
}
#endif
