/*
    module  : jlabel.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JLABEL_C
#define JLABEL_C

/**
jlabel  :  obj label  ->  event
Creates a new label component with the specified label and returns its event
number.
*/
void do_jlabel(void)
{
    char *label;
    int obj, temp;

    COMPILE;
    label = (char *)do_pop();
    obj = do_pop();
    temp = j_label(obj, label);
    do_push(temp);
}
#endif
