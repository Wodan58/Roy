/*
    module  : jdispose.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDISPOSE_C
#define JDISPOSE_C

/**
jdispose  :  obj  ->
Releases the resources of the component obj.
*/
PRIVATE void do_jdispose(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_dispose(obj);
}
#endif
