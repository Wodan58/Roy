/*
    module  : jgetparentid.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JGETPARENTID_C
#define JGETPARENTID_C

/**
jgetparentid  :  obj  ->  event
Returns the parent event number of component obj. If obj is a frame -1 will be
returned.
*/
void do_jgetparentid(void)
{
    int obj, temp;

    COMPILE;
    obj = do_pop();
    temp = j_getparentid(obj);
    do_push(temp);
}
#endif
