/*
    module  : all.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef ALL_C
#define ALL_C

/**
2880  all  :  DDA	A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void all_lst(Stack *prog)
{
    int i;
    Stack *list;

    list = (Stack *)GET_AS_LIST(stack[-1]);
    for (i = vec_size(list) - 1; i >= 0; i--) {
        stack[-1] = vec_at(list, i);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (!GET_AS_BOOLEAN(stack[-1]))
            break;
    }
}

#ifdef COMPILING
void put_all_lst(Stack *prog)
{
    fprintf(program, "{ int i; Stack *list;");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack[-1]);");
    fprintf(program, "for (i = vec_size(list) - 1; i >= 0; i--) {");
    fprintf(program, "stack[-1] = vec_at(list, i);");
    compile_cond(prog, 1);
    fprintf(program, "if (!GET_AS_BOOLEAN(stack[-1])) break; } }");
}
#endif

void all_str(Stack *prog)
{
    int i;
    char *volatile str;

    str = get_string(stack[-1]);
    for (i = 0; str[i]; i++) {
        stack[-1] = MAKE_CHAR(str[i]);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (!GET_AS_BOOLEAN(stack[-1]))
            break;
    }
}

#ifdef COMPILING
void put_all_str(Stack *prog)
{
    fprintf(program, "{ int i; char *volatile str = get_string(stack[-1]);");
    fprintf(program, "for (i = 0; str[i]; i++) {");
    fprintf(program, "stack[-1] = MAKE_CHAR(str[i]);");
    compile_cond(prog, 1);
    fprintf(program, "if (!GET_AS_BOOLEAN(stack[-1])) break; } }");
}
#endif

void all_set(Stack *prog)
{
    int i;
    uint64_t set;

    set = GET_AS_SET(stack[-1]);
    for (i = 0; i < SETSIZE_; i++)
        if (set & ((uint64_t)1 << i)) {
            stack[-1] = MAKE_INTEGER(i);
            execute_cond(prog, 1);
            CHECKSTACK;
            if (!GET_AS_BOOLEAN(stack[-1]))
                break;
        }
}

#ifdef COMPILING
void put_all_set(Stack *prog)
{
    fprintf(program, "{ uint64_t set; int i;");
    fprintf(program, "set = GET_AS_SET(stack[-1]);");
    fprintf(program, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(program, "if (set & ((uint64_t)1 << i)) {");
    fprintf(program, "stack[-1] = MAKE_INTEGER(i);");
    compile_cond(prog, 1);
    fprintf(program, "if (!GET_AS_BOOLEAN(stack[-1])) break; } }");
}
#endif

#ifdef COMPILING
void put_all(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void all_%d(void);", ++ident);
    fprintf(old = program, "all_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void all_%d(void) {", ident);
    fprintf(program, "if (IS_LIST(stack[-1]))");
    put_all_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_all_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_all_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_all(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_all);
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        all_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        all_str(prog);
    else if (IS_SET(stack[-1]))
        all_set(prog);
    else
        BADAGGREGATE;
}
#endif
