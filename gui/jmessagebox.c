/*
    module  : jmessagebox.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JMESSAGEBOX_C
#define JMESSAGEBOX_C

/**
jmessagebox  :  obj title text  ->  event
Shows a messagebox with the specified title and text and returns its event
number. In the case of an error -1 will be returned. A messagebox generates an
event, if the close icon is clicked.
*/
void do_jmessagebox(void)
{
    int obj, temp;
    char *title, *text;

    COMPILE;
    text = (char *)do_pop();
    title = (char *)do_pop();
    obj = do_pop();
    temp = j_messagebox(obj, title, text);
    do_push(temp);
}
#endif
