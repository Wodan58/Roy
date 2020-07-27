/*
    module  : split.c
    version : 1.25
    date    : 07/23/20
*/
#ifndef SPLIT_C
#define SPLIT_C

void split(Stack *prog)
{
    int i, j;
    intptr_t Value;
    Stack *list, *result[2];

    result[0] = result[1] = 0;
    list = (Stack *)do_pop();
    for (i = 0, j = vec_size(list); i < j; i++) {
	Value = vec_at(list, i);
	do_push(Value);
	execute(prog);
	if (do_pop())
	    vec_push(result[0], Value);
	else
	    vec_push(result[1], Value);
	do_pop();
    }
    do_push((intptr_t)result[0]);
    do_push((intptr_t)result[1]);
}

#ifdef COMPILING
void put_split(Stack *prog)
{
    fprintf(program, "{ int i, j; intptr_t Value; Stack *list, *result[2];");
    fprintf(program, "result[0] = result[1] = 0; list = (Stack *)do_pop();");
    fprintf(program, "for (i = 0, j = vec_size(list); i < j; i++) {");
    fprintf(program, "Value = vec_at(list, i); do_push(Value);");
    execute(prog);
    fprintf(program, "if (do_pop()) vec_push(result[0], Value);");
    fprintf(program, "else vec_push(result[1], Value); do_pop(); }");
    fprintf(program, "do_push((intptr_t)result[0]);");
    fprintf(program, "do_push((intptr_t)result[1]); } }");
}
#endif

/**
split  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void do_split(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_split(prog);
    else
#endif
    split(prog);
}
#endif
