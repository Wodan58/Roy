/*
    module  : jpanel.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JPANEL_C
#define JPANEL_C

/**
jpanel  :  obj  ->  event
Creates a new panel component and returns its event number.
*/
void do_jpanel(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_panel(obj);
    do_push(temp);
}
#endif
