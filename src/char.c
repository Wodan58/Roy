/*
    module  : char.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef CHAR_C
#define CHAR_C

/**
2340  char  :  DA	X  ->  B
Tests whether X is a character.
*/
void do_char(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_CHAR(stack[-1]));
}
#endif
