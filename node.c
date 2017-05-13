/*
    module  : node.c
    version : 1.3
    date    : 05/13/17
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gc.h"
#include "parse.h"
#include "node.h"

// #define DEBUG

int compiling, debugging;

/* dynamic arrays */
Stack *theStack;
Table *theTable;

/*
    Add a symbol to the symbol table
*/
void addsym(node_t *cur, char *str, int index, node_t *next)
{
    memset(cur, 0, sizeof(node_t));
    cur->str = str;
    cur->type = Defined;
    cur->index = index;
    cur->next = next;
}

/*
    Allocate a symbol
*/
node_t *allocsym(char *str, int index)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->str = str;
    cur->type = Defined;
    cur->index = index;
    return cur;
}

/*
    Enter a symbol in the symbol table, if it is not already there.
*/
void enterdef(char *str, node_t *next)
{
    int sym;
    node_t *cur;

    for (sym = vec_size(theTable) - 1; sym >= 0; sym--) {
	cur = vec_index(theTable, sym);
	if (!strcmp(cur->str, str)) {
	    cur->next = next;
	    return;
	}
    }
    cur = vec_push(theTable);
    addsym(cur, str, vec_size(theTable) - 1, next);
}

/*
    Search a symbol in the symbol table and return a copy
*/
node_t *entersym(char *str)
{
    int sym;
    node_t *cur;

    for (sym = vec_size(theTable) - 1; sym >= 0; sym--) {
	cur = vec_index(theTable, sym);
	if (!strcmp(cur->str, str))
	    return allocsym(str, cur->index);
    }
    cur = vec_push(theTable);
    cur->str = str;
    cur->type = Defined;
    cur->index = vec_size(theTable) - 1;
    return allocsym(str, cur->index);
}

/*
    Allocate a node of type List
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
    Allocate a node of any other type
*/
node_t *newnode(int type, int value)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    cur->num = value;
    cur->type = type;
    return cur;
}

/*
    Concatenate two lists
*/
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

/*
    Copy a list
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
    Copy a node
*/
node_t *cons(value_t *node, node_t *next)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    memcpy(cur, node, sizeof(value_t));
    cur->next = next;
    return cur;
}

/*
    Copy the stack to a list
*/
node_t *stk2lst()
{
    value_t *top;
    int stk, max_stk;
    node_t *root = 0, *cur;

    max_stk = vec_size(theStack);
    for (stk = 0; stk < max_stk; stk++) {
	if ((cur = mem_alloc()) == 0)
	    return 0;
	top = vec_index(theStack, stk);
	memcpy(cur, top, sizeof(value_t));
	cur->next = root;
	root = cur;
    }
    return root;
}

/*
    Replace the stack by a list
*/
void lst2stk(node_t *root)
{
    node_t *cur;
    value_t *top;

    vec_clear(theStack);
    for (cur = reverse(root); cur; cur = cur->next) {
	top = vec_push(theStack);
	memcpy(top, cur, sizeof(value_t));
    }
}

/*
    Reverse a list
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
    Print a factor to screen
*/
void writefactor(value_t *cur)
{
    switch (cur->type) {
    case Symbol:
	switch (cur->num) {
	case AND:
	    printf("and");
	    break;
	case BODY:
	    printf("body");
	    break;
	case CONS:
	    printf("cons");
	    break;
	case DIP:
	    printf("dip");
	    break;
	case DUP:
	    printf("dup");
	    break;
	case GET:
	    printf("get");
	    break;
	case I:
	    printf("i");
	    break;
	case INDEX:
	    printf("index");
	    break;
	case NOT:
	    printf("not");
	    break;
	case NOTHING:
	    printf("nothing");
	    break;
	case OR:
	    printf("or");
	    break;
	case POP:
	    printf("pop");
	    break;
	case PUT:
	    printf("put");
	    break;
	case SAMETYPE:
	    printf("sametype");
	    break;
	case SMALL:
	    printf("small");
	    break;
	case PRED:
	    printf("pred");
	    break;
	case BINREC:
	    printf("binrec");
	    break;
	case SELECT:
	    printf("select");
	    break;
	case STACK:
	    printf("stack");
	    break;
	case STEP:
	    printf("step");
	    break;
	case SWAP:
	    printf("swap");
	    break;
	case UNCONS:
	    printf("uncons");
	    break;
	case UNSTACK:
	    printf("unstack");
	    break;
	case '*':
	case '+':
	case '-':
	case '/':
	case '<':
	case '=':
	    printf("%c", cur->num);
	    break;
	default:
	    fprintf(stderr, "ERROR 5\n");
	    break;
	}
	break;
    case Defined:
	printf("%s", cur->str);
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
	putchar('[');
	writeterm(cur->ptr);
	putchar(']');
	break;
    case Function:
	printf("PROC");
	break;
    default:
	fprintf(stderr, "ERROR 6\n");
	break;
    }
}

/*
    Print a term to screen
*/
void writeterm(node_t *cur)
{
    value_t temp;

    while (cur) {
	memcpy(&temp, cur, sizeof(value_t));
	writefactor(&temp);
	if (cur->next)
	    putchar(' ');
	cur = cur->next;
    }
}

/*
    Print the contents of the symbol table
*/
void dump()
{
    node_t *cur;
    int sym, max_sym;

    max_sym = vec_size(theTable);
    for (sym = 0; sym < max_sym; sym++) {
	cur = vec_index(theTable, sym);
	printf("%s == ", cur->str);
	writeterm(cur->next);
	printf("\n");
    }
}

/*
    Print the contents of stack and program
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
    putchar('.');
    putchar(' ');
    writeterm(cur);
    putchar('\n');
}
#endif

void binrec(node_t *first, node_t *second, node_t *third, node_t *fourth)
{
    value_t temp, *top;

    exeterm(first);
    top = vec_pop(theStack);
    if (top->num)
	exeterm(second);
    else {
	exeterm(third);
	top = vec_pop(theStack);
	temp = *top;
	binrec(first, second, third, fourth);
	top = vec_push(theStack);
	*top = temp;
	binrec(first, second, third, fourth);
	exeterm(fourth);
    }
}

/*
    Evaluate a term
*/
void exeterm(node_t *cur)
{
    value_t *deep, *down;
    value_t temp, *sub, *top;
    node_t *tmp /* list */,
	   *ptr /* program */;

    while (cur) {
#ifdef DEBUG
	debug(cur);
#endif
	switch (cur->type) {
	case Symbol:
	    switch (cur->num) {
	    case AND:
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num &= top->num;
		sub->type = Boolean;
		break;
	    case BODY:
		top = vec_top(theStack);
		tmp = vec_index(theTable, top->index);
		top->ptr = tmp->next;
		top->type = List;
		break;
	    case CONS:
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		if (sub->type == Symbol && sub->num == NOTHING)
		    *sub = *top;
		else {
		    sub->ptr = cons(sub, top->ptr);
		    sub->type = List;
		}
		break;
	    case DIP:
		top = vec_pop(theStack);
		sub = vec_pop(theStack);
		temp = *sub;
		exeterm(top->ptr);
		top = vec_push(theStack);
		*top = temp;
		break;
	    case DUP:
		top = vec_push(theStack);
		sub = vec_subtop(theStack);
		*top = *sub;
		break;
	    case GET:
		top = vec_push(theStack);
		top->type = yylex();
		top->ptr = yylval.ptr;
		break;
	    case I:
		top = vec_pop(theStack);
		exeterm(top->ptr);
		break;
	    case INDEX:
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		tmp = top->ptr;
		if (sub->num)
		    tmp = tmp->next;
		memcpy(sub, tmp, sizeof(value_t));
		break;
	    case NOT:
		top = vec_top(theStack);
		top->num = !top->num;
		top->type = Boolean;
		break;
	    case NOTHING:
		top = vec_push(theStack);
		memcpy(top, cur, sizeof(value_t));
		break;
	    case OR:
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num |= top->num;
		sub->type = Boolean;
		break;
	    case POP:
		(void)vec_pop(theStack);
		break;
	    case PUT:
		top = vec_pop(theStack);
		writefactor(top);
		break;
	    case SAMETYPE:
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num = sub->type == top->type;
		sub->type = Boolean;
		break;
	    case SMALL:
		top = vec_top(theStack);
		top->num = top->num < 2;
		top->type = Boolean;
		break;
	    case PRED:
		top = vec_top(theStack);
		top->num--;
		break;
	    case BINREC:
		top = vec_pop(theStack);
		sub = vec_pop(theStack);
		down = vec_pop(theStack);
		deep = vec_pop(theStack);
		binrec(deep->ptr, down->ptr, sub->ptr, top->ptr);
		break;
	    case SELECT:
		break;
	    case STACK:
		tmp = stk2lst();
		top = vec_push(theStack);
		top->ptr = tmp;
		top->type = List;
		break;
	    case STEP:
		top = vec_pop(theStack);
		sub = vec_pop(theStack);
		for (ptr = top->ptr, tmp = sub->ptr; tmp; tmp = tmp->next) {
		    top = vec_push(theStack);
		    memcpy(top, tmp, sizeof(value_t));
		    exeterm(ptr);
		}
		break;
	    case SWAP:
		top = vec_top(theStack);
		sub = vec_subtop(theStack);
		temp = *sub;
		*sub = *top;
		*top = temp;
		break;
	    case UNCONS:
		top = vec_push(theStack);
		sub = vec_subtop(theStack);
		*top = *sub;
		if ((tmp = top->ptr) == 0) {
		    sub->num = NOTHING;
		    sub->type = Symbol;
		} else {
		    memcpy(sub, tmp, sizeof(value_t));
		    top->ptr = tmp->next;
		}
		break;
	    case UNSTACK:
		top = vec_top(theStack);
		lst2stk(top->ptr);
		break;
	    case '*':
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num *= top->num;
		break;
	    case '+':
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num += top->num;
		break;
	    case '-':
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num -= top->num;
		break;
	    case '/':
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num /= top->num;
		break;
	    case '<':
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		if (sub->type == Defined)
		    sub->num = strcmp(sub->str, top->str) < 0;
		else
		    sub->num = sub->num < top->num;
		sub->type = Boolean;
		break;
	    case '=':
		top = vec_pop(theStack);
		sub = vec_top(theStack);
		sub->num = sub->num == top->num;
		sub->type = Boolean;
		break;
	    default:
		fprintf(stderr, "ERROR 7\n");
		break;
	    }
	    break;
	case Defined:
	    tmp = vec_index(theTable, cur->index);
	    exeterm(tmp->next);
	    break;
	case Boolean:
	case Char:
	case Int:
	case List:
	    top = vec_push(theStack);
	    memcpy(top, cur, sizeof(value_t));
	    break;
	case Function:
	    (*cur->fun)();
	    break;
	default:
	    fprintf(stderr, "ERROR 8 - %d\n", cur->type);
	    break;
	}
	cur = cur->next;
    }
}

/*
    Print and remove the top value of the stack
*/
void writestack()
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
   Interprete a term
*/
void execute(node_t *cur)
{
    exeterm(cur);
    writestack();
}
