/*
    module  : node.c
    version : 1.10
    date    : 07/31/18
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "node.h"
#include "parse.h"
#include "builtin.h"

/* global variables */
int compiling, debugging;

/* dynamic arrays */
Stack *theStack;
Table *theTable;

/* local functions */
static void initsym(void);
static void dump(void);

/*
 * Add a symbol to the symbol table.
 */
static symbol_t *addsym(char *str)
{
    symbol_t *cur;

    cur = vec_push(theTable);
    cur->str = str;
    cur->ptr = 0;
    cur->type = Unknown;
    cur->uniq = cur->mark = cur->recur = cur->used = 0;
    cur->print = 0;
    return cur;
}

/*
 * Initialise the symbol table with builtins.
 */
static void initsym(void)
{
    symbol_t *cur;

    vec_init(theTable);

    cur = addsym("false");
    cur->type = Builtin;
    cur->proc = do_false;

    cur = addsym("true");
    cur->type = Builtin;
    cur->proc = do_true;

    cur = addsym("+");
    cur->type = Builtin;
    cur->proc = do_add;
    cur->print = "add";

    cur = addsym("*");
    cur->type = Builtin;
    cur->proc = do_mul;
    cur->print = "mul";

    cur = addsym("-");
    cur->type = Builtin;
    cur->proc = do_sub;
    cur->print = "sub";

    cur = addsym("/");
    cur->type = Builtin;
    cur->proc = do_div;
    cur->print = "div";

    cur = addsym("=");
    cur->type = Builtin;
    cur->proc = do_eql;
    cur->print = "eql";

    cur = addsym("<");
    cur->type = Builtin;
    cur->proc = do_lss;
    cur->print = "lss";

    cur = addsym("swap");
    cur->type = Builtin;
    cur->proc = do_swap;

    cur = addsym("and");
    cur->type = Builtin;
    cur->proc = do_and;

    cur = addsym("or");
    cur->type = Builtin;
    cur->proc = do_or;

    cur = addsym("not");
    cur->type = Builtin;
    cur->proc = do_not;

    cur = addsym("step");
    cur->type = Builtin;
    cur->proc = do_step;

    cur = addsym("cons");
    cur->type = Builtin;
    cur->proc = do_cons;

    cur = addsym("dip");
    cur->type = Builtin;
    cur->proc = do_dip;

    cur = addsym("i");
    cur->type = Builtin;
    cur->proc = do_i;

    cur = addsym("dup");
    cur->type = Builtin;
    cur->proc = do_dup;

    cur = addsym("uncons");
    cur->type = Builtin;
    cur->proc = do_uncons;

    cur = addsym("pop");
    cur->type = Builtin;
    cur->proc = do_pop;

    cur = addsym("index");
    cur->type = Builtin;
    cur->proc = do_index;

    cur = addsym("put");
    cur->type = Builtin;
    cur->proc = do_put;

    cur = addsym("get");
    cur->type = Builtin;
    cur->proc = do_get;

    cur = addsym("stack");
    cur->type = Builtin;
    cur->proc = do_stack;

    cur = addsym("unstack");
    cur->type = Builtin;
    cur->proc = do_unstack;

    cur = addsym("body");
    cur->type = Builtin;
    cur->proc = do_body;
}

/*
    Search a symbol in the symbol table.
    Create a new entry when not found.
    Return the index in the symbol table.
*/
int enterdef(char *str, node_t *ptr)
{
    int sym;
    symbol_t *cur;

    if (!theTable)
	initsym();
    for (sym = vec_size(theTable) - 1; sym >= 0; sym--) {
	cur = vec_index(theTable, sym);
	if (cur->type == Parameter)
	    continue;
	if (!strcmp(cur->str, str)) {
	    if (ptr) {
		cur->ptr = ptr;
		cur->type = Defined;
	    }
	    return sym;
	}
    }
    cur = addsym(str);
    cur->ptr = ptr;
    cur->type = Defined;
    return vec_size(theTable) - 1;
}

/*
    Allocate a node of type List.
*/
node_t *newlist(node_t *ptr)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->ptr = ptr;
    cur->type = List;
    return cur;
}

/*
    Allocate a node of any other type.
*/
node_t *newnode(int type, int value)
{
    node_t *cur;
    symbol_t *tmp;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->num = value;
    cur->type = type;
    return cur;
}

/*
    Allocate a node of type Symbol.
*/
node_t *newsymbol(char *str)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->str = str;
    cur->type = Symbol;
    return cur;
}

/*
    Allocate a node of type Function.
*/
node_t *newfunction(void (*proc)(void))
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->proc = proc;
    cur->type = Function;
    return cur;
}

/*
    Allocate a node of type Expression.
*/
node_t *newexpression(node_t *parm, node_t *list)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    if ((cur->ptr = mem_alloc()) == 0)
	return 0;
    cur->ptr->ptr = parm;
    cur->ptr->next = list;
    cur->type = Expression;
    return cur;
}

/*
    Allocate a node of parameter type.
*/
node_t *newparameter(char *str)
{
    node_t *cur;
    int sym = -1;
    symbol_t *tmp;

    if (!theTable)
	initsym();
    for (sym = vec_size(theTable) - 1; sym >= 0; sym--) {
	 tmp = vec_index(theTable, sym);
	 if (tmp->type == Parameter && !strcmp(tmp->str, str))
	     break;
    }
    if (sym == -1) {
	tmp = addsym(str);
	tmp->type = Parameter;
	sym = vec_size(theTable) - 1;
    }
    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->num = sym;
    cur->type = Parameter;
    return cur;
}

/*
    Concatenate two lists.
*/
#if 0
node_t *concat(node_t *root, node_t *next)
{
    node_t *cur = root;

    if (cur) {
	while (cur->next)
	    cur = cur->next;
	cur->next = next;
    }
    return root;
}
#endif

/*
    Copy a list.
*/
node_t *copy(node_t *node)
{
    node_t *root = 0, **cur;

    for (cur = &root; node; node = node->next) {
	if ((*cur = mem_alloc()) == 0)
	    return 0;
	**cur = *node;
	cur = &(*cur)->next;
	*cur = 0;
    }
    return root;
}

/*
    Copy a node.
*/
node_t *cons(value_t *node, node_t *next)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->ptr = node->ptr;
    cur->type = node->type;
    cur->next = next;
    return cur;
}

/*
    Copy the stack to a list.
*/
node_t *stk2lst(void)
{
    value_t *top;
    int stk, max_stk;
    node_t *root = 0, *cur;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	if ((cur = mem_alloc()) == 0)
	    return 0;
	top = vec_index(theStack, stk);
	cur->ptr = top->ptr;
	cur->type = top->type;
	cur->next = root;
	root = cur;
    }
    return root;
}

/*
    Replace the stack by a list.
*/
void lst2stk(node_t *root)
{
    node_t *cur;
    value_t *top;

    vec_clear(theStack);
    for (cur = reverse(root); cur; cur = cur->next) {
	top = vec_push(theStack);
	top->ptr = cur->ptr;
	top->type = cur->type;
    }
}

/*
    Reverse a list.
*/
node_t *reverse(node_t *cur)
{
    node_t *old = 0, *prev;

    while (cur) {
	prev = cur;
	cur = cur->next;
	prev->next = old;
	old = prev;
    }
    return old;
}

/*
    Print a factor to screen.
*/
void writefactor(value_t *cur)
{
    char *body;
    node_t *ptr;
    symbol_t *tmp;

    switch (cur->type) {
    case 0:
	break;

    case Unknown:
    case Builtin:
    case Defined:
    case Parameter:
	tmp = vec_index(theTable, cur->num);
	printf("%s", tmp->str);
	break;

    case Boolean:
	printf(cur->num ? "true" : "false");
	break;

    case Char:
	if (debugging && cur->num == '\n')
	    printf("'\\10");
	else
	    printf("%c", cur->num);
	break;

    case Int:
	printf("%d", cur->num);
	break;

    case List:
	printf("[");
	writeterm(cur->ptr);
	printf("]");
	break;

    case Function:
	printf("%s", lookup(cur->proc, &body));
	break;

    case Symbol:
	printf("%s", cur->str);
	break;

    case Expression:
	printf("LET");
	for (ptr = cur->ptr->ptr; ptr; ptr = ptr->next) {
	    tmp = vec_index(theTable, ptr->num);
	    printf(" %s", tmp->str);
	}
	printf(" IN ");
	writeterm(cur->ptr->next);
	printf(" END");
	break;

    default:
	fprintf(stderr, "ERROR: unknown type %d in writefactor\n", cur->type);
	break;
    }
}

/*
    Print a term to screen.
*/
void writeterm(node_t *cur)
{
    value_t temp;

    while (cur) {
	temp.ptr = cur->ptr;
	temp.type = cur->type;
	writefactor(&temp);
	if (cur->next)
	    putchar(' ');
	cur = cur->next;
    }
}

/*
    Print the contents of stack and program.
*/
#ifdef DEBUG
void debug(node_t *cur)
{
    value_t *top;
    int stk, max_stk;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	top = vec_index(theStack, stk);
	writefactor(top);
	putchar(' ');
    }
    printf(". ");
    writeterm(cur);
    putchar('\n');
}

void debug1(const char *str)
{
    value_t *top;
    int stk, max_stk;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	top = vec_index(theStack, stk);
	writefactor(top);
	putchar(' ');
    }
    if (!strncmp(str, "do_", 3))
	str += 3;
    printf(". %s\n", str);
}
#endif

/*
    Evaluate a term.
*/
void exeterm(node_t *cur)
{
    short type;
    node_t *ptr;
    value_t *top;
    symbol_t *tmp;

    while (cur) {
	type = cur->type;
#ifdef DEBUG
	if (debugging)
	    debug(cur);
#endif
again:
	switch (type) {
	case 0:
	    break;

	case Unknown:
	    tmp = vec_index(theTable, cur->num);
	    type = tmp->type;
	    goto again;

	case Builtin:
	    tmp = vec_index(theTable, cur->num);
	    (*tmp->proc)();
	    break;

	case Defined:
	    tmp = vec_index(theTable, cur->num);
	    exeterm(tmp->ptr);
	    break;

	case Boolean:
	case Char:
	case Int:
	case List:
	    top = vec_push(theStack);
	    top->ptr = cur->ptr;
	    top->type = cur->type;
	    break;

	case Function:
	    (*cur->proc)();
	    break;

	case Symbol:
	    top = vec_push(theStack);
	    top->str = cur->str;
	    top->type = cur->type;
	    break;

	case Expression:
	    type = 0;
	    for (ptr = cur->ptr->ptr; ptr; ptr = ptr->next)
		type++;
	    if (vec_size(theStack) < type)
		break;
	    for (ptr = cur->ptr->ptr; ptr; ptr = ptr->next) {
		tmp = vec_index(theTable, ptr->num);
		top = vec_pop(theStack);
		tmp->ptr = top->ptr;
		tmp->uniq = top->type;
	    }
	    exeterm(cur->ptr->next);
	    break;

	case Parameter:
	    tmp = vec_index(theTable, cur->num);
	    top = vec_push(theStack);
	    top->ptr = tmp->ptr;
	    top->type = tmp->uniq;
	    break;

	default:
	    fprintf(stderr, "ERROR: unknown type %d in exeterm\n", cur->type);
	    break;
	}
	cur = cur->next;
    }
}

/*
    Print and remove the top value of the stack.
*/
void writestack(void)
{
    value_t *cur;

    if (!vec_empty(theStack)) {
	cur = vec_pop(theStack);
	writefactor(cur);
	putchar('\n');
    }
    if (vec_empty(theStack))
	mem_free();
}

/*
   Interprete a term.
*/
void execute(node_t *cur)
{
    exeterm(cur);
    writestack();
}

/*
    Print the contents of the symbol table.
*/
static void dump(void)
{
    symbol_t *cur;
    int sym, max_sym;

    max_sym = vec_size(theTable);
    for (sym = 0; sym < max_sym; sym++) {
	cur = vec_index(theTable, sym);
	printf("%s == ", cur->str);
	if (cur->type == Defined)
	    writeterm(cur->ptr);
	else
	    printf("%p", cur->proc);
	printf("\n");
    }
    printf("---\n");
}
