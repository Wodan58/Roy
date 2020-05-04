/*
    module  : __symtabmax.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
void do___symtabmax(void)
{
#ifdef COMPILING
    COMPILE;
    do_push(symtabmax());
#endif
}
#endif
