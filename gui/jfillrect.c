/*
    module  : jfillrect.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILLRECT_C
#define JFILLRECT_C

/**
jfillrect  :  obj x y width height  ->
Draws a filled rectangle from (x, y) of size width x height.
*/
void do_jfillrect(void)
{
    int obj, x, y, width, height;

    COMPILE;
    height = do_pop();
    width = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_fillrect(obj, x, y, width, height);
}
#endif
