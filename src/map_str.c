/*
    module  : map_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef MAP_STR_C
#define MAP_STR_C

void map_str(Stack *prog)
{
    char *str, *ptr;
    int i = 0, j = 1;

    str = (char *)stack[-1];
    ptr = GC_malloc_atomic(strlen(str) + 2);
    ptr[0] = '"';
    while (str[i]) {
	stack[-1] = str[i++];
	execute(prog);
	ptr[j++] = stack[-1];
    }
    ptr[j] = 0;
    stack[-1] = (intptr_t)ptr | JLAP_INVALID;
}

#ifdef COMPILING
void put_map_str(Stack *prog)
{
    fprintf(program, "{ char *str, *ptr; int i = 0, j = 1;");
    fprintf(program, "str = (char *)stack[-1];");
    fprintf(program, "ptr = GC_malloc_atomic(strlen(str) + 2); ptr[0] = '\"';");
    fprintf(program, "while (str[i]) {");
    fprintf(program, "stack[-1] = str[i++];");
    execute(prog);
    fprintf(program, "ptr[j++] = stack[-1]; } ptr[j] = 0;");
    fprintf(program, "stack[-1] = (intptr_t)ptr | JLAP_INVALID; }");
}
#endif

/**
map_str  :  A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void do_map_str(void)
{
    Stack *prog;

    BINARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_map_str(prog);
    else
#endif
    map_str(prog);
}
#endif
