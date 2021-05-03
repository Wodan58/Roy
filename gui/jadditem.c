/*
    module  : jadditem.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JADDITEM_C
#define JADDITEM_C

/**
jadditem  :  obj str  ->
Adds a new item containing str to component obj.
*/
void do_jadditem(void)
{
    int obj;
    char *str;

    COMPILE;
    str = (char *)do_pop();
    obj = do_pop();
    j_additem(obj, str);
}
#endif
