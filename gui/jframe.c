/*
    module  : jframe.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFRAME_C
#define JFRAME_C

/**
jframe  :  label  ->  event
Creates a new frame component with the specified label and returns its event
number.
*/
void do_jframe(void)
{
    int temp;
    char *label;

    COMPILE;
    label = (char *)do_pop();
    temp = j_frame(label);
    do_push(temp);
}
#endif
