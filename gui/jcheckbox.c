/*
    module  : jcheckbox.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCHECKBOX_C
#define JCHECKBOX_C

/**
jcheckbox  :  obj label  ->  event
Creates a new checkbox component with the specified label and returns its event
number.
*/
void do_jcheckbox(void)
{
    int obj, temp;
    char *message;

    COMPILE;
    message = (char *)do_pop();
    obj = do_pop();
    temp = j_checkbox(obj, message);
    do_push(temp);
}
#endif
