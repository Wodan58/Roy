/*
    module  : map.c
    version : 1.25
    date    : 06/23/20
*/
#ifndef MAP_C
#define MAP_C

void map(Stack *prog)
{
    int i, j;
    Stack *list, *List = 0;

    list = (Stack *)do_pop();
    for (i = 0, j = vec_size(list); i < j; i++) {
	do_push(vec_at(list, i));
	execute(prog);
	vec_push(List, do_pop());
    }
    do_push((intptr_t)List);
}

#ifdef COMPILING
void put_map(Stack *prog)
{
    fprintf(program, "{ int i; Stack *list, *List = 0;");
    fprintf(program, "list = (Stack *)do_pop();");
    fprintf(program, "for (i = vec_size(list) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(list, i));");
    execute(prog);
    fprintf(program, "vec_push(List, do_pop()); }");
    fprintf(program, "do_push((intptr_t)List); }");
}
#endif

/**
map  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void do_map(void)
{
    Stack *prog;

    BINARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_map(prog);
    else
#endif
    map(prog);
}
#endif
