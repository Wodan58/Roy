/*
    module  : name.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef NAME_C
#define NAME_C

/**
name  :  sym  ->  "sym"
For operators and combinators, the string "sym" is the name of item sym,
for literals sym the result string is its type.
*/
void do_name(void)
{
    char *str, *ptr;

    if ((str = (char *)(stack[-1] & ~JLAP_INVALID)) != 0) {
	ptr = GC_malloc_atomic(strlen(str) + 2);
	*ptr = '"';
	strcpy(ptr + 1, str);
	stack[-1] = (intptr_t)ptr | JLAP_INVALID;
    }
}
#endif
