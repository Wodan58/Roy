/*
    module  : filter.c
    version : 1.25
    date    : 06/21/22
*/
#ifndef FILTER_C
#define FILTER_C

/**
2850  filter  :  DDA	A [B]  ->  A1
Uses test B to filter aggregate A producing sametype aggregate A1.
*/
void filter_lst(Stack *prog)
{
    int i, j;
    Stack *list, *result;

    vec_init(result);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    for (i = 0, j = vec_size(list); i < j; i++) {
        stack[-1] = vec_at(list, i);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack[-1]))
            vec_push(result, vec_at(list, i));
    }
    stack[-1] = MAKE_LIST(result);
}

#ifdef COMPILING
void put_filter_lst(Stack *prog)
{
    fprintf(program, "{ int i, j; Stack *list, *result; vec_init(result);");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack[-1]);");
    fprintf(program, "for (i = 0, j = vec_size(list); i < j; i++) {");
    fprintf(program, "stack[-1] = vec_at(list, i);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1]))");
    fprintf(program, "vec_push(result, vec_at(list, i)); }");
    fprintf(program, "stack[-1] = MAKE_LIST(result); }");
}
#endif

void filter_str(Stack *prog)
{
    int i = 0, j = 1;
    char *ptr, *volatile str;

    str = get_string(stack[-1]);
    ptr = GC_malloc_atomic(strlen(str) + 2);
    *ptr = '"';
    for (; str[i]; i++) {
        stack[-1] = MAKE_CHAR(str[i]);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack[-1]))
            ptr[j++] = str[i];
    }
    ptr[j] = 0;
    stack[-1] = MAKE_USR_STRING(ptr);
}

#ifdef COMPILING
void put_filter_str(Stack *prog)
{
    fprintf(program, "{ int i = 0, j = 1; char *ptr, *volatile str;");
    fprintf(program, "str = get_string(stack[-1]);");
    fprintf(program, "ptr = GC_malloc_atomic(strlen(str) + 2); *ptr = '\"';");
    fprintf(program, "for (; str[i]; i++) { stack[-1] = MAKE_CHAR(str[i]);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1])) ptr[j++] = str[i]; }");
    fprintf(program, "ptr[j] = 0; stack[-1] = MAKE_USR_STRING(ptr); }");
}
#endif

void filter_set(Stack *prog)
{
    int i;
    uint64_t j, set, zet = 0;

    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j) {
            stack[-1] = MAKE_INTEGER(i);
            execute_cond(prog, 1);
            CHECKSTACK;
            if (GET_AS_BOOLEAN(stack[-1]))
                zet |= j;
        }
    stack[-1] = MAKE_SET(zet);
}

#ifdef COMPILING
void put_filter_set(Stack *prog)
{
    fprintf(program, "{ int i; uint64_t j, set, zet = 0;");
    fprintf(program, "set = GET_AS_SET(stack[-1]);");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) {");
    fprintf(program, "stack[-1] = MAKE_INTEGER(i);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1])) zet |= j; }");
    fprintf(program, "stack[-1] = MAKE_SET(zet); }");
}
#endif

#ifdef COMPILING
void put_filter(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void filter_%d(void);", ++ident);
    fprintf(old = program, "filter_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void filter_%d(void) {", ident);
    fprintf(program, "if (IS_LIST(stack[-1]))");
    put_filter_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_filter_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_filter_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_filter(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_filter);
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        filter_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        filter_str(prog);
    else if (IS_SET(stack[-1]))
        filter_set(prog);
    else
        BADAGGREGATE;
}
#endif
