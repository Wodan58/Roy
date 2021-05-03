/*
    module  : 
    version : 1.1
    date    : 04/27/21
*/
#ifndef JWINDOWLISTENER_C
#define JWINDOWLISTENER_C

/**
jwindowlistener  :  window kind  ->  event
Adds a new windowlistener to component obj, and returns its event number. An
event occurs, if the user action is of kind kind. Possible values for kind: An
event occurs when the component J_ACTIVATED is activated; J_DEACTIVATED is
deactivated; J_OPENED has been opened; J_CLOSED closed; J_ICONIFIED iconified;
J_DEICONIFIED deiconified; J_CLOSING when the close icon has been clicked.
*/
void do_jwindowlistener(void)
{
    int window, kind, temp;

    COMPILE;
    kind = do_pop();
    window = do_pop();
    temp = j_windowlistener(window, kind);
    do_push(temp);
}
#endif
