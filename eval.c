/*
    module  : eval.c
    version : 1.6
    date    : 07/22/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "parse.h"

static int uniq;
static FILE *declhdr, *program, *library, *symbols;

static char *types[] = {
    "Boolean",
    "Char",
    "Int"
};

/*
    Start the output file.
*/
static void initcompile(void)
{
    time_t t = time(0);
    printf("/*\n * generated %s */\n", ctime(&t));
    printf("#include \"joy.h\"\n");
    printf("YYSTYPE yylval;\n");
    declhdr = tmpfile();
    program = tmpfile();
    library = tmpfile();
    symbols = tmpfile();
}

/*
    Check that a name consists of alphanumerics or underscore and if not,
    return "op".
*/
static char *scramble(char *str)
{
    int i;

    for (i = 0; str[i]; i++)
	if (isalnum(str[i]) || str[i] == '_')
	    continue;
	else
	    return "op";
    return str;
}

#ifdef DEBUG
static void dumpstack(void)
{
    value_t *top;
    int stk, max_stk;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	top = vec_index(theStack, stk);
	putchar(' ');
	writefactor(top);
    }
}
#endif

static void printlist(node_t *cur, FILE *fp);

/*
 * Print a factor as part of a list to be pushed onto the stack.
 */
static void printfactor(node_t *cur, FILE *fp)
{
    short type;
    symbol_t *tmp;

    fprintf(fp, "cur = mem_alloc();\n");
    type = cur->type;
again:
    switch (type) {
    case Unknown:
	tmp = vec_index(theTable, cur->num);
	type = tmp->type;
	goto again;

    case Builtin:
	tmp = vec_index(theTable, cur->num);
	tmp->recur = 1;
	fprintf(fp, "cur->proc = do_%s;\n", tmp->print ? tmp->print : tmp->str);
	fprintf(fp, "cur->type = Function;\n");
	break;

    case Defined:
	tmp = vec_index(theTable, cur->num);
	if (!tmp->ptr) {
	    fprintf(fp, "cur->str = \"%s\";\n", tmp->str);
	    fprintf(fp, "cur->type = Symbol;\n");
	    break;
	}
	if (!tmp->uniq)
	    tmp->uniq = ++uniq;
	fprintf(fp, "cur->proc = %s_%d;\n", scramble(tmp->str), tmp->uniq);
	fprintf(fp, "cur->type = Function;\n");
	break;

    case Boolean:
    case Char:
    case Int:
	fprintf(fp, "cur->num = %d;\n", cur->num);
	fprintf(fp, "cur->type = %s;\n", types[type - Boolean]);
	break;

    case List:
	printlist(cur->ptr, fp);
	fprintf(fp, "{ value_t *top = vec_pop(theStack);\n");
	fprintf(fp, "cur->ptr = top->ptr;\ncur->type = List; }\n");
	break;

    default:
	fprintf(stderr, "ERROR: unknown type %d in printfactor\n", cur->type);
	break;
    }
    fprintf(fp, "cur->next = list;\n");
    fprintf(fp, "list = cur;\n");
}

/*
 * Print a list on the stack; that is generate instructions that allow the
 * runtime to recreate the list.
 */
void printlist(node_t *cur, FILE *fp)
{
    fprintf(fp, "{ value_t *top;\n");
    if (!cur)
	fprintf(fp, "top = vec_push(theStack);\ntop->ptr = 0;\n");
    else {
	fprintf(fp, "node_t *cur, *list = 0;\n");
	for (cur = reverse(copy(cur)); cur; cur = cur->next)
	    printfactor(cur, fp);
	fprintf(fp, "top = vec_push(theStack);\ntop->ptr = list;\n");
    }
    fprintf(fp, "top->type = List; }\n");
}

/*
 * Push a node onto the stack at runtime. Currently assuming that no symbols
 * ended up on the stack.
 */
static void printnode(value_t *cur, FILE *fp)
{
    short type;

    type = cur->type;
    switch (type) {
    case Boolean:
    case Char:
    case Int:
	fprintf(fp, "do_push(%s, %d);\n", types[type - Boolean], cur->num);
	break;

    case List:
	printlist(cur->ptr, fp);
	break;

    default:
	fprintf(stderr, "ERROR: unknown type %d in printnode\n", cur->type);
	break;
    }
}

/*
 * The contents of the stack are printed before any subsequent actions that may
 * need them. The stack is also emptied.
 */
static void printstack(FILE *fp)
{
    value_t *top;
    int stk, max_stk;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	top = vec_index(theStack, stk);
	printnode(top, fp);
    }
    vec_clear(theStack);
}

/*
 * Following a simple compile scheme, no attempt is made to execute builtins
 * while compiling. Definitions are being followed, unless they are called
 * recursively.
 */
static void printterm(node_t *cur, FILE *fp)
{
    short type;
    value_t *top;
    symbol_t *tmp;

    while (cur) {
	type = cur->type;
#ifdef DEBUG
	if (debugging) {
	    printf("//");
	    dumpstack();
	    printf(" . ");
	    writeterm(cur);
	    printf("\n");
	}
#endif
again:
	switch (type) {
	case Unknown:
	    tmp = vec_index(theTable, cur->num);
	    type = tmp->type;
	    goto again;

	case Builtin:
	    tmp = vec_index(theTable, cur->num);
	    printstack(fp);
	    fprintf(fp, "do_%s();\n", tmp->print ? tmp->print : tmp->str);
	    break;

	case Defined:
	    tmp = vec_index(theTable, cur->num);
	    if (tmp->recur) {
		printstack(fp);
		if (!tmp->uniq)
		    tmp->uniq = ++uniq;
		fprintf(fp, "%s_%d();\n", scramble(tmp->str), tmp->uniq);
	    } else {
		tmp->recur = 1;
		printterm(tmp->ptr, fp);
		tmp->recur = 0;
	    }
	    break;
/*
 * Data items are first pushed onto the stack, because maybe they are needed
 * by a combinator.
 */
	case Boolean:
	case Char:
	case Int:
	case List:
	    top = vec_push(theStack);
	    top->ptr = cur->ptr;
	    top->type = cur->type;
	    break;

	default:
	    fprintf(stderr, "ERROR: unknown type %d in printterm\n", cur->type);
	    break;
	}
	cur = cur->next;
    }
}

/*
    Compile the library.
*/
static void compilelib(FILE *fp)
{
    char *name;
    symbol_t *cur;
    int changed, maxsym, sym, first = 0;

    do {
	maxsym = vec_size(theTable);
	for (changed = sym = 0; sym < maxsym; sym++) {
	    cur = vec_index(theTable, sym);
	    if (!cur->mark && cur->uniq) {
		cur->mark = changed = 1;
		name = scramble(cur->str);
		fprintf(declhdr, "void %s_%d(void);\n", name, cur->uniq);
		fprintf(fp, "void %s_%d(void) {\n", name, cur->uniq);
		printterm(cur->ptr, fp);
		fprintf(fp, "}\n");
		if (!first) {
		    first = 1;
		    fprintf(symbols, "struct {\nvoid (*fun)(void);\n");
		    fprintf(symbols, "char *str;\n} funTable[] = {\n");
		}
		fprintf(symbols, "{ %s_%d, \"%s\"},\n", name, cur->uniq, name);
	    }
	}
    } while (changed);
    do {
	for (sym = 0; sym < maxsym; sym++) {
	    cur = vec_index(theTable, sym);
	    if (!cur->mark && !cur->uniq && cur->recur) {
		name = cur->print ? cur->print : cur->str;
		if (!first) {
		    first = 1;
		    fprintf(symbols, "struct {\nvoid (*fun)(void);\n");
		    fprintf(symbols, "char *str;\n} funTable[] = {\n");
		}
		fprintf(symbols, "{ do_%s, \"%s\"},\n", name, cur->str);
	    }
	}
    } while (changed);
    fprintf(symbols, "{ 0, \"\" }\n};\n");
    fprintf(symbols, "char *lookup(void (*fun)(void)) {\n");
    fprintf(symbols, "int i; for (i = 0; funTable[i].fun; i++)\n");
    fprintf(symbols, "if (fun == funTable[i].fun) break;\n");
    fprintf(symbols, "return funTable[i].str; }\n");
}

/*
    Compile the library and print the 4 files.
*/
static void exitcompile(void)
{
    int ch;

    compilelib(library);
    rewind(declhdr);
    rewind(symbols);
    rewind(program);
    rewind(library);
    while ((ch = fgetc(declhdr)) != EOF)
	putchar(ch);
    while ((ch = fgetc(symbols)) != EOF)
	putchar(ch);
    printf("int main(int argc, char *argv[]) {\n");
    printf("vec_init(theStack);\n");
    printf("if (argc > 1 && !strcmp(argv[1], \"-d\"))\n");
    printf("debugging = 1;\n");
    while ((ch = fgetc(program)) != EOF)
	putchar(ch);
    printf("return 0; }\n");
    while ((ch = fgetc(library)) != EOF)
	putchar(ch);
}

/*
    Compile a term - instead of being executed, commands are printed.
*/
void compile(node_t *cur)
{
    static int init;

    if (!init) {
	init = 1;
	atexit(exitcompile);
	initcompile();
    }
    printterm(cur, program);
#ifdef DEBUG
    if (debugging) {
	printf("//");
	dumpstack();
	printf("\n");
    }
#endif
    printstack(program);
    fprintf(program, "writestack();\n");
}

char *lookup(void (*proc)(void))
{
    return "unknown";
}
