/*
    module  : jshow.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSHOW_C
#define JSHOW_C

/**
jshow  :  obj  ->
Shows the component obj.
*/
void do_jshow(void)
{
    int obj;

    COMPILE;
    obj = do_pop();
    j_show(obj);
}
#endif
