/*
    module  : node.c
    version : 1.1
    date    : 08/30/16
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "parse.h"
#include "node.h"

// #define DEBUG

#ifndef MAXSYM
#define MAXSYM	300
#endif

#ifndef MAXSTK
#define MAXSTK	300
#endif

int compiling;

int symptr;
node_t symtab[MAXSYM];

int stkptr;
node_t stktab[MAXSTK];

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
    node_t cur;

    for (sym = symptr - 1; sym >= 0; sym--)
	if (!strcmp(symtab[sym].str, str)) {
	    symtab[sym].next = next;
	    return;
	}
    addsym(&cur, str, symptr, next);
    if (symptr < MAXSYM)
	symtab[symptr++] = cur;
}

/*
    Search a symbol in the symbol table and return a copy
*/
node_t *entersym(char *str)
{
    int sym;
    node_t *cur;

    for (sym = symptr - 1; sym >= 0; sym--)
	if (!strcmp(symtab[sym].str, str))
	    return allocsym(str, sym);
    cur = allocsym(str, symptr);
    if (symptr < MAXSYM)
	symtab[symptr++] = *cur;
    return cur;
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
node_t *alloc(node_t *node)
{
    node_t *cur;

    if ((cur = mem_alloc()) == 0)
	return 0;
    *cur = *node;
    return cur;
}

/*
    Copy the stack to a list
*/
node_t *stk2lst()
{
    int stk;
    node_t *root = 0, **cur;

    for (cur = &root, stk = stkptr - 1; stk >= 0; stk--) {
	if ((*cur = mem_alloc()) == 0)
	    return 0;
	**cur = stktab[stk];
	cur = &(*cur)->next;
	*cur = 0;
    }
    return root;
}

/*
    Replace the stack by a list
*/
void lst2stk(node_t *root)
{
    int num = 0;
    node_t *cur;

    for (cur = root; cur; cur = cur->next)
	num++;
    stkptr = num;
    for (cur = root; cur; cur = cur->next) {
	stktab[--num] = *cur;
	stktab[num].next = 0;
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

static short newline;

/*
    Print a factor to screen
*/
void writefactor(node_t *cur)
{
    newline = 0;
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
	    printf("ERROR");
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
	printf("%c", cur->num);
	if (cur->num == '\n')
	    newline = 1;
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
	printf("ERROR");
	break;
    }
}

/*
    Print a term to screen
*/
void writeterm(node_t *cur)
{
    while (cur) {
	writefactor(cur);
	if (cur->next)
	    putchar(' ');
	cur = cur->next;
    }
}

/*
    Print the contents of the symbol table
*/
void table()
{
    int sym;

    for (sym = 0; sym < symptr; sym++) {
	printf("%s == ", symtab[sym].str);
	writeterm(symtab[sym].next);
	printf("\n");
    }
}

/*
    Print the contents of stack and program
*/
void debug(node_t *cur)
{
    int stk;

    for (stk = 0; stk < stkptr; stk++) {
	writefactor(&stktab[stk]);
	putchar(' ');
    }
    putchar('.');
    putchar(' ');
    writeterm(cur);
    putchar('\n');
}

/*
    Evaluate a term
*/
void exeterm(node_t *cur)
{
    node_t temp, *tmp /* list */,
		 *ptr /* program */;

    while (cur) {
#ifdef DEBUG
	debug(cur);
#endif
	switch (cur->type) {
	case Symbol:
	    switch (cur->num) {
	    case AND:
		stkptr--;
		stktab[stkptr-1].num &= stktab[stkptr].num;
		stktab[stkptr-1].type = Boolean;
		break;
	    case BODY:
		stktab[stkptr-1].ptr = symtab[stktab[stkptr-1].index].next;
		stktab[stkptr-1].type = List;
		break;
	    case CONS:
		stkptr--;
		if (stktab[stkptr-1].type == Symbol &&
		    stktab[stkptr-1].num == NOTHING)
		    stktab[stkptr-1] = stktab[stkptr];
		else {
		    stktab[stkptr-1].next = stktab[stkptr].ptr;
		    stktab[stkptr-1].ptr = alloc(&stktab[stkptr-1]);
		    stktab[stkptr-1].type = List;
		}
		break;
	    case DIP:
		stkptr -= 2;
		temp = stktab[stkptr];
		exeterm(stktab[stkptr+1].ptr);
		stktab[stkptr++] = temp;
		break;
	    case DUP:
		stktab[stkptr] = stktab[stkptr-1];
		stkptr++;
		break;
	    case GET:
		stktab[stkptr].type = yylex();
		stktab[stkptr++].num = yylval.num;
		break;
	    case I:
		exeterm(stktab[--stkptr].ptr);
		break;
	    case INDEX:
		tmp = stktab[--stkptr].ptr;
		if (stktab[stkptr-1].num)
		    tmp = tmp->next;
		stktab[stkptr-1] = *tmp;
		break;
	    case NOT:
		stktab[stkptr-1].num = !stktab[stkptr-1].num;
		stktab[stkptr-1].type = Boolean;
		break;
	    case NOTHING:
		stktab[stkptr].num = cur->num;
		stktab[stkptr++].type = cur->type;
		break;
	    case OR:
		stkptr--;
		stktab[stkptr-1].num |= stktab[stkptr].num;
		stktab[stkptr-1].type = Boolean;
		break;
	    case POP:
		stkptr--;
		break;
	    case PUT:
		writefactor(&stktab[--stkptr]);
		break;
	    case SAMETYPE:
		stkptr--;
		stktab[stkptr-1].num  = stktab[stkptr-1].type ==
					stktab[stkptr].type;
		stktab[stkptr-1].type = Boolean;
		break;
	    case SELECT:
		break;
	    case STACK:
		stktab[stkptr].ptr = stk2lst();
		stktab[stkptr++].type = List;
		break;
	    case STEP:
		ptr = stktab[--stkptr].ptr;
		for (tmp = stktab[--stkptr].ptr; tmp; tmp = tmp->next) {
		    stktab[stkptr++] = *tmp;
		    exeterm(ptr);
		}
		break;
	    case SWAP:
		temp = stktab[stkptr-2];
		stktab[stkptr-2] = stktab[stkptr-1];
		stktab[stkptr-1] = temp;
		break;
	    case UNCONS:
		stktab[stkptr] = stktab[stkptr-1];
		if (!stktab[stkptr].ptr) {
		    stktab[stkptr-1].num = NOTHING;
		    stktab[stkptr-1].type = Symbol;
		} else {
		    tmp = stktab[stkptr].ptr;
		    stktab[stkptr-1] = *tmp;
		    stktab[stkptr].ptr = tmp->next;
		}
		stkptr++;
		break;
	    case UNSTACK:
		lst2stk(stktab[stkptr-1].ptr);
		break;
	    case '*':
		stkptr--;
		stktab[stkptr-1].num *= stktab[stkptr].num;
		break;
	    case '+':
		stkptr--;
		stktab[stkptr-1].num += stktab[stkptr].num;
		break;
	    case '-':
		stkptr--;
		stktab[stkptr-1].num -= stktab[stkptr].num;
		break;
	    case '/':
		stkptr--;
		stktab[stkptr-1].num /= stktab[stkptr].num;
		break;
	    case '<':
		stkptr--;
		if (stktab[stkptr-1].type == Defined)
		    stktab[stkptr-1].num = strcmp(stktab[stkptr-1].str,
						  stktab[stkptr].str) < 0;
		else
		    stktab[stkptr-1].num = stktab[stkptr-1].num <
					   stktab[stkptr].num;
		stktab[stkptr-1].type = Boolean;
		break;
	    case '=':
		stkptr--;
		stktab[stkptr-1].num  = stktab[stkptr-1].num ==
					stktab[stkptr].num;
		stktab[stkptr-1].type = Boolean;
		break;
	    default:
		printf("ERROR");
		break;
	    }
	    break;
	case Defined:
	    exeterm(symtab[cur->index].next);
	    break;
	case Boolean:
	case Char:
	case Int:
	    stktab[stkptr].num = cur->num;
	    stktab[stkptr++].type = cur->type;
	    break;
	case List:
	    stktab[stkptr].ptr = cur->ptr;
	    stktab[stkptr++].type = cur->type;
	    break;
	case Function:
	    (*cur->fun)();
	    break;
	default:
	    printf("ERROR");
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
    if (stkptr)
	writefactor(&stktab[--stkptr]);
    if (!newline)
	putchar('\n');
    if (!stkptr)
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
