/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCHECKMENUITEM_C
#define JCHECKMENUITEM_C

/**
jcheckmenuitem  :  obj label  ->  event
Creates a new checkmenuitem with the specified label and returns its event
number.
*/
void do_jcheckmenuitem(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_checkmenuitem(obj, label);
    do_push(temp);
}
#endif
