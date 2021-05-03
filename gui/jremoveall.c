/*
    module  : jremoveall.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JREMOVEALL_C
#define JREMOVEALL_C

/**
jremoveall  :  obj  ->
Removes all items from the component obj.
*/
void do_jremoveall(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_removeall(obj);
}
#endif
