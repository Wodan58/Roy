/*
    module  : builtin.c
    version : 1.2
    date    : 07/22/18
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "parse.h"

void do_push(short type, int value)
{
    value_t *top;

    TRACE;
    top = vec_push(theStack);
    top->num = value;
    top->type = type;
}

void do_add(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num += top->num;
}

void do_mul(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num *= top->num;
}

void do_eql(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num = sub->num == top->num;
    sub->type = Boolean;
}

void do_lss(void)
{
    value_t *top, *sub;
    char *name1, *name2;
    symbol_t *first, *second;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    switch (sub->type) {
    case Boolean:
    case Char:
    case Int:
    case List:
	sub->num = sub->num < top->num;
	break;

    case Unknown:
    case Builtin:
    case Defined:
	first = vec_index(theTable, sub->num);
	second = vec_index(theTable, top->num);
	sub->num = strcmp(first->str, second->str) < 0;
	break;

    case Function:
	name1 = lookup(sub->proc);
	name2 = lookup(top->proc);
	sub->num = strcmp(name1, name2) < 0;
	break;

    default:
	fprintf(stderr, "ERROR: unknown type %d in do_lss\n", sub->type);
	break;
    }
    sub->type = Boolean;
}

void do_swap(void)
{
    value_t *top, *sub, temp;

    TRACE;
    top = vec_top(theStack);
    sub = vec_subtop(theStack);
    temp = *sub;
    *sub = *top;
    *top = temp;
}

void do_true(void)
{
    value_t *top;

    TRACE;
    top = vec_push(theStack);
    top->num = 1;
    top->type = Boolean;
}

void do_false(void)
{
    value_t *top;

    TRACE;
    top = vec_push(theStack);
    top->num = 0;
    top->type = Boolean;
}

void do_and(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num &= top->num;
}

void do_or(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num |= top->num;
}

void do_not(void)
{
    value_t *top;

    TRACE;
    top = vec_top(theStack);
    top->num = !top->num;
}

void do_step(void)
{
    node_t *ptr, *tmp;
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_pop(theStack);
    for (ptr = top->ptr, tmp = sub->ptr; tmp; tmp = tmp->next) {
	top = vec_push(theStack);
	top->ptr = tmp->ptr;
	top->type = tmp->type;
	exeterm(ptr);
    }
}

void do_cons(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->ptr = cons(sub, top->ptr);
    sub->type = List;
}

void do_dip(void)
{
    value_t *top, *sub, temp;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_pop(theStack);
    temp = *sub;
    exeterm(top->ptr);
    top = vec_push(theStack);
    *top = temp;
}

void do_i(void)
{
    value_t *top;

    TRACE;
    top = vec_pop(theStack);
    exeterm(top->ptr);
}

void do_dup(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_push(theStack);
    sub = vec_subtop(theStack);
    *top = *sub;
}

void do_uncons(void)
{
    node_t *tmp;
    value_t *top, *sub;

    TRACE;
    top = vec_push(theStack);
    sub = vec_subtop(theStack);
    tmp = sub->ptr;
    top->ptr = tmp->next;
    top->type = List;
    sub->ptr = tmp->ptr;
    sub->type = tmp->type;
}

void do_pop(void)
{
    TRACE;
    if (!vec_empty(theStack))
	(void)vec_pop(theStack);
}

void do_index(void)
{
    node_t *tmp;
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    tmp = top->ptr;
    if (sub->num)
	tmp = tmp->next;
    sub->ptr = tmp->ptr;
    sub->type = tmp->type;
}

void do_put(void)
{
    value_t *top;

    TRACE;
    top = vec_pop(theStack);
    writefactor(top);
}

void do_get(void)
{
    value_t *top;

    TRACE;
    top = vec_push(theStack);
    top->type = yylex();
    top->ptr = yylval.ptr;
}

void do_sub(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num -= top->num;
}

void do_div(void)
{
    value_t *top, *sub;

    TRACE;
    top = vec_pop(theStack);
    sub = vec_top(theStack);
    sub->num /= top->num;
}

void do_stack(void)
{
    node_t *tmp;
    value_t *top;

    TRACE;
    tmp = stk2lst();
    top = vec_push(theStack);
    top->ptr = tmp;
    top->type = List;
}

void do_unstack(void)
{
    value_t *top;

    TRACE;
    top = vec_top(theStack);
    lst2stk(top->ptr);
}

void do_body(void)
{
    value_t *top;
    symbol_t *tmp;

    TRACE;
    top = vec_top(theStack);
    tmp = vec_index(theTable, top->num);
    top->ptr = tmp->ptr;
    top->type = List;
}
