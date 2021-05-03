/*
    module  : jchoicebox3.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JCHOICEBOX3_C
#define JCHOICEBOX3_C

/**
jchoicebox3  :  obj title text button1 button2 button3  ->  event
Shows a choicebox with the specified title, text, and three buttons.
Choiceboxes are modal dialogs, the application is blocked until a button or the
close icon is clicked. The focus is set to the first button. The return value
is 0 if the close icon is clicked, 1 for the first button, 2 for the second and
3 for the third one.
*/
void do_jchoicebox3(void)
{
    int obj, temp;
    char *title, *text, *button1, *button2, *button3;

    COMPILE;
    button3 = (char *)do_pop();
    button2 = (char *)do_pop();
    button1 = (char *)do_pop();
    text = (char *)do_pop();
    title = (char *)do_pop();
    temp = j_choicebox3(obj, title, text, button1, button2, button3);
    do_push(temp);
}
#endif
