/*
    module  : eval.c
    version : 1.11
    date    : 08/05/18
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

/* runtime symbol table */
function_t funTable[1];

/* runtime function, dummy local copy */
char *lookup(void (*proc)(void), char **body)
{
    return *body = "unknown";
}

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

    for (i = 0; str[i]; i++) {
	if (isalnum(str[i]) || str[i] == '_')
	    continue;
	return "op";
    }
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
    char *str;
    short type;
    node_t *ptr;
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

	case Expression:
	    printstack(fp);
	    type = 0;
	    for (ptr = cur->ptr->ptr; ptr; ptr = ptr->next)
		type++;
	    fprintf(fp, "if (vec_size(theStack) >= %d) {\n", type);
	    for (ptr = cur->ptr->ptr; ptr; ptr = ptr->next) {
		if (ptr->type == Cons) {
		    tmp = vec_index(theTable, ptr->ptr->num);
		    fprintf(fp, "value_t %s;\n", str = tmp->str);
		    fprintf(fp, "value_t %s_", str);
		    tmp = vec_index(theTable, ptr->ptr->next->num);
		    fprintf(fp, "%s = *vec_pop(theStack);\n", tmp->str);
		    fprintf(fp, "value_t %s;\n", tmp->str);
		    fprintf(fp, "%s.ptr = %s_%s.ptr->ptr;\n", str, str,
			    tmp->str);
		    fprintf(fp, "%s.type = %s_%s.ptr->type;\n", str, str,
			    tmp->str);
		    fprintf(fp, "%s.ptr = %s_%s.ptr->next;\n", tmp->str, str,
			    tmp->str);
		    fprintf(fp, "%s.type = List;\n", tmp->str);
		} else {
		    tmp = vec_index(theTable, ptr->num);
		    fprintf(fp, "value_t %s = *vec_pop(theStack);\n", tmp->str);
		}
	    }
	    printterm(cur->ptr->next, fp);
	    fprintf(fp, "}\n");
	    break;

	case Parameter:
	    tmp = vec_index(theTable, cur->num);
	    fprintf(fp, "*vec_push(theStack) = %s;\n", tmp->str);
	    break;

	case Cons:
	    tmp = vec_index(theTable, cur->ptr->num);
	    fprintf(fp, "{ value_t %s_", str = tmp->str);
	    tmp = vec_index(theTable, cur->ptr->next->num);
	    fprintf(fp, "%s;\n", tmp->str);
	    fprintf(fp, "%s_%s.ptr = cons(&%s, %s.ptr);\n", str, tmp->str,
							    str, tmp->str);
	    fprintf(fp, "%s_%s.type = List;\n", str, tmp->str);
	    fprintf(fp, "*vec_push(theStack) = %s_%s; }\n", str, tmp->str);
	    break;

	default:
	    fprintf(stderr, "ERROR: unknown type %d in printterm\n", cur->type);
	    break;
	}
	cur = cur->next;
    }
}

void printbodyterm(node_t *cur, FILE *fp);

void printbodyfactor(value_t *cur, FILE *fp)
{
    char *body;
    short type;
    node_t *ptr;
    symbol_t *tmp;

    type = cur->type;
again:
    switch (type) {
    case Unknown:
	tmp = vec_index(theTable, cur->num);
	type = tmp->type;
	goto again;

    case Builtin:
    case Defined:
	tmp = vec_index(theTable, cur->num);
	if (type == Defined)
	    tmp->used = 1;
	fprintf(fp, "%s", tmp->str);
	break;

    case Boolean:
	fprintf(fp, cur->num ? "true" : "false");
	break;

    case Char:
	fprintf(fp, "'\\\\%d", cur->num);
	break;

    case Int:
	fprintf(fp, "%d", cur->num);
	break;

    case List:
	fputc('[', fp);
	printbodyterm(cur->ptr, fp);
	fputc(']', fp);
	break;

    case Function:
	fprintf(fp, "%s", lookup(cur->proc, &body));
	break;

    case Symbol:
	fprintf(fp, "%s", cur->str);
	break;

    case Expression:
	fprintf(fp, "LET");
	for (ptr = cur->ptr->ptr; ptr; ptr = ptr->next) {
	    if (ptr->type == Cons) {
		tmp = vec_index(theTable, ptr->ptr->num);
		fprintf(fp, " %s:", tmp->str);
		tmp = vec_index(theTable, ptr->ptr->next->num);
		fprintf(fp, "%s", tmp->str);
	    } else {
		tmp = vec_index(theTable, ptr->num);
		fprintf(fp, " %s", tmp->str);
	    }
	}
	fprintf(fp, " IN ");
	printbodyterm(cur->ptr->next, fp);
	fprintf(fp, " END");
	break;

    case Parameter:
	tmp = vec_index(theTable, cur->num);
	fprintf(fp, "%s", tmp->str);
	break;

    case Cons:
	tmp = vec_index(theTable, cur->ptr->num);
	fprintf(fp, " %s:", tmp->str);
	tmp = vec_index(theTable, cur->ptr->next->num);
	fprintf(fp, "%s", tmp->str);
	break;

    default:
	fprintf(stderr, "ERROR: unknown type %d in printbodyfactor\n",
		cur->type);
	break;
    }
}

void printbodyterm(node_t *cur, FILE *fp)
{
    value_t temp;

    while (cur) {
	temp.ptr = cur->ptr;
	temp.type = cur->type;
	printbodyfactor(&temp, fp);
	if (cur->next)
	    fputc(' ', fp);
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
	    if (!cur->mark && (cur->uniq || cur->used)) {
		cur->mark = changed = 1;
		name = scramble(cur->str);
		if (cur->uniq) {
		    fprintf(declhdr, "void %s_%d(void);\n", name, cur->uniq);
		    fprintf(fp, "void %s_%d(void) {\n", name, cur->uniq);
		} else {
		    fprintf(declhdr, "void %s(void);\n", name);
		    fprintf(fp, "void %s(void) {\n", name);
		}
		printterm(cur->ptr, fp);
		printstack(fp);
		fprintf(fp, "}\n");
		if (!first) {
		    first = 1;
		    fprintf(symbols, "function_t funTable[] = {\n");
		}
		if (cur->uniq)
		    fprintf(symbols, "{ %s_%d, \"%s\", \"", name, cur->uniq,
			    cur->str);
		else
		    fprintf(symbols, "{ %s, \"%s\", \"", name, cur->str);
		printbodyterm(cur->ptr, symbols);
		fprintf(symbols, "\" },\n");
	    }
	}
    } while (changed);
    for (sym = 0; sym < maxsym; sym++) {
	cur = vec_index(theTable, sym);
	if (cur->type == Builtin) {
	    name = cur->print ? cur->print : cur->str;
	    if (!first) {
		first = 1;
		fprintf(symbols, "function_t funTable[] = {\n");
	    }
	    fprintf(symbols, "{ do_%s, \"%s\", 0 },\n", name, cur->str);
	}
    }
    fprintf(symbols, "{ 0, \"\" }\n};\n");
    fprintf(symbols, "char *lookup(void (*proc)(void), char **body) {\n");
    fprintf(symbols, "int i; for (i = 0; funTable[i].proc; i++)\n");
    fprintf(symbols, "if (funTable[i].proc == proc) break;\n");
    fprintf(symbols, "*body = funTable[i].body;\n");
    fprintf(symbols, "return funTable[i].name; }\n");
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
