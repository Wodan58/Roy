/*
    module  : get.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef GET_C
#define GET_C

/**
3090  get  :  A 	->  F
Reads a factor from input and pushes it onto stack.
*/
void do_get(void)
{
    COMPILE;
    readfactor(yylex());
}
#endif
