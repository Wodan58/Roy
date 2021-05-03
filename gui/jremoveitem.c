/*
    module  : jremoveitem.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JREMOVEITEM_C
#define JREMOVEITEM_C

/**
jremoveitem  :  obj item  ->
Removes the first occurrence of item from the component.
*/
void do_jremoveitem(void)
{
    int obj;
    char *item;

    COMPILE;
    item = (char *)do_pop();
    obj = do_pop();
    j_removeitem(obj, item);
}
#endif
