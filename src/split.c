/*
    module  : split.c
    version : 1.26
    date    : 06/21/22
*/
#ifndef SPLIT_C
#define SPLIT_C

/**
2860  split  :  DDAA	A [B]  ->  A1 A2
Uses test B to split aggregate A into sametype aggregates A1 and A2.
*/
void split_lst(Stack *prog)
{
    int i, j;
    Stack *list, *result[2];

    vec_init(result[0]);
    vec_init(result[1]);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    for (i = 0, j = vec_size(list); i < j; i++) {
        stack[-1] = vec_at(list, i);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack[-1]))
            vec_push(result[0], vec_at(list, i));
        else
            vec_push(result[1], vec_at(list, i));
    }
    stack[-1] = MAKE_LIST(result[0]);
    do_push(MAKE_LIST(result[1]));
}

#ifdef COMPILING
void put_split_lst(Stack *prog)
{
    fprintf(program, "{ int i, j; Stack *list, *result[2];");
    fprintf(program, "vec_init(result[0]); vec_init(result[1]);");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack[-1]);");
    fprintf(program, "for (i = 0, j = vec_size(list); i < j; i++) {");
    fprintf(program, "stack[-1] = vec_at(list, i);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1]))");
    fprintf(program, "vec_push(result[0], vec_at(list, i));");
    fprintf(program, "else vec_push(result[1], vec_at(list, i)); }");
    fprintf(program, "stack[-1] = MAKE_LIST(result[0]);");
    fprintf(program, "do_push(MAKE_LIST(result[1])); }");
}
#endif

void split_str(Stack *prog)
{
    int i, yesptr = 1, noptr = 1;
    char *yesstring, *nostring, *volatile str;

    str = get_string(stack[-1]);
    yesstring = GC_malloc_atomic(strlen(str) + 2);
    nostring = GC_malloc_atomic(strlen(str) + 2);
    *yesstring = *nostring = '"';
    for (i = 0; str[i]; i++) {
        stack[-1] = MAKE_CHAR(str[i]);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack[-1]))
            yesstring[yesptr++] = str[i];
        else
            nostring[noptr++] = str[i];
    }
    yesstring[yesptr] = nostring[noptr] = 0;
    stack[-1] = MAKE_USR_STRING(yesstring);
    do_push(MAKE_USR_STRING(nostring));
}

#ifdef COMPILING
void put_split_str(Stack *prog)
{
    fprintf(program, "{ int i, yesptr = 1, noptr = 1;");
    fprintf(program, "char *yesstring, *nostring, *volatile str;");
    fprintf(program, "str = get_string(stack[-1]);");
    fprintf(program, "yesstring = GC_malloc_atomic(strlen(str) + 2);");
    fprintf(program, "nostring = GC_malloc_atomic(strlen(str) + 2);");
    fprintf(program, "*yesstring = *nostring = '\"';");
    fprintf(program, "for (i = 0; str[i]; i++) {");
    fprintf(program, "stack[-1] = MAKE_CHAR(str[i]);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1]))");
    fprintf(program, "yesstring[yesptr++] = str[i];");
    fprintf(program, "else nostring[noptr++] = str[i]; }");
    fprintf(program, "yesstring[yesptr] = nostring[noptr] = 0;");
    fprintf(program, "stack[-1] = MAKE_USR_STRING(yesstring);");
    fprintf(program, "do_push(MAKE_USR_STRING(nostring)); }");
}
#endif

void split_set(Stack *prog)
{
    int i;
    uint64_t j, set, yes_set = 0, no_set = 0;

    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j) {
            stack[-1] = MAKE_INTEGER(i);
            execute_cond(prog, 1);
            CHECKSTACK;
            if (GET_AS_BOOLEAN(stack[-1]))
                yes_set |= j;
            else
                no_set |= j;
        }
    stack[-1] = MAKE_SET(yes_set);
    do_push(MAKE_SET(no_set));
}

#ifdef COMPILING
void put_split_set(Stack *prog)
{
    fprintf(program, "{ int i; uint64_t j, set, yes_set = 0, no_set = 0;");
    fprintf(program, "set = GET_AS_SET(stack[-1]);");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) {");
    fprintf(program, "stack[-1] = MAKE_INTEGER(i);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1]))");
    fprintf(program, "yes_set |= j; else no_set |= j; }");
    fprintf(program, "stack[-1] = MAKE_SET(yes_set);");
    fprintf(program, "do_push(MAKE_SET(no_set)); }");
}
#endif

#ifdef COMPILING
void put_split(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void split_%d(void);", ++ident);
    fprintf(old = program, "split_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void split_%d(void) {", ident);
    fprintf(program, "if (IS_LIST(stack[-1]))");
    put_split_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_split_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_split_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_split(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_split);
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        split_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        split_str(prog);
    else if (IS_SET(stack[-1]))
        split_set(prog);
    else
        BADAGGREGATE;
}
#endif
