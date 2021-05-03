/*
    module  : jrelease.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JRELEASE_C
#define JRELEASE_C

/**
jrelease  :  obj  ->
Releases component obj from its parent component (container).
*/
void do_jrelease(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_release(obj);
}
#endif
