/*
    module  : jremove.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JREMOVE_C
#define JREMOVE_C

/**
jremove  :  obj item  ->
Removes the item with the index item from the component obj.
*/
void do_jremove(void)
{
    int obj, item;

    COMPILE;
    item = do_pop();
    obj = do_pop();
    j_remove(obj, item);
}
#endif
