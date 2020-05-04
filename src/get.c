/*
    module  : get.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef GET_C
#define GET_C

/**
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
void do_get(void)
{
    COMPILE;
    readfactor(yylex());
}
#endif
