/*
    module  : __symtabmax.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_SYMTABMAX_C
#define _LOWBAR__LOWBAR_SYMTABMAX_C

/**
1050  __symtabmax  :  A 	->  I
Pushes value of maximum size of the symbol table.
*/
void do__lowbar__lowbar_symtabmax(void)
{
#ifdef COMPILING
    COMPILE;
    do_push(MAKE_INTEGER(symtabmax()));
#endif
}
#endif
