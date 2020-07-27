/*
    module  : filter.c
    version : 1.24
    date    : 06/23/20
*/
#ifndef FILTER_C
#define FILTER_C

void filter(Stack *prog)
{
    int i, j;
    intptr_t Value;
    Stack *list, *result = 0;

    list = (Stack *)do_pop();
    for (i = 0, j = vec_size(list); i < j; i++) {
	Value = vec_at(list, i);
	do_push(Value);
	execute(prog);
	if (do_pop())
	    vec_push(result, Value);
    }
    do_push((intptr_t)result);
}

#ifdef COMPILING
void put_filter(Stack *prog)
{
    fprintf(program, "int i, j; intptr_t Value; Stack *list, *result = 0;");
    fprintf(program, "list = (Stack *)do_pop();");
    fprintf(program, "for (i = 0, j = vec_size(list); i < j; i++) {");
    fprintf(program, "Value = vec_at(list, i); do_push(Value);");
    execute(prog);
    fprintf(program, "if (do_pop()) vec_push(result, Value);");
    fprintf(program, "do_push((intptr_t)result); }");
}
#endif

/**
filter  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void do_filter(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_filter(prog);
    else
#endif
    filter(prog);
}
#endif
