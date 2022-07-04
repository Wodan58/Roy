/*
    module  : __symtabindex.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_SYMTABINDEX_C
#define _LOWBAR__LOWBAR_SYMTABINDEX_C

/**
1060  __symtabindex  :  A	->  I
Pushes current size of the symbol table.
*/
void do__lowbar__lowbar_symtabindex(void)
{
#ifdef COMPILING
    COMPILE;
    do_push(MAKE_INTEGER(symtabindex()));
#endif
}
#endif
