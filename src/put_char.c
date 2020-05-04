/*
    module  : put_char.c
    version : 1.2
    date    : 01/19/20
*/
#ifndef PUT_CHAR_C
#define PUT_CHAR_C

/**
put_char  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_char(void)
{
    COMPILE;
    putchar('\'');
    putchar(do_pop());
}
#endif
