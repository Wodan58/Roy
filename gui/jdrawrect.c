/*
    module  : jdrawrect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWRECT_C
#define JDRAWRECT_C

/**
jdrawrect  :  obj x y width height  ->
Draws an unfilled rectangle from (x, y) of size width x height
*/
void do_jdrawrect(void)
{
    int obj, x, y, width, height;

    COMPILE;
    height = do_pop();
    width = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawrect(obj, x, y, width, height);
}
#endif
