/*
    module  : map.c
    version : 1.26
    date    : 06/21/22
*/
#ifndef MAP_C
#define MAP_C

/**
2810  map  :  DDA	A [P]  ->  B
Executes P on each member of aggregate A,
collects results in sametype aggregate B.
*/
void map_lst(Stack *prog)
{
    int i, j;
    Stack *list, *quot;

    list = (Stack *)GET_AS_LIST(stack[-1]);
    vec_init(quot);
    for (i = 0, j = vec_size(list); i < j; i++) {
        stack[-1] = vec_at(list, i);
        execute_cond(prog, 1);
        CHECKSTACK;
        vec_push(quot, stack[-1]);
    }
    stack[-1] = MAKE_LIST(quot);
}

#ifdef COMPILING
void put_map_lst(Stack *prog)
{
    fprintf(program, "{ int i, j; Stack *list, *quot; vec_init(quot);");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack[-1]);");
    fprintf(program, "for (i = 0, j = vec_size(list); i < j; i++) {");
    fprintf(program, "stack[-1] = vec_at(list, i);");
    compile_cond(prog, 1);
    fprintf(program, "vec_push(quot, stack[-1]); }");
    fprintf(program, "stack[-1] = MAKE_LIST(quot); }");
}
#endif

void map_str(Stack *prog)
{
    int i = 0, j = 1;
    char *ptr, *volatile str;

    str = get_string(stack[-1]);
    ptr = GC_malloc_atomic(strlen(str) + 2);
    *ptr = '"';
    while (str[i]) {
        stack[-1] = MAKE_CHAR(str[i++]);
        execute_cond(prog, 1);
        CHECKSTACK;
        ptr[j++] = GET_AS_CHAR(stack[-1]);
    }
    ptr[j] = 0;
    stack[-1] = MAKE_USR_STRING(ptr);
}

#ifdef COMPILING
void put_map_str(Stack *prog)
{
    fprintf(program, "{ int i = 0, j = 1; char *ptr, *volatile str;");
    fprintf(program, "str = get_string(stack[-1]);");
    fprintf(program, "ptr = GC_malloc_atomic(strlen(str) + 2); *ptr = '\"';");
    fprintf(program, "while (str[i]) {");
    fprintf(program, "stack[-1] = MAKE_CHAR(str[i++]);");
    compile_cond(prog, 1);
    fprintf(program, "ptr[j++] = GET_AS_CHAR(stack[-1]); } ptr[j] = 0;");
    fprintf(program, "stack[-1] = MAKE_USR_STRING(ptr); }");
}
#endif

void map_set(Stack *prog)
{
    int i;
    uint64_t j, set, zet = 0;

    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j) {
            stack[-1] = MAKE_INTEGER(i);
            execute_cond(prog, 1);
            CHECKSTACK;
            zet |= (uint64_t)1 << GET_AS_INTEGER(stack[-1]);
        }
    stack[-1] = MAKE_SET(zet);
}

#ifdef COMPILING
void put_map_set(Stack *prog)
{
    fprintf(program, "{ int i; uint64_t j, set, zet = 0;");
    fprintf(program, "set = GET_AS_SET(stack[-1]);");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) { stack[-1] = MAKE_INTEGER(i);");
    compile_cond(prog, 1);
    fprintf(program, "zet |= (uint64_t)1 << GET_AS_INTEGER(stack[-1]); }");
    fprintf(program, "stack[-1] = MAKE_SET(zet); }");
}
#endif

#ifdef COMPILING
void put_map(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void map_%d(void);", ++ident);
    fprintf(old = program, "map_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void map_%d(void) {", ident);
    fprintf(program, "if (IS_LIST(stack[-1]))");
    put_map_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_map_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_map_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_map(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_map);
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        map_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        map_str(prog);
    else if (IS_SET(stack[-1]))
        map_set(prog);
    else
        BADAGGREGATE;
}
#endif
