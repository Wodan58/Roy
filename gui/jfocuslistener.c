/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFOCUSLISTENER_C
#define JFOCUSLISTENER_C

/**
jfocuslistener  :  obj  ->  event
Adds a new focus listener to component obj and returns its event number.
*/
void do_jfocuslistener(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_focuslistener(obj);
    do_push(temp);
}
#endif
