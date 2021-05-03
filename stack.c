/*
    module  : stack.c
    version : 1.5
    date    : 03/16/21
*/
#ifdef VECTOR
/* declare data stack */
static Stack *theStack;

/* make stack addressing possible */
#define stack	vec_end(theStack)
#else
intptr_t memory[MEMORYMAX], *stack;
#endif

void init_stack(void)
{
#ifdef VECTOR
    vec_init(theStack);
#else
    stack = memory;
#endif
}

void clear_stack(void)
{
#ifdef VECTOR
    vec_setsize(theStack, 0);
#else
    stack = memory;
#endif
}

int stack_size(void)
{
#ifdef VECTOR
    return vec_size(theStack);
#else
    return stack - memory;
#endif
}

int stack_max(void)
{
#ifdef VECTOR
    return vec_max(theStack);
#else
    return MEMORYMAX;
#endif
}

int stack_empty(void)
{
#ifdef VECTOR
    return !vec_size(theStack);
#else
    return stack == memory;
#endif
}

intptr_t stack_top(void)
{
#ifdef VECTOR
    return vec_back(theStack);
#else
    return stack[-1];
#endif
}

void write_stack(void)
{
#ifdef VECTOR
    int Index, Limit;

    for (Index = 0, Limit = vec_size(theStack) - 1; Index <= Limit; Index++) {
	writefactor(vec_at(theStack, Index));
	if (Index < Limit)
	    putchar(' ');
    }
#else
    intptr_t *mem;

    for (mem = memory; mem < stack; mem++) {
	writefactor(*mem);
	if (mem < stack)
	    putchar(' ');
    }
#endif
}

Stack *copy_stack(void)
{
    Stack *Quot = 0;

#ifdef VECTOR
    vec_copy(Quot, theStack);
#else
    intptr_t *mem;

    for (mem = memory; mem < stack; mem++)
	vec_push(Quot, *mem);
#endif
    return Quot;
}

void do_push(intptr_t Value)
{
#ifdef VECTOR
    vec_push(theStack, Value);
#else
    *stack++ = Value;
#endif
}

intptr_t stack_pop(void)
{
    if (!stack_empty())
#ifdef VECTOR
	return vec_pop(theStack);
#else
	return *--stack;
#endif
    return 0;
}
