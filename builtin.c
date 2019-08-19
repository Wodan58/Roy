/*
    module  : builtin.c
    version : 1.19
    date    : 07/19/19
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "stack.h"
#include "parse.h"

#ifdef COMPILING
#define kcalloc(N,Z)	GC_MALLOC((N)*(Z))
#include "khash.h"

#define STACK(n)	(vec_size(theStack) < (n))
#define COMPILE	\
	if (compiling) { printstack(program, __func__); return; }
#define UNARY	\
	if (compiling && STACK(1)) { printstack(program, __func__); return; }
#define UNARY0	\
	if (compiling && STACK(1)) { printstack(program, __func__); return 0; }
#define BINARY	\
	if (compiling && STACK(2)) { printstack(program, __func__); return; }
#define TERNARY	\
	if (compiling && STACK(3)) { printstack(program, __func__); return; }
#define QUATERN	\
	if (compiling && STACK(4)) { printstack(program, __func__); return; }
#define CHECK2	\
	if (compiling && (vec_back(theStack) < 0 || vec_back(theStack) > SMALLINT)) \
	printstack(program, 0)
#define SYNCING	\
	if (compiling) fprintf(program, "clear_stack();")
#else
#define COMPILE
#define UNARY
#define UNARY0
#define BINARY
#define TERNARY
#define QUATERN
#define CHECK2
#define SYNCING

YYSTYPE yylval;
#endif

intptr_t lookup(const char *str);	/* parse.c */
void dump(void);

int yylex(void);			/* yylex.c */
void yyerror(char *str);

void init_heap(void);			/* print.c */
void writefactor(intptr_t Value);
void writeterm(Stack *List, int Index);

void execute(Stack *ptr);

extern int g_argc;
extern char **g_argv;

#ifdef VECTOR
/* declare data stack */
static Stack *theStack;

/* make stack addressing possible */
#define stack	vec_overtop(theStack)
#else
#define MEMORYMAX	100

intptr_t memory[MEMORYMAX], *stack;
#endif

#ifdef COMPILING
static FILE *program;

KHASH_MAP_INIT_STR(Decl, char);

static khash_t(Decl) *declTab;

typedef struct Node {
    int seqnr, print;
    Stack *node;
} Node;

/* declare vector type */
typedef vector(Node) NodeList;

/* declare node list */
static NodeList *theList;
#endif

void reverse(Stack *List)
{
    int i, j;
    intptr_t *PValue1, *PValue2, Temp;

    for (i = 0, j = vec_size(List) - 1; i < j; i++, j--) {
	PValue2 = vec_index(List, j);
	PValue1 = vec_index(List, i);
	Temp = *PValue1;
	*PValue1 = *PValue2;
	*PValue2 = Temp;
    }
}

void init_stack(void)
{
#ifdef VECTOR
    vec_init(theStack);
#else
    stack = memory;
#endif
#ifdef COMPILING
    declTab = kh_init(Decl);
    vec_init(theList);
#endif
}

void clear_stack(void)
{
#ifdef VECTOR
    vec_clear(theStack);
#else
    stack = memory;
#endif
}

#ifdef COMPILING
const char *identifier(const char *str)
{
    switch (*str) {
    case '+': return "add";
    case '*': return "mul";
    case '=': return "eql";
    case '<': if (str[1] == '=')
		  return "leq";
	      return "lss";
    case '-': return "sub";
    case '/': return "div";
    case '>': if (str[1] == '=')
		  return "geq";
	      return "gtr";
    default : return str;
    }
}

int FindNode(Stack *node)
{
    static int seqnr;
    int i;
    Node *cur;

    for (i = vec_size(theList) - 1; i >= 0; i--) {
	cur = vec_index(theList, i);
	if (vec_equal(node, cur->node))
	    return cur->seqnr;
    }
    cur = vec_push(theList);
    cur->seqnr = ++seqnr;
    cur->print = 0;
    cur->node = node;
    printf("void do_list_%d(void);", seqnr);
    return seqnr;
}

void printlist(FILE *fp, Stack *List, int seqnr)
{
    int i, j, rv;
    khiter_t key;
    intptr_t Value;
    const char *Name;

    fprintf(fp, "void do_list_%d(void)", seqnr);
    fprintf(fp, "{ static Stack *List = 0; intptr_t *PValue;");
    fprintf(fp, "if (!List) { vec_init(List);");
    for (j = vec_size(List), i = 0; i < j; i++) {
	Value = vec_at(List, i);
	fprintf(fp, "PValue = vec_push(List);");
	if (Value >= 0 && Value <= SMALLINT)
	    fprintf(fp, "*PValue = %" PRIdPTR ";", Value);
	else if ((Value & JLAP_INVALID) == 0) {
	    fprintf(fp, "do_list_%d();", FindNode((Stack *)Value));
	    fprintf(fp, "*PValue = do_pop();");
	} else {
	    Name = (const char *)(Value & ~JLAP_INVALID);
	    if ((Value = lookup(Name)) == 0)
		fprintf(fp, "*PValue = (intptr_t)\"%s\";", Name);
	    else {
		if ((Value & JLAP_INVALID) == 0) {
		    key = kh_put(Decl, declTab, Name, &rv);
		    if (rv)
			kh_value(declTab, key) = 0;
		}
		fprintf(fp, "*PValue = (intptr_t)do_%s | JLAP_INVALID;",
			identifier(Name));
	    }
	}
    }
    fprintf(fp, "} do_push((intptr_t)List); }");
}

int PrintNode(FILE *fp)
{
    int i, changed = 0;
    Node *cur;

    for (i = vec_size(theList) - 1; i >= 0; i--) {
	cur = vec_index(theList, i);
	if (cur->print)
	    continue;
	changed = cur->print = 1;
	printlist(fp, cur->node, cur->seqnr);
    }
    return changed;
}

void compilelib(void)
{
    khiter_t key;
    intptr_t Value;
    const char *Name;
    char changed, flag;

    do {
	changed = PrintNode(program);
	for (key = kh_begin(declTab); key != kh_end(declTab); key++) {
	    if (kh_exist(declTab, key)) {
		if ((flag = kh_value(declTab, key)) == 0) {
		    kh_value(declTab, key) = changed = 1;
		    Name = kh_key(declTab, key);
		    if ((Value = lookup(Name)) != 0) {
			if (Value & ~JLAP_INVALID) {
			    fprintf(program, "void do_%s(void) {", identifier(Name));
			    vec_clear(theStack);
			    execute((Stack *)Value);
			    fprintf(program, "}");
			}
		    }
		}
	    }
	}
    } while (changed);
}

void exitcompile(void)
{
    int ch;
    khiter_t key;
    const char *Name;

    fprintf(program, "return 0; }");
    compilelib();
    for (key = kh_begin(declTab); key != kh_end(declTab); key++)
	if (kh_exist(declTab, key)) {
	    Name = kh_key(declTab, key);
	    printf("void do_%s(void);", identifier(Name));
	}
    printf("int yyparse() {");
    rewind(program);
    while ((ch = fgetc(program)) != EOF)
	putchar(ch);
    printf("YYTABLE table[] = {");
    for (key = kh_begin(declTab); key != kh_end(declTab); key++)
	if (kh_exist(declTab, key)) {
	    Name = kh_key(declTab, key);
	    printf("{ \"%s\", do_%s, \"", Name, identifier(Name));
	    writeterm((Stack *)lookup(Name), -1);
	    printf("\"},");
	}
    dump();
    printf("{ 0 } };\n");
}

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
    printf("#include \"builtin.c\"\n");
    program = tmpfile();
}

void printstack(FILE *fp, const char *str)
{
    int rv;
    khiter_t key;
    const char *Name;
    intptr_t Value, Index, Limit;

    Limit = vec_size(theStack);
    if (!str)
	Limit--;
    for (Index = 0; Index < Limit; Index++) {
	Value = vec_at(theStack, Index);
	if (Value >= 0 && Value <= SMALLINT)
	    fprintf(fp, "do_push(%" PRIdPTR ");", Value);
	else if ((Value & JLAP_INVALID) == 0)
	    fprintf(fp, "do_list_%d();", FindNode((Stack *)Value));
	else {
	    Name = (const char *)(Value & ~JLAP_INVALID);
	    if ((Value = lookup(Name)) == 0)
		fprintf(fp, "do_push((intptr_t)\"%s\");", Name);
	    else {
		if ((Value & JLAP_INVALID) == 0) {
		    key = kh_put(Decl, declTab, Name, &rv);
		    if (rv)
			kh_value(declTab, key) = 0;
		}
		fprintf(fp, "do_push((intptr_t)\"%s\");", Name);
	    }
	}
    }
    if (str)
	fprintf(fp, "%s();", str);
    else if (vec_size(theStack))
	fprintf(fp, "do_push(%" PRIdPTR ");", vec_back(theStack));
    vec_clear(theStack);
}
#endif

void do_push(intptr_t Value)
{
#ifdef VECTOR
    vec_add(theStack, Value);
#else
    *stack++ = Value;
#endif
}

void do_zap(void)
{
#ifdef VECTOR
    vec_pop_back(theStack);
#else
    --stack;
#endif
}

void do_add(void)
{
    BINARY;
    stack[-2] += stack[-1];
    do_zap();
    CHECK2;
}

void do_mul(void)
{
    BINARY;
    stack[-2] *= stack[-1];
    do_zap();
    CHECK2;
}

void do_eql(void)
{
    BINARY;
    stack[-2] = stack[-2] == stack[-1];
    do_zap();
}

void do_swap(void)
{
    intptr_t Temp;

    BINARY;
    Temp = stack[-1];
    stack[-1] = stack[-2];
    stack[-2] = Temp;
}

void do_lss(void)
{
    BINARY;
    stack[-2] = stack[-2] < stack[-1];
    do_zap();
}

void do_or(void)
{
    BINARY;
    stack[-2] |= stack[-1];
    do_zap();
}

void do_and(void)
{
    BINARY;
    stack[-2] &= stack[-1];
    do_zap();
}

void do_not(void)
{
    UNARY;
    stack[-1] = !stack[-1];
}

intptr_t do_pop(void)
{
    UNARY0;
#ifdef VECTOR
    return *vec_pop(theStack);
#else
    return *--stack;
#endif
}

void do_step(void)
{
    int i;
    Stack *Prog, *Quot;

    BINARY;
    Prog = (Stack *)do_pop();
    Quot = (Stack *)do_pop();
    for (i = vec_size(Quot) - 1; i >= 0; i--) {
	do_push(vec_at(Quot, i));
	execute(Prog);
    }
}

void do_cons(void)
{
    Stack *Quot;

    BINARY;
    if (stack[-1])
	vec_copy((Stack *)stack[-1], Quot);
    else
	vec_init(Quot);
    *vec_push(Quot) = stack[-2];
    stack[-2] = (intptr_t)Quot;
    do_zap();
}

void do_dip(void)
{
    Stack *Prog;
    intptr_t Value;

    BINARY;
    Prog = (Stack *)do_pop();
    Value = do_pop();
    execute(Prog);
    do_push(Value);
}

void do_i(void)
{
    UNARY;
    execute((Stack *)do_pop());
}

void do_dup(void)
{
    UNARY;
    do_push(stack[-1]);
}

void do_uncons(void)
{
    Stack *list, *quot;

    UNARY;
    list = (Stack *)stack[-1];
    stack[-1] = vec_back(list);
    vec_next(list, quot);
    do_push(vec_empty(quot) ? 0 : (intptr_t)quot);
}

void do_index(void)
{
    int index;
    Stack *Quot;

    BINARY;
    Quot = (Stack *)do_pop();
    index = vec_size(Quot) - 1 - stack[-1];
    stack[-1] = vec_at(Quot, index);
}

void do_put(void)
{
    COMPILE;
#ifdef VECTOR
    if (vec_size(theStack))
#else
    if (stack > memory)
#endif
	writefactor(do_pop());
}

void do_stop(void)
{
    COMPILE;
#ifdef VECTOR
    if (vec_size(theStack)) {
#else
    if (stack > memory) {
#endif
	writefactor(do_pop());
	printf("\n");
    }
}

void do_putch(void)
{
    COMPILE;
    putchar(do_pop());
}

#ifdef COMPILING
void do_get(void)
{
    yylex();
    do_push(yylval.num);
}
#endif

void do_sub(void)
{
    BINARY;
    stack[-2] -= stack[-1];
    do_zap();
    CHECK2;
}

#if 0
void do_div(void)
{
    BINARY;
    stack[-2] /= stack[-1];
    do_zap();
    CHECK2;
}
#endif

void do_stack(void)
{
#ifndef VECTOR
    intptr_t *mem;
#endif
    Stack *Quot = 0;

    UNARY;
#ifdef VECTOR
    vec_copy(theStack, Quot);
#else
    for (mem = memory; mem < stack; mem++) {
	if (!Quot)
	    vec_init(Quot);
	vec_add(Quot, *mem);
    }
#endif
    do_push((intptr_t)Quot);
}

void do_unstack(void)
{
#ifndef VECTOR
    int i, j;
#endif
    Stack *Quot;

    SYNCING;
    UNARY;
    Quot = (Stack *)do_pop();
#ifdef VECTOR
    if (!Quot)
	vec_clear(theStack);
    else
	vec_copy(Quot, theStack);
#else
    stack = memory;
    for (j = vec_size(Quot) - 1, i = 0; i <= j; i++)
	*stack++ = vec_at(Quot, i);
#endif
}

void do_body(void)
{
#ifdef COMPILING
    const char *Name;

    UNARY;
#ifdef COMPILING
    Name = (const char *)(stack[-1] & ~JLAP_INVALID);
#else
    Name = (const char *)stack[-1];
#endif
    stack[-1] = lookup(Name);
#endif
}

void do_lt(void)
{
    BINARY;
    stack[-2] = strcmp((char *)(stack[-2] & ~JLAP_INVALID),
		       (char *)(stack[-1] & ~JLAP_INVALID)) < 0;
    do_zap();
}

void do_put_bool(void)
{
    COMPILE;
    printf(do_pop() ? "true" : "false");
}

void do_put_int(void)
{
    COMPILE;
    printf("%" PRIdPTR, do_pop());
}

#if 0
void do_put_str(void)
{
    COMPILE;
    printf("%s", (char *)do_pop());
}
#endif

#ifdef COMPILING
void dumpstack(void)
{
    intptr_t Value, Index, Limit;

    Limit = vec_size(theStack);
    for (Index = 0; Index < Limit; Index++) {
	Value = vec_at(theStack, Index);
	writefactor(Value);
	if (Index < Limit - 1)
	    putchar(' ');
    }
}

void trace(Stack *List, int Index)
{
    dumpstack();
    printf(" : ");
    writeterm(List, Index);
    printf(" ;\n");
}
#endif

void execute(Stack *List)
{
    int i;
    intptr_t Value;

#ifdef COMPILING
    if (compiling)
	initcompile();
#endif
    for (i = vec_size(List) - 1; i >= 0; i--) {
#ifdef COMPILING
	if (debugging)
	    trace(List, i);
#endif
	Value = vec_at(List, i);
	if ((Value >= 0 && Value <= SMALLINT) || ((Value & JLAP_INVALID) == 0))
	    do_push(Value);
	else {
#ifdef COMPILING
	    Value = lookup((const char *)(Value & ~JLAP_INVALID));
	    if ((Value & JLAP_INVALID) == 0)
		execute((Stack *)Value);
	    else
#endif
		(*(void (*)(void))(Value & ~JLAP_INVALID))();
	}
    }
}
