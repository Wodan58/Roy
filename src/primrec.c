/*
    module  : primrec.c
    version : 1.14
    date    : 06/21/22
*/
#ifndef PRIMREC_C
#define PRIMREC_C

/**
2840  primrec  :  DDDA	X [I] [C]  ->  R
Executes I to obtain an initial value R0.
For integer X uses increasing positive integers to X, combines by C for new R.
For aggregate X uses successive members and combines by C for new R.
*/
void primrec_int(Stack *prog[2])
{
    int i, j;

    j = GET_AS_INTEGER(stack_pop());
    for (i = j; i; i--)
        do_push(MAKE_INTEGER(i));
    execute(prog[0]);
    while (j--)
        execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_int(Stack *prog[2])
{
    fprintf(program, "{ int i, j = GET_AS_INTEGER(stack_pop());");
    fprintf(program, "for (i = j; i; i--) do_push(MAKE_INTEGER(i));");
    compile(prog[0]);
    fprintf(program, "while (j--) {");
    compile(prog[1]);
    fprintf(program, "} }");
}
#endif

void primrec_lst(Stack *prog[2])
{
    int i, j;
    Stack *list;

    list = (Stack *)GET_AS_LIST(stack_pop());
    for (j = vec_size(list), i = j - 1; i >= 0; i--)
        do_push(vec_at(list, i));
    execute(prog[0]);
    while (j--)
        execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_lst(Stack *prog[2])
{
    fprintf(program, "{ int i, j; Stack *list;");
    fprintf(program, "list = (Stack *)GET_AS_LIST(stack_pop());");
    fprintf(program, "for (j = vec_size(list), i = j - 1; i >= 0; i--)");
    fprintf(program, "do_push(vec_at(list, i));");
    compile(prog[0]);
    fprintf(program, "while (j--) {");
    compile(prog[1]);
    fprintf(program, "} }");
}
#endif

void primrec_str(Stack *prog[2])
{
    int j;
    char *volatile str;

    str = get_string(stack_pop());
    for (j = strlen(str); *str; str++)
        do_push(MAKE_CHAR(*str));
    execute(prog[0]);
    while (j--)
        execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_str(Stack *prog[2])
{
    fprintf(program, "{ int j; char *volatile str = get_string(stack_pop());");
    fprintf(program, "for (j = strlen(str); *str; str++)");
    fprintf(program, "do_push(MAKE_CHAR(*str));");
    compile(prog[0]);
    fprintf(program, "while (j--) {");
    compile(prog[1]);
    fprintf(program, "} }");
}
#endif

void primrec_set(Stack *prog[2])
{
    int i, num;
    uint64_t j, set;

    set = GET_AS_SET(stack_pop());
    for (num = i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j) {
            do_push(MAKE_INTEGER(i));
            num++;
        }
    execute(prog[0]);
    while (num--)
        execute(prog[1]);
}

#ifdef COMPILING
void put_primrec_set(Stack *prog[2])
{
    fprintf(program, "{ int i, num; uint64_t j, set = GET_AS_SET(stack_pop());");
    fprintf(program, "for (num = i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)");
    fprintf(program, "if (set & j) { do_push(MAKE_INTEGER(i)); num++; }");
    compile(prog[0]);
    fprintf(program, "while (num--) {");
    compile(prog[1]);
    fprintf(program, "} }");
}
#endif

#ifdef COMPILING
void put_primrec(Stack *prog[2])
{
    static int ident;
    int ch;
    FILE *old;

    printf("void primrec_%d(void);", ++ident);
    fprintf(old = program, "primrec_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void primrec_%d(void) {", ident);
    fprintf(program, "ONEPARAM; if (IS_INTEGER(stack[-1]))");
    put_primrec_int(prog);
    fprintf(program, "else if (IS_LIST(stack[-1]))");
    put_primrec_lst(prog);
    fprintf(program, "else if (IS_USR_STRING(stack[-1]))");
    put_primrec_str(prog);
    fprintf(program, "else if (IS_SET(stack[-1]))");
    put_primrec_set(prog);
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_primrec(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_primrec);
    ONEPARAM;
    if (IS_INTEGER(stack[-1]))
        primrec_int(prog);
    else if (IS_LIST(stack[-1]))
        primrec_lst(prog);
    else if (IS_USR_STRING(stack[-1]))
        primrec_str(prog);
    else if (IS_SET(stack[-1]))
        primrec_set(prog);
    else
        BADDATA;
}
#endif
