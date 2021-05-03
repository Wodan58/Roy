/*
    module  : jdeselect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDESELECT_C
#define JDESELECT_C

/**
jdeselect  :  obj item  ->
Deselects the item at the designated position item, if selected.
*/
void do_jdeselect(void)
{
    int obj, item;

    COMPILE;
    item = do_pop();
    obj = do_pop();
    j_deselect(obj, item);
}
#endif
