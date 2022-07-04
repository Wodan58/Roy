/*
    module  : step.c
    version : 1.14
    date    : 06/21/22
*/
#ifndef STEP_C
#define STEP_C

/**
2790  step  :  DDU	A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void step_lst(Stack *prog)
{
    int i;
    Stack *quot;

    quot = (Stack *)GET_AS_LIST(stack_pop());
    for (i = vec_size(quot) - 1; i >= 0; i--) {
        do_push(vec_at(quot, i));
        execute(prog);
    }
}

#ifdef COMPILING
void put_step_lst(Stack *prog)
{
    fprintf(program, "{ Stack *quot = (Stack *)GET_AS_LIST(stack_pop());");
    fprintf(program, "int i; for (i = vec_size(quot) - 1; i >= 0; i--) {");
    fprintf(program, "do_push(vec_at(quot, i));");
    compile(prog);
    fprintf(program, "} }");
}
#endif

void step_str(Stack *prog)
{
    int i;
    char *volatile str;

    str = get_string(stack_pop());
    for (i = 0; str[i]; i++) {
        do_push(MAKE_CHAR(str[i]));
        execute(prog);
    }
}

#ifdef COMPILING
void put_step_str(Stack *prog)
{
    fprintf(program, "{ int i; char *volatile str;");
    fprintf(program, "str = get_string(stack_pop());");
    fprintf(program, "for (i = 0; str[i]; i++) {");
    fprintf(program, "do_push(MAKE_CHAR(str[i]));");
    compile(prog);
    fprintf(program, "} }");
}
#endif

void step_set(Stack *prog)
{
    int i;
    uint64_t j, set;

    set = GET_AS_SET(stack_pop());
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j) {
            do_push(MAKE_INTEGER(i));
            execute(prog);
        }
}

#ifdef COMPILING
void put_step_set(Stack *prog)
{
    fprintf(program, "{ int i; uint64_t j, set = GET_AS_SET(stack_pop());");
    fprintf(program, "for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) { do_push(MAKE_INTEGER(i));");
    compile(prog);
    fprintf(program, "} }");
}
#endif

#ifdef COMPILING
void put_step(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    printf("void step_%d(void);", ++ident);
    fprintf(old = program, "step_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void step_%d(void) {", ident);
    fprintf(program, "if (IS_LIST(stack[-1]))");
    put_step_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_step_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_step_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_step(void)
{
    Stack *prog;

    ONEPARAM;
    ONEQUOTE;
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_step);
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        step_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        step_str(prog);
    else if (IS_SET(stack[-1]))
        step_set(prog);
    else
        BADAGGREGATE;
}
#endif
