/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMOUSELISTENER_C
#define JMOUSELISTENER_C

/**
jmouselistener  :  obj kind  ->  event
Adds a new mouse listener to component obj, and returns its event number. An
event occurs, if the user action is of kind kind. Possible values for kind:
An event occurs if the mouse cursor has been moved J_ENTERED into; J_MOVED
inside; J_EXITED out of component obj; J_PRESSED if the mouse button was
pressed; J_RELEASED released; J_DOUBLECLICK double clicked; J_DRAGGED if the
mouse cursor has been dragged (moved with pressed button) inside component obj.
*/
void do_jmouselistener(void)
{
    int obj, kind, temp;

    COMPILE;
    kind = do_pop();
    obj = do_pop();
    temp = j_mouselistener(obj, kind);
    do_push(temp);
}
#endif
