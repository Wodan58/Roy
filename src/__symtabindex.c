/*
    module  : __symtabindex.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef __SYMTABINDEX_C
#define __SYMTABINDEX_C

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
void do___symtabindex(void)
{
#ifdef COMPILING
    COMPILE;
    do_push(symtabindex());
#endif
}
#endif
