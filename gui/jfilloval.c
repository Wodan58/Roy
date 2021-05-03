/*
    module  : jfilloval.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JFILLOVAL_C
#define JFILLOVAL_C

/**
jfilloval  :  obj x y rx ry  ->
Draws a filled oval with the center (x, y) and the horizontal radius rx and the
vertical radius ry.
*/
void do_jfilloval(void)
{
    int obj, x, y, rx, ry;

    COMPILE;
    ry = do_pop();
    rx = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_filloval(obj, x, y, rx, ry);
}
#endif
