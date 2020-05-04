/*
    module  : put_set.c
    version : 1.2
    date    : 01/19/20
*/
#ifndef PUT_SET_C
#define PUT_SET_C

/**
put_set  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_set(void)
{
    int i;
    intptr_t j, set;

    COMPILE;
    printf("{");
    set = do_pop();
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j) {
	    printf("%d", i);
	    if ((set &= ~j) == 0)
		break;
	    putchar(' ');
	}
    printf("}");
}
#endif
