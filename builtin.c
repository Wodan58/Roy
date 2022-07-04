/*
    module  : builtin.c
    version : 1.36
    date    : 06/22/22
*/
#include "runtime.h"
#include "runtime.c"

#ifdef REPORT
static double count_execute;

/*
    report_execute - report the number of times the interpreter was called.
*/
static void report_execute(void)
{
    fprintf(stderr, "execute = %.0f\n", count_execute);
}
#endif

/*
    trace - print the stack from bottom to top and the current program.
*/
static void trace(Stack *list, int i)
{
    stack_write();
    printf(" : ");
    writeterm(list, i);
    putchar('\n');
}

/*
    execute_rest - execute the fetch, decode, evaluate cycle.
*/
void execute_rest(Stack *prog, int i)
{
#ifdef COMPILING
    int found;
    Stack *list;
    const char *name;
#endif
    value_t value;
    int type, index;

#ifdef REPORT
    static int first;

    if (!first) {
        first = 1;
        atexit(report_execute);
    }
    count_execute++;
#endif
#ifdef COMPILING
    if (compiling)
        initcompile();
#endif
    if (i == -1)
        i += vec_size(prog);
    for (; i >= 0; i--) {
        if (debugging)
            trace(prog, i);
        value = vec_at(prog, i);
        type = get_type(value);
        switch (type) {
        case ANON_FUNCT_:
            (*GET_AS_ANON_FUNCT(value))();
            break;
/*
    locate by index is faster than lookup by name. That is why user defined
    functions are better registered as INDEX than as USR. What remains for
    USR are undefined functions, that is functions without a body.
*/
#ifdef COMPILING
        case INDEX_:
            index = GET_AS_USR_INDEX(value);
            value = locate(index);
            if (IS_LIST(value)) {
                list = (Stack *)GET_AS_LIST(value);
                if (!compiling)
                    execute(list);
                else {
                    if (vec_getrecur(list) == RECURRING) {
                        name = str_locate(index);
                        name = identifier(name);
                        print(name);
                    } else {
                        vec_setrecur(list, RECURRING);
                        execute(list);
                        vec_setrecur(list, NOT_RECURRING);
                    }
                }
            }
#if 0
            else if (IS_ANON_FUNCT(value))
                (*GET_AS_ANON_FUNCT(value))();
#endif
            else if (undeferror) {
                name = str_locate(index);
                execerror("definition", name);
            }
            break;
#endif
        case USR_:
#ifdef COMPILING
            name = GET_AS_USR_STRING(value);
            value = lookup(name, &found);
            if (found) {
                if (IS_LIST(value))
                    execute((Stack *)GET_AS_LIST(value));
#if 0
                else if (IS_ANON_FUNCT(value))
                    (*GET_AS_ANON_FUNCT(value))();
#endif
                break;
            }
            if (undeferror)
                execerror("definition", name);
            break;
#endif
        case BOOLEAN_:
        case CHAR_:
        case INTEGER_:
        case SET_:
        case STRING_:
        case LIST_:
        case FLOAT_:
        case FILE_:
            do_push(value);
            break;
/*
    The list above is complete as it is; no need for a default clause.
*/
#if 1
        default:
            execerror("valid datatype", "interpreter");
            break;
#endif
        }
    }
}

/*
    execute - execute a list.
*/
void execute(Stack *prog)
{
    execute_rest(prog, -1);
}

/*
    execute_cond - execute a list, but first check whether the stack needs
                   saving and restoring. This check is beneficial to compiled
                   programs. For interpreted programs it may be faster to
                   always backup and restore the stack.
*/
void execute_cond(Stack *prog, int num)
{
    int i;
    Stack *list;

    if ((i = vec_getarity(prog)) == ARITY_UNKNOWN)
        vec_setarity(prog, i = arity(prog, num) == 1);
    if (!i)
        list = stack_copy();       /* make a backup of the stack */
    execute_rest(prog, -1);        /* execute the program */
    if (!i) {
        if (num)
            vec_pop(list);         /* replace the top item of the list ... */
        CHECKSTACK;
        vec_push(list, stack_pop());  /* ... with the top item of the stack */
        stack_from_list(list);     /* restore the modified backup */
    }
}
