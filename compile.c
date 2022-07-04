/*
    module  : compile.c
    version : 1.5
    date    : 07/04/22
*/
#include "joy.h"

FILE *program;

KHASH_MAP_INIT_STR(Decl, char);

/* table with declared symbols */
static khash_t(Decl) *declTab;

typedef struct Node {
    int seqnr, print;
    Stack *node;
} Node;

/* declare vector type */
typedef vector(Node) NodeList;

/* declare node list */
static NodeList *theList;

/*
    init_decl - initialize the list of declared functions.
*/
static void init_decl(void)
{
    declTab = kh_init(Decl);
}

/*
    declare - register a user defined name in declTab.
              The rv value is 1 if this is a new entry;
              0 if the entry was already there.
*/
static void declare(const char *name)
{
    int rv;
    khiter_t key;

    if (is_builtin(name))
        return;
    if (kh_get(Decl, declTab, name) == kh_end(declTab)) {
        key = kh_put(Decl, declTab, name, &rv);
        if (rv)
            kh_value(declTab, key) = 0;
    }
}

/*
    FindNode - store a list and print the instruction that builds the list at
               runtime.
*/
int FindNode(Stack *node)
{
    static int seqnr;
    Node cur;
    int i, empty1, empty2;

    empty1 = !vec_size(node);
    for (i = vec_size(theList) - 1; i >= 0; i--) {
        cur = vec_at(theList, i);
        empty2 = !vec_size(cur.node);
        if (empty1 && empty2)
            return cur.seqnr;
        if (empty1 || empty2)
            continue;
        if (vec_equal(node, cur.node))
            return cur.seqnr;
    }
    cur.seqnr = ++seqnr;
    cur.print = 0;
    cur.node = node;
    vec_push(theList, cur);
    printf("void do_list_%d(void);", seqnr);
    return seqnr;
}

/*
    printlist - print a function that recreates the list at runtime.
*/
static void printlist(FILE *fp, Stack *list, int seqnr)
{
    value_t value;
    int i, j, type;
    const char *name;
    void (*proc)(void);

    fprintf(fp, "void do_list_%d(void)", seqnr);
    fprintf(fp, "{ static Stack *list = 0; if (!list) { vec_init(list);");
    for (i = 0, j = vec_size(list); i < j; i++) {
        value = vec_at(list, i);
        type = get_type(value);
        switch (type) {
        case INDEX_:
            name = str_locate(GET_AS_USR_INDEX(value));
            declare(name);
            name = identifier(name);
            fprintf(fp, "vec_push(list, MAKE_ANON_FUNCT(do_%s));", name);
            break;
        case USR_:
            name = GET_AS_USR_STRING(value);
            declare(name);
            name = identifier(name);
            fprintf(fp, "vec_push(list, MAKE_ANON_FUNCT(do_%s));", name);
            break;
        case ANON_FUNCT_:
            proc = GET_AS_ANON_FUNCT(value);
            name = find(proc);
            declare(name);
            name = identifier(name);
            fprintf(fp, "vec_push(list, MAKE_ANON_FUNCT(do_%s));", name);
            break;
        case BOOLEAN_:
            fprintf(fp,
                "vec_push(list, MAKE_BOOLEAN(%d));", GET_AS_BOOLEAN(value));
            break;
        case CHAR_:
            fprintf(fp,
                "vec_push(list, MAKE_CHAR(%d));", (int)GET_AS_CHAR(value));
            break;
        case INTEGER_:
            fprintf(fp,
                "vec_push(list, MAKE_INTEGER(%ld));", GET_AS_INTEGER(value));
            break;
        case SET_:
            fprintf(fp, "vec_push(list, MAKE_SET(%ld));", GET_AS_SET(value));
            break;
        case STRING_:
            fprintf(fp, "vec_push(list, MAKE_USR_STRING(GC_strdup(");
            writestring(fp, GET_AS_USR_STRING(value));
            fprintf(fp, ")));");
            break;
        case LIST_:
            fprintf(fp, "do_list_%d();", FindNode((Stack *)GET_AS_LIST(value)));
            fprintf(fp, "vec_push(list, stack_pop());");
            break;
        case FLOAT_:
            fprintf(fp, "vec_push(list, MAKE_DOUBLE((double)%g));",
                GET_AS_DOUBLE(value));
            break;
/*
    A FILE_ cannot occur on the stack. The only producer of a FILE_ is fopen,
    but fopen is not executed at compile time.
*/
#if 0
        case FILE_:
            fprintf(fp, "vec_push(list, MAKE_FILE(%p));", GET_AS_FILE(value));
            break;
#endif
        }
    }
    fprintf(fp, "} do_push(MAKE_LIST(list)); }");
}

/*
    PrintNode - print all list functions, avoiding duplicates.
*/
static int PrintNode(FILE *fp)
{
    Node *cur;
    int i, changed = 0;

    for (i = vec_size(theList) - 1; i >= 0; i--) {
        cur = &vec_at(theList, i);
        if (cur->print)
            continue;
        changed = cur->print = 1;
        printlist(fp, cur->node, cur->seqnr);
    }
    return changed;
}

/*
    printstack - print and clear the stack.
*/
void printstack(void)
{
    int i, j;

    for (i = 0, j = vec_size(theStack); i < j; i++)
        printvalue(vec_at(theStack, i));
    stack_clear();
}

/*
    printdecl - print the start of a function.
*/
static void printdecl(const char *name)
{
    fprintf(program, "void do_%s(void) {", name);
}

/*
    compilelib - compile all functions called and not yet printed.
*/
static void compilelib(void)
{
    khiter_t key;
    value_t value;
    const char *name;
    int found, changed;

    library = 1;
    do {
        changed = PrintNode(program);
        for (key = kh_begin(declTab); key != kh_end(declTab); key++) {
            if (kh_exist(declTab, key)) {
                if (kh_value(declTab, key) == 0) {
                    name = kh_key(declTab, key);
                    value = lookup(name, &found);
                    if (found && IS_LIST(value)) {
                        kh_value(declTab, key) = changed = 1;
                        printdecl(identifier(name));
                        compile((Stack *)GET_AS_LIST(value));
                        fprintf(program, "}");
                    }
                }
            }
        }
    } while (changed);
    for (key = kh_begin(declTab); key != kh_end(declTab); key++) {
        if (kh_exist(declTab, key)) {
            if (kh_value(declTab, key) == 0) {
                name = kh_key(declTab, key);
                printdecl(identifier(name));
                fprintf(program, "}");
            }
        }
    }
}

/*
    exitcompile - finish compiler output.
*/
static void exitcompile(void)
{
    int ch;
    khiter_t key;
    const char *name;

    /*
       Finish the program that was started with initcompile.
    */
    fprintf(program, "return 0; }");
    compilelib();
    /*
        Declare user defined functions.
    */
    for (key = kh_begin(declTab); key != kh_end(declTab); key++)
        if (kh_exist(declTab, key)) {
            name = kh_key(declTab, key);
            printf("void do_%s(void);", identifier(name));
        }
    /*
        Print the collected temporary files.
    */
    print_bucket();
    printf("int yyparse(void) {");
    rewind(program);
    while ((ch = fgetc(program)) != EOF)
        putchar(ch);
    fclose(program);
    printf("table_t yytable[] = {");
    /*
        Dump user defined symbols in the symbol table.
    */
    printf("\n/* user */\n");
    for (key = kh_begin(declTab); key != kh_end(declTab); key++)
        if (kh_exist(declTab, key)) {
            name = kh_key(declTab, key);
            printf("{ do_%s, \"%s\" },", identifier(name), name);
        }
    printf("\n/* prim */\n");
    /*
        Dump builtins in the symbol table, those that are actually used.
    */
    dump(0);
    printf("{ 0 } };\n");
    /*
        Dump preprocessor defines that exclude symbols that are not used.
    */
    dump(1);
    printf("#include \"builtin.c\"\n");
    remove_tmpfiles();
}

/*
    initcompile - initialize the compiler.
*/
void initcompile(void)
{
    static int init;
    time_t t;

    if (init)
        return;
    init = 1;
    atexit(exitcompile);
    t = time(0);
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#define RUNTIME\n");
    printf("#include \"runtime.h\"\n");
    program = my_tmpfile();
    init_decl();
}

/*
    printvalue - print the instruction that pushes one value on the stack.
*/
void printvalue(value_t value)
{
    Stack *list;
    int type, seqnr;
    const char *name;
    void (*proc)(void);

    type = get_type(value);
    switch (type) {
    case INDEX_:
        name = str_locate(GET_AS_USR_INDEX(value));
        declare(name);
        name = identifier(name);
        fprintf(program, "do_push(MAKE_ANON_FUNCT(do_%s));", name);
        break;
    case USR_:
        name = GET_AS_USR_STRING(value);
        declare(name);
        name = identifier(name);
        fprintf(program, "do_push(MAKE_ANON_FUNCT(do_%s));", name);
        break;
    case ANON_FUNCT_:
        proc = GET_AS_ANON_FUNCT(value);
        name = find(proc);
        declare(name);
        name = identifier(name);
        fprintf(program, "do_push(MAKE_ANON_FUNCT(do_%s));", name);
        break;
    case BOOLEAN_:
        fprintf(program, "do_push(MAKE_BOOLEAN(%d));", GET_AS_BOOLEAN(value));
        break;
    case CHAR_:
        fprintf(program, "do_push(MAKE_CHAR(%d));", (int)GET_AS_CHAR(value));
        break;
    case INTEGER_:
        fprintf(program, "do_push(MAKE_INTEGER(%ld));", GET_AS_INTEGER(value));
        break;
    case SET_:
        fprintf(program, "do_push(MAKE_SET(%ld));", GET_AS_SET(value));
        break;
    case STRING_:
        fprintf(program, "do_push(MAKE_USR_STRING(GC_strdup(");
        writestring(program, GET_AS_USR_STRING(value));
        fprintf(program, ")));");
        break;
    case LIST_:
        list = (Stack *)GET_AS_LIST(value);
        seqnr = FindNode(list);
        fprintf(program, "do_list_%d();", seqnr);
        break;
    case FLOAT_:
        fprintf(program, "do_push(MAKE_DOUBLE((double)%g));",
            GET_AS_DOUBLE(value));
        break;
/*
    A FILE_ cannot occur on the stack. The only producer of a FILE_ is fopen,
    but fopen is not executed at compile time.
*/
#if 0
    case FILE_:
        fprintf(program, "do_push(MAKE_FILE(%p));", GET_AS_FILE(value));
        break;
#endif
    }
}

/*
    print - print and clear the stack; also print one instruction. No need to
            declare the name, because it must be a builtin.
*/
void print(const char *name)
{
    printstack();
    if (!strncmp(name, "do_", 3))
        name += 3;
    declare(unidentify(name));
    fprintf(program, "do_%s();", name);
}

/*
    compile - the compile function is similar to the execute function, except
              that before and after the compile function the stack is printed
              and cleared.
*/
void compile_rest(Stack *prog, int i)
{
    printstack();
    execute_rest(prog, i);
    printstack();
}

void compile(Stack *prog)
{
    printstack();
    execute(prog);
    printstack();
}

/*
    If the program does not have the correct arity, code that saves and restores
    the stack must be added. The top of the saved stack is replaced with the
    value produced by the program.
*/
void compile_cond(Stack *prog, int start)
{
    int ok;

    ok = arity(prog, start) == 1;
    if (!ok)
        fprintf(program, "{ Stack *list = stack_copy();");
    compile(prog);
    if (!ok) {
        if (start)
            fprintf(program, "vec_pop(list);");
        fprintf(program, "vec_push(list, stack_pop());");
        fprintf(program, "stack_from_list(list); }");
    }
}
