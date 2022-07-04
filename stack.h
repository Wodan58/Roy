/*
    module  : stack.h
    version : 1.1
    date    : 06/21/22
*/
#ifndef STACK_H
#define STACK_H

/* make stack addressing possible */
#ifdef VECTOR
#define stack vec_end(theStack)
#endif

typedef vector(value_t) Stack;

extern Stack *theStack;

void stack_init(void);
void stack_clear(void);
int stack_size(void);
int stack_max(void);
int stack_empty(void);
void stack_write(void);
void writestack(void);
void stack_trace(const char *str);
Stack *stack_copy(void);
void do_push(value_t Value);
void stack_from_list(Stack *list);
value_t stack_pop(void);
#endif
