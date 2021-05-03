/*
    module  : jmenuitem.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMENUITEM_C
#define JMENUITEM_C

/**
jmenuitem  :  obj label  ->  event
Creates a new menuitem with the specified label and returns its event number.
*/
void do_jmenuitem(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_menuitem(obj, label);
    do_push(temp);
}
#endif
