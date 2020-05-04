/*
    module  : undefs.c
    version : 1.13
    date    : 01/20/20
*/
#ifndef UNDEFS_C
#define UNDEFS_C

/**
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
void do_undefs(void)
{
#ifdef COMPILING
    khiter_t key;
    int start = 1;
    Stack *List = 0;
    const char *Name;

    while ((Name = dump1(start, &key)) != 0) {
	vec_push(List, (intptr_t)Name | JLAP_INVALID);
	start = 0;
    }
    do_push((intptr_t)List);
#endif
}
#endif
