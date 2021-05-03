/*
    module  : jhelpmenu.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JHELPMENU_C
#define JHELPMENU_C

/**
jhelpmenu  :  obj label  ->  event
Creates a new helpmenu component with the specified label and returns its
event number.
*/
void do_jhelpmenu(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_helpmenu(obj, label);
    do_push(temp);
}
#endif
