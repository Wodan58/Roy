/*
    module  : intern.c
    version : 1.14
    date    : 01/19/20
*/
#ifndef INTERN_C
#define INTERN_C

/**
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
void do_intern(void)
{
    char *str;

    UNARY;
    if ((str = (char *)stack[-1]) != 0)
	stack[-1] = (intptr_t)GC_strdup(str) | JLAP_INVALID;
}
#endif
