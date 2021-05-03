/*
    module  : jvscrollbar.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JVSCROLLBAR_C
#define JVSCROLLBAR_C

/**
jvscrollbar  :  obj  ->  event
Creates a new vertical scrollbar and returns its event number.
*/
void do_jvscrollbar(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_vscrollbar(obj);
    do_push(temp);
}
#endif
