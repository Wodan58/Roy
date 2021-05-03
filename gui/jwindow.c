/*
    module  : jwindow.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JWINDOW_C
#define JWINDOW_C

/**
jwindow  :  obj  ->  event
Creates a new simple window and returns its event number.
*/
void do_jwindow(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_window(obj);
    do_push(temp);
}
#endif
