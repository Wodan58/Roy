/*
    module  : jselect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSELECT_C
#define JSELECT_C

/**
jselect  :  obj item  ->
Makes the given item the selected one for the component obj.
*/
void do_jselect(void)
{
    int obj, item;

    COMPILE;
    item = do_pop();
    obj = do_pop();
    j_select(obj, item);
}
#endif
