/*
    module  : treerec.c
    version : 1.16
    date    : 06/21/22
*/
#ifndef TREEREC_C
#define TREEREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

/**
2900  treerec  :  DDDU	T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
void treerec(void)
{
    static value_t _treerec;
    Stack *prog;

    if (IS_INITIAL(_treerec)) {
        do_push(MAKE_ANON_FUNCT(treerec));
        vec_init(prog);
        do_push(MAKE_LIST(prog));
        do_cons();
        _treerec = stack_pop();
#ifdef COMPILING
        enter("_treerec", "", treerec);
#endif
    }
    TWOPARAMS;
    if (IS_LIST(stack[-2])) {
        do_push(_treerec);
        do_cons();
        prog = (Stack *)GET_AS_LIST(stack[-1]);
        prog = (Stack *)GET_AS_LIST(vec_back(prog));
        execute_rest(prog, vec_size(prog) - 2);
    } else {
        prog = (Stack *)GET_AS_LIST(stack_pop());
        prog = (Stack *)GET_AS_LIST(vec_back(prog));
        execute(prog);
    }
}

#ifdef COMPILING
void put_treerec(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    set_inuse("treerec");
    printf("void treerec(void);");
    printf("void treerec_%d(void);", ++ident);
    fprintf(old = program, "treerec_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void treerec_%d(void) { Stack *list;", ident);
    fprintf(program, "if (IS_LIST(stack[-2])) {");
    fprintf(program, "do_list_%d();", FindNode(prog));
    fprintf(program, "do_push(MAKE_ANON_FUNCT(treerec)); vec_init(list);");
    fprintf(program, "do_push(MAKE_LIST(list)); do_cons(); do_cons();");
    prog = (Stack *)GET_AS_LIST(vec_back(prog));
    compile_rest(prog, vec_size(prog) - 2);
    fprintf(program, "} else {");
    compile(prog);
    fprintf(program, "} }");
    print_tmpfile(old);
}
#endif

void do_treerec(void)
{
    Stack *prog;
    value_t temp;

    TWOPARAMS;
    TWOQUOTES;
    do_cons();
    temp = stack_pop();
    prog = (Stack *)GET_AS_LIST(temp);
    INSTANT(put_treerec);
    do_push(temp);
    treerec();
}
#endif
