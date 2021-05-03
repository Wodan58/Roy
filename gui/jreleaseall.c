/*
    module  : jreleaseall.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JRELEASEALL_C
#define JRELEASEALL_C

/**
jreleaseall  :  obj  ->
Releases all components from component obj.
*/
void do_jreleaseall(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_releaseall(obj);
}
#endif
