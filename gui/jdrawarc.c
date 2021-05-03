/*
    module  : jdrawarc.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef JDRAWARC_C
#define JDRAWARC_C

/**
jdrawarc  :  obj x y rx ry arc1 arc2  ->
Draws an unfilled arc from angle arc1 to angle arc2 with the center (x, y) and
the horizontal radius rx and the vertical radius ry.
*/
void do_jdrawarc(void)
{
    int obj, x, y, rx, ry, arc1, arc2;

    COMPILE;
    arc2 = do_pop();
    arc1 = do_pop();
    ry = do_pop();
    rx = do_pop();
    y = do_pop();
    x = do_pop();
    obj = do_pop();
    j_drawarc(obj, x, y, rx, ry, arc1, arc2);
}
#endif
