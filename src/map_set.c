/*
    module  : map_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef MAP_SET_C
#define MAP_SET_C

void map_set(Stack *prog)
{
    int i;
    intptr_t j, set, zet = 0;

    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    stack[-1] = i;
	    execute(prog);
	    zet |= (intptr_t)1 << stack[-1];
	}
    stack[-1] = zet;
}

#ifdef COMPILING
void put_map_set(Stack *prog)
{
    fprintf(program, "{ int i; intptr_t j, set, zet = 0; set = stack[-1];");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) { stack[-1] = i;");
    execute(prog);
    fprintf(program, "zet |= (intptr_t)1 << stack[-1]; }");
    fprintf(program, "stack[-1] = zet; }");
}
#endif

/**
map_set  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void do_map_set(void)
{
    Stack *prog;

    BINARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_map_set(prog);
    else
#endif
    map_set(prog);
}
#endif
