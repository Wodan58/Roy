/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCOMPONENTLISTENER_C
#define JCOMPONENTLISTENER_C

/**
jcomponentlistener  :  obj kind  ->  event
Adds a new componentlistener to component obj, and returns its event number. An
event occurs, if the user action is of kind kind. Possible values for kind:
J_RESIZED: An event occurs when the component has been resized; J_HIDDEN: an
event occurs when the component has been hidden; J_SHOWN: an event occurs when
the component has been shown.
*/
void do_jcomponentlistener(void)
{
    int obj, kind, temp;

    COMPILE;
    kind = do_pop();
    obj = do_pop();
    temp = j_componentlistener(obj, kind);
    do_push(temp);
}
#endif
