/*
    module  : undefs.c
    version : 1.14
    date    : 06/21/22
*/
#ifndef UNDEFS_C
#define UNDEFS_C

/**
1110  undefs  :  A	->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
void do_undefs(void)
{
    /*
        Push empty list, because undefined symbols are not stored in the symbol
        table.
    */
    Stack *list;

    vec_init(list);
    do_push(MAKE_LIST(list));
}
#endif
