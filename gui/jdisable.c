/*
    module  : jdisable.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDISABLE_C
#define JDISABLE_C

/**
jdisable  :  obj  ->
Disables component obj so that it is unresponsive to user interactions.
*/
void do_jdisable(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_disable(obj);
}
#endif
