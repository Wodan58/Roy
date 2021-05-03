/*
    module  : jdrawpixel.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWPIXEL_C
#define JDRAWPIXEL_C

/**
jdrawpixel  :  obj x y  ->
Draws a pixel at (x, y).
*/
void do_jdrawpixel(void)
{
    int obj, x, y;

    COMPILE;
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawpixel(obj, x, y);
}
#endif
