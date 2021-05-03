/*
    module  : jbutton.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JBUTTON_C
#define JBUTTON_C

/**
jbutton  :  obj label  ->  event
Creates a new button component with the specified label and returns its event
number.
*/
void do_jbutton(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_button(obj, label);
    do_push(temp);
}
#endif
