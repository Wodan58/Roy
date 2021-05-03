/*
    module  : jdrawoval.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWOVAL_C
#define JDRAWOVAL_C

/**
jdrawoval  :  obj x y rx ry  ->
Draws an unfilled oval with the center (x, y) and the horizontal radius rx and
the vertical radius ry.
*/
void do_jdrawoval(void)
{
    int obj, x, y, rx, ry;

    COMPILE;
    ry = do_pop();
    rx = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawoval(obj, x, y, rx, ry);
}
#endif
