/*
    module  : jmenu.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMENU_C
#define JMENU_C

/**
jmenu  :  obj label  ->  event
Creates a new menu component with the specified label and returns its event
number.
*/
void do_jmenu(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_menu(obj, label);
    do_push(temp);
}
#endif
