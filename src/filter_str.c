/*
    module  : filter_str.c
    version : 1.2
    date    : 06/23/20
*/
#ifndef FILTER_STR_C
#define FILTER_STR_C

void filter_str(Stack *prog)
{
    char *str, *ptr;
    int i = 0, j = 1;

    str = (char *)stack[-1];
    ptr = GC_malloc_atomic(strlen(str) + 2);
    ptr[0] = '"';
    for (; str[i]; i++) {
	stack[-1] = str[i];
	execute(prog);
	if (stack[-1])
	    ptr[j++] = str[i];
    }
    ptr[j] = 0;
    stack[-1] = (intptr_t)ptr | JLAP_INVALID;
}

#ifdef COMPILING
void put_filter_str(Stack *prog)
{
    fprintf(program, "char *str, *ptr; int i = 0, j = 1;");
    fprintf(program, "str = (char *)stack[-1];");
    fprintf(program, "ptr = GC_malloc_atomic(strlen(str) + 2); ptr[0] = '\"';");
    fprintf(program, "for (; str[i]; i++) { stack[-1] = str[i];");
    execute(prog);
    fprintf(program, "if (stack[-1]) ptr[j++] = str[i]; } ptr[j] = 0;");
    fprintf(program, "stack[-1] = (intptr_t)ptr | JLAP_INVALID; }");
}
#endif

/**
filter_str  :  A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void do_filter_str(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_filter_str(prog);
    else
#endif
    filter_str(prog);
}
#endif
