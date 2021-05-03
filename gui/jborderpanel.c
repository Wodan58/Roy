/*
    module  : jborderpanel.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JBORDERPANEL_C
#define JBORDERPANEL_C

/**
jborderpanel  :  obj type  ->  event
Creates a new borderpanel component with the style type and returns its event
number.
*/
void do_jborderpanel(void)
{
    int obj, type, temp;

    COMPILE;
    type = do_pop();
    obj = do_pop();
    temp = j_borderpanel(obj, type);
    do_push(temp);
}
#endif
