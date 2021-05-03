/*
    module  : jscrollpane.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSCROLLPANE_C
#define JSCROLLPANE_C

/**
jscrollpane  :  obj  ->  event
Creates a new scrollpane component and returns its event number.
*/
void do_jscrollpane(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_scrollpane(obj);
    do_push(temp);
}
#endif
