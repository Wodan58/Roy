/*
    module  : split_str.c
    version : 1.8
    date    : 07/23/20
*/
#ifndef SPLIT_STR_C
#define SPLIT_STR_C

void split_str(Stack *prog)
{
    int i, yesptr = 1, noptr = 1;
    char *str, *yesstring, *nostring;

    if ((str = (char *)stack[-1]) == 0)
	return;
    yesstring = GC_malloc_atomic(strlen(str) + 2);
    nostring = GC_malloc_atomic(strlen(str) + 2);
    yesstring[0] = nostring[0] = '"';
    for (i = 0; str[i]; i++) {
	stack[-1] = str[i];
	execute(prog);
	if (stack[-1])
	    yesstring[yesptr++] = str[i];
	else
	    nostring[noptr++] = str[i];
	do_pop();
    }
    yesstring[yesptr] = nostring[noptr] = 0;
    stack[-1] = (intptr_t)yesstring | JLAP_INVALID;
    do_push((intptr_t)nostring | JLAP_INVALID);
}

#ifdef COMPILING
void put_split_str(Stack *prog)
{
    fprintf(program, "{ int i, yesptr = 1, noptr = 1;");
    fprintf(program, "char *str, *yesstring = 0, *nostring = 0;");
    fprintf(program, "if ((str = (char *)stack[-1]) == 0) return;");
    fprintf(program, "yesstring = GC_malloc_atomic(strlen(str) + 2);");
    fprintf(program, "nostring = GC_malloc_atomic(strlen(str) + 2);");
    fprintf(program, "yesstring[0] = nostring[0] = '\"';");
    fprintf(program, "for (i = 0; str[i]; i++) { stack[-1] = str[i];");
    execute(prog);
    fprintf(program, "if (stack[-1]) { yesstring[yesptr++] = str[i];");
    fprintf(program, "else nostring[noptr++] = str[i]; }");
    fprintf(program, "yesstring[yesptr] = nostring[noptr] = 0;");
    fprintf(program, "stack[-1] = (intptr_t)yesstring;");
    fprintf(program, "do_push((intptr_t)nostring); } }");
}
#endif

/**
split_str  :  A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void do_split_str(void)
{
    Stack *prog;

    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && STACK(1))
	put_split_str(prog);
    else
#endif
    split_str(prog);
}
#endif
