/*
    module  : jhscrollbar.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JHSCROLLBAR_C
#define JHSCROLLBAR_C

/**
jhscrollbar  :  obj  ->  event
Creates a new horizontal scrollbar and returns its event number.
*/
void do_jhscrollbar(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_hscrollbar(obj);
    do_push(temp);
}
#endif
