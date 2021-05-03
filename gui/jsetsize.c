/*
    module  : jsetsize.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JSETSIZE_C
#define JSETSIZE_C

/**
jsetsize  :  obj width height  ->
Resizes component obj to the specified width and height.
*/
void do_jsetsize(void)
{
    int obj, width, height;

    COMPILE;
    height = do_pop();
    width = do_pop();
    obj = do_pop();
    j_setsize(obj, width, height);
}
#endif
