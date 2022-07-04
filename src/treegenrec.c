/*
    module  : treegenrec.c
    version : 1.15
    date    : 06/21/22
*/
#ifndef TREEGENREC_C
#define TREEGENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

/**
2910  treegenrec  :  DDDDU	T [O1] [O2] [C]  ->  ...
T is a tree. If T is a leaf, executes O1.
Else executes O2 and then [[[O1] [O2] C] treegenrec] C.
*/
void treegenrec(void)
{
    static value_t _treegenrec;
    Stack *prog;

    if (IS_INITIAL(_treegenrec)) {
        do_push(MAKE_ANON_FUNCT(treegenrec));
        vec_init(prog);
        do_push(MAKE_LIST(prog));
        do_cons();
        _treegenrec = stack_pop();
#ifdef COMPILING
        enter("_treegenrec", "", treegenrec);
#endif
    }
    prog = (Stack *)GET_AS_LIST(stack_pop());
    ONEPARAM;
    if (IS_LIST(stack[-1])) {
        execute((Stack *)GET_AS_LIST(vec_at(prog, vec_size(prog) - 2)));
        do_push(MAKE_LIST(prog));
        do_push(_treegenrec);
        do_cons();
        execute_rest(prog, vec_size(prog) - 3);
    } else
        execute((Stack *)GET_AS_LIST(vec_back(prog)));
}

#ifdef COMPILING
void put_treegenrec(Stack *prog)
{
    static int ident;
    int ch;
    FILE *old;

    set_inuse("treegenrec");
    printf("void treegenrec(void);");
    printf("void treegenrec_%d(void);", ++ident);
    fprintf(old = program, "treegenrec_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void treegenrec_%d(void) { Stack *list;", ident);
    fprintf(program, "if (IS_LIST(stack[-1])) {");
    compile((Stack *)GET_AS_LIST(vec_at(prog, vec_size(prog) - 2)));
    fprintf(program, "do_list_%d();", FindNode(prog));
    fprintf(program, "do_push(MAKE_ANON_FUNCT(treegenrec)); vec_init(list);");
    fprintf(program, "do_push(MAKE_LIST(list)); do_cons(); do_cons();");
    compile_rest(prog, vec_size(prog) - 3);
    fprintf(program, "} else {");
    compile((Stack *)GET_AS_LIST(vec_back(prog)));
    fprintf(program, "} }");
    print_tmpfile(old);
}
#endif

void do_treegenrec(void)
{
    Stack *prog;
    value_t temp;

    THREEPARAMS;
    THREEQUOTES;
    do_cons();
    do_cons();
    temp = stack_pop();
    prog = (Stack *)GET_AS_LIST(temp);
    INSTANT(put_treegenrec);
    do_push(temp);
    treegenrec();
}
#endif
