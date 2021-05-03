/*
    module  : jalertbox.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JALERTBOX_C
#define JALERTBOX_C

/**
jalertbox  :  obj title text button  ->  status
Shows an alertbox with the specified title, text, and button. Alertboxes are
modal dialogs; the application is blocked until the button or the close icon is
clicked. The return value is 0, if the close icon is clicked and 1 if the
button is used.
*/
void do_jalertbox(void)
{
    int obj, temp;
    char *title, *text, *button;

    COMPILE;
    button = (char *)do_pop();
    text = (char *)do_pop();
    title = (char *)do_pop();
    obj = do_pop();
    temp = j_alertbox(obj, title, text, button);
    do_push(temp);
}
#endif
