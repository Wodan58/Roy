/*
    module  : jgetheight.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETHEIGHT_C
#define JGETHEIGHT_C

/**
jgetheight  :  obj  ->  height
Returns the height of component obj.
*/
void do_jgetheight(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getheight(obj);
    do_push(temp);
}
#endif
