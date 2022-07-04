/*
    module  : stack.c
    version : 1.6
    date    : 06/21/22
*/
#include "joy.h"

/* declare data stack */
#ifdef VECTOR
Stack *theStack;
#else
value_t memory[MEMORYMAX], *stack;
#endif

#ifdef REPORT
static double count_push;

/*
    report_push - report the number of times an item was pushed on the stack.
*/
static void report_push(void)
{
    fprintf(stderr, "push = %.0f\n", count_push);
}
#endif

/*
    stack_init - start using the stack.
*/
void stack_init(void)
{
#ifdef REPORT
    atexit(report_push);
#endif
#ifdef VECTOR
    vec_init(theStack);
    vec_setowner(theStack, OWNER);
#else
    stack = memory;
#endif
}

/*
    stack_clear - make the stack empty again.
*/
void stack_clear(void)
{
#ifdef VECTOR
    vec_setsize(theStack, 0);
#else
    stack = memory;
#endif
}

/*
    stack_size - report the size of the stack that is currently in use.
*/
int stack_size(void)
{
#ifdef VECTOR
    return vec_size(theStack);
#else
    return stack - memory;
#endif
}

/*
    stack_max - report the current maximum size of the stack.
*/
int stack_max(void)
{
#ifdef VECTOR
    return vec_max(theStack);
#else
    return MEMORYMAX;
#endif
}

/*
    stack_empty - tell whether the stack is empty or not.
*/
int stack_empty(void)
{
#ifdef VECTOR
    return !vec_size(theStack);
#else
    return stack == memory;
#endif
}

/*
    writestack - print the contents of the stack from top to bottom.
*/
void writestack(void)
{
#ifdef VECTOR
    int i;

    for (i = vec_size(theStack) - 1; i >= 0; i--) {
        writefactor(vec_at(theStack, i));
        if (i)
            putchar(' ');
    }
#else
    value_t *mem;

    for (mem = stack - 1; mem >= memory; mem--) {
        writefactor(*mem);
        if (mem > memory)
            putchar(' ');
    }
#endif
}

/*
    stack_write - print the contents of the stack from bottom to top.
*/
void stack_write(void)
{
#ifdef VECTOR
    int i, j;

    for (i = 0, j = vec_size(theStack) - 1; i <= j; i++) {
        writefactor(vec_at(theStack, i));
        if (i < j)
            putchar(' ');
    }
#else
    value_t *mem;

    for (mem = memory; mem < stack; mem++) {
        writefactor(*mem);
        if (mem < stack)
            putchar(' ');
    }
#endif
}

/*
    stack_copy - return a copy of the stack.
*/
Stack *stack_copy(void)
{
    Stack *quot = 0;

#ifdef VECTOR
    vec_copy(quot, theStack);
#else
    value_t *mem;

    for (mem = memory; mem < stack; mem++)
        vec_push(quot, *mem);
#endif
    return quot;
}

/*
    do_push - push a value onto the stack.
*/
void do_push(value_t value)
{
#ifdef REPORT
    count_push++;
#endif
#ifdef VECTOR
    vec_push(theStack, value);
#else
    *stack++ = value;
#endif
}

/*
    stack_from_list - replace the stack by the contents of a list. An exception
                      is made for the initial value: it cannot exist.
*/
void stack_from_list(Stack *list)
{
    int i, j;
    value_t value;

    stack_clear();
    for (i = 0, j = vec_size(list); i < j; i++) {
        value = vec_at(list, i);
        do_push(value);
    }
}

/*
    stack_pop - remove and return the top value of the stack.
*/
value_t stack_pop(void)
{
#ifdef VECTOR
    return vec_pop(theStack);
#else
    return *--stack;
#endif
}
