/*
    module  : char.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef CHAR_C
#define CHAR_C

/**
char  :  X  ->  B
Tests whether X is a character.
*/
void do_char(void)
{
    UNARY;
    stack[-1] = is_char(stack[-1]);
}
#endif
