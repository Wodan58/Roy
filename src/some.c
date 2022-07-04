/*
    module  : some.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef SOME_C
#define SOME_C

/**
2870  some  :  DDA	A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
void some_lst(Stack *prog)
{
    int i;
    Stack *list;

    list = (Stack *)GET_AS_LIST(stack[-1]);
    for (i = vec_size(list) - 1; i >= 0; i--) {
        stack[-1] = vec_at(list, i);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack[-1]))
            break;
    }
}

#ifdef COMPILING
void put_some_lst(Stack *prog)
{
    fprintf(program, "{ Stack *list; int i;");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack[-1]);");
    fprintf(program, "for (i = vec_size(list) - 1; i >= 0; i--) {");
    fprintf(program, "stack[-1] = vec_at(list, i);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1])) break; } }");
}
#endif

void some_str(Stack *prog)
{
    int i;
    char *volatile str;

    str = get_string(stack[-1]);
    for (i = 0; str[i]; i++) {
        stack[-1] = MAKE_CHAR(str[i]);
        execute_cond(prog, 1);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack[-1]))
            break;
    }
}

#ifdef COMPILING
void put_some_str(Stack *prog)
{
    fprintf(program, "{ int i; char *volatile str = get_string(stack[-1]);");
    fprintf(program, "for (i = 0; str[i]; i++) {");
    fprintf(program, "do_push(MAKE_CHAR(str[i]));");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1])) break; } }");
}
#endif

void some_set(Stack *prog)
{
    int i;
    uint64_t set;

    set = GET_AS_SET(stack[-1]);
    for (i = 0; i < SETSIZE_; i++)
        if (set & ((uint64_t)1 << i)) {
            stack[-1] = MAKE_INTEGER(i);
            execute_cond(prog, 1);
            CHECKSTACK;
            if (GET_AS_BOOLEAN(stack[-1]))
                break;
        }
}

#ifdef COMPILING
void put_some_set(Stack *prog)
{
    fprintf(program, "{ uint64_t set; int i;");
    fprintf(program, "set = GET_AS_SET(stack[-1]);");
    fprintf(program, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(program, "if (set & ((uint64_t)1 << i)) {");
    fprintf(program, "stack[-1] = MAKE_INTEGER(i);");
    compile_cond(prog, 1);
    fprintf(program, "if (GET_AS_BOOLEAN(stack[-1])) break; } }");
}
#endif

#ifdef COMPILING
void put_some(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void some_%d(void);", ++ident);
    fprintf(old = program, "some_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void some_%d(void) {", ident);
    fprintf(program, "if (IS_LIST(stack[-1]))");
    put_some_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_some_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_some_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_some(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_some);
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        some_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        some_str(prog);
    else if (IS_SET(stack[-1]))
        some_set(prog);
    else
        BADAGGREGATE;
}
#endif
