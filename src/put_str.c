/*
    module  : put_str.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef PUT_STR_C
#define PUT_STR_C

/**
put_str  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_str(void)
{
    char *str;

    COMPILE;
    if ((str = (char *)do_pop()) == 0)
	printf("\"\"");
    else
	printf("\"%s\"", str);
}
#endif
