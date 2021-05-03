/*
    module  : jgetitem.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETITEM_C
#define JGETITEM_C

/**
jgetitem  :  obj item  ->  label
Returns the label of the given item.
*/
void do_jgetitem(void)
{
    int obj, item;
    char label[MAXSTR];

    COMPILE;
    item = do_pop();
    obj = do_pop();
    j_getitem(obj, item, label);
    do_push((intptr_t)GC_strdup(label) | JLAP_INVALID);
}
#endif
