/*
    module  : split_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef SPLIT_SET_C
#define SPLIT_SET_C

void split_set(Stack *prog)
{
    int i;
    intptr_t j, set, yes_set = 0, no_set = 0;

    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    stack[-1] = i;
	    execute(prog);
	    if (stack[-1])
		yes_set |= j;
	    else
		no_set |= j;
	}
    stack[-1] = yes_set;
    do_push(no_set);
}

#ifdef COMPILING
void put_split_set(Stack *prog)
{
    fprintf(program, "{ int i; intptr_t j, set, yes_set = 0, no_set = 0;");
    fprintf(program, "set = stack[-1];");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) {");
    fprintf(program, "stack[-1] = i;");
    execute(prog);
    fprintf(program, "if (stack[-1]) yes_set |= j else no_set |= j;");
    fprintf(program, "} stack[-1] = yes_set; do_push(no_set); } }");
}
#endif

/**
split_set  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void do_split_set(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_split_set(prog);
    else
#endif
    split_set(prog);
}
#endif
