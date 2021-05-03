/*
    module  : jgetselect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETSELECT_C
#define JGETSELECT_C

/**
jgetselect  :  obj  ->  position
Returns the position of the currently selected item.
*/
void do_jgetselect(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getselect(obj);
    do_push(temp);
}
#endif
