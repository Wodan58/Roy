/*
    module  : jradiobutton.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JRADIOBUTTON_C
#define JRADIOBUTTON_C

/**
jradiobutton  :  obj label  ->  event
Creates a new radiobutton with the specified label and returns its event number.
*/
void do_jradiobutton(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_radiobutton(obj, label);
    do_push(temp);
}
#endif
