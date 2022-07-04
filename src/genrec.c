/*
    module  : genrec.c
    version : 1.20
    date    : 06/21/22
*/
#ifndef GENREC_C
#define GENREC_C

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#include "cons.c"

/**
2760  genrec  :  DDDDU	[B] [T] [R1] [R2]  ->  ...
Executes B, if that yields true, executes T.
Else executes R1 and then [[[B] [T] [R1] R2] genrec] R2.
*/
void genrec(void)
{
    static value_t _genrec;
    int size;
    Stack *prog;

    /*
        Initialize _genrec, if not already done.
    */
    if (IS_INITIAL(_genrec)) {
        do_push(MAKE_ANON_FUNCT(genrec));
        vec_init(prog);
        do_push(MAKE_LIST(prog));
        do_cons();
        _genrec = stack_pop();
#ifdef COMPILING
        enter("_genrec", "", genrec);
#endif
    }
    prog = (Stack *)GET_AS_LIST(stack_pop());
    size = vec_size(prog);
    execute_cond((Stack *)GET_AS_LIST(vec_back(prog)), 0);
    CHECKSTACK;
    if (GET_AS_BOOLEAN(stack_pop()))
        execute((Stack *)GET_AS_LIST(vec_at(prog, size - 2)));
    else {
        execute((Stack *)GET_AS_LIST(vec_at(prog, size - 3)));
        do_push(MAKE_LIST(prog));
        do_push(_genrec);
        do_cons();
        execute_rest(prog, size - 4);
    }
}

#ifdef COMPILING
void put_genrec(Stack *prog)
{
    static int ident;
    FILE *old;
    int ch, size;

    set_inuse("genrec");
    size = vec_size(prog);
    printf("void genrec(void);");
    printf("void genrec_%d(void);", ++ident);
    fprintf(old = program, "genrec_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void genrec_%d(void) { Stack *list;", ident);
    compile_cond((Stack *)GET_AS_LIST(vec_back(prog)), 0);
    fprintf(program, "if (GET_AS_BOOLEAN(stack_pop())) {");
    compile((Stack *)GET_AS_LIST(vec_at(prog, size - 2)));
    fprintf(program, "} else {");
    compile((Stack *)GET_AS_LIST(vec_at(prog, size - 3)));
    fprintf(program, "do_list_%d();", FindNode(prog));
    fprintf(program, "do_push(MAKE_ANON_FUNCT(genrec));");
    fprintf(program, "vec_init(list); do_push(MAKE_LIST(list));");
    fprintf(program, "do_cons(); do_cons();");
    compile_rest(prog, size - 4);
    fprintf(program, "} }");
    print_tmpfile(old);
}
#endif

void do_genrec(void)
{
    Stack *prog;
    value_t temp;

    FOURPARAMS;
    FOURQUOTES;
    do_cons();
    do_cons();
    do_cons();
    temp = stack_pop();
    prog = (Stack *)GET_AS_LIST(temp);
    INSTANT(put_genrec);
    do_push(temp);
    genrec();
}
#endif
