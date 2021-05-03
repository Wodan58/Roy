/*
    module  : jinsert.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JINSERT_C
#define JINSERT_C

/**
jinsert  :  obj pos label  ->
Inserts a new item to component obj at position pos with the specified label.
*/
void do_jinsert(void)
{
    char *label;
    int obj, pos, temp;

    COMPILE;
    label = (char *)do_pop();
    pos = do_pop();
    obj = do_pop();
    j_insert(obj, pos, label);
}
#endif
