/*
    module  : getenv.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef GETENV_C
#define GETENV_C

/**
getenv  :  "variable"  ->  "value"
Retrieves the value of the environment variable "variable".
*/
void do_getenv(void)
{
    char *str, *ptr;

    if (stack[-1]) {
	str = (char *)stack[-1];
	if ((str = getenv(str)) == 0)
	    stack[-1] = 0;
	else {
	    ptr = GC_malloc_atomic(strlen(str) + 2);
	    ptr[0] = '"';
	    strcpy(ptr + 1, str);
	    stack[-1] = (intptr_t)ptr | JLAP_INVALID;
	}
    }
}
#endif
