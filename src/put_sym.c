/*
    module  : put_sym.c
    version : 1.3
    date    : 01/19/20
*/
#ifndef PUT_SYM_C
#define PUT_SYM_C

/**
put_sym  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_sym(void)
{
    intptr_t Value;

    COMPILE;
    if ((Value = do_pop()) != 0)
#ifdef COMPILING
	printf("%s", (char *)(Value & ~JLAP_INVALID));
#else
	if (!writeproc(Value))
	    printf("%s", (char *)Value);
#endif
}
#endif
