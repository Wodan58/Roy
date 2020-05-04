/*
    module  : filter_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FILTER_SET_C
#define FILTER_SET_C

void filter_set(Stack *prog)
{
    int i;
    intptr_t j, zet = 0, set;

    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    stack[-1] = i;
	    execute(prog);
	    if (stack[-1])
		zet |= j;
	}
    stack[-1] = zet;
}

#ifdef COMPILING
void put_filter_set(Stack *prog)
{
    fprintf(program, "int i; intptr_t j, zet = 0, set = stack[-1];");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) {");
    fprintf(program, "stack[-1] = i;");
    execute(prog);
    fprintf(program, "if (stack[-1]) zet |= j; } stack[-1] = zet; }");
}
#endif

/**
filter_set  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void do_filter_set(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_filter_set(prog);
    else
#endif
    filter_set(prog);
}
#endif
