/*
    module  : jpopupmenu.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPOPUPMENU_C
#define JPOPUPMENU_C

/**
jpopupmenu  :  obj label  ->  event
Creates a new popupmenu with the specified label and returns its event number.
*/
void do_jpopupmenu(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_popupmenu(obj, label);
    do_push(temp);
}
#endif
