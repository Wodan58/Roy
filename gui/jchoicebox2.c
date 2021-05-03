/*
    module  : jchoicebox2.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCHOICEBOX2_C
#define JCHOICEBOX2_C

/**
jchoicebox2  :  obj title text button1 button2  ->  event
Shows a choicebox with the specified title, text, and two buttons. Choiceboxes
are modal dialogs, the application is blocked until a button or the close icon
is clicked. The focus is set to the first button. The return value is 0 if the
close icon is clicked, 1 for the first button and 2 for the second one.
*/
void do_jchoicebox2(void)
{
    int obj, temp;
    char *title, *text, *button1, *button2;

    COMPILE;
    button2 = (char *)do_pop();
    button1 = (char *)do_pop();
    text = (char *)do_pop();
    title = (char *)do_pop();
    obj = do_pop();
    temp = j_choicebox2(obj, title, text, button1, button2);
    do_push(temp);
}
#endif
