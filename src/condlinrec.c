/*
    module  : condlinrec.c
    version : 1.21
    date    : 06/21/22
*/
#ifndef CONDLINREC_C
#define CONDLINREC_C

/**
2780  condlinrec  :  DU 	[ [C1] [C2] .. [D] ]  ->  ...
Each [Ci] is of the form [[B] [T]] or [[B] [R1] [R2]].
Tries each B. If that yields true and there is just a [T], executes T and exit.
If there are [R1] and [R2], executes R1, recurses, executes R2.
Subsequent case are ignored. If no B yields true, then [D] is used.
It is then of the form [[T]] or [[R1] [R2]]. For the former, executes T.
For the latter executes R1, recurses, executes R2.
*/
void condnestrec(Stack *list)
{
    int i, j = 0;
    Stack *quot = 0;

    for (i = vec_size(list) - 1; i >= 0; i--) {
        CHECKLIST(vec_at(list, i));
        quot = (Stack *)GET_AS_LIST(vec_at(list, i));
        if (!i) {
            j = vec_size(quot) - 1;
            break;
        }
        CHECKLIST(vec_back(quot));
        execute_cond((Stack *)GET_AS_LIST(vec_back(quot)), 0);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack_pop())) {
            j = vec_size(quot) - 2;
            break;
        }
    }
    CHECKLIST(vec_at(quot, j));
    execute((Stack *)GET_AS_LIST(vec_at(quot, j)));
    for (i = j - 1; i >= 0; i--) {
        condnestrec(list);
        CHECKLIST(vec_at(quot, i));
        execute((Stack *)GET_AS_LIST(vec_at(quot, i)));
    }
}

#ifdef COMPILING
void put_condnestrec(Stack *list)
{
    static int ident;
    FILE *old;
    Stack *quot;
    int i, j, k, ch;

    printf("void condnestrec_%d(void);", ++ident);
    fprintf(old = program, "condnestrec_%d();", ident);
    program = my_tmpfile();
    fprintf(program, "void condnestrec_%d(void) {", ident);
    for (i = vec_size(list) - 1; i > 0; i--) {
        CHECKLIST(vec_at(list, i));
        quot = (Stack *)GET_AS_LIST(vec_at(list, i));
        CHECKLIST(vec_back(quot));
        compile_cond((Stack *)GET_AS_LIST(vec_back(quot)), 0);
        fprintf(program, "if (GET_AS_BOOLEAN(stack_pop())) {");
        j = vec_size(quot) - 2;
        CHECKLIST(vec_at(quot, j));
        compile((Stack *)GET_AS_LIST(vec_at(quot, j)));
        for (k = j - 1; k >= 0; k--) {
            printstack();
            fprintf(program, "condnestrec_%d();", ident);
            CHECKLIST(vec_at(quot, k));
            compile((Stack *)GET_AS_LIST(vec_at(quot, k)));
        }
        fprintf(program, "return; }");
    }
    CHECKLIST(vec_at(list, 0));
    quot = (Stack *)GET_AS_LIST(vec_at(list, 0));
    j = vec_size(quot) - 1;
    CHECKLIST(vec_at(quot, j));
    compile((Stack *)GET_AS_LIST(vec_at(quot, j)));
    for (k = j - 1; k >= 0; k--) {
        printstack();
        fprintf(program, "condnestrec_%d();", ident);
        CHECKLIST(vec_at(quot, k));
        compile((Stack *)GET_AS_LIST(vec_at(quot, k)));
    }
    fprintf(program, "}");
    print_tmpfile(old);
}
#endif

void do_condlinrec(void)
{
    Stack *prog;

    ONEPARAM;
    LIST;
    CHECKEMPTYLIST(stack[-1]);
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_condnestrec);
    condnestrec(prog);
}
#endif
