/*
    module  : cond.c
    version : 1.17
    date    : 01/20/20
*/
#ifndef COND_C
#define COND_C

void cond(Stack *list)
{
    int i;
    Stack *quot, *next;

    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	execute((Stack *)vec_back(quot));
	if (do_pop())
	    break;
    }
    if (i) {
	vec_copy(next, quot);
	vec_pop(next);
    } else
	next = (Stack *)vec_at(list, 0);
    execute(next);
}

#ifdef COMPILING
void put_cond(Stack *list)
{
    int i;
    Stack *quot, *next;

    fprintf(program, "{ intptr_t num = 0; for (;;) {");
    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	execute((Stack *)vec_back(quot));
	fprintf(program, "if ((num = do_pop()) != 0) {");
	vec_copy(next, quot);
	vec_pop(next);
	execute(next);
	fprintf(program, "break; }");
    }
    fprintf(program, "break; } if (!num) {");
    execute((Stack *)vec_at(list, 0));
    fprintf(program, "} }");
}
#endif

/**
cond  :  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
void do_cond(void)
{
    Stack *list;

    UNARY;
    list = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_cond(list);
    else
#endif
    cond(list);
}
#endif
